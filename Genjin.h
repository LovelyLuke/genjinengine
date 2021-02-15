// Genjin.h
// Created 11/02/2021 by Luke T Matakitoga
// This code is licensed under the GNU General Public License
#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <map>

namespace Genjin
{
	class GenjinEngine;
	void GameLoop(GenjinEngine* handle);

	std::map<std::string, sf::Color> Map = {
		{"Empty", {0, 0, 0, 0}},
		{"Ground", {0, 0, 0}},
		{"Start", {0, 255, 0}},
		{"End", {255, 0, 0}}
	};

	class GenjinEngine
	{
	public:
		int width = 640;
		int height = 480;
		std::string windowTitle = "Genjin Window";
		bool fullscreen;
		bool vignette;
		sf::RenderWindow rWindow;
		sf::Window window;		
		std::time_t timeAtStart;
		void create()
		{
			std::cout << "Initialised Engine\n";
			this->rWindow.create(sf::VideoMode(this->width, this->height, 16), this->windowTitle, (fullscreen) ? sf::Style::Fullscreen : sf::Style::Default);
			timeAtStart = std::time(nullptr);
			GameLoop(this);
		}
		void reload()
		{
			std::cout << "Reloading Engine\n";
			this->rWindow.create(sf::VideoMode(this->width, this->height, 16), this->windowTitle, (fullscreen) ? sf::Style::Fullscreen : sf::Style::Default);
			GameLoop(this);
		}
		void Vignette(sf::Color c1 = sf::Color::Black, sf::Color c2 = sf::Color::Transparent, float length = 200) {
			sf::Vertex topgrad[] =
			{
				sf::Vertex(sf::Vector2f(0, 0), c1),
				sf::Vertex(sf::Vector2f(width, 0), c1),
				sf::Vertex(sf::Vector2f(width, length), c2),
				sf::Vertex(sf::Vector2f(0, length), c2)
			};
			sf::Vertex rightgrad[] =
			{
				sf::Vertex(sf::Vector2f(width, 0), c1),
				sf::Vertex(sf::Vector2f(width, height), c1),
				sf::Vertex(sf::Vector2f(width-length, height), c2),
				sf::Vertex(sf::Vector2f(width-length, 0), c2)
			};
			sf::Vertex leftgrad[] =
			{
				sf::Vertex(sf::Vector2f(0, 0), c1),
				sf::Vertex(sf::Vector2f(0, height), c1),
				sf::Vertex(sf::Vector2f(length, height), c2),
				sf::Vertex(sf::Vector2f(length, 0), c2)
			};
			sf::Vertex bottomgrad[] =
			{
				sf::Vertex(sf::Vector2f(0, height), c1),
				sf::Vertex(sf::Vector2f(width, height), c1),
				sf::Vertex(sf::Vector2f(width, height-length), c2),
				sf::Vertex(sf::Vector2f(0, height-length), c2)
			};
			rWindow.draw(topgrad, 4, sf::Quads);
			rWindow.draw(rightgrad, 4, sf::Quads);
			rWindow.draw(leftgrad, 4, sf::Quads);
			rWindow.draw(bottomgrad, 4, sf::Quads);
		}
	};
	void GameLoop(GenjinEngine* handle)
	{
		// run the program as long as the window is open
		while (handle->rWindow.isOpen())
		{
			// check all the window's events that were triggered since the last iteration of the loop
			sf::Event event;
			while (handle->rWindow.pollEvent(event))
			{
				// "close requested" event: we close the window
				if (event.type == sf::Event::Closed)
					handle->rWindow.close();
			}

			handle->rWindow.clear(sf::Color::White);

			

			if (std::time(nullptr) - handle->timeAtStart < 3) {
				// Load splash screen
				sf::Texture splashTexture;
				if (!splashTexture.loadFromFile("splash.png"))
				{
					std::cout << "Failed to read splash screen image\n";
				}
				sf::Sprite splashSprite;
				splashSprite.setTexture(splashTexture);
				splashSprite.setPosition(handle->width / 2 - (splashTexture.getSize().x/2), handle->height / 2 - (splashTexture.getSize().y/2));
				handle->rWindow.draw(splashSprite);
			}
			else {
				// Do Game Updates
				sf::RectangleShape bg;
				bg.setSize(sf::Vector2f(handle->width, handle->height));
				bg.setFillColor(sf::Color{191, 255, 250});
				handle->rWindow.draw(bg);
			}
			

			// Display the window
			handle->rWindow.display();
		}
	}
}