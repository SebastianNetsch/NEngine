#include "../nresource_wrapper.hpp"
#include <SFML/Graphics.hpp>

int main()
{
	nengine::nresource_manager::nresource_wrapper<sf::Texture> resource_management;
	resource_management.load_texture("Hallo", "../test.png");
	resource_management.load_font("Hallo", "../test.otf");
	resource_management.load_soundbuffer("Hallo", "../test.wav");
	
	sf::Sprite sprite;
	sprite.setTexture(resource_management.get_texture("Hallo"));
	sf::Sprite sprite2;
	sprite2.setTexture(resource_management.get_texture("Hallo"));
	sprite2.setPosition(sf::Vector2f(50.0, 50.0));
	
	sf::Text text;
	text.setFont(resource_management.get_font("Hallo"));
	
    sf::RenderWindow window(sf::VideoMode(960, 540), "Resource Manager Test");
	
	sf::Sound sound;
	sound.setBuffer(resource_management.get_soundbuffer("Hallo"));
	sound.play();
	
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        window.clear(sf::Color::Black);
        window.draw(sprite);
        window.draw(sprite2);
        window.display();
    }
	return 0;
}

