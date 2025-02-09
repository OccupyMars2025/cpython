/*---------------------------------------------------------------------------*
 * <RCS keywords>
 *
 * C++ Library
 *
 * Copyright 1992-1994, David Gottner
 *
 *                    All Rights Reserved
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose and without fee is hereby granted,
 * provided that the above copyright notice, this permission notice and
 * the following disclaimer notice appear unmodified in all copies.
 *
 * I DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING ALL
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS.  IN NO EVENT SHALL I
 * BE LIABLE FOR ANY SPECIAL, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY
 * DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA, OR PROFITS, WHETHER
 * IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT
 * OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *---------------------------------------------------------------------------*/

/* Modified to support --help and --version, as well as /? on Windows
 * by Georg Brandl. */

#include <Python.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include "pycore_getopt.h"

int _PyOS_opterr = 1;                 /* generate error messages */
Py_ssize_t _PyOS_optind = 1;          /* index into argv array   */
const wchar_t *_PyOS_optarg = NULL;   /* optional argument, e.g., in "-m module", _PyOS_optarg points to "module"      */


/* Pointer to the current option character in the current argument,
e.g. if argv[_PyOS_optind] is "-ab", opt_ptr can point to "b". */
static const wchar_t *opt_ptr = L"";

/* Python command line short and long options */

/* options that require arguments (marked with : in SHORT_OPTS).
    use "./python -h" to see the list of options
*/
#define SHORT_OPTS L"bBc:dEhiIJm:OPqRsStuvVW:xX:?"

static const _PyOS_LongOption longopts[] = {
    /* name, has_arg, val (used in switch in initconfig.c) */
    {L"check-hash-based-pycs", 1, 0},
    {L"help-all", 0, 1},
    {L"help-env", 0, 2},
    {L"help-xoptions", 0, 3},
    {NULL, 0, -1},                     /* sentinel */
};


void _PyOS_ResetGetOpt(void)
{
    _PyOS_opterr = 1;
    _PyOS_optind = 1;
    _PyOS_optarg = NULL;
    opt_ptr = L"";
}


/*
Main Function: _PyOS_GetOpt
This is the core function that parses command-line options. It takes:
argc: Number of command-line arguments.
argv: Array of wide-character strings containing the arguments.
longindex: Pointer to store the index of matched long options.
*/
int _PyOS_GetOpt(Py_ssize_t argc, wchar_t * const *argv, int *longindex)
{
    wchar_t *ptr;
    wchar_t option;

    if (*opt_ptr == L'\0') {

        if (_PyOS_optind >= argc)
            return -1;
#ifdef MS_WINDOWS
        else if (wcscmp(argv[_PyOS_optind], L"/?") == 0) {
            ++_PyOS_optind;
            return 'h';
        }
#endif

        else if (argv[_PyOS_optind][0] != L'-' ||
                 argv[_PyOS_optind][1] == L'\0' /* lone dash */ )
            return -1;

        else if (wcscmp(argv[_PyOS_optind], L"--") == 0) {
            ++_PyOS_optind;
            return -1;
        }

        else if (wcscmp(argv[_PyOS_optind], L"--help") == 0) {
            ++_PyOS_optind;
            return 'h';
        }

        else if (wcscmp(argv[_PyOS_optind], L"--version") == 0) {
            ++_PyOS_optind;
            return 'V';
        }

        opt_ptr = &argv[_PyOS_optind++][1];
    }

    if ((option = *opt_ptr++) == L'\0')
        return -1;

    if (option == L'-') {
        // Parse long option.
        // just "--"
        if (*opt_ptr == L'\0') {
            if (_PyOS_opterr) {
                fprintf(stderr, "Expected long option\n");
            }
            return -1;
        }
        *longindex = 0;
        const _PyOS_LongOption *opt;
        for (opt = &longopts[*longindex]; opt->name; opt = &longopts[++(*longindex)]) {
            if (!wcscmp(opt->name, opt_ptr))
                break;
        }
        if (!opt->name) {
            if (_PyOS_opterr) {
                fprintf(stderr, "Unknown option: %ls\n", argv[_PyOS_optind - 1]);
            }
            return '_';
        }
        opt_ptr = L"";
        if (!opt->has_arg) {
            return opt->val;
        }
        // If the option requires an argument but none is available
        if (_PyOS_optind >= argc) {
            if (_PyOS_opterr) {
                fprintf(stderr, "Argument expected for the %ls options\n",
                        argv[_PyOS_optind - 1]);
            }
            return '_';
        }
        _PyOS_optarg = argv[_PyOS_optind++];
        return opt->val;
    }

    if (option == 'J') {
        if (_PyOS_opterr) {
            fprintf(stderr, "-J is reserved for Jython\n");
        }
        return '_';
    }

    if ((ptr = wcschr(SHORT_OPTS, option)) == NULL) {
        if (_PyOS_opterr) {
            fprintf(stderr, "Unknown option: -%c\n", (char)option);
        }
        return '_';
    }

    if (*(ptr + 1) == L':') {
        /*
        If the argument is attached (e.g., -ofile), stores it and resets opt_ptr.
        _PyOS_optarg will point to "file".
        */
        if (*opt_ptr != L'\0') {
            _PyOS_optarg  = opt_ptr;
            opt_ptr = L"";
        }
        // If the argument is separate, checks if it exists, stores it, and increments _PyOS_optind.
        else {
            if (_PyOS_optind >= argc) {
                if (_PyOS_opterr) {
                    fprintf(stderr,
                        "Argument expected for the -%c option\n", (char)option);
                }
                return '_';
            }

            _PyOS_optarg = argv[_PyOS_optind++];
        }
    }

    return option;
}
