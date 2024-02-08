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

    void* sandbox_info = nullptr;

    #if defined(CEF_USE_SANDBOX)
    // Manage the life span of the sandbox information object. This is necessary
    // for sandbox support on Windows. See cef_sandbox_win.h for complete details.
    CefScopedSandboxInfo scoped_sandbox;
    sandbox_info = scoped_sandbox.sandbox_info();
    #endif

    CefRefPtr<OverlayRenderProcessHandler> renderProcessHandler = new OverlayRenderProcessHandler();
    CefRefPtr<OverlayApp> app = new OverlayApp(renderProcessHandler);

    CefMainArgs mainArgs(hInstance);
    return CefExecuteProcess(mainArgs, app, sandbox_info);
}
#endif
