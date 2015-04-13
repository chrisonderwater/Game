/*
Leuk bedacht, snelle resource container voor *alle* resources. Mooi, templates, cool!
Nadeel: Resources specifieke functies gaan hier niet in werken. Alle plaatjes scalen?
Misschien moet je een functie performAll(functie); maken die ervoor zorgt dat een functie
op alle objecten wordt toegepast... :/
*/
#ifndef RES_H
#define RES_H

#include <SFML/Graphics.hpp>
#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<stack>
#include <memory>

template <class T>
class Resource {
	private:
		std::vector< T* > resources;
		std::map<std::string, int> names;
		std::stack<int> freePlaces;
	public:
		Resource();
		~Resource();
		int add( T * item, std::string name);
		T * get(int id);
		T * get(std::string name);
		void remove(int id);
};

template<class T>
Resource <T>::Resource(){
	
}

template<class T>
Resource <T>::~Resource(){
	// Let the smart pointers do the work.
}

template <class T> int Resource<T>::add(T * item, std::string name){
	
	if(names.count(name) != 0){
		if(resources[names[name]]!=NULL)
			return names[name];
	}
	if(freePlaces.empty()){
		resources.push_back(item);
		names[name] = resources.size()-1;
		return resources.size()-1;
	} else {
		int temp;
		temp = freePlaces.top();
		freePlaces.pop();
		resources[temp] = item;
		names[name] = temp;
		return temp;
	}
}

//Get using a ID. Very fast access. No extra tests though.
template <class T>
T * Resource<T> ::get(int id){
		return resources[id];
}

//Get using a string.
template <class T>
T * Resource<T> ::get(std::string name){
	if (names.count(name) > 0){
		return resources[names[name]];
	} else {
		//Als het plaatje er nog niet is, laad je het.
		T * plaatje(new T);
		plaatje->loadFromFile(name);
		plaatje->setSmooth(true);
		resources.push_back(plaatje);
		names[name] = resources.size()-1;
		return plaatje;
	}
}

template <class T>
void Resource <T>::remove(int id){
	if(resources[id] != NULL){
		delete resources[id];
		resources[id]=NULL;
	}
}
#endif