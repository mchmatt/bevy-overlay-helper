#include "app.h"
#include "render_process_handler.h"

int main(int argc, char* argv[]) {
    CefRefPtr<OverlayRenderProcessHandler> renderProcessHandler = new OverlayRenderProcessHandler();
    CefRefPtr<OverlayApp> app = new OverlayApp(renderProcessHandler);

    CefMainArgs main_args(argc, argv);
    return CefExecuteProcess(main_args, app, nullptr);
}