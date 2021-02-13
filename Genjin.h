// Genjin.h
// Created 11/02/2021 by Luke T Matakitoga
// This code is licensed under the GNU General Public License
#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

namespace Genjin
{
	class GenjinEngine;
	void GameLoop(GenjinEngine* handle);

	class GenjinEngine
	{
	public:
		int width = 100;
		int height = 100;
		std::string windowTitle = "Genjin Window";
		bool fullscreen;
		sf::Window window;		
		void create()
		{
			std::cout << "Initialised Engine\n";
			this->window.create(sf::VideoMode(this->width, this->height, 16), this->windowTitle, (fullscreen) ? sf::Style::Fullscreen : sf::Style::Default);
			GameLoop(this);
		}
	};
	void GameLoop(GenjinEngine* handle)
	{
		// run the program as long as the window is open
		while (handle->window.isOpen())
		{
			// check all the window's events that were triggered since the last iteration of the loop
			sf::Event event;
			while (handle->window.pollEvent(event))
			{
				// "close requested" event: we close the window
				if (event.type == sf::Event::Closed)
					handle->window.close();
			}
		}
	}
}