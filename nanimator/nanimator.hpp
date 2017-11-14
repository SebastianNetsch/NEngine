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
// ! unordered_map for storage
/////////////////////////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <memory>
#include <mutex>
#include <unordered_map>

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
// ! the nanimated_sprite
/////////////////////////////////////////////////////////////////////////////////
class nanimated_sprite : public sf::Drawable
{
	public:
		/////////////////////////////////////////////////////////////////////////////////
		// ! delete default constructor
		/////////////////////////////////////////////////////////////////////////////////
		nanimated_sprite(const nanimated_sprite&) = delete;
		/////////////////////////////////////////////////////////////////////////////////
		// ! delete copy constructor
		/////////////////////////////////////////////////////////////////////////////////
		nanimated_sprite& operator=(const nanimated_sprite&) = delete;
		/////////////////////////////////////////////////////////////////////////////////
		// ! custom constructor: with initialization list
		/////////////////////////////////////////////////////////////////////////////////
		nanimated_sprite()
			: _mutex()
			, _iterators()
			, _textures()
			, _durations()
			, _intrects()
			, _clocks()
			, _sprite()
			, _last_animation("")
		{
			_sprite.setPosition(0, 0);
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! set's the position of the sprite
		// @param1: the x coordinate
		// @param2: the y coordinate
		/////////////////////////////////////////////////////////////////////////////////
		auto set_position(float x, float y) -> void
		{
			std::unique_lock<std::mutex> lock(_mutex);
			{ // locked area
				_sprite.setPosition(sf::Vector2f(x, y));
			} // lock freed
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! adds a animation to the sprite
		// @param1: the key to identify the animation
		// @param2: the amount of steps the animation has
		// @param3: the shared pointer to the texture
		// @param4: the amount of time a single frame is displayed
		// @param5: the start x coordinate
		// @param6: the start y coordinate
		// @param7: the spritesheet row of the animation frames
		// @param8: the height of each frame
		// @param9: the width of each frame
		// @return: to indicate if the adding succeeded
		/////////////////////////////////////////////////////////////////////////////////
		auto add(std::string const& key, unsigned int steps, std::shared_ptr<const sf::Texture> texture, float step_duration, int start_x, int start_y, unsigned int row, unsigned int height, unsigned int width) -> bool
		{
			std::unique_lock<std::mutex> lock(_mutex);
			{ // locked area
				// validate parameters
				{
					if(steps <= 0)
					{
						return false;
					}
					if(step_duration <= 0)
					{
						return false;
					}
					if(row <= 0)
					{
						return false;
					}
					if(key == "")
					{
						return false;
					}
					if(!texture) // check for nullptr
					{
						return false;
					}
				}

				// check all maps for existing animations
				{
					bool exists = false;
					if(_textures.find(key) != _textures.end())
					{
						exists = true;
					}
					if(_durations.find(key) != _durations.end())
					{
						exists = true;
					}
					if(_intrects.find(key) != _intrects.end())
					{
						exists = true;
					}
					if(_iterators.find(key) != _iterators.end())
					{
						exists = true;
					}
					if(_clocks.find(key) != _clocks.end())
					{
						exists = true;
					}
					if(exists)
					{
						return false;
					}
				}

				// create and save all used data
				{
					// decrease row by one because you have to insert row >= 1 but the calculations are based on row - 1
					row--;

					// save default iterator
					_iterators.insert(std::make_pair(key, 0));

					// save texture
					_textures.insert(std::make_pair(key, std::move(texture)));

					// save step_duration
					_durations.insert(std::make_pair(key, step_duration));

					// save default clock
					_clocks.insert(std::make_pair(key, std::move(sf::Clock())));
					_clocks.at(key).restart();

					// create and save int rectangles
					{
						std::vector<sf::IntRect> tmp;
						for(unsigned int i = 0; i < steps; i++)
						{
							tmp.push_back(sf::IntRect(start_x + width * i, start_y + row * height, width, height));
						}
						_intrects.insert(std::make_pair(key, std::move(tmp)));
					}
				}
			} // lock freed
			return true;
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! to animate the sprite
		// @param1: the key to identify the animation
		/////////////////////////////////////////////////////////////////////////////////
		auto animate(std::string const& key) -> void
		{
			std::unique_lock<std::mutex> lock(_mutex);
			{ // locked area
				// validate parameters
				{
					if(key == "")
					{
						return;
					}
				}

				// check all maps for existing animations
				{
					bool exists = false;
					if(_textures.find(key) != _textures.end())
					{
						exists = true;
					}
					if(_durations.find(key) != _durations.end())
					{
						exists = true;
					}
					if(_intrects.find(key) != _intrects.end())
					{
						exists = true;
					}
					if(_iterators.find(key) != _iterators.end())
					{
						exists = true;
					}
					if(_clocks.find(key) != _clocks.end())
					{
						exists = true;
					}
					if(!exists)
					{
						return;
					}
				}

				// animate the sprite
				{
					if(key != _last_animation)
					{
						_last_animation = key;
						_sprite.setTexture(*_textures.at(key));
						_sprite.setTextureRect(_intrects.at(key).at(0));
					}

					if(_clocks.at(key).getElapsedTime().asSeconds() >= _durations.at(key))
					{
						_sprite.setTextureRect(_intrects.at(key).at(_iterators.at(key)));
						_iterators.at(key)++;
						if(_iterators.at(key) >= _intrects.at(key).size())
						{
							_iterators.at(key) = 0;
						}
						_clocks.at(key).restart();
					}
				}
			} // lock freed
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! to stop an animation
		/////////////////////////////////////////////////////////////////////////////////
		auto stop() -> void
		{
			std::unique_lock<std::mutex> lock(_mutex);
			{ // locked area
				if(_last_animation == "")
				{
					return;
				}
				_sprite.setTexture(*_textures.at(_last_animation));
				_sprite.setTextureRect(_intrects.at(_last_animation).at(0));
				_iterators.at(_last_animation) = 0;
			} // lock freed
		}
	private:
		/////////////////////////////////////////////////////////////////////////////////
		// ! for thread safety
		/////////////////////////////////////////////////////////////////////////////////
		std::mutex _mutex;
		/////////////////////////////////////////////////////////////////////////////////
		// ! the SFML sprite used to draw the nanimated_sprite
		/////////////////////////////////////////////////////////////////////////////////
		sf::Sprite _sprite;
		/////////////////////////////////////////////////////////////////////////////////
		// ! for each animation
		/////////////////////////////////////////////////////////////////////////////////
		std::unordered_map<std::string, unsigned int> _iterators;
		/////////////////////////////////////////////////////////////////////////////////
		// ! for each animation
		/////////////////////////////////////////////////////////////////////////////////
		std::unordered_map<std::string, std::shared_ptr<const sf::Texture>> _textures;
		/////////////////////////////////////////////////////////////////////////////////
		// ! for each animation
		/////////////////////////////////////////////////////////////////////////////////
		std::unordered_map<std::string, float> _durations;
		/////////////////////////////////////////////////////////////////////////////////
		// ! for each animation
		/////////////////////////////////////////////////////////////////////////////////
		std::unordered_map<std::string, std::vector<sf::IntRect>> _intrects;
		/////////////////////////////////////////////////////////////////////////////////
		// ! to determine the amount of time passed for each animation
		/////////////////////////////////////////////////////////////////////////////////
		std::unordered_map<std::string, sf::Clock> _clocks;
		/////////////////////////////////////////////////////////////////////////////////
		// 
		/////////////////////////////////////////////////////////////////////////////////
		std::string _last_animation;
		/////////////////////////////////////////////////////////////////////////////////
		// ! draw function
		/////////////////////////////////////////////////////////////////////////////////
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {target.draw(_sprite, states);};
}; // end of class nanimated_sprite

} // end of namespace nanimator

} // end of namespace nengine

#endif // end of __NENGINE__NANIMATOR_NANIMATED_SPRITE__
