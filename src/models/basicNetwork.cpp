#include "../../include/booleanNetwork.h"

// Utility funcs -----------------------------------------------------------------------

int sequenceContains(sequence trace, state in) {
	for (int i = 0; i < trace.size(); i++) {
		if (trace[i] == in) {
			return i;
		}
	}
	return -1;
}

bool sequenceEqualsPerm(sequence& in1, sequence& in2) {
	for (auto& it : in1) {
		if (in1 == in2) {
			return true;
		}

		/*state temp = it.back();
		for (int i = it.size() - 1; i > 0; i--) {
			it[i] = it[i - 1];
		}
		it[0] = temp;

		Algorithm implementation of above*/
		std::rotate(in1.begin(), in1.begin() + 1, in1.end());
	}
	return false;
}

bool sequenceArrContains(std::vector<sequence>& arr, sequence& in) {
	for (auto& it : arr) {
		return sequenceEqualsPerm(it, in);
	}
	return false;
}

bool sequenceArrContainsSubsequence(std::vector<sequence>& arr, sequence& in) {
	for (auto& it : arr) {
		if (in.size() <= it.size()) {
			int dif = it.size() - in.size();
			sequence temp(it.begin() + dif, it.end());
			if (sequenceEqualsPerm(temp, in)) {
				return true;
			}
		}
		else{
			int dif = in.size() - it.size();
			sequence temp(in.begin() + dif, in.end());
			if (sequenceEqualsPerm(temp, it)) {
				it = in;
				return true;
			}
		}
	}
	return false;
}

// Constructor/Destructor(s) -----------------------------------------------------------

booleanNetwork::booleanNetwork(std::vector<state> inTT) {
	int len = inTT.size() / 2;

	netTT.reserve(len);
	traces.reserve(len);

	for (int i = 0; i < len; i++) {
		netTT.push_back({ inTT[i * 2], inTT[(i * 2) + 1] });
		traces.push_back({ inTT[i * 2] });
	}
}

// Private Methods -----------------------------------------------------------------------

void booleanNetwork::genTrace(sequence& trace) {

	trace.reserve(netTT.size());
	attractors.reserve(netTT.size());
	uniqueTraces.reserve(netTT.size());

	bool attractorHit = false;
	while (!attractorHit) {
		for (auto& it : netTT) {
			if (it.t0 == trace.back()) {
				int index = sequenceContains(trace, it.t1);

				if (index > -1) {
					sequence temp(trace.begin() + index, trace.end());

					if (!sequenceArrContains(attractors, temp)) {
						mtx.lock();
						attractors.push_back(temp);
						mtx.unlock();
					}

					if (!sequenceArrContainsSubsequence(uniqueTraces, trace)) {
						mtx.lock();
						uniqueTraces.push_back(trace);
						mtx.unlock();
					}

					attractorHit = true;
				}
				else {
					trace.push_back(it.t1);
				}

				break;
			}
		}
	}

	attractors.shrink_to_fit();
}

// Public Methods ------------------------------------------------------------------------

void booleanNetwork::genTraces() {
	for (auto& it : traces) {
		genTrace(it);
	}
}

void booleanNetwork::genTracesThreaded() {
	std::vector<std::thread> threads;
	for (auto& it : traces) {
		threads.push_back(std::thread(&booleanNetwork::genTrace, this, std::ref(it)));
	}

	for (auto& it : threads) {
		it.join();
	}
}

// Getter/Setter Methods -----------------------------------------------------------------

std::vector<statePair> booleanNetwork::getTT() {
	return netTT;
}

std::vector<sequence> booleanNetwork::getTraces() {
	return traces;
}

std::vector<sequence> booleanNetwork::getAttractors() {
	return attractors;
}

std::vector<sequence> booleanNetwork::getUniqueTraces() {
	return uniqueTraces;
}

void booleanNetwork::del() {
	traces.clear();
	attractors.clear();
	uniqueTraces.clear();
}