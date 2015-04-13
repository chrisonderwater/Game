#include "INIReader.h"

/*
Note: 
There is a bug that requires the last item to be a \n. If not there will be a segmentation fault.

*/

void INIReader::read(std::string fileName){
	int mode = 0;
	// modes: 0 = new name. 1 = new attribute. 2 = new attribute value.
	std::string temp;
	Container<std::string> emptyC;
	Container<std::string> c;

	std::ifstream file;
	file.open(fileName);

	if (!file.is_open()){
		std::cout << "\nCould not open file: " << fileName;
		return; 
		// Without return there will be an infinite loop.
	}

	// If coding is art, here comes the art.
	char k = file.get();
	while( !file.eof() ){
		if (k == '#'){ 
			// Ignore all the hashtags! 
			while(k != '\n')
				k = file.get();
		} else if (k == '[')
			mode = 0;
		else if (k == ']'){
			// We have a name! Save it.
			elements.key.push_back(temp);
			elements.value.push_back(c);
			mode = 1;
			c = emptyC;
			temp = "";
		} else if(k == '='){
			mode = 2;
			elements.value.back().key.push_back(temp);
			temp = "";
		} else if (mode == 1 && k != '\n'){
			//Substract the parameter!
			temp.push_back(k);
		}else if (mode == 0 && k!='\n'){
			// This is the key!
			temp.push_back(k);
		} else if ( mode == 2){
			// And then there was value.
			if ( k == '\n' ){
				mode = 0;
				elements.value.back().value.push_back(temp);
				temp = "";
			} else {
				temp.push_back(k);
			}		
		}
		k = file.get();
	}
}

void INIReader::write(std::string fileName){
	std::ofstream file(fileName, std::ofstream::trunc);
	for ( int i = 0; i < elements.key.size(); i++){
		// Print the key!
		file << "[" ;
		file << elements.key.at(i);
		file << "]\n";

		// Print parameters.
		for (int j = 0; j < elements.value.at(i).key.size(); j++){
			file << elements.value.at(i).key.at(j);
			file << " = ";
			file << elements.value.at(i).value.at(j);
			file << "\n";
		}// for j
	}// for i
}

void INIReader::print(){
	for (int i = 0; i< elements.key.size();i++){
		std::cout << elements.key.at(i);
		for (int j=0;j<elements.value.at(i).key.size();j++){
			std::cout << elements.value.at(i).key.at(j);
			std::cout << std::endl;
			std::cout << elements.value.at(i).value.at(j);
			std::cout << std::endl;
		}
	}
}

// Description:
// [key]
// parameter = value
std::string INIReader::getParameterValue(std::string tempKey, std::string parameter){
	int temp = 0;
	for (int i=0; i<elements.key.size(); i++){
		if (elements.key.at(i) == tempKey){
			temp = i;
			break;
		}
	}

	for (int i=0; i<elements.value.at(temp).key.size();i++){
		if (elements.value.at(temp).key.at(i) == parameter){
			return elements.value.at(temp).value.at(i);
		}
	}
	return "";// If nothing is found, just return an empty string.
}

// Description:
//        a,tree,in,forest
// place: 0, 1  , 2, 3
std::string INIReader::commaExtract(std::string text, int place){
	std::string temp;
	int commaNumber = 0;

	for (int i=0; i<text.size();i++){
		if (text.at(i) == ',')
			commaNumber++;
		else if (commaNumber == place) {
			temp.push_back(text.at(i));
		}
	}
	return temp;
}

// Add a new element to the end of the list.
void INIReader::writeParameterValue(std::string tempKey, std::string parameter, std::string value){
	Container<std::string> temp;
	temp.value.push_back(value);
	temp.key.push_back(parameter);
	
	elements.key.push_back(tempKey);
	elements.value.push_back(temp);
}