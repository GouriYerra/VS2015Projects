#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <map>
#include <random>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Grid.h"

using namespace std;
using namespace sf;

int main() {
	Grid g;
	g.initialize();

	clock_t checkpoint = 0;
	RenderWindow window(VideoMode(640, 500), "Segregation Simulation");

	// load this only once
	g.font.loadFromFile("data/DroidSans.ttf");

	// run the program as long as the window is open
	while (window.isOpen()) {
		// check all the window's events that were triggered 
		// since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event)) {
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// give an iteration a little time (250 ms)
		if (checkpoint == 0) {
			checkpoint = clock();
		}
		else if (clock() - checkpoint < CLOCKS_PER_SEC / 4) {
			continue;
		}
		else {
			checkpoint = clock();
		}

		// start with a fresh slate each iteration
		window.clear(Color(255, 255, 255));

		string msg = "Woo Hoo";
		g.draw(window, msg);

		g.scan(window);
	}

	return 0;
}