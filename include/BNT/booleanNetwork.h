#ifndef _booleanNetwork_H_
#define _booleanNetwork_H_
#pragma once

// std includes ----------------------------------------------------------------------------

#include <crow/json.h>
#include <vector>
#include <thread>
#include <string>
#include <fstream> //File operations (read/write)

// Network Structs ----------------------------------------------------------------------------

namespace BooleanNetwork{

typedef std::vector<bool> state;
typedef std::vector<state> sequence;

struct nodeMap{
	int nodeName;
	bool nodeValue;
};

struct statePair{
	std::vector<nodeMap> in;
	bool out;

	bool operator ==(state);
};

struct node {
	std::vector<statePair> TT;
	std::string exp;
	std::string label;
	bool curr;
	bool next;

	void getNext(state);
	void update();
};

typedef std::vector<node> netStruc;
typedef std::vector<netStruc> netStrucArr;

// Output Utilities--------------------------------------------------------------------------------------

//std::string stringify(netStruc in);

// Network Utilities--------------------------------------------------------------------------------

template<typename T>
int vectorContains(std::vector<T> arr, T in){
    for(int i = 0; i < arr.size(); i++){
        if(arr[i] == in){
            return i;
        }
    }
    return -1;
}

template<typename T>
bool vecEquals(std::vector<T> seq, std::vector<T> in){
	for(int i = 0; i < seq.size(); i++){
		if(seq == in){
			return true;
		}
		T temp = seq[0];
		for(int i = 1; i < seq.size(); i++){
			seq[i-1] = seq[i];
		}
		seq[seq.size()-1] = temp;
	}
	return false;
}

template<typename T>
bool vecArrContains(std::vector<std::vector<T> > arr, std::vector<T> in){
    for(auto it: arr){
		if(vecEquals(it, in)){
			return true;
		}
    }
	return false;
}

#include <iostream>

template<typename T>
bool vectorUniqueAdd(std::vector<std::vector<T> > &arr, std::vector<T> &in){
	for(int i = 0; i < arr.size(); i++){
		std::vector<T> one = arr[i];
		std::vector<T> two = in;

		one.pop_back();
		two.pop_back();

		int diff = one.size() - two.size();

		if(diff > 0){
			one.erase(one.begin(), one.begin()+diff);
		}else if(diff < 0){
			two.erase(two.begin(), two.begin()-diff);
		}

		if(vecEquals(one, two)){
			if(diff < 0){
				arr[i] = in;
				return true;
			}
			return false;
		}
	}
	arr.push_back(in);
	return true;
}

netStrucArr parseFile();
netStrucArr parseFile(std::string path);
netStruc parseExpression(std::vector<std::string> in);

// Network Classes--------------------------------------------------------------------------------------

class nodeNetwork{
private:
	netStruc nodes;

	sequence trace;
	std::vector<sequence> attractors;
	std::vector<sequence> uniqueTraces;

	void iterateAll(state in);

public:
	nodeNetwork(netStruc in);

	void setState(state in);

	void synchronusIterate();
	void synchronusIterate(state start);
	void synchronusIterate(crow::json::rvalue start);

	void generateStateGraph();
	void generateStateGraphThreaded();

	void clear();

	state getState();

	std::string getTraceS();
	std::string getAttractorsS();
	std::string getUniqueTracesS();

	std::string getNodesS();
	std::string getNodesExpS();
};

}

#endif