#include <napi.h>
#include <string>
#include <vector>
#include "SimpleAnomalyDetector.h"
#include "AnomalyDetector.h"

using namespace std;
using namespace Napi;

class AsyncAnomalyAlgorithm : public AsyncWorker {
 public:
  AsyncAnomalyAlgorithm(Function& callback, string modelType, string trainPath, string csvPath);
  virtual ~AsyncAnomalyAlgorithm(){};

  void Execute();
  void OnOK();

 private:
  string modelType;
  string trainPath;
  string csvPath;
  vector<AnomalyReport> anomalies;
};