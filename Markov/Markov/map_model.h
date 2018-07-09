/*
CSCI 262 Data Structures, Fall 2016, Project 4 - Markov
map_model.h
Author: C. Painter-Wakefield
Modified: 10/30/2016
*/

#pragma once
#include "model.h"
#include "map.h"
#include <string>

using namespace std;

class map_model : public markov_model {
public:
	// give the model the example text and the model order; the model should do any preprocessing in this call
	virtual void initialize(std::string text, int order) {
		// copy first order characters to back to simulate wrap-around
		_data = text + text.substr(0, order);
		_order = order;

		for (int i = 0; i < _data.length() - order; i++) {
			model[_data.substr(i, order)].add(_data[i + order]);
		}
	}
	// produce a text in the style of the example
	virtual std::string generate(int size);

protected:
	std::string _data;
	int _order;
	Map<std::string, Vector<char>> model;
};