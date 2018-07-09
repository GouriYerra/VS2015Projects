/*
CSCI 262 Data Structures, Fall 2016, Project 4 - Markov
brute_model.cpp
Class method implementation for brute_model, the brute-force Markov
text generation model.
Author: C. Painter-Wakefield
Modified: 10/30/2016
*/

#pragma once
#include <cstdlib>
#include "vector.h"
#include "map_model.h"

using namespace std;

// Brute force character generator
string map_model::generate(int sz) {

	// pick random k-character substring as initial seed
	int start = rand() % (_data.length() - _order);
	string seed = _data.substr(start, _order);

	string answer;
	answer.reserve(sz);

	for (int i = 0; i < sz; i++) {
		// choose next character based on probability of occurrence in list
		char c = model[seed][rand() % model[seed].size()];

		// update seed
		seed = seed.substr(1) + c;
		answer = answer + c;
	}
	return answer;
}