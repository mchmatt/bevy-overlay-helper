#include <windows.h>
#include <stdio.h>
#include <include/cef_app.h>

int APIENTRY wWinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPTSTR lpCmdLine,
    int nCmdShow
) {
    printf("Starting helper process\n");

    CefMainArgs main_args(hInstance);
    return CefExecuteProcess(main_args, nullptr, nullptr);
}