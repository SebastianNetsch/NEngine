#include "main_menu.hpp"
#include "../game_loop/game_loop.hpp"
#include "../../definitions.hpp"
#include <sstream>

main_menu::main_menu(std::shared_ptr<game_data> data)
	: _data(data)
	, _clock()
	, _title()
	, _background()
	, _play_button()
	, _textures()
{
}

auto main_menu::init() -> void
{
	_data->resource_manager.load_texture("Main Menu Title", MAIN_MENU_TITLE_FILEPATH);
	_data->resource_manager.load_texture("Main Menu Background", MAIN_MENU_BACKGROUND_FILEPATH);
	_data->resource_manager.load_texture("Main Menu Play Button", MAIN_MENU_PLAY_BUTTON_FILEPATH);
	
	_textures.push_back(_data->resource_manager.get_texture_p("Main Menu Title"));
	_textures.push_back(_data->resource_manager.get_texture_p("Main Menu Background"));
	_textures.push_back(_data->resource_manager.get_texture_p("Main Menu Play Button"));
	
	_title.setTexture(_data->resource_manager.get_texture("Main Menu Title"));
	_background.setTexture(_data->resource_manager.get_texture("Main Menu Background"));
	_play_button.setTexture(_data->resource_manager.get_texture("Main Menu Play Button"));
	
	_title.setPosition(0.0, 0.0);
	_background.setPosition(0.0, 0.0);
	_play_button.setPosition(((_data->window.getSize().x / 2.0) - (_play_button.getGlobalBounds().width / 2.0)), ((_data->window.getSize().y / 2.0) - (_play_button.getGlobalBounds().height / 2.0)));
	
}

auto main_menu::pause() -> void
{
}

auto main_menu::resume() -> void
{
}

auto main_menu::handle() -> void
{
	sf::Event event;
	while(_data->window.pollEvent(event))
	{
		if(event.type == sf::Event::Closed)
		{
			_data->window.close();
		}
		if(_data->input_manager.clicked(_play_button, sf::Mouse::Left, _data->window))
		{
			_data->state_manager.add(std::unique_ptr<nstate>(new game_loop(_data)), true);
		}
	}
}

auto main_menu::update(float dt) -> void
{
}

auto main_menu::draw(float dt) -> void
{
	_data->window.setActive(true);
	_data->window.clear(sf::Color::Black);
	_data->window.draw(_background);
	_data->window.draw(_title);
	_data->window.draw(_play_button);
	_data->window.display();
	_data->window.setActive(false);
}

