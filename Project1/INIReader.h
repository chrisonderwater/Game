/*
Simple INI reader inspired by state-machines.
Deals with specific issues such as:
-Extracting comma separated data.cv
-Extracting data when multiple keys have the same value.

Code is quite efficient and very short. d.

NOTE: All values are returned as a string.

To make a map, use flare map type in Tiled map editor.

It's name does not suggest it, but the reader also has limited write support.
*/
#ifndef IREADER_H
#define IREADER_H
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

template <class T>
class Container{
	public:
		std::vector<std::string> key;
		std::vector<T> value;
};

class INIReader {
public:
	void read(std::string fileName);
	void write(std::string fileName);
	void print();
	// If a comma separated value is found, this can return the separated values.
	std::string commaExtract(std::string text, int place);

	// Simpelste manier om data uit een ini-file te lezen. 
	std::string getParameterValue(std::string tempKey, std::string parameter);

	void writeParameterValue(std::string tempKey, std::string parameter, std::string value);

	// Een container houdt een container van elementen. dus [] -> variabelen.
	Container<Container<std::string>> elements;
};

template class Container<Container<std::string>>;
template class Container<std::string>;

#endif