#ifndef MEMORY_DEBUG_H
#define MEMORY_DEBUG_H

// Memory Debugging Utilities
static int alloc_count = 0;
static int free_count = 0;
// Debug versions of malloc and free
static inline void* dbg_malloc(size_t size, const char* func, int line) {
    void* pObj = NULL;

    pObj = malloc(size);
    if (pObj == NULL) {
        fprintf(stderr, "[ERROR] %s:%d -> malloc failed for %zu bytes\n", func, line, size);
        return pObj;
    }
    alloc_count++;
    printf("[ALLOC] %s:%d -> %p (%zu bytes)\n", func, line, pObj, size);

    return pObj;
}
static inline void dbg_free(void* pObj, const char* func, int line) {
    if (pObj == NULL) {
        return;
    }
    free_count++;
    printf("[FREE ] %s:%d -> %p\n", func, line, pObj);
    free(pObj);
}
static inline void dbg_report(void) {
    printf("\n=== Memory Debug Report ===\n");
    printf("Total allocs: %d\n", alloc_count);
    printf("Total frees : %d\n", free_count);
    if (alloc_count > free_count) {
        printf("⚠ Memory leak detected: %d blocks not freed\n", alloc_count - free_count);
    } else if (alloc_count < free_count) {
        printf("⚠ More frees than allocs (double free?)\n");
    } else {
        printf("✅ All memory freed correctly\n");
    }
    printf("===========================\n");
}

// Macros to replace malloc and free with debug versions
#define MALLOC(size) dbg_malloc(size, __func__, __LINE__)
#define FREE(ptr) dbg_free(ptr, __func__, __LINE__)
#define ENABLE_MEMORY_REPORT() atexit(dbg_report)

#endif  // MEMORY_DEBUG_H
