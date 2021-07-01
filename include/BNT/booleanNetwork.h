#ifndef _booleanNetwork_H_
#define _booleanNetwork_H_
#pragma once

// std includes ----------------------------------------------------------------------------

#include <crow/json.h>
#include <vector>
//#include <thread>
#include <string>
#include <fstream> //File operations (read/write)

// Network Structs ----------------------------------------------------------------------------

namespace BooleanNetwork{

typedef std::vector<int> state;
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

	void check(state);
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
bool vectorPermComparison(std::vector<T> seq, std::vector<T> in){

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
bool vectorArrEquals(std::vector<std::vector<T> > arr, std::vector<T> in){
    for(auto it: arr){
		if(vectorPermComparison(it, in)){
			return true;
		}
    }
	return false;
}

template<typename T>
int vectorArrContains(std::vector<std::vector<T> > arr, std::vector<T> in){
	for(int i = 0; i < arr.size(); i++){
		auto one = arr[i];
		auto two = in;

		one.pop_back();
		two.pop_back();

		int diff = one.size() - two.size();

		if(diff > 0){
			one.erase(one.begin(), one.begin()+diff);
		}else if(diff < 0){
			two.erase(two.begin(), two.begin()-diff);
		}

		if(vectorPermComparison(one, two)){
			if(diff < 0){
				return i;
			}
			return -2;
		}
	}
	return -1;
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

	void clear();

	state getState();

	sequence getTrace();
	std::string getTraceS();
	std::vector<sequence> getAttractors();
	std::string getAttractorsS();
	std::vector<sequence> getUniqueTraces();
	std::string getUniqueTracesS();
	std::string getNodesS();
};

}

#endif