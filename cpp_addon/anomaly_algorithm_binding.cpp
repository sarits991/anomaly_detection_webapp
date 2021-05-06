#include <napi.h>
using namespace Napi;

  Napi::String Method(const Napi::CallbackInfo& info) {
     Napi::Env env = info.Env();
     return Napi::String::New(env, "world");
  }

  Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set("hello",
                Napi::Function::New(env, Method));
    return exports;
  }

   NODE_API_MODULE(anomaly_detection_addon, Init);
