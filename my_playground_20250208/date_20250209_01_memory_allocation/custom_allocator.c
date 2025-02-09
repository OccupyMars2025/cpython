#include <Python.h>
#include <stdio.h>

// Custom context to track allocations
typedef struct {
    size_t total_allocated;
} AllocatorContext;

// Custom malloc
void* custom_malloc(void *ctx, size_t size) {
    AllocatorContext *context = (AllocatorContext *)ctx;
    context->total_allocated += size;
    // Always use %zu when printing values of type size_t to ensure correctness and portability.
    printf("Allocating %zu bytes (Total: %zu)\n", size, context->total_allocated);
    return malloc(size);
}

// Custom calloc
void* custom_calloc(void *ctx, size_t nelem, size_t elsize) {
    AllocatorContext *context = (AllocatorContext *)ctx;
    size_t total_size = nelem * elsize;
    context->total_allocated += total_size;
    printf("Allocating %zu bytes (Total: %zu)\n", total_size, context->total_allocated);
    return calloc(nelem, elsize);
}

// Custom realloc
void* custom_realloc(void *ctx, void *ptr, size_t new_size) {
    // Note: This is a simplified version; real realloc tracking is more complex
    printf("Reallocating to %zu bytes\n", new_size);
    return realloc(ptr, new_size);
}

// Custom free
void custom_free(void *ctx, void *ptr) {
    printf("Freeing memory\n");
    free(ptr);
}


void setup_custom_allocator() {
    // Initialize the context
    AllocatorContext context = {0};

    // Create the allocator structure
    PyMemAllocatorEx allocator = {
        .ctx = &context,
        .malloc = custom_malloc,
        .calloc = custom_calloc,
        .realloc = custom_realloc,
        .free = custom_free
    };

    // Set the allocator for Python’s raw memory domain
    PyMem_SetAllocator(PYMEM_DOMAIN_RAW, &allocator);
}



static PyModuleDef custom_module = {
    PyModuleDef_HEAD_INIT,
    "custom_allocator",
    "Module with custom memory allocator",
    -1,
    NULL
};

PyMODINIT_FUNC PyInit_custom_allocator(void) {
    setup_custom_allocator();
    return PyModule_Create(&custom_module);
}
