#ifndef _booleanNetwork_H_
#define _booleanNetwork_H_
#pragma once

// std includes ----------------------------------------------------------------------------

#include <crow/json.h>
#include <vector>
#include <thread>
#include <string>
#include <fstream>

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
	bool curr;
	bool next;

	void check(state);
	void update();
};

typedef std::vector<node> netStruc;
typedef std::vector<netStruc> netStrucArr;

// Output Utilities--------------------------------------------------------------------------------------

std::string stringify(netStruc in);

// Network Utilities--------------------------------------------------------------------------------

template<typename T>
bool vectorContains(std::vector<T> arr, T in){
    for(auto& it: arr){
        if(it == in){
            return true;
        }
    }
    return false;
}

netStrucArr parseFile();
netStrucArr parseFile(std::string path);

netStruc parseExpression(std::vector<std::string> in);

// Network Classes--------------------------------------------------------------------------------------

class nodeNetwork{
	private:
		netStruc nodes;

		std::vector<sequence> traces;
		std::vector<sequence> attractors;
		std::vector<sequence> uniqueTraces;

		void iterateAll(state in);

	public:
		nodeNetwork(netStruc in);

		void setState(state in);
		void synchronusIterate();
		void synchronusIterate(state start);
		void synchronusIterate(crow::json::rvalue start);

		void clear();

		state getState();
		std::string getTraces();
		std::vector<sequence> getAttractors();
		std::vector<sequence> getUniqueTraces();
};

}

#endif