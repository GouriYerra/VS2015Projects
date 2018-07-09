#pragma once
#include <cstdlib>
#include "vector.h"
#include "word_model.h"

using namespace std;

string word_model::generate(int sz) {
	// pick random k-character substring as initial seed
	int start = rand() % (mword_model.size() - _order);

	string seed = "";
	for (int j = 0; j < _order; ++j) {  //get map Key
		seed += mword_model[start + j];
	}

	Vector<string> answer;
	for (int i = 0; i < sz; i++) {
		// choose next string based on probability of occurrence in list
		string c = new_word_model[seed].get(rand() % new_word_model[seed].size());
		answer.add(c);

		// update seed
		seed = "";
		start = rand() % (mword_model.size() - _order);
		for (int j = 0; j < _order; ++j) {  //get map Key
			seed += mword_model[start + j];
		}
	}

	string tmpStr;
	for (int i = 0; i < answer.size(); ++i) {
		tmpStr += (answer[i] + " ");
	}
	return tmpStr;
}