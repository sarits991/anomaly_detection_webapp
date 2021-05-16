
function parseAnomalies(anomaliesArray)
{
    let anomalies = [];
    for(let i in anomaliesArray){
        let res = i.split(':');
        let anomaly = {description:res[0] + ':' + res[1], timestep:res[2]};
        anomalies.push(anomaly);
    }

    let map = new Map();

    for(let i in anomalies){
        if(!map.has(i.description)){
            map.set(i.description, [i.timestep]);
        }
        else{
            map.get(i.description).push(i.timestep);
        }
    }
}


module.exports = {
};

