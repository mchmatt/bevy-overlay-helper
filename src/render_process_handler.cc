#include "render_process_handler.h"
#include "send_ipc_message_handler.h"

const char kCEFOverlayMessage[] = "CEFOverlayMessage";
const char kMessageProcessor[] = "_processOverlayMessage";

OverlayRenderProcessHandler::OverlayRenderProcessHandler() {}

void OverlayRenderProcessHandler::OnContextCreated(
  CefRefPtr<CefBrowser> browser,
  CefRefPtr<CefFrame> frame,
  CefRefPtr<CefV8Context> context
) {
  CefRefPtr<CefV8Value> global = context->GetGlobal();
  if (!global)
    return;

  CefRefPtr<CefV8Handler> sendIPCMessageHandler = new SendIPCMessageHandler();
  CefRefPtr<CefV8Value> sendIPCMessageFunction = CefV8Value::CreateFunction("_sendIPCMessage", sendIPCMessageHandler);
  if (!sendIPCMessageFunction)
    return;

  global->SetValue("_sendIPCMessage", sendIPCMessageFunction, V8_PROPERTY_ATTRIBUTE_READONLY);
}

bool OverlayRenderProcessHandler::OnProcessMessageReceived(
  CefRefPtr<CefBrowser> browser,
  CefRefPtr<CefFrame> frame,
  CefProcessId source_process,
  CefRefPtr<CefProcessMessage> message
) {
  // only handle messages coming from the overlay plugin
  if (message->GetName() != kCEFOverlayMessage)
    return false;
  
  CefRefPtr<CefListValue> inputArguments = message->GetArgumentList();
  if (
    inputArguments->GetSize() != 2 || // we expect exactly two parameters
    inputArguments->GetType(0) != CefValueType::VTYPE_STRING || // handler should be a string
    inputArguments->GetType(1) != CefValueType::VTYPE_STRING // data should be a string
  )
    return false;

  CefRefPtr<CefV8Context> context = frame->GetV8Context();
  if (!context)
    return false;
  
  context->Enter();
  
  CefRefPtr<CefV8Value> global = context->GetGlobal();
  if(!global) {
    context->Exit();
    return false;
  }

  if (!global->HasValue(kMessageProcessor)) {
    context->Exit();
    return false;
  }

  CefRefPtr<CefV8Value> processor = global->GetValue(kMessageProcessor);
  if (!processor || !processor->IsFunction()) {
    context->Exit();
    return false;
  }
  
  CefV8ValueList argumentsList;
  argumentsList.push_back(CefV8Value::CreateString(inputArguments->GetString(0)));
  argumentsList.push_back(CefV8Value::CreateString(inputArguments->GetString(1)));

  processor->ExecuteFunction(nullptr, argumentsList);
  context->Exit();
  return true;
}
