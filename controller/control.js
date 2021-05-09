const modelHandler = require("../model/modelHandler");
const anomalyHandler = require('../build/Release/anomaly_detection_addon');

exports.learn = async (req, res, next) => {
    console.log("in")
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

   // let model = modelHandler.addItem();
    anomalyHandler.anomaly_detection("C:\\Users\\sarit\\WebstormProjects\\anomaly_detection_webapp\\reg_flight.csv", "C:\\Users\\sarit\\WebstormProjects\\anomaly_detection_webapp\\anomaly_flight.csv", "hybrid", function (err, result) {
        console.log(Array.from(result));
        res.send("hi");
    });

}

exports.getModel = async (req, res, next) => {
    let id = req.query.model_id;
    if(typeof id == "undefined"){
        res.status(400).send("invalid model id");
        return;
    }
    let model = modelHandler.getItem(id);
    if(typeof model == "undefined"){
        res.status(400).send("invalid model id");
        return;
    }

    res.status(200).json(model);
}

exports.deleteModel = async (req, res, next) => {
    let id = req.query.model_id;
    if(typeof id == "undefined"){
        res.status(400).send("invalid model id");
        return;
    }
    let isSuccess =modelHandler.deleteItem(id);
    if(isSuccess) {
        res.status(200).send(" model deleted successfully");
    }
    else{
        res.status(400).send("invalid model id");
    }
}

exports.getAllModels  = async (req, res, next) => {
    let models = modelHandler.getAllModels();
    res.status(200).json(Array.from(models));
}
