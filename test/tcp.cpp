// test.cpp : Defines the entry point for the console application.
//

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "graph.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "Drawing Graphs");
	sf::Font font;

	// Load font file from disk
	if (!font.loadFromFile("courier.ttf"))
	{
		std::cout << "Error loading font: courier.tff \n";
	}


	graph sinusoid(100, 100, 300, 100);
	graph coss(100, 100, 500, 100);

	sinusoid.setPosition(100, 500);
	sinusoid.setAxisLength(500, 100);
	sinusoid.setTitle(font, "this is a title");
	
	coss.setPosition(100, 100);
	coss.setAxisLength(500, 100);
	coss.setTitle(font, "this is a title");
	
	int i = 0;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (event.type == sf::Event::Resized)
		{
			std::cout << "new width: " << event.size.width << std::endl;
			std::cout << "new height: " << event.size.height << std::endl;
		}

		// HERE 
		
		sinusoid.addDatapoint((100 - ((100) * sin(i * 2 * 3.141592 / 500))));
		coss.addDatapoint((100 - ((100) * cos(i * 2 * 3.141592 / 500))));
		
		i++;

		//update the chart

		
		window.clear();

		sinusoid.update(window);
		sinusoid.drawStats(window, font);
		sinusoid.draw(window);

		coss.update(window);
		coss.drawStats(window, font);
		coss.draw(window);


		window.display();
	}

	return 0;
}

