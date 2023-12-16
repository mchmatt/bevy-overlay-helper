#ifdef __APPLE__

#include <stdio.h>
#include <include/cef_app.h>
#include <include/wrapper/cef_library_loader.h>

// This define is automatically set by the CMake files unless told otherwise
// In our case though, we should never need it to be off.
#if defined(CEF_USE_SANDBOX)
#include <include/cef_sandbox_mac.h>
#endif
#include "render_process_handler.h"
#include "app.h"

int main(int argc, char* argv[]) {
    printf("Starting helper process\n");
    // Initialize the macOS sandbox context as required by Chromium V2 sandbox
    #if defined(CEF_USE_SANDBOX)
    CefScopedSandboxContext sandbox_context;
    if (!sandbox_context.Initialize(argc, argv)) {
        return 1;
    }
    #endif

    // Load in the dynamic library. We have to load it here instead
    // of just linking, due to a requirement in the V2 sandbox
    // implementation.
    CefScopedLibraryLoader library_loader;
    if (!library_loader.LoadInHelper()) {
        return 1;
    }

    CefRefPtr<OverlayRenderProcessHandler> renderProcessHandler = new OverlayRenderProcessHandler();
    CefRefPtr<OverlayApp> app = new OverlayApp(renderProcessHandler);

    CefMainArgs main_args(argc, argv);
    return CefExecuteProcess(main_args, app, nullptr);
}
#endif
