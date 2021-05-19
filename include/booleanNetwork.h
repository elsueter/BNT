#ifndef _booleanNetwork_H_
#define _booleanNetwork_H_
#pragma once

// std includes ----------------------------------------------------------------------------

#include <vector>
#include <algorithm>
#include <thread>
#include <mutex>

// Network Structs ----------------------------------------------------------------------------

typedef std::vector<bool> state;
typedef std::vector<state> sequence;

struct statePair {
	state t0;
	state t1;
};

// Network Class--------------------------------------------------------------------------------------

class booleanNetwork {
private:

	std::mutex mtx;

	//the network truth table for all states
	std::vector<statePair> netTT;

	std::vector<sequence> traces;
	std::vector<sequence> attractors;
	std::vector<sequence> uniqueTraces;

	void genTrace(sequence& trace);

public:
	booleanNetwork(std::vector<state> inTT);

	void genTraces();
	void genTracesThreaded();

	void del();

	std::vector<statePair> getTT();
	std::vector<sequence> getTraces();
	std::vector<sequence> getAttractors();
	std::vector<sequence> getUniqueTraces();
};
#include "../src/models/basicNetwork.cpp"

#endif