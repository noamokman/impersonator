#include <node.h>
#include <iostream>
#include "Impersonation.h"

using namespace v8;
using namespace std;

Impersonation impersonation;

std::string FlattenArgString(v8::Local<v8::Value> v8arg) {
  if(!v8arg->IsString()) {
   return "";
  }

  v8::String::Utf8Value utf8str(v8arg->ToString());
  return string(*utf8str, utf8str.length());
}

void Logon(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  if (args.Length() < 2) {
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, "Wrong number of arguments"));
    return;
  }

  if((args.Length() >= 2 && !args[0]->IsString() && !args[1]->IsString()) || (args.Length() > 2 && !args[2]->IsString())) {
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, "Arguments must be string"));
    return;
  }

  string error = impersonation.Logon(FlattenArgString(args[0]), FlattenArgString(args[1]), FlattenArgString(args[2]));
  args.GetReturnValue().Set(String::NewFromUtf8(isolate, error.c_str()));
}

void Logoff(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  string error = impersonation.Logoff();
  args.GetReturnValue().Set(String::NewFromUtf8(isolate, error.c_str()));
}

void init(Handle<Object> exports) {
  NODE_SET_METHOD(exports, "logon", Logon);
  NODE_SET_METHOD(exports, "logoff", Logoff);
}

NODE_MODULE(impersonator, init);