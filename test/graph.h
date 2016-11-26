#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

class graph {
public:
	float xOffset, yOffset, xAxis, yAxis, currentVal, RMSvalue;
	int chartLength; // length sounds like number of elements? if so then int it is.
	std::vector<float> dataPoints;
	sf::Text title;


	graph(float x, float y, float w, float h) : xOffset(x), yOffset(y), xAxis(x), yAxis(y), chartLength(100) {
	}

	void setPosition(float x, float y);
	float getPosition();
	void setAxisLength(float xlen, float ylen);
	float getAxisLength();
	void setTitle(sf::Font &font, char text[]);
	void drawStats(sf::RenderWindow &window, sf::Font &font);
	void draw(sf::RenderWindow &window);
	void addDatapoint(float data);
	void update(sf::RenderWindow &window);

};