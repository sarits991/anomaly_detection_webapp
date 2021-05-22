const modelHandler = require("../model/modelHandler");
const anomalyHandler = require('../build/Release/anomaly_detection_addon');

exports.findAnomalies = async (req, res) => {
    let type = req.body['model_type'];
    if(typeof type == "undefined") {
        res.status(400).send({error:"invalid data"});
        return;
    }
    if(type.localeCompare("hybrid") && type.localeCompare("regression")) {
        res.status(400).send({error:"invalid model type"});
        return;
    }

    if(typeof req.files.train_file == "undefined" || typeof req.files.detect_file == "undefined" ){
        res.status(400).send({error:"invalid files"});
        return;
    }

    let train_file = String(req.files.train_file.data).replace(/(\r\n)/g, "\n");
    let detect_file = String(req.files.detect_file.data).replace(/(\r\n)/g, "\n");
    let files = modelHandler.createFiles(train_file, detect_file);
    anomalyHandler.anomaly_detection(files.train, files.detect, type , function (err, result) {
        let jsonRes = modelHandler.parseAnomalies(Array.from(result));
        res.send(jsonRes);
        modelHandler.deleteFiles(files);
    });

}

exports.getHtml = (req, res) => {
    res.sendfile("index.html")
}





