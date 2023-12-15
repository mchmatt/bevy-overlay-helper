#include "render_process_handler.h"
#include "send_ipc_message_handler.h"

OverlayRenderProcessHandler::OverlayRenderProcessHandler() {}

void OverlayRenderProcessHandler::OnContextCreated(
  CefRefPtr<CefBrowser> browser,
  CefRefPtr<CefFrame> frame,
  CefRefPtr<CefV8Context> context
) {
  CefRefPtr<CefV8Value> global = context->GetGlobal();
  if (!global)
    throw new std::runtime_error("Could not get global in OverlayRenderProcessHandler");

  CefRefPtr<CefV8Handler> sendIPCMessageHandler = new SendIPCMessageHandler();
  CefRefPtr<CefV8Value> sendIPCMessageFunction = CefV8Value::CreateFunction("_sendIPCMessage", sendIPCMessageHandler);
  if (!sendIPCMessageFunction)
    throw new std::runtime_error("Could not create function in OverlayRenderProcessHandler");

  global->SetValue("_sendIPCMessage", sendIPCMessageFunction, V8_PROPERTY_ATTRIBUTE_READONLY);
}