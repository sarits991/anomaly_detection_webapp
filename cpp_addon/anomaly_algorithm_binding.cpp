#include <napi.h>
#include "timeseries.h"
#include "SimpleAnomalyDetector.h"
#include "HybridAnomalyDetector.h"
#include <vector>
#include <string.h>
#include "AsyncAnomalyAlgorithm.h"

using namespace Napi;
using namespace std;

Number RunAsyncAnomaly(const Napi::CallbackInfo& info) {
    Env env = info.Env();
    String train_file_path = info[0].As<Napi::String>();
    String csv_file_path = info[1].As<Napi::String>();
    String model_type = info[2].As<Napi::String>();
    Function callback = info[3].As<Function>();

    string type(model_type.Utf8Value().c_str());
    string train_file(train_file_path.Utf8Value().c_str());
    string csv_file(csv_file_path.Utf8Value().c_str());
    AsyncAnomalyAlgorithm* anomalyAlg = new AsyncAnomalyAlgorithm(callback, type,
           train_file, csv_file);
    anomalyAlg->Queue();
     return Napi::Number::New(env,1);
}

Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set("anomaly_detection", Napi::Function::New(env, RunAsyncAnomaly));
    return exports;
}

NODE_API_MODULE(anomaly_detection_addon, Init);
