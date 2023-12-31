#include "send_ipc_message_handler.h"

SendIPCMessageHandler::SendIPCMessageHandler() {}

bool SendIPCMessageHandler::Execute(
  const CefString& name,
  CefRefPtr<CefV8Value> object,
  const CefV8ValueList& arguments,
  CefRefPtr<CefV8Value>& retval,
  CefString& exception
) {
  if (arguments.size() < 2)
    return true;

  CefRefPtr<CefV8Context> context = CefV8Context::GetCurrentContext();
  if (!context)
    return true;

  CefRefPtr<CefFrame> frame = context->GetFrame();
  if (!frame)
    return true;

  CefRefPtr<CefProcessMessage> processMessage = CefProcessMessage::Create("CEFOverlayMessage");
  if (!processMessage)
    return true;

  CefRefPtr<CefListValue> argumentsList = processMessage->GetArgumentList();
if (!argumentsList)
    return true;

  CefRefPtr<CefV8Value> firstArgument = arguments.at(0); // first argument should be message type
  if (!firstArgument || !firstArgument->IsString())
    return true;

  CefRefPtr<CefV8Value> secondArgument = arguments.at(1); // second argument should be data (stringified JSON for now)
  if (!secondArgument || !secondArgument->IsString())
    return true;
  
  argumentsList->SetSize(2);
  argumentsList->SetString(0, arguments.at(0)->GetStringValue());
  argumentsList->SetString(1, arguments.at(1)->GetStringValue());

  frame->SendProcessMessage(CefProcessId::PID_BROWSER, processMessage);
  return true;
}
