/*
clang -o study_wchar_2 study_wchar_2.c -Wall -Wextra
*/

#include <stdio.h>
#include <wchar.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "");
    // fwprintf(stdout, L"Wide character: %lc\n", L'€');

    wchar_t option = L'€'; // Euro symbol (Unicode U+20AC)
    fprintf(stderr, "Option: -%lc\n", option);
    return 0;
}

// #include <stdio.h>
// #include <wchar.h>

// int main() {
//     wchar_t option = L'€'; // Euro symbol (Unicode U+20AC)

//     // Incorrect: Casting to char truncates the wide character
//     fprintf(stderr, "Option (incorrect): -%c\n", (char)option);

//     // Correct: Using %lc to print the wide character
//     fprintf(stderr, "Option (correct): -%lc\n", option);

//     return 0;
// }



// #include <stdio.h>
// #include <wchar.h>
// #include <locale.h>

// int main() {
//     const char *locale = setlocale(LC_ALL, "");
//     if (locale == NULL) {
//         fprintf(stderr, "Failed to set locale.\n");
//     } else {
//         fprintf(stderr, "Locale set to: %s\n", locale);
//     }

//     wchar_t option = L'€'; // Euro symbol (Unicode U+20AC)

//     // Incorrect: Casting to char truncates the wide character
//     fprintf(stderr, "Option (incorrect): -%c\n", (char)option);

//     if (fwide(stderr, 1) <= 0) {
//         fprintf(stderr, "stderr is not in wide mode.\n");
//     }
//     // Correct: Using %lc to print the wide character
//     fwprintf(stdout, L"fwprintf(stdout): Option (correct): -%lc\n", option);
//     fwprintf(stderr, L"fwprintf(stderr): Option (correct): -%lc\n", option);
//     fprintf(stderr, "fprintf: Option (correct): -%lc\n", option);
//     fprintf(stderr, "fprintf: Option (correct): -%lc\n", option);
//     fprintf(stderr, "fprintf: Option (correct): -%lc\n", option);
//     fprintf(stderr, "fprintf: Option (correct): -%lc\n", option);

//     return 0;
// }
