
#pragma once

#include "model.h"
#include "vector.h"
#include "map.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class word_model : public markov_model {
public:
	// give the model the example text and the model order; the model should do any preprocessing in this call
	virtual void initialize(std::string text, int order) {
		// copy first order characters to back to simulate wrap-around
		_data = text + text.substr(0, order);
		_order = order;

		std::istringstream s_in(_data);
		while (!s_in.eof()) {
			std::string word;
			s_in >> word;
			mword_model.push_back(word);
		}

		for (int i = 0; i < mword_model.size() - order; i++) {
			//model[_data.substr(i, order)].add(_data[i + order]);
			string tmp = "";
			for (int j = 0; j < order; ++j) {  //get map Key
				tmp += mword_model[i + j];
			}
			new_word_model[tmp].add(mword_model[i + order]);
		}
	}

	// produce a text in the style of the example
	virtual std::string generate(int size);

protected:
	std::string _data;
	int _order;
	Map<std::string, Vector<std::string>> new_word_model;
	Vector<std::string> mword_model;
};
