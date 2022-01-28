#ifndef AED_T2_FILES_READER_H
#define AED_T2_FILES_READER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <sstream>
#include "structs.h"


/**
 * Tests if file passed as param exists
 * @param name file to be searched
 * @return boolean if found file
 */
bool file_exists(const string &name);

/**
 * Operator << overload for Location, allowing for printing a location's values
 * @param os ostream to be used for output
 * @param l value to be outputted
 * @return ostream (altered)
 */
ostream &operator<<(ostream &os, const Location &l);

/**
 * Operator << overload for Stop, allowing for printing a stops's values
 * @param os ostream to be used for output
 * @param l value to be outputted
 * @return ostream (altered)
 */
ostream &operator<<(ostream &os, const Stop &l);

/**
 * Operator << overload for Line, allowing for printing a line's values
 * @param os ostream to be used for output
 * @param l value to be outputted
 * @return ostream (altered)
 */
ostream &operator<<(ostream &os, const Line &l);


/**
 * Operator >> overload for Location, allowing extracting a Location from istream
 * @param is istream that contains the values to extract
 * @param l Location that will be set
 * @return istream (altered)
 */
istream &operator>>(istream &is, Location &l);

/**
 * Operator >> overload for Location, allowing extracting a Location from istream
 * @param is istream that contains the values to extract
 * @param l Location that will be set
 * @return istream (altered)
 */
istream &operator>>(istream &is, Stop &l);

/**
 * Operator >> overload for Line, allowing extracting a Line from istream
 * @param is istream that contains the values to extract
 * @param l Line that will be set
 * @return istream (altered)
 */
istream &operator>>(istream &is, Line &l);

/**
 * Operator >> overload for LineStops, allowing extracting a LineStops from istream
 * @param is istream that contains the values to extract
 * @param l LineStops that will be set
 * @return istream (altered)
 */
istream &operator>>(istream &is, LineStops &l);

/**
 * Reads the stops.csv file and returns a vector with all stops read
 * @param path path to stops.csv file
 * @return vector with all stops read from file
 */
vector<Stop> StopsReader(const string &path);

/**
 * Reads the lines.csv file and returns a vector with all lines read
 * @param path path to lines.csv file
 * @return vector with all lines read from file
 */
vector<Line> LinesReader(const string &path);

/**
 * Reads all stops code from stops.csv file
 * @param path path to stops.csv file
 * @return vector of all stop codes
 */
vector<string> StopsCodesReader(const string &path);

/**
 * Reads the lines files in both directions (0 & 1)
 * @param code line code to be read
 * @param includeM_lines boolean to choose if M lines should be read
 * @return list of lines files that met the criteria
 */
list<string> availableLines(const string &code, bool includeM_lines);

#endif //AED_T2_FILES_READER_H
