#include "pause_menu.hpp"
#include "../main_menu/main_menu.hpp"
#include "../../definitions.hpp"
#include <sstream>

pause_menu::pause_menu(std::shared_ptr<game_data> data)
	: _data(data)
	, _clock()
	, _title()
	, _background()
	, _resume_button()
	, _home_button()
	, _textures()
{
}

auto pause_menu::init() -> void
{
	_data->resource_manager.load_texture("Pause Menu Title", PAUSE_MENU_TITLE_FILEPATH);
	_data->resource_manager.load_texture("Pause Menu Background", PAUSE_MENU_BACKGROUND_FILEPATH);
	_data->resource_manager.load_texture("Pause Menu Resume Button", PAUSE_MENU_RESUME_BUTTON_FILEPATH);
	_data->resource_manager.load_texture("Pause Menu Home Button", PAUSE_MENU_HOME_BUTTON_FILEPATH);
	
	_textures.push_back(_data->resource_manager.get_texture_p("Pause Menu Title"));
	_textures.push_back(_data->resource_manager.get_texture_p("Pause Menu Background"));
	_textures.push_back(_data->resource_manager.get_texture_p("Pause Menu Resume Button"));
	_textures.push_back(_data->resource_manager.get_texture_p("Pause Menu Home Button"));
	
	_title.setTexture(_data->resource_manager.get_texture("Pause Menu Title"));
	_background.setTexture(_data->resource_manager.get_texture("Pause Menu Background"));
	_resume_button.setTexture(_data->resource_manager.get_texture("Pause Menu Resume Button"));
	_home_button.setTexture(_data->resource_manager.get_texture("Pause Menu Home Button"));
	
	_title.setPosition(0.0, 0.0);
	_background.setPosition(0.0, 0.0);
	_resume_button.setPosition(((_data->window.getSize().x / 2.0) - (_resume_button.getGlobalBounds().width / 2.0)), ((_data->window.getSize().y / 2.0) - (_resume_button.getGlobalBounds().height / 2.0)));
	_home_button.setPosition(((_data->window.getSize().x / 2.0) - (_home_button.getGlobalBounds().width / 2.0)), ((_data->window.getSize().y / 2.0 + _resume_button.getGlobalBounds().height + 2.0) - (_home_button.getGlobalBounds().height / 2.0)));
}

auto pause_menu::pause() -> void
{
}

auto pause_menu::resume() -> void
{
}

auto pause_menu::handle() -> void
{
	sf::Event event;
	while(_data->window.pollEvent(event))
	{
		if(event.type == sf::Event::Closed)
		{
			_data->window.close();
		}
		if(_data->input_manager.clicked(_resume_button, sf::Mouse::Left, _data->window))
		{
			_data->state_manager.remove();
		}
		if(_data->input_manager.clicked(_home_button, sf::Mouse::Left, _data->window))
		{
			_data->state_manager.remove();
			_data->state_manager.add(std::unique_ptr<nstate>(new main_menu(_data)), true);
			_data->particle_system.clr();
		}
	}
}

auto pause_menu::update(float dt) -> void
{
}

auto pause_menu::draw(float dt) -> void
{
	_data->window.setActive(true);
	_data->window.clear(sf::Color::Black);
	_data->window.draw(_background);
	_data->window.draw(_title);
	_data->window.draw(_resume_button);
	_data->window.draw(_home_button);
	_data->window.display();
	_data->window.setActive(false);
}

