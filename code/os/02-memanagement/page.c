#include "os.h"

extern uint32_t TEXT_START;
extern uint32_t TEXT_END;
extern uint32_t DATA_START;
extern uint32_t DATA_END;
extern uint32_t RODATA_START;
extern uint32_t RODATA_END;
extern uint32_t BSS_START;
extern uint32_t BSS_END;
extern uint32_t HEAP_START;
extern uint32_t HEAP_SIZE;

static uint32_t _alloc_start = 0;
static uint32_t _alloc_end = 0;
static uint32_t _num_pages = 0;

#define PAGE_SIZE 4096
#define PAGE_ORDER 12

#define PAGE_TAKEN (uint8_t)(1 << 0)
#define PAGE_LAST (uint8_t)(1 << 1)

struct Page
{
    uint8_t flags;
};

static inline void _clear(struct Page *page)
{
    page->flags = 0;
}

static inline int _is_free(struct Page *page)
{
    return (page->flags & PAGE_TAKEN) ? 0 : 1;
}

static inline void _set_flag(struct Page *page, uint8_t flags)
{
    page->flags |= flags;
}

static inline int _is_last(struct Page *page)
{
    return (page->flags & PAGE_LAST) ? 1 : 0;
}

static inline uint32_t _align_page(uint32_t address)
{
    uint32_t order = (1 << PAGE_ORDER) - 1;
    return (address + order) & (~order);
}

void page_init(void)
{
    /* 拿8个page作为内部管理用, 不开放给用户 */
    _num_pages = (HEAP_SIZE / PAGE_SIZE) - 8;
    printf("HEAP_START = %x, HEAP_SIZE = %x, num of pages = %d\n",
           HEAP_START, HEAP_SIZE, _num_pages);

    struct Page *page = (struct Page *)HEAP_START;
    for (int i = 0; i < _num_pages; i++)
    {
        _clear(page);
        page++;
    }

    /* 由于分了8个page内部使用, 所以实际使用的page从这里开始 */
    /* 这里做了一个4k字节对齐, 存取效率更高 */
    _alloc_start = _align_page(HEAP_START + 8 * PAGE_SIZE);
    _alloc_end = _alloc_start + (PAGE_SIZE * _num_pages);

    printf("TEXT:   0x%x -> 0x%x\n", TEXT_START, TEXT_END);
    printf("RODATA: 0x%x -> 0x%x\n", RODATA_START, RODATA_END);
    printf("DATA:   0x%x -> 0x%x\n", DATA_START, DATA_END);
    printf("BSS:    0x%x -> 0x%x\n", BSS_START, BSS_END);
    printf("HEAP:   0x%x -> 0x%x\n", _alloc_start, _alloc_end);
}

void *page_alloc(int npages)
{
    int found = 0;
    struct Page *page_i = (struct Page *)HEAP_START;

    /* 为什么要减去npages, 因为要在这_num_pages里边挑出等于npages的内存块 */
    for (int i = 0; i <= (_num_pages - npages); i++)
    {
        /* 发现一个未使用的page, 就去查看后边n个是否也未使用 */
        if (_is_free(page_i))
        {
            found = 1;

            struct Page *page_j = page_i;
            for (int j = i; j < (i + npages); j++)
            {
                if (!_is_free(page_j))
                {
                    found = 0;
                    break;
                }
                page_j++;
            }

            /* 如果能找到npages的内存块，就设置标志位 */
            if (found)
            {
                struct Page *page_k = page_i;
                for (int k = i; k < (i + npages); k++)
                {
                    _set_flag(page_k, PAGE_TAKEN);
                    page_k++;
                }
                /* 减一个page的作用是回到最后一个内存块 */
                /* 因为k < (i + npages)这个条件会循环到 i + nages */
                page_k--;
                _set_flag(page_k, PAGE_LAST);
                /* 返回一个地址 */
                return (void *)(_alloc_start + i * PAGE_SIZE);
            }
        }
        page_i++;
    }
    /* 没有npages大小的内存块 */
    return NULL;
}

void page_free(void *p)
{
    /* p为NULL, 或者p的地址大于heap_end了就返回 */
    if (!p || (uint32_t)p >= _alloc_end)
    {
        return;
    }

    /* 计算要释放内存块的起始地址对应的page索引 */
    struct Page *page = (struct Page *)HEAP_START;
    page += ((uint32_t)p - _alloc_start) / PAGE_SIZE;

    while (!_is_free(page))
    {
        if (_is_last(page))
        {
            _clear(page);
            break;
        }
        else
        {
            _clear(page);
            page++;
        }
    }
}

void page_test()
{
    void *p = page_alloc(2);
    printf("p = 0x%x\n", p);

    void *p2 = page_alloc(7);
    printf("p2 = 0x%x\n", p2);

    void *p3 = page_alloc(4);
    printf("p3 = 0x%x\n", p3);
}