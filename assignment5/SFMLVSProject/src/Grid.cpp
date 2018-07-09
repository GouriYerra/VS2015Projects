#include "Grid.h"

int Grid::size = 30;  // Grid size default to 30
int Grid::simPer = 30;		// similarity percentage default to 30
int Grid::redPer = 50;		// red percentage default
int Grid::emptyPer = 10;	// empty percentage default
int Grid::bluePer = 40;	// blue percentage 

int getNo()
{
	int dd;
	string tmp;

	std::getline(std::cin, tmp);
	if (tmp.length() == 0)
		return 0;

	return atoi(tmp.c_str());
}

bool operator< (const Cord& lhs, const Cord& rhs)
{
	int left = lhs.row + lhs.col * Grid::size;
	int right = rhs.row + rhs.col * Grid::size;

	return (left < right);
}

void Grid::initialize()
{
	int no;
	cout << "Enter similarity percentage(default = 30) :";
	no = getNo();
	if (no != 0)
		simPer = no;

	cout << "Enter Red percentage(default = 50) :";
	no = getNo();
	if (no != 0)
		redPer = no;

	cout << "Enter empty percentage(default = 10) :";
	no = getNo();
	if (no != 0)
		emptyPer = no;

	bluePer = 100 - redPer - emptyPer;

	cout << "Enter grid size (default = 30):";
	no = getNo();
	if (no != 0)
		size = no;

	blueBoxCtr = ((size * size) * bluePer) / 100;
	redBoxCtr = ((size * size) * redPer) / 100;
	emptyBoxCtr = ((size * size) * emptyPer) / 100;

	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(0, size - 1);

	// Initialize the GRID (map) with blue
	for (int i = 0; i < blueBoxCtr; ++i) {
		do {
			int x = distribution(generator);
			int y = distribution(generator);
			Cord c(x, y);

			if (GRID[c] == EMP) {
				GRID[c] = BLUE;
				break;
			}
		} while (1);
	}

	// Initialize the GRID (map) with red
	for (int i = 0; i < redBoxCtr; ++i) {
		do {
			int x = distribution(generator);
			int y = distribution(generator);
			Cord c(x, y);

			if (GRID[c] == EMP) {
				GRID[c] = RED;
				break;
			}
		} while (1);
	}


}

void Grid::drawRect(RenderWindow& window, Cord c)
{
	Vector2u winSz = window.getSize();
	double side = winSz.y / ((double)size);
	RectangleShape rect(Vector2f(side, side));
	double x = c.row * side;
	double y = c.col * side;
	rect.setPosition(y, x); //(x, y);
	int color = GRID[c];

	if (color == BLUE)
		rect.setFillColor(sf::Color::Blue);
	else if (color == RED)
		rect.setFillColor(sf::Color::Red);
	else
		rect.setFillColor(sf::Color::White);

	rect.setOutlineColor(Color(200, 200, 200));
	rect.setOutlineThickness(1);

	window.draw(rect);
}

void Grid::draw(RenderWindow& window, string message)
{
	// TODO: modify the code below which displays rectangles
	// and text.  Your code will display the updated simulation
	// grid for each step and text noting the iteration and
	// the percent satisfied.

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			Cord c(i, j);

			drawRect(window, c);
		}
	}

	Vector2u winSz = window.getSize();
	double side = winSz.y / ((double)size);

	// message text
	Text text(message, font, 16);
	text.setPosition(side * 30 + 10, winSz.y / 2);
	text.setColor(Color(0, 0, 0));
	window.draw(text);
	window.display();
}

// get all non empty box count
vector<Cord> Grid::getSourindingBoxes(Cord c)
{
	vector<Cord> sou;

	for (int i = c.row - 1; i < c.row + 2; ++i) {
		for (int j = c.col - 1; j < c.col + 2; ++j) {
			if (i == c.row && j == c.col)
				continue;

			if (i < 0 || j < 0)
				continue;

			if (i >(size - 1) || j >(size - 1))
				continue;

			Cord tmp(i, j);
			if (GRID[tmp] == EMP)
				continue;

			sou.push_back(tmp);
		}
	}

	return sou;
}

// get count of same color ones
int Grid::getSourindingSimilarColor(Cord c, int color)
{
	int count = 0;

	for (int i = c.row - 1; i < c.row + 2; ++i) {
		for (int j = c.col - 1; j < c.col + 2; ++j) {
			if (i == c.row && j == c.col)
				continue;

			if (i < 0 || j < 0)
				continue;

			if (i >(size - 1) || j >(size - 1))
				continue;

			Cord tmp(i, j);
			if (GRID[tmp] == color)
				++count;
		}
	}

	return count;
}


void Grid::scan(RenderWindow& window)
{
	std::uniform_int_distribution<int> distribution(0, size - 1);

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			// Pick a cell and its color
			Cord c(i, j);
			int cellColor = GRID[c];
			if (cellColor == EMP) // if this is empty cell then nothing to do
				continue;

			// Get sourrounding cells
			vector<Cord> s = getSourindingBoxes(c);

			//how many similar boxes neded to be happy
			int happyCount = ceil(s.size() * simPer / 100.0);

			int x = 0;
			for (int i = 0; i < s.size(); ++i) {
				if (GRID[s[i]] == cellColor)
					++x;
			}

			if (x < happyCount) {
				// this guy not happy so needs to be moved
				do {
					int xCord = distribution(generator2);
					int yCord = distribution(generator2);
					Cord n(xCord, yCord);

					if (GRID[n] == EMP) {
						// Check if any same color around me then only move else 
						// he wont like it
						if (getSourindingSimilarColor(n, cellColor) > 0)
						{
							GRID[n] = cellColor;
							GRID[c] = EMP;
							drawRect(window, c);
							drawRect(window, n);
							draw(window, "Woo Ho");
							break;
						}
					}
				} while (1);
			}
		}
	}
}