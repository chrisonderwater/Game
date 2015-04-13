#include <sstream>
#include <string>
// Stupid quickfix for lack of C++11
/*
namespace std{
inline std::string to_string(int number){
	std::stringstream ss;
	std::string s;
	ss << number;
	ss >> s;
	return s;
}

inline int stoi(string str){
	std::stringstream ss;
	int s;
	ss << str;
	ss >> s;
	return s;
}

inline float stof(string str){
	std::stringstream ss;
	float s;
	ss << str;
	ss >> s;
	return s;
}
}
*/