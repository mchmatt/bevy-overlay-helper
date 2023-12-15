#ifndef OVERLAY_HELPER_APP_H_
#define OVERLAY_HELPER_APP_H_

#include "include/cef_app.h"

class OverlayApp : public CefApp {
  private:
    CefRefPtr<CefRenderProcessHandler> _render_process_handler;

  public:
    OverlayApp(CefRefPtr<CefRenderProcessHandler> pRenderProcessHandler);

    CefRefPtr<CefRenderProcessHandler> OverlayApp::GetRenderProcessHandler() override {
      return _render_process_handler;
    }

  private:
    IMPLEMENT_REFCOUNTING(OverlayApp);
};

#endif //OVERLAY_HELPER_APP_H_