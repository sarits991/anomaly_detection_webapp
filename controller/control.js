const modelHandler = require("../model/modelHandler");
const anomalyHandler = require('../build/Release/anomaly_detection_addon');

exports.findAnomalies = async (req, res, next) => {
    let type = req.query.model_type;
    if(type.localeCompare("hybrid") && type.localeCompare("regression")) {
        res.status(400).send("invalid model type");
        return;
    }
    let data = req.body['train_data'];
    if(typeof data == "undefined") {
        res.status(400).send("invalid data");
        return;
    }

    anomalyHandler.anomaly_detection("C:\\Users\\sarit\\WebstormProjects\\anomaly_detection_webapp\\reg_flight.csv", "C:\\Users\\sarit\\WebstormProjects\\anomaly_detection_webapp\\anomaly_flight.csv", "hybrid", function (err, result) {
        console.log(Array.from(result));
        res.send("hi");
    });
}






