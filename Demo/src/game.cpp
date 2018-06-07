#include "game.hpp"
#include "states/splash/splash.hpp"

game::game(int width, int height, std::string title)
	: _dt(1.0f / 60.0f)
	, _clock()
	, _data(std::make_shared<game_data>())
{
	_data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
	_data->window.setVerticalSyncEnabled(true);
	_data->state_manager.add(std::unique_ptr<nstate>(new splash(_data)), true);
}

auto game::run() -> void
{
	float new_time = 0.0;
	float frame_time = 0.0;
	float current_time = _clock.getElapsedTime().asSeconds();
	float accumulator = 0.0;
	_data->particle_system.set_gravity(0.1, 0.1);
	_data->particle_system.set_max(2000);
	while(_data->window.isOpen())
	{
		_data->state_manager.process();
		
		_data->resource_manager.clr_unused();
		
		new_time = _clock.getElapsedTime().asSeconds();
		frame_time = new_time - current_time;
		
		if(frame_time > 0.25)
		{
			frame_time = 0.25;
		}
		
		current_time = new_time;
		accumulator += frame_time;
		
		while(accumulator >= _dt)
		{
			_data->state_manager.get()->handle();
			_data->state_manager.get()->update(_dt);
			
			accumulator -= _dt;
		}
		
		_data->state_manager.get()->draw(accumulator);
	}
}
