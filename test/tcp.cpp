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
	sinusoid.setPosition(100, 500);
	sinusoid.setAxisLength(500, 100);
	sinusoid.setTitle(font, "this is a title");
	

	
	// Setup chart with a position and axis sizes
	float xOffset = 100;
	float yOffset = 100;
	float yAxis = 100;
	float xAxis = 500;

	sf::VertexArray chartAxis(sf::LinesStrip, 4);
	chartAxis[0].position = sf::Vector2f(0 + xOffset, 0 + yOffset);
	chartAxis[1].position = sf::Vector2f(0 + xOffset, yAxis + 2 * yOffset);
	chartAxis[2].position = sf::Vector2f(0 + xOffset, yAxis + yOffset);
	chartAxis[3].position = sf::Vector2f(xAxis + xOffset, yAxis + yOffset);
	chartAxis[0].color = sf::Color::Green;
	chartAxis[1].color = sf::Color::Green;
	chartAxis[2].color = sf::Color::Green;
	chartAxis[3].color = sf::Color::Green;

	sf::VertexArray chart(sf::LinesStrip, 0);
	std::vector<float> dataPoints;

	sf::Text title;
	title.setFont(font);
	char test[] = "Plot of Sin() Over Time";
	title.setString(test);
	title.setCharacterSize(24);
	title.setPosition(125,95-24);

	sf::Text currentValue; 
	currentValue.setFont(font);
	currentValue.setCharacterSize(24);
	currentValue.setPosition(300,300);

	sf::Text CurrentValue;
	CurrentValue.setFont(font);
	CurrentValue.setCharacterSize(24);
	CurrentValue.setPosition(xOffset, 300);
	CurrentValue.setString("Current Value:");
	

	sf::Text rmstValue;
	rmstValue.setFont(font);
	rmstValue.setCharacterSize(24);
	rmstValue.setPosition(300, 300 + 30);

	sf::Text RmstValue;
	RmstValue.setFont(font);
	RmstValue.setCharacterSize(24);
	RmstValue.setPosition(xOffset, 300 + 30);
	RmstValue.setString("RMS Value:");


	float RMSvalue = 0;
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
		
		dataPoints.push_back(100 - ((100) * cos(i * 2 * 3.141592 / xAxis)));
		sinusoid.addDatapoint((100 - ((100) * cos(i * 2 * 3.141592 / xAxis))));
		
		i++;

		while (dataPoints.size() > xAxis) {
			dataPoints.erase(dataPoints.begin());
		}

		//update the chart
		chart.clear();
		RMSvalue = 0;
		for (int i = 0; i < dataPoints.size(); i++) {
			float x = i;
			float y = *(dataPoints.begin() + i);
			currentValue.setString(std::to_string(yOffset - y) );

			RMSvalue += pow((yOffset - y), 2.0);
			chart.append(sf::Vertex(sf::Vector2f(x + xOffset, y + yOffset), sf::Color::Blue));
		}
		RMSvalue = sqrtf((1.0 / xAxis) * RMSvalue);
		rmstValue.setString(std::to_string(RMSvalue));
		
		std::cout << "dataPoints Size: " << dataPoints.size() << std::endl;
		window.clear();
		sinusoid.update(window);
		sinusoid.drawStats(window, font);
		window.draw(chartAxis);
		window.draw(chart);
		window.draw(title);
		window.draw(currentValue);
		window.draw(CurrentValue);
		window.draw(rmstValue);
		window.draw(RmstValue);
		sinusoid.draw(window);

		window.display();
	}

	return 0;
}

