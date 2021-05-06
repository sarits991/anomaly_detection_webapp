const modelHandler = require("../model/modelHandler");
//const anomalyHandler = require('../build/Release/anomaly_algorithm_binding');

exports.learn = async (req, res, next) => {
    let type = req.query.model_type;
    if(type != "hybrid" && type != "regression") {
        res.status(400).send("invalid model type");
        return;
    }
    let data = req.body['train_data'];
    if(data == undefined) {
        res.status(400).send("invalid data");
        return;
    }
    let model = modelHandler.addItem();
    //onsole.log(anomalyHandler.HelloWorld)
    res.status(200).json(model);
}

exports.getModel = async (req, res, next) => {
    let id = req.query.model_id;
    if(id == undefined){
        res.status(400).send("invalid model id");
        return;
    }
    let model = modelHandler.getItem(id);
    if(model == undefined){
        res.status(400).send("invalid model id");
        return;
    }

    res.status(200).json(model);
}

exports.deleteModel = async (req, res, next) => {
    let id = req.query.model_id;
    if(id == undefined){
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
