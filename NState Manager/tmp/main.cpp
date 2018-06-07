#include "../nstate_manager.hpp"
#include "../nstate.hpp"

#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(960, 540), "State Manager Test");
	
	nengine::nstate_manager::nstate_manager state_manager;
	
	nengine::nstate_manager::nstate state;
	
	state_manager.push(state);
	
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
        	state_manager.get()->handle(event);
        }
        state_manager.get()->update();
        window.clear(sf::Color::Black);
        window.draw(*state_manager.get());
        window.display();
    }
	
	return 0;
}

