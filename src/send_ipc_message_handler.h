#ifndef OVERLAY_HELPER_RENDER_SEND_IPC_MESSAGE_HANDLER_H_
#define OVERLAY_HELPER_RENDER_SEND_IPC_MESSAGE_HANDLER_H_

#include "include/cef_v8.h"

class SendIPCMessageHandler : public CefV8Handler {
  public:
    SendIPCMessageHandler();

    bool Execute(
      const CefString& name,
      CefRefPtr<CefV8Value> object,
      const CefV8ValueList& arguments,
      CefRefPtr<CefV8Value>& retval,
      CefString& exception
    ) override;
  private:
    IMPLEMENT_REFCOUNTING(SendIPCMessageHandler);
};
#endif //OVERLAY_HELPER_RENDER_SEND_IPC_MESSAGE_HANDLER_H_