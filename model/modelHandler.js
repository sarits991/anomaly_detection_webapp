const fs = require('fs');
const path = require('path');
let counter = 0;

function parseAnomalies(anomaliesArray)
{
    let anomalies = [];
    anomaliesArray.forEach(i => {
        let res = i.split(':');
        let anomaly = {description:res[0] + ':' + res[1], timestep:res[2]};
        anomalies.push(anomaly);
    })

    let map = new Map();

    anomalies.forEach( i => {
        if(!map.has(i.description)){
            map.set(i.description, [i.timestep]);
        }
        else{
            map.get(i.description).push(i.timestep);
        }
    })


    let anomaliesRange = [];
    map.forEach((value, key) => {let res = value.reduce(function (r, a, i, aa) {
        r.push(!i || aa[i - 1] - a + 1 ? a : r.pop().split('-')[0] + '-' + a);
        return r;
    }, []);
    let features = key.split(':');
    anomaliesRange.push({feature1:features[0], feature2 : features[1], range: res});
    })
    return JSON.stringify(anomaliesRange);
}

function createFiles (train_file, detect_file) {
    counter++;
    let train_file_path = path.resolve(`./csv_files/train_file_${counter}.csv`);
    fs.writeFileSync(train_file_path, train_file);

    let detect_file_path = path.resolve(`./csv_files/detect_file_${counter}.csv`);
    fs.writeFileSync(detect_file_path, detect_file);

    return {train: train_file_path, detect: detect_file_path};
}


function deleteFiles(files){
    fs.unlink(files.train, (err) => {
        if (err) {}
    })
    fs.unlink(files.detect, (err) => {
        if (err) {}
    })
}

module.exports = {
    createFiles,
    deleteFiles,
    parseAnomalies
};

