#include <BNT/booleanNetwork.h>
#include <algorithm>

using namespace BooleanNetwork;

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

std::string stringifySequenceArr(std::vector<sequence> in){
	std::string out = "dinetwork {node[shape=circle]; ";

	for(int i = 0; i < in.size(); i++){
		for(int j = 0; j < in[i].size(); j++){
			std::stringstream ss;
			for(auto& i: in[i][j]){
				ss << i;
			}
			out += '"';
			out += ss.str();
			out += '"';
			if(j < in[i].size()-1){
				out += " -> ";
			}
		}
		out += "; ";
	}
	
	out += "}";

	return out;
}

// Constructor/Destructor(s) -----------------------------------------------------------

basicNetwork::basicNetwork(std::vector<state> inTT) {
	int len = inTT.size() / 2;

	netTT.reserve(len);
	traces.reserve(len);

	for (int i = 0; i < len; i++) {
		netTT.push_back({ inTT[i * 2], inTT[(i * 2) + 1] });
	}

	generated = false;
}

// Private Methods -----------------------------------------------------------------------

void basicNetwork::genTrace(sequence& trace) {
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
						attractors.push_back(temp);
					}

					if (!sequenceArrContainsSubsequence(uniqueTraces, trace)) {
						uniqueTraces.push_back(trace);
					}

					attractorHit = true;
				}

				trace.push_back(it.t1);

				break;
			}
		}
	}
}

// Public Methods ------------------------------------------------------------------------

void basicNetwork::genTraces() {
	if(!generated){
		for (auto& it: netTT) {
			traces.push_back({it.t0});
		}
		for (auto& it : traces) {
			genTrace(it);
		}
		
		attractors.shrink_to_fit();
		generated = true;
	}
}

// Getter/Setter Methods -----------------------------------------------------------------

std::vector<sequence> basicNetwork::getTT() {
	std::vector<sequence> out;
	for(auto& it:netTT){
		sequence temp;
		temp.push_back(it.t0);
		temp.push_back(it.t1);
		out.push_back(temp);
	}
	return out;
}

std::string basicNetwork::getTraces() {
	return stringifySequenceArr(traces);
}

std::string basicNetwork::getAttractors() {
	return stringifySequenceArr(attractors);
}

std::string basicNetwork::getUniqueTraces() {
	return stringifySequenceArr(uniqueTraces);
}

void basicNetwork::del() {
	traces.clear();
	attractors.clear();
	uniqueTraces.clear();
	generated = false;
}