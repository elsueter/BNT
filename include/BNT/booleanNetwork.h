#ifndef _booleanNetwork_H_
#define _booleanNetwork_H_
#pragma once

// std includes ----------------------------------------------------------------------------

#include <vector>
#include <thread>
#include <string>
#include <sstream>

// Network Structs ----------------------------------------------------------------------------

namespace BooleanNetwork{

typedef std::vector<int> state;
typedef std::vector<state> sequence;

struct statePair {
	state t0;
	state t1;
};

struct node {
	std::vector<int> nodes;
	std::vector<char> ops;
	state tt;

	bool getVal(state in);
};

// Network Utilities--------------------------------------------------------------------------------

std::vector<node> parseExpression(std::vector<std::string> in);

// Network Classes--------------------------------------------------------------------------------------

class basicNetwork {
	private:

		//the network truth table for all states
		std::vector<statePair> netTT;

		std::vector<sequence> traces;
		std::vector<sequence> attractors;
		std::vector<sequence> uniqueTraces;

		bool generated;

		void genTrace(sequence& trace);

	public:
		basicNetwork(std::vector<state> inTT);

		void genTraces();
		void genTracesThreaded();

		void del();

		std::vector<sequence> getTT();
		std::string getTraces();
		std::string getAttractors();
		std::string getUniqueTraces();
};

class nodeNetwork{
	private:
		std::vector<std::string> baseLogic;

		std::vector<node> nodes;

		std::vector<sequence> traces;
		std::vector<sequence> attractors;
		std::vector<sequence> uniqueTraces;

	public:
		nodeNetwork(std::vector<std::string> in);
};

}

#endif