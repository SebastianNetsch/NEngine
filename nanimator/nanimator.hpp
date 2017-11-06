/////////////////////////////////////////////////////////////////////////////////
//
// NEngine C++ Library
// Copyright (c) 2017-2017 Sebastian Netsch
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////
#ifndef __NENGINE__NANIMATOR_NANIMATED_SPRITE__
#define __NENGINE__NANIMATOR_NANIMATED_SPRITE__

/////////////////////////////////////////////////////////////////////////////////
// ! SFML/Graphics.hpp for SFML structures
// ! memory for shared pointers
// ! mutex for thread safety
/////////////////////////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <memory>
#include <mutex>

/////////////////////////////////////////////////////////////////////////////////
// ! namespace for the nengine
/////////////////////////////////////////////////////////////////////////////////
namespace nengine {

/////////////////////////////////////////////////////////////////////////////////
// ! namespace for the nanimator
/////////////////////////////////////////////////////////////////////////////////
namespace nanimator {

/////////////////////////////////////////////////////////////////////////////////
// ! namespace using for easier and cleaner programming
/////////////////////////////////////////////////////////////////////////////////
using namespace nengine;
using namespace nengine::nanimator;

/////////////////////////////////////////////////////////////////////////////////
// ! the nanimated_sprites' pose
/////////////////////////////////////////////////////////////////////////////////
enum class pose
{
	NONE,
	STILL,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

/////////////////////////////////////////////////////////////////////////////////
// ! the nanimated
/////////////////////////////////////////////////////////////////////////////////
class nanimated : public sf::Drawable
{
	public:
		/////////////////////////////////////////////////////////////////////////////////
		// ! delete default constructor
		/////////////////////////////////////////////////////////////////////////////////
		nanimated(const nanimated&) = delete;
		/////////////////////////////////////////////////////////////////////////////////
		// ! delete copy constructor
		/////////////////////////////////////////////////////////////////////////////////
		nanimated& operator=(const nanimated&) = delete;
		/////////////////////////////////////////////////////////////////////////////////
		// ! custom constructor: with initialization list
		/////////////////////////////////////////////////////////////////////////////////
		nanimated()
			: _mutex()
			, _still_animation()
			, _left_animation()
			, _right_animation()
			, _up_animation()
			, _down_animation()
			, _still_texture()
			, _left_texture()
			, _right_texture()
			, _up_texture()
			, _down_texture()
			, _still_iterator()
			, _left_iterator()
			, _right_iterator()
			, _up_iterator()
			, _down_iterator()
			, _still_duration()
			, _left_duration()
			, _right_duration()
			, _up_duration()
			, _down_duration()
			, _animation_clock()
			, _sprite()
			, _pose(pose::NONE)
		{
		}
		/////////////////////////////////////////////////////////////////////////////////
		// 
		/////////////////////////////////////////////////////////////////////////////////
		auto set_position(float x, float y) -> void
		{
			std::unique_lock<std::mutex> lock(_mutex);
			{ // locked area
				_sprite.setPosition(sf::Vector2f(x, y));
			} // lock freed
		}
		/////////////////////////////////////////////////////////////////////////////////
		// 
		/////////////////////////////////////////////////////////////////////////////////
		auto still() -> void
		{
			std::unique_lock<std::mutex> lock(_mutex);
			{ // locked area
				if(_still_animation.size() == 0)
				{
					return;
				}
				if(_pose != pose::STILL)
				{
					_pose = pose::STILL;
					_sprite.setTexture(*_still_texture);
					_sprite.setTextureRect(_still_animation.at(0));
				}
				if(_animation_clock.getElapsedTime().asSeconds() >= _still_duration)
				{
					_sprite.setTextureRect(_still_animation.at(_still_iterator));
					_still_iterator++;
					if(_still_iterator >= _still_animation.size())
					{
						_still_iterator = 0;
					}
					_animation_clock.restart();
				}
			} // lock freed
		}
		/////////////////////////////////////////////////////////////////////////////////
		// 
		/////////////////////////////////////////////////////////////////////////////////
		auto left() -> void
		{
			std::unique_lock<std::mutex> lock(_mutex);
			{ // locked area
				if(_left_animation.size() == 0)
				{
					return;
				}
				if(_pose != pose::LEFT)
				{
					_pose = pose::LEFT;
					_sprite.setTexture(*_left_texture);
					_sprite.setTextureRect(_left_animation.at(0));
				}
				if(_animation_clock.getElapsedTime().asSeconds() >= _left_duration)
				{
					_sprite.setTextureRect(_left_animation.at(_left_iterator));
					_left_iterator++;
					if(_left_iterator >= _left_animation.size())
					{
						_left_iterator = 0;
					}
					_animation_clock.restart();
				}
			} // lock freed
		}
		/////////////////////////////////////////////////////////////////////////////////
		// 
		/////////////////////////////////////////////////////////////////////////////////
		auto right() -> void
		{
			std::unique_lock<std::mutex> lock(_mutex);
			{ // locked area
				if(_right_animation.size() == 0)
				{
					return;
				}
				if(_pose != pose::RIGHT)
				{
					_pose = pose::RIGHT;
					_sprite.setTexture(*_right_texture);
					_sprite.setTextureRect(_right_animation.at(0));
				}
				if(_animation_clock.getElapsedTime().asSeconds() >= _right_duration)
				{
					_sprite.setTextureRect(_right_animation.at(_right_iterator));
					_right_iterator++;
					if(_right_iterator >= _right_animation.size())
					{
						_right_iterator = 0;
					}
					_animation_clock.restart();
				}
			} // lock freed
		}
		/////////////////////////////////////////////////////////////////////////////////
		// 
		/////////////////////////////////////////////////////////////////////////////////
		auto up() -> void
		{
			std::unique_lock<std::mutex> lock(_mutex);
			{ // locked area
				if(_up_animation.size() == 0)
				{
					return;
				}
				if(_pose != pose::UP)
				{
					_pose = pose::UP;
					_sprite.setTexture(*_up_texture);
					_sprite.setTextureRect(_up_animation.at(0));
				}
				if(_animation_clock.getElapsedTime().asSeconds() >= _up_duration)
				{
					_sprite.setTextureRect(_up_animation.at(_up_iterator));
					_up_iterator++;
					if(_up_iterator >= _up_animation.size())
					{
						_up_iterator = 0;
					}
					_animation_clock.restart();
				}
			} // lock freed
		}
		/////////////////////////////////////////////////////////////////////////////////
		// 
		/////////////////////////////////////////////////////////////////////////////////
		auto down() -> void
		{
			std::unique_lock<std::mutex> lock(_mutex);
			{ // locked area
				if(_down_animation.size() == 0)
				{
					return;
				}
				if(_pose != pose::DOWN)
				{
					_pose = pose::DOWN;
					_sprite.setTexture(*_down_texture);
					_sprite.setTextureRect(_down_animation.at(0));
				}
				if(_animation_clock.getElapsedTime().asSeconds() >= _down_duration)
				{
					_sprite.setTextureRect(_down_animation.at(_down_iterator));
					_down_iterator++;
					if(_down_iterator >= _down_animation.size())
					{
						_down_iterator = 0;
					}
					_animation_clock.restart();
				}
			} // lock freed
		}
		/////////////////////////////////////////////////////////////////////////////////
		// 
		/////////////////////////////////////////////////////////////////////////////////
		auto add_still(unsigned int steps, std::shared_ptr<const sf::Texture> texture, unsigned int step_size, float step_duration, int x_coordinate, int y_coordinate, int width, int height) -> void
		{
			std::unique_lock<std::mutex> lock(_mutex);
			{ // locked area
				_still_duration = step_duration;
				_still_texture = std::move(texture);
				_still_iterator = 0;
				for(unsigned int i = 0; i < steps; i++)
				{
					_still_animation.push_back(sf::IntRect(x_coordinate + width * i, y_coordinate, width, height));
				}
			} // lock freed
		}
		/////////////////////////////////////////////////////////////////////////////////
		// 
		/////////////////////////////////////////////////////////////////////////////////
		auto add_still(unsigned int steps, std::shared_ptr<const sf::Texture> texture, unsigned int step_size, unsigned int sheet_row, float step_duration, int x_coordinate, int y_coordinate, int width, int height) -> void
		{
			std::unique_lock<std::mutex> lock(_mutex);
			{ // locked area
				_still_duration = step_duration;
				_still_texture = std::move(texture);
				_still_iterator = 0;
				for(unsigned int i = 0; i < steps; i++)
				{
					_still_animation.push_back(sf::IntRect(x_coordinate + width * i, y_coordinate *+ sheet_row * height, width, height));
				}
			} // lock freed
		}
		/////////////////////////////////////////////////////////////////////////////////
		// 
		/////////////////////////////////////////////////////////////////////////////////
		auto add_left(unsigned int steps, std::shared_ptr<const sf::Texture> texture, unsigned int step_size, float step_duration, int x_coordinate, int y_coordinate, int width, int height) -> void
		{
			std::unique_lock<std::mutex> lock(_mutex);
			{ // locked area
				_left_duration = step_duration;
				_left_texture = std::move(texture);
				_left_iterator = 0;
				for(unsigned int i = 0; i < steps; i++)
				{
					_left_animation.push_back(sf::IntRect(x_coordinate + width * i, y_coordinate, width, height));
				}
			} // lock freed
		}
		/////////////////////////////////////////////////////////////////////////////////
		// 
		/////////////////////////////////////////////////////////////////////////////////
		auto add_left(unsigned int steps, std::shared_ptr<const sf::Texture> texture, unsigned int step_size, unsigned int sheet_row, float step_duration, int x_coordinate, int y_coordinate, int width, int height) -> void
		{
			std::unique_lock<std::mutex> lock(_mutex);
			{ // locked area
				_left_duration = step_duration;
				_left_texture = std::move(texture);
				_left_iterator = 0;
				for(unsigned int i = 0; i < steps; i++)
				{
					_left_animation.push_back(sf::IntRect(x_coordinate + width * i, y_coordinate + sheet_row * height, width, height));
				}
			} // lock freed
		}
		/////////////////////////////////////////////////////////////////////////////////
		// 
		/////////////////////////////////////////////////////////////////////////////////
		auto add_right(unsigned int steps, std::shared_ptr<const sf::Texture> texture, unsigned int step_size, float step_duration, int x_coordinate, int y_coordinate, int width, int height) -> void
		{
			std::unique_lock<std::mutex> lock(_mutex);
			{ // locked area
				_right_duration = step_duration;
				_right_texture = std::move(texture);
				_right_iterator = 0;
				for(unsigned int i = 0; i < steps; i++)
				{
					_right_animation.push_back(sf::IntRect(x_coordinate + width * i, y_coordinate, width, height));
				}
			} // lock freed
		}
		/////////////////////////////////////////////////////////////////////////////////
		// 
		/////////////////////////////////////////////////////////////////////////////////
		auto add_right(unsigned int steps, std::shared_ptr<const sf::Texture> texture, unsigned int step_size, unsigned int sheet_row, float step_duration, int x_coordinate, int y_coordinate, int width, int height) -> void
		{
			std::unique_lock<std::mutex> lock(_mutex);
			{ // locked area
				_right_duration = step_duration;
				_right_texture = std::move(texture);
				_right_iterator = 0;
				for(unsigned int i = 0; i < steps; i++)
				{
					_right_animation.push_back(sf::IntRect(x_coordinate + width * i, y_coordinate + sheet_row * height, width, height));
				}
			} // lock freed
		}
		/////////////////////////////////////////////////////////////////////////////////
		// 
		/////////////////////////////////////////////////////////////////////////////////
		auto add_up(unsigned int steps, std::shared_ptr<const sf::Texture> texture, unsigned int step_size, float step_duration, int x_coordinate, int y_coordinate, int width, int height) -> void
		{
			std::unique_lock<std::mutex> lock(_mutex);
			{ // locked area
				_up_duration = step_duration;
				_up_texture = std::move(texture);
				_up_iterator = 0;
				for(unsigned int i = 0; i < steps; i++)
				{
					_up_animation.push_back(sf::IntRect(x_coordinate + width * i, y_coordinate, width, height));
				}
			} // lock freed
		}
		/////////////////////////////////////////////////////////////////////////////////
		// 
		/////////////////////////////////////////////////////////////////////////////////
		auto add_up(unsigned int steps, std::shared_ptr<const sf::Texture> texture, unsigned int step_size, unsigned int sheet_row, float step_duration, int x_coordinate, int y_coordinate, int width, int height) -> void
		{
			std::unique_lock<std::mutex> lock(_mutex);
			{ // locked area
				_up_duration = step_duration;
				_up_texture = std::move(texture);
				_up_iterator = 0;
				for(unsigned int i = 0; i < steps; i++)
				{
					_up_animation.push_back(sf::IntRect(x_coordinate + width * i, y_coordinate + sheet_row * height, width, height));
				}
				} // lock freed
		}
		/////////////////////////////////////////////////////////////////////////////////
		// 
		/////////////////////////////////////////////////////////////////////////////////
		auto add_down (unsigned int steps, std::shared_ptr<const sf::Texture> texture, unsigned int step_size, float step_duration, int x_coordinate, int y_coordinate, int width, int height) -> void
		{
			std::unique_lock<std::mutex> lock(_mutex);
			{ // locked area
				_down_duration = step_duration;
				_down_texture = std::move(texture);
				_down_iterator = 0;
				for(unsigned int i = 0; i < steps; i++)
				{
					_down_animation.push_back(sf::IntRect(x_coordinate + width * i, y_coordinate, width, height));
				}
			} // lock freed
		}
		/////////////////////////////////////////////////////////////////////////////////
		// 
		/////////////////////////////////////////////////////////////////////////////////
		auto add_down(unsigned int steps, std::shared_ptr<const sf::Texture> texture, unsigned int step_size, unsigned int sheet_row, float step_duration, int x_coordinate, int y_coordinate, int width, int height) -> void
		{
			std::unique_lock<std::mutex> lock(_mutex);
			{ // locked area
				_down_duration = step_duration;
				_down_texture = std::move(texture);
				_down_iterator = 0;
				for(unsigned int i = 0; i < steps; i++)
				{
					_down_animation.push_back(sf::IntRect(x_coordinate + width * i, y_coordinate + sheet_row * height, width, height));
				}
			} // lock freed
		}
	private:
		/////////////////////////////////////////////////////////////////////////////////
		// ! for thread safety
		/////////////////////////////////////////////////////////////////////////////////
		std::mutex _mutex;
		/////////////////////////////////////////////////////////////////////////////////
		// 
		/////////////////////////////////////////////////////////////////////////////////
		std::vector<sf::IntRect> _still_animation;
		/////////////////////////////////////////////////////////////////////////////////
		// 
		/////////////////////////////////////////////////////////////////////////////////
		std::vector<sf::IntRect> _left_animation;
		/////////////////////////////////////////////////////////////////////////////////
		// 
		/////////////////////////////////////////////////////////////////////////////////
		std::vector<sf::IntRect> _right_animation;
		/////////////////////////////////////////////////////////////////////////////////
		// 
		/////////////////////////////////////////////////////////////////////////////////
		std::vector<sf::IntRect> _up_animation;
		/////////////////////////////////////////////////////////////////////////////////
		// 
		/////////////////////////////////////////////////////////////////////////////////
		std::vector<sf::IntRect> _down_animation;
		/////////////////////////////////////////////////////////////////////////////////
		// 
		/////////////////////////////////////////////////////////////////////////////////
		std::shared_ptr<const sf::Texture> _still_texture;
		/////////////////////////////////////////////////////////////////////////////////
		// 
		/////////////////////////////////////////////////////////////////////////////////
		std::shared_ptr<const sf::Texture> _left_texture;
		/////////////////////////////////////////////////////////////////////////////////
		// 
		/////////////////////////////////////////////////////////////////////////////////
		std::shared_ptr<const sf::Texture> _right_texture;
		/////////////////////////////////////////////////////////////////////////////////
		// 
		/////////////////////////////////////////////////////////////////////////////////
		std::shared_ptr<const sf::Texture> _up_texture;
		/////////////////////////////////////////////////////////////////////////////////
		// 
		/////////////////////////////////////////////////////////////////////////////////
		std::shared_ptr<const sf::Texture> _down_texture;
		/////////////////////////////////////////////////////////////////////////////////
		// 
		/////////////////////////////////////////////////////////////////////////////////
		unsigned int _still_iterator;
		/////////////////////////////////////////////////////////////////////////////////
		// 
		/////////////////////////////////////////////////////////////////////////////////
		unsigned int _left_iterator;
		/////////////////////////////////////////////////////////////////////////////////
		// 
		/////////////////////////////////////////////////////////////////////////////////
		unsigned int _right_iterator;
		/////////////////////////////////////////////////////////////////////////////////
		// 
		/////////////////////////////////////////////////////////////////////////////////
		unsigned int _up_iterator;
		/////////////////////////////////////////////////////////////////////////////////
		// 
		/////////////////////////////////////////////////////////////////////////////////
		unsigned int _down_iterator;
		/////////////////////////////////////////////////////////////////////////////////
		// 
		/////////////////////////////////////////////////////////////////////////////////
		float _still_duration;
		/////////////////////////////////////////////////////////////////////////////////
		// 
		/////////////////////////////////////////////////////////////////////////////////
		float _left_duration;
		/////////////////////////////////////////////////////////////////////////////////
		// 
		/////////////////////////////////////////////////////////////////////////////////
		float _right_duration;
		/////////////////////////////////////////////////////////////////////////////////
		// 
		/////////////////////////////////////////////////////////////////////////////////
		float _up_duration;
		/////////////////////////////////////////////////////////////////////////////////
		// 
		/////////////////////////////////////////////////////////////////////////////////
		float _down_duration;
		/////////////////////////////////////////////////////////////////////////////////
		// 
		/////////////////////////////////////////////////////////////////////////////////
		sf::Clock _animation_clock;
		/////////////////////////////////////////////////////////////////////////////////
		// 
		/////////////////////////////////////////////////////////////////////////////////
		sf::Sprite _sprite;
		/////////////////////////////////////////////////////////////////////////////////
		// 
		/////////////////////////////////////////////////////////////////////////////////
		pose _pose;
		/////////////////////////////////////////////////////////////////////////////////
		// ! draw function
		/////////////////////////////////////////////////////////////////////////////////
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {target.draw(_sprite, states);};
}; // end of class nanimated_sprite

} // end of namespace nanimator

} // end of namespace nengine

#endif // end of __NENGINE__NANIMATOR_NANIMATED_SPRITE__
