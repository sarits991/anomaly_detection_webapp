{
  "targets": [
    {
      "target_name": "anomaly_detection_addon",
      "sources": [ "cpp_addon/anomaly_algorithm_binding.cpp" ],
      "include_dirs": [
              "<!@(node -p \"require('node-addon-api').include\")"
      ],
       "defines": [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
    }
  ]
}


