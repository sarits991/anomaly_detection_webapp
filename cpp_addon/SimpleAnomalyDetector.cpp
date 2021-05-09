#include "SimpleAnomalyDetector.h"
#include <iostream>

SimpleAnomalyDetector::SimpleAnomalyDetector()
{
	// TODO Auto-generated constructor stub
}

SimpleAnomalyDetector::~SimpleAnomalyDetector()
{
	// TODO Auto-generated destructor stub
}

// find corollation and return struct of correlatedFeatures
correlatedFeatures SimpleAnomalyDetector::findCorollation(const TimeSeries &ts, string feature1, int index)
{
	vector<string> header_line = ts.getHeaderLine();
	correlatedFeatures c_features;
	c_features.feature1 = feature1;
	string feature2;
	vector<float> feature1_data = ts.getColumnDataByName(feature1);
	int size_of_rows = feature1_data.size();
	float max_pearson = (float)0.9;
	// itreate of the columns from specific index
	for (int i = index; i < ts.getColumnsSize(); i++)
	{
		vector<float> column_data = ts.getColumnDataByName(header_line[i]);
		// find the preason
		float result = pearson(feature1_data.data(), column_data.data(), size_of_rows);
		// if the pearson is bigger than the mac - replace and save the specific feature
		if (max_pearson < fabs(result))
		{
			max_pearson = result;
			feature2 = header_line[i];
		}
	}
	c_features.feature2 = feature2;
	c_features.corrlation = fabs(max_pearson);
	return c_features;
}

// create arr points from two given columns and return it
vector<Point *> SimpleAnomalyDetector::createArrPointsFromcFeatures(const TimeSeries &ts, correlatedFeatures c_features)
{
	vector<Point *> points;
	vector<float> fearture1 = ts.getColumnDataByName(c_features.feature1);
	vector<float> fearture2 = ts.getColumnDataByName(c_features.feature2);
	// iteatre on the rows and create new point from couple of values in the features
	for (int i = 0; i < ts.getRowsSize(); i++)
	{
		Point *point = new Point(fearture1[i], fearture2[i]);
		points.push_back(point);
	}
	return points;
}

// find the maxinum threshold between point an line and return it.
float SimpleAnomalyDetector::find_threshold(vector<Point *> points, Line line_reg)
{
	float max_threshold = 0;
	// itreate on the points array and find the max dev
	for (int i = 0; i < points.size(); i++)
	{
		float result_dev = dev(*(points[i]), line_reg);
		if (max_threshold <= result_dev)
		{
			max_threshold = result_dev;
		}
	}
	return max_threshold;
}

void SimpleAnomalyDetector::learnNormal(const TimeSeries &ts)
{
	vector<string> header_line = ts.getHeaderLine();
	// map index of feature 1 coulm and the data of the corraltion
	map<int, correlatedFeatures> map_index_cf;
	int index = 0;
	// itreate on the coulmns to find corraltion
	for (auto &column_name : header_line)
	{
		index++;
		// if the last column - no others columns to find corraltion
		if (index == ts.getColumnsSize())
		{
			continue;
		}
		correlatedFeatures cFeatures = findCorollation(ts, column_name, index);
		// if the corraltion is above 0.9 - it is a corraltion
		if (cFeatures.corrlation > 0.9)
		{
			map_index_cf.insert({index, cFeatures});
		}
	}
	// itreate on the map and insert the line regression and threshold
	for (auto &entry : map_index_cf)
	{
		vector<Point *> points = createArrPointsFromcFeatures(ts, entry.second);
		Line line_reg = linear_reg(points.data(), points.size());
		float max_point = find_threshold(points, line_reg);
		entry.second.lin_reg = line_reg;
		entry.second.threshold = max_point * 1.1;
		this->cf.push_back(entry.second);
	}
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts)
{
	vector<AnomalyReport> p;
	// itreate on the features
	for (auto &c_features : this->cf)
	{
		vector<Point *> points = createArrPointsFromcFeatures(ts, c_features);
		// itreate on the points anf find if there is point above the threshold
		for (int i = 0; i < points.size(); i++)
		{
			float devision = dev(*(points[i]), c_features.lin_reg);
			if (devision > c_features.threshold)
			{
				// create description - "feature1-feature2"
				string description = c_features.feature1 + ":" + c_features.feature2;
				// cretae time step - line that the detecet found
				long timeStep = i + 1;
				AnomalyReport report = AnomalyReport(description, timeStep);
				p.push_back(report);
			}
		}
	}
	return p;
}