#ifdef _WIN32
#include <windows.h>
#include <stdio.h>
#include <include/cef_app.h>

#include "app.h"
#include "render_process_handler.h"

int APIENTRY wWinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPTSTR lpCmdLine,
    int nCmdShow
) {
    printf("Starting helper process\n");

    CefRefPtr<OverlayRenderProcessHandler> renderProcessHandler = new OverlayRenderProcessHandler();
    CefRefPtr<OverlayApp> app = new OverlayApp(renderProcessHandler);

    CefMainArgs mainArgs(hInstance);
    return CefExecuteProcess(mainArgs, app, nullptr);
}
#endif
