#include "../nparticle_system.hpp"

#include <iostream>

int main()
{
    nengine::nparticle_system::nparticle_system part_system(0.0, 0.1, 1000);
	
    sf::RenderWindow window(sf::VideoMode(960, 540), "Particle System Test");
	
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			part_system.add(10, 100.0, 1.0, sf::Color::White, sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, 5.0, 0.0);
		}
        part_system.update(1.0);
        std::cout << part_system.get_amount() << std::endl;
        
        window.clear(sf::Color::Black);
        window.draw(part_system);
        window.display();
    }
	
	return 0;
}

