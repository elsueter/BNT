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

//"State" is an array of bools (ints for speed & typedef vector acting as a "stuct") that describe a networks state
//eg: {0, 0, 1} describes a 3 node network with A=0, B=0, C=1
typedef std::vector<int> state;
//a sequence of states that may hold traces and attractors of a network
typedef std::vector<state> sequence;

struct nodeMap{
	int nodeName;
	bool nodeValue;
};

//Maps an input state of nodes to this nodes resultant state
struct statePair{
	//input state
	std::vector<nodeMap> in;
	//output value
	bool out;

	bool operator ==(state);
};

//Node describes the behaviour for a node in a network.
struct node {
	//Array of statePairs acting as a local truth table.
	std::vector<statePair> TT;
	//The input expression that defines the behaviour and therefore truth table.
	std::string exp;
	//Current value of the node and the next value buffered for iteration.
	bool curr;
	bool next;

	//Check the input state against the truth table then buffer the future value for the node
	void check(state);
	//Iterate the node to its future state
	void update();
};

//Defines the structure for a full network (array of nodes)
typedef std::vector<node> netStruc;
typedef std::vector<netStruc> netStrucArr;

// Output Utilities--------------------------------------------------------------------------------------

//std::string stringify(netStruc in);

// Network Utilities--------------------------------------------------------------------------------

//Generalised function for checking if array contains member
template<typename T>
bool vectorContains(std::vector<T> arr, T in){
    for(auto& it: arr){
        if(it == in){
            return true;
        }
    }
    return false;
}

//Functions for parsing a JSON file containing descriptors of networks, returning passible network structures
netStrucArr parseFile();
netStrucArr parseFile(std::string path);

//Parses an input expression string and returns a network structure
netStruc parseExpression(std::vector<std::string> in);

// Network Classes--------------------------------------------------------------------------------------

//Node based network model
class nodeNetwork{
private:
	//Structure of the network
	netStruc nodes;

	sequence trace;
	std::vector<sequence> attractors;
	std::vector<sequence> uniqueTraces;

	//Iterates every node from a given state
	void iterateAll(state in);

public:
	//Constructor
	nodeNetwork(netStruc in);

	//Sets the current state of the network
	void setState(state in);

	//Iterates every node synchonusly until an attractor is hit (from current or given state)
	void synchronusIterate();
	void synchronusIterate(state start);
	void synchronusIterate(crow::json::rvalue start);

	//Clears the calculated structures (traces/attractors/etc...)
	void clear();

	//Returns the current state of the network
	state getState();

	//Private variable get methods
	std::string getTrace();
	std::vector<sequence> getAttractors();
	std::vector<sequence> getUniqueTraces();
};

}

#endif