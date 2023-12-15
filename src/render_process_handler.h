#ifndef OVERLAY_HELPER_RENDER_PROCESS_HANDLER_H_
#define OVERLAY_HELPER_RENDER_PROCESS_HANDLER_H_

#include "include/cef_app.h"

class OverlayRenderProcessHandler : public CefRenderProcessHandler {
  public:
    OverlayRenderProcessHandler();

  void OnContextCreated(
    CefRefPtr<CefBrowser> browser,
    CefRefPtr<CefFrame> frame,
    CefRefPtr<CefV8Context> context
  ) override;

  private:
    IMPLEMENT_REFCOUNTING(OverlayRenderProcessHandler);
};

#endif //OVERLAY_HELPER_RENDER_PROCESS_HANDLER_H_
