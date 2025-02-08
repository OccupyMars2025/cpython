#include <iostream>
#include <cwchar> // For wide character functions

int main() {
    wchar_t wc = L'A'; // Wide character literal
    wchar_t wstr[] = L"Hello, World!"; // Wide string literal

    std::wcout << wc << L'\n'; // Output wide character
    std::wcout << wstr << L'\n'; // Output wide string

    // Using wide string functions
    size_t len = wcslen(wstr); // Get length of wide string
    std::wcout << L"Length: " << len << L'\n';

    return 0;
}
