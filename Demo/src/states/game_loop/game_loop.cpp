#include "game_loop.hpp"
#include "../pause_menu/pause_menu.hpp"
#include "../../definitions.hpp"
#include <sstream>

game_loop::game_loop(std::shared_ptr<game_data> data)
	: _data(data)
	, _clock()
	, _popup_clock()
	, _health_bar_clock()
	, _health_bar_cnt(1)
	, _show_popup(false)
	, _background()
	, _popup()
	, _health_bar()
	, _health_bar_background()
	, _particles()
	, _running(true)
	, _gui_layer()
	, _popup_layer()
	, _textures()
	, _animated()
{
}

auto game_loop::init() -> void
{
	_data->resource_manager.load_texture("Game Loop Background", GAME_LOOP_BACKGROUND_FILEPATH);
	_data->resource_manager.load_texture("Game Loop Popup Button", GAME_LOOP_POPUP_BUTTON_FILEPATH);
	_data->resource_manager.load_texture("Game Loop Popup Background Button", GAME_LOOP_POPUP_BACKGROUND_BUTTON_FILEPATH);
	_data->resource_manager.load_texture("Game Loop Popup Button Menu", GAME_LOOP_POPUP_MENU_BUTTON_FILEPATH);
	_data->resource_manager.load_texture("Game Loop Popup Button Close", GAME_LOOP_POPUP_CLOSE_BUTTON_FILEPATH);
	_data->resource_manager.load_texture("Game Loop Health Bar", GAME_LOOP_HEALTH_BAR_FILEPATH);
	_data->resource_manager.load_texture("Game Loop Health Bar Background", GAME_LOOP_HEALTH_BAR_BACKGROUND_FILEPATH);
	_data->resource_manager.load_texture("Game Loop Particles", GAME_LOOP_PARTICLES_BUTTON_FILEPATH);
	
	_textures.push_back(_data->resource_manager.get_texture_p("Game Loop Background"));
	_textures.push_back(_data->resource_manager.get_texture_p("Game Loop Popup Button"));
	_textures.push_back(_data->resource_manager.get_texture_p("Game Loop Popup Background Button"));
	_textures.push_back(_data->resource_manager.get_texture_p("Game Loop Popup Button Menu"));
	_textures.push_back(_data->resource_manager.get_texture_p("Game Loop Popup Button Close"));
	_textures.push_back(_data->resource_manager.get_texture_p("Game Loop Health Bar"));
	_textures.push_back(_data->resource_manager.get_texture_p("Game Loop Health Bar Background"));
	_textures.push_back(_data->resource_manager.get_texture_p("Game Loop Particles"));
	
	_data->resource_manager.load_font("Game Loop Name Font", GAME_LOOP_NAME_FONT_FILEPATH);
	
	_background.setTexture(_data->resource_manager.get_texture("Game Loop Background"));
	_popup.setTexture(_data->resource_manager.get_texture("Game Loop Popup Button"));
	_health_bar.setTexture(_data->resource_manager.get_texture("Game Loop Health Bar"));
	_health_bar_background.setTexture(_data->resource_manager.get_texture("Game Loop Health Bar Background"));
	_particles.setTexture(_data->resource_manager.get_texture("Game Loop Particles"));
	
	_background.setPosition(0.0, 0.0);
	_popup.setPosition(0.0, _data->window.getSize().y - _popup.getGlobalBounds().height);
	_health_bar.setPosition(251.0, 11.0);
	_health_bar_background.setPosition(250.0, 10.0);
	_particles.setPosition(((_data->window.getSize().x / 2.0) - (_particles.getGlobalBounds().width / 2.0)), ((_data->window.getSize().y / 2.0) - (_particles.getGlobalBounds().height / 2.0)));
	
	sf::Sprite _popup_background;
	_popup_background.setTexture(_data->resource_manager.get_texture("Game Loop Popup Background Button"));
	sf::Sprite _popup_button;
	_popup_button.setTexture(_data->resource_manager.get_texture("Game Loop Popup Button Menu"));
	
	_gui_layer.add_text("Character Name", 10.0, 10.0, _data->resource_manager.get_font_p("Game Loop Name Font"), "Fluriman Hansson", 20, sf::Color::White, 1, sf::Color::Black);
	
	_popup_layer.add_sprite("Popup Background", 0.0, _data->window.getSize().y - _popup_background.getGlobalBounds().height - _popup.getGlobalBounds().height, _data->resource_manager.get_texture_p("Game Loop Popup Background Button"));
	_popup_layer.add_sprite("Popup Button Close", 1.0, _data->window.getSize().y - _popup_layer.get_sprite("Popup Background").getGlobalBounds().height - _popup.getGlobalBounds().height + _popup_button.getGlobalBounds().height + 2.0, _data->resource_manager.get_texture_p("Game Loop Popup Button Close"));
	_popup_layer.add_sprite("Popup Button Menu", 1.0, _data->window.getSize().y - _popup_layer.get_sprite("Popup Background").getGlobalBounds().height - _popup.getGlobalBounds().height + 2.0, _data->resource_manager.get_texture_p("Game Loop Popup Button Menu"));
	
	_data->resource_manager.load_texture("Animated Sprite", "../res/rpg.png");
	_animated.add("still", 4,_data->resource_manager.get_texture_p("Animated Sprite"), 0.2f, 0, 0, 1, 51, 51); // row 1
	_animated.add("down", 4, _data->resource_manager.get_texture_p("Animated Sprite"),  0.2f, 0, 0, 2, 51, 51); // row 2
	_animated.add("left", 4, _data->resource_manager.get_texture_p("Animated Sprite"), 0.2f, 0, 0, 3, 51, 51); // row 3
	_animated.add("right", 4, _data->resource_manager.get_texture_p("Animated Sprite"), 0.2f, 0, 0, 4, 51, 51); // row 4
	_animated.add("up", 4, _data->resource_manager.get_texture_p("Animated Sprite"),  0.2f, 0, 0, 5, 51, 51); // row 5
	_animated.set_position(350.0, 350.0);
}

auto game_loop::pause() -> void
{
	_running = false;
}

auto game_loop::resume() -> void
{
	_running = true;
}

auto game_loop::handle() -> void
{
	if(_running)
	{
		sf::Event event;
		while(_data->window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
			{
				_data->window.close();
			}
		}
		if(_data->input_manager.clicked(_popup, sf::Mouse::Left, _data->window))
		{
			if(_popup_clock.getElapsedTime().asSeconds() > GAME_LOOP_POPUP_SHOW_TIME) // timer to cope with SFMLs multiple events per second
			{
				_show_popup = !_show_popup;
				_popup_clock.restart();
			}
		}
		if(_data->input_manager.clicked(_particles, sf::Mouse::Left, _data->window))
		{
			_data->particle_system.add(1, 100.0, 1.0, sf::Color::Red, sf::Mouse::getPosition(_data->window).x, sf::Mouse::getPosition(_data->window).y, 5.0, 0.0);
		}
		if(_show_popup)
		{
			if(_popup_clock.getElapsedTime().asSeconds() > GAME_LOOP_POPUP_SHOW_TIME) // timer to cope with SFMLs multiple events per second)
			{
				if(_data->input_manager.clicked(_popup_layer.get_sprite("Popup Button Menu"), sf::Mouse::Left, _data->window))
				{
					_data->state_manager.add(std::unique_ptr<nstate>(new pause_menu(_data)), false);
				}
				if(_data->input_manager.clicked(_popup_layer.get_sprite("Popup Button Close"), sf::Mouse::Left, _data->window))
				{
					_data->window.close();
				}
			}
		}
		
		bool up = false;
		bool left = false;
		bool right = false;
		bool down = false;
		
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			left = true;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			right = true;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			up = true;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			down = true;
		}
		
		if(left)
		{
			_animated.animate("left");
		}
		if(right)
		{
			_animated.animate("right");
		}
		if(up)
		{
			_animated.animate("up");
		}
		if(down)
		{
			_animated.animate("down");
		}
		if(!left && ! right && !up & !down)
		{
			_animated.stop();
		}
	}
}

auto game_loop::update(float dt) -> void
{
	_data->particle_system.update(25.0 * dt);
	if(_health_bar_clock.getElapsedTime().asSeconds() > GAME_LOOP_HEALTH_BAR_TIME)
   	{
		if(_health_bar_cnt >= 1)
		{
			_health_bar.setTextureRect(sf::IntRect(0, 0, _health_bar_cnt, 18));
			_health_bar_cnt--;
		}
		else
		{
			_health_bar.setTextureRect(sf::IntRect(0, 0, 100.0, 18));
			_health_bar_cnt = 100;
		}
		_health_bar_clock.restart();
	}
}

auto game_loop::draw(float dt) -> void
{
	_data->window.setActive(true);
	_data->window.clear(sf::Color::Black);
	_data->window.draw(_background);
	_data->window.draw(_popup);
	_data->window.draw(_gui_layer);
	if(_show_popup)
	{
		_data->window.draw(_popup_layer);
	}
	_data->window.draw(_health_bar_background);
	_data->window.draw(_health_bar);
	_data->window.draw(_particles);
	_data->window.draw(_data->particle_system);
	_data->window.draw(_animated);
	_data->window.display();
	_data->window.setActive(false);
}

