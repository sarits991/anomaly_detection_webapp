#include <napi.h>
#include "timeseries.h"
#include "SimpleAnomalyDetector.h"
#include "HybridAnomalyDetector.h"
#include <vector>
#include <string.h>
#include "AsyncAnomalyAlgorithm.h"

using namespace Napi;
using namespace std;

AsyncAnomalyAlgorithm::AsyncAnomalyAlgorithm(Function& callback, string modelType,string trainPath, string csvPath)
    : AsyncWorker(callback), modelType(modelType), trainPath(trainPath),csvPath(csvPath)
    {};

void AsyncAnomalyAlgorithm::Execute() {
     TimeSeries ts_train(trainPath.c_str());
     TimeSeries ts_csv(csvPath.c_str());

     if(modelType.compare("regression")==0){
            SimpleAnomalyDetector anomaly;
            anomaly.learnNormal(ts_train);
            anomalies = anomaly.detect(ts_csv);
     }
     if(modelType.compare("hybrid")==0){
        HybridAnomalyDetector anomaly;
        anomaly.learnNormal(ts_train);
        anomalies = anomaly.detect(ts_csv);
     }
};

void AsyncAnomalyAlgorithm::OnOK() {
     Napi::Array outputArray = Napi::Array::New(Env(), anomalies.size());
      for (int i = 0; i < anomalies.size(); i++) {
             string des = anomalies[i].description + ":" + to_string(anomalies[i].timeStep);
             outputArray[i] = Napi::String::New(Env(), des);
      }
      Callback().Call({Env().Null(), outputArray});
};