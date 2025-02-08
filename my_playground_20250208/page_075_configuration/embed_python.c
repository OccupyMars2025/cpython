/*
page 76: study PyPreConfig

gcc -o embed_python embed_python.c $(python3-config --cflags --ldflags --embed)
 */

#include <Python.h>



int main(int argc, char **argv) {
    PyStatus status;
    PyPreConfig preconfig;

    // Initialize PyPreConfig
    PyPreConfig_InitPythonConfig(&preconfig);

    // Set some pre-configuration options
    preconfig.utf8_mode = 1;  // Enable UTF-8 mode
    preconfig.coerce_c_locale = 0;  // Disable locale coercion


    // Preinitialize Python
    status = Py_PreInitialize(&preconfig);
    if (PyStatus_Exception(status)) {
        Py_ExitStatusException(status);
        return 1;
    }

    // Initialize Python
    Py_Initialize();

    // Your Python code here
    PyRun_SimpleString("print('Hello from embedded Python!')");

    // Finalize Python
    Py_Finalize();

    return 0;
}
