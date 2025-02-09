#include <wchar.h>
#include <stdio.h>

int main() {
    wchar_t a = L'A';
    wchar_t b = L'B';

    // An array of pointers to wchar_t
    wchar_t *arr[2] = { &a, &b };

    // A pointer to a constant pointer to wchar_t
    wchar_t * const *argv = arr;

    // Accessing and modifying the wchar_t values
    wprintf(L"Before: %lc %lc\n", *argv[0], *argv[1]);
    *argv[0] = L'C'; // Allowed: Modifying the wchar_t value
    wprintf(L"After: %lc %lc\n", *argv[0], *argv[1]);

    // Attempting to modify the constant pointer
    argv[0] = &b; // ERROR: Cannot modify a const pointer

    return 0;
}
