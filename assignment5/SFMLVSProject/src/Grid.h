#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <random>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

struct Cord
{
public:
	int row;
	int col;

	inline Cord(int xx, int yy) { row = xx; col = yy; }

	friend bool operator< (const Cord& lhs, const Cord& rhs);
};

class Grid {
private:
	// based on above percentages - calculate how many blue, red and empty boxes
	int blueBoxCtr, redBoxCtr, emptyBoxCtr;

	// static constants to represent color
	static const int RED = 1;
	static const int BLUE = 2;
	static const int EMP = 0;

	map<Cord, int> GRID;  // this holds the values of colors in the GRID.

public:
	static int size;	//grid Size
	static int simPer;		// similarity percentage
	static int redPer;		// red percentage
	static int bluePer;	// blue percentage
	static int emptyPer;	// empty percentage
	bool scanContinue = true;
	Font font;
	std::default_random_engine generator2;

	void initialize();		// this must be called first to initialize 
	void draw(RenderWindow& window, string message);			// this will draw the grid based on colors in GRID map
	void scan(RenderWindow& window);
	vector<Cord> Grid::getSourindingBoxes(Cord c);
	void Grid::drawRect(RenderWindow& window, Cord c);
	int Grid::getSourindingSimilarColor(Cord c, int color);

};