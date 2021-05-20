#include <napi.h>
#include "timeseries.h"
#include "SimpleAnomalyDetector.h"
#include "HybridAnomalyDetector.h"
#include <vector>
#include <string.h>
#include <iostream>
#include "AsyncAnomalyAlgorithm.h"

using namespace Napi;
using namespace std;

AsyncAnomalyAlgorithm::AsyncAnomalyAlgorithm(Function& callback, string modelType,string trainPath, string csvPath)
    : AsyncWorker(callback), modelType(modelType), trainPath(trainPath),csvPath(csvPath)
    {};

void AsyncAnomalyAlgorithm::Execute() {
     printf("file name async : %s\n",trainPath.c_str());
     printf("file name async : %s\n",csvPath.c_str());
     TimeSeries ts_train(trainPath.c_str());
     TimeSeries ts_csv(csvPath.c_str());
     printf("%s %d\n","ts_train size: ", (int)ts_train.getHeaderLine().size());
     printf("%s %d\n","ts_csv size: ", (int)ts_csv.getHeaderLine().size());

     if(modelType.compare("regression")==0){
            SimpleAnomalyDetector anomaly;
            anomaly.learnNormal(ts_train);
            printf("finish learn normal\n");
            anomalies = anomaly.detect(ts_csv);
            printf("finish detecet\n");
     }
     if(modelType.compare("hybrid")==0){
        HybridAnomalyDetector anomaly;
        anomaly.learnNormal(ts_train);
        anomalies = anomaly.detect(ts_csv);
     }

//     for(int i=0; i<anomalies.size();i++){
//        printf("%s ",anomalies[i].description.c_str());
//        printf("%lu \n",anomalies[i].timeStep);
//     }
//      printf("%d",(int)anomalies.size());

     //outputArray = Napi::Array::New(anomalies.size());
};

void AsyncAnomalyAlgorithm::OnOK() {
     Napi::Array outputArray = Napi::Array::New(Env(), anomalies.size());
      for (int i = 0; i < anomalies.size(); i++) {
             string des = anomalies[i].description + ":" + to_string(anomalies[i].timeStep);
             outputArray[i] = Napi::String::New(Env(), des);
      }
      Callback().Call({Env().Null(), outputArray});
};