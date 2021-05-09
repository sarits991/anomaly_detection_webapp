{
  "targets": [
    {
      "target_name": "anomaly_detection_addon",
      "sources": [ "cpp_addon/anomaly_algorithm_binding.cpp", "cpp_addon/timeseries.h", "cpp_addon/timeseries.cpp",
       "cpp_addon/anomaly_detection_util.cpp", "cpp_addon/anomaly_detection_util.h","cpp_addon/AnomalyDetector.h",
       "cpp_addon/SimpleAnomalyDetector.cpp", "cpp_addon/SimpleAnomalyDetector.h", "cpp_addon/minCircle.h",
       "cpp_addon/minCircle.cpp", "cpp_addon/HybridAnomalyDetector.cpp", "cpp_addon/HybridAnomalyDetector.h",
       "cpp_addon/AsyncAnomalyAlgorithm.h", "cpp_addon/AsyncAnomalyAlgorithm.cpp"],
      "include_dirs": [
              "<!@(node -p \"require('node-addon-api').include\")"
      ],
       "defines": [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
    }
  ]
}


