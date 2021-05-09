#ifndef TIMESERIES_H_
#define TIMESERIES_H_

using namespace std;
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

class TimeSeries
{

private:
	// csv file name
	const char *csv_file_name;
	// vector of headers line
	vector<string> header_line;
	// map between column name and data of the coulm
	map<string, vector<float>> map_csv_data;
	// column size
	int columns_size;
	// row size
	int rows_size;
	// read and parse header line
	vector<string> readAndParseHeaderLine(ifstream &file);
	// parse and split line to vectoer
	vector<float> parseLine(string line);

public:
	TimeSeries(const char *CSVfileName) : csv_file_name(CSVfileName)
	{
		readCsvFile();
	}
	//read data from a CSV File
	void readCsvFile();
	// get vector of headers line
	vector<string> getHeaderLine() const
	{
		return this->header_line;
	}
	// get data of scpecific column by column name
	vector<float> getColumnDataByName(string name) const;
	// get size of columns in csv
	int getColumnsSize() const
	{
		return this->columns_size;
	}
	// get size of rows in csv
	int getRowsSize() const
	{
		return this->rows_size;
	}
	int getRowNumberByFeatureAndFields(string column1, string column2, float val1, float val2) const;
};

#endif /* TIMESERIES_H_ */