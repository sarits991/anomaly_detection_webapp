#ifndef HYBRIDANOMALYDETECTOR_H_
#define HYBRIDANOMALYDETECTOR_H_

#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include "minCircle.h"

class HybridAnomalyDetector:public TimeSeriesAnomalyDetector {

	vector<correlatedFeatures> cf;
	float correlation_threshold;
	// find corollation and return struct of correlatedFeatures
	correlatedFeatures findCorollation(const TimeSeries &ts, string feature1, int index);
	// create arr points from two given columns and return it
	vector<Point*> createArrPointsFromcFeatures (const TimeSeries &ts,correlatedFeatures c_features);
	// find the maxinum threshold between point an line and return it.
	float find_threshold(vector<Point*> points, int size, correlatedFeatures &cFeatures);
	bool findAnomaly(Point point, correlatedFeatures cFeatures);
    bool isCorrlation(float corrlation);

public:
	HybridAnomalyDetector();
	virtual ~HybridAnomalyDetector();

	virtual void learnNormal(const TimeSeries &ts);
	virtual vector<AnomalyReport> detect(const TimeSeries &ts);

	vector<correlatedFeatures> getNormalModel()
	{
		return cf;
	}
	float getCorrelationThreshold(){
       return correlation_threshold;
    }
    void setCorrelationThreshold(float correlation_threshold) {
    	this->correlation_threshold = correlation_threshold;
    }
};

#endif /* HYBRIDANOMALYDETECTOR_H_ */