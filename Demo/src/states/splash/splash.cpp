#include "splash.hpp"
#include "../main_menu/main_menu.hpp"
#include "../../definitions.hpp"

splash::splash(std::shared_ptr<game_data> data)
	: _data(data)
	, _clock()
	, _background()
	, _textures()
{
}

auto splash::init() -> void
{
	_data->resource_manager.load_texture("Splash Screen Background", SPLASH_SCENE_BACKGROUND_FILEPATH);
	
	_background.setTexture(_data->resource_manager.get_texture("Splash Screen Background"));
	
	_background.setPosition(0.0, 0.0);
	
	_textures.push_back(_data->resource_manager.get_texture_p("Splash Screen Background"));
}

auto splash::pause() -> void
{
}

auto splash::resume() -> void
{
}

auto splash::handle() -> void
{
	sf::Event event;
	while(_data->window.pollEvent(event))
	{
		if(event.type == sf::Event::Closed)
		{
			_data->window.close();
		}
	}
}

auto splash::update(float dt) -> void
{
	if(_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME)
	{
		_data->state_manager.add(std::unique_ptr<nstate>(new main_menu(_data)), true);
	}
}

auto splash::draw(float dt) -> void
{
	_data->window.setActive(true);
	_data->window.clear(sf::Color::Black);
	_data->window.draw(_background);
	_data->window.display();
	_data->window.setActive(false);
}

