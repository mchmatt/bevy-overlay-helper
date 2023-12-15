#include "app.h"

OverlayApp::OverlayApp(CefRefPtr<CefRenderProcessHandler> pRenderProcessHandler) {
  this->_render_process_handler = pRenderProcessHandler;
}
