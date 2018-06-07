#include "../ninput_manager.hpp"

#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(960, 540), "Input Manager Test");
	
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        window.clear(sf::Color::Black);
        window.display();
    }
	
	return 0;
}

