let modelsMap = new Map();
let size = 0;

function getTimeZone() {
    let offset = new Date().getTimezoneOffset();
    let o = Math.abs(offset);
    return (offset < 0 ? "+" : "-") + ("00" + Math.floor(o / 60)).slice(-2) + ":" + ("00" + (o % 60)).slice(-2);
}

function addItem(){
    const timeElapsed = Date.now();
    const today = new Date(timeElapsed);
    let date = new Date(today);
    date.setHours(date.getHours() - (date.getTimezoneOffset()/ 60 ));
    let uploadTime = date.toISOString().split('.')[0] + getTimeZone();
    let model = {"model_id": ++size, "upload_time": uploadTime, "status":"pending"};
    modelsMap.set(model.model_id.toString(), model);
    return model;
}

function getItem(id){
    return modelsMap.get(id);
}

function deleteItem(id){
    let isExist = modelsMap.has(id);
    if(isExist) {
        modelsMap.delete(id);
    }
    return isExist;
}

function getAllModels(){
    return modelsMap.values();
}

module.exports = {
    addItem,
    getItem,
    deleteItem,
    getAllModels
};


//models.unshift(model);