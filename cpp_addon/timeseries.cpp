#include "timeseries.h"

// read and parse header line
vector<string> TimeSeries::readAndParseHeaderLine(ifstream &file)
{
    vector<string> headers;
    string header_line = "";
    // read line
    getline(file, header_line);
    stringstream sStream(header_line);
    // split string by comma to headers name
    while (sStream.good())
    {
        string splitter;
        //get first string delimited by comma
        getline(sStream, splitter, ',');
        headers.push_back(splitter);
    }
    return headers;
}

// parse and split line to vectoer
vector<float> TimeSeries::parseLine(string line)
{
    vector<float> splittedLine;
    stringstream sStream(line);
    // split string to float csv values
    while (sStream.good())
    {
        string value;
        //get first string delimited by comma
        getline(sStream, value, ',');
        float f = stof(value);
        splittedLine.push_back(f);
    }
    return splittedLine;
}

//read data from a CSV File
void TimeSeries::readCsvFile()
{
    ifstream file(this->csv_file_name);
    this->header_line = readAndParseHeaderLine(file);
    this->columns_size = this->header_line.size();
    string line = "";
    int number_of_lines = 0;
    while (getline(file, line))
    {
        number_of_lines++;
        vector<float> record = parseLine(line);
        // split line and insert into vector
        for (int i = 0; i < this->columns_size; i++)
        {
            // if column name exists in map - insert another value to vector
            if (this->map_csv_data.find(this->header_line[i]) != map_csv_data.end())
            {
                this->map_csv_data[this->header_line[i]].push_back(record[i]);
            }
            // otherwise - create new vebtor and insert the new key and value
            else
            {
                vector<float> column_data;
                column_data.push_back(record[i]);
                this->map_csv_data.insert({this->header_line[i], column_data});
            }
        }
    }
    this->rows_size = number_of_lines;
    file.close();
}

// get data of scpecific column by column name
vector<float> TimeSeries::getColumnDataByName(string name) const
{
    vector<float> data = this->map_csv_data.at(name);
    return data;
}