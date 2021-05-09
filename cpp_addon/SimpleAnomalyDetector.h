
#ifndef SIMPLEANOMALYDETECTOR_H_
#define SIMPLEANOMALYDETECTOR_H_

#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include <vector>
#include <algorithm>
#include <string.h>
#include <map>
#include <math.h>
#include <stdlib.h>


class SimpleAnomalyDetector : public TimeSeriesAnomalyDetector
{
	vector<correlatedFeatures> cf;
	// find corollation and return struct of correlatedFeatures
	correlatedFeatures findCorollation(const TimeSeries &ts, string feature1, int index);
	// create arr points from two given columns and return it
	vector<Point*> createArrPointsFromcFeatures (const TimeSeries &ts,correlatedFeatures c_features);
	// find the maxinum threshold between point an line and return it.
	float find_threshold(vector<Point*> points, Line line_reg);

public:
	SimpleAnomalyDetector();
	virtual ~SimpleAnomalyDetector();

	virtual void learnNormal(const TimeSeries &ts);
	virtual vector<AnomalyReport> detect(const TimeSeries &ts);

	vector<correlatedFeatures> getNormalModel()
	{
		return cf;
	}
};

#endif /* SIMPLEANOMALYDETECTOR_H_ */