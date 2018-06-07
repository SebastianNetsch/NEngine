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
#ifndef __NENGINE__NPARTICLE_SYSTEM__NPARTICLE_SYSTEM__
#define __NENGINE__NPARTICLE_SYSTEM__NPARTICLE_SYSTEM__

/////////////////////////////////////////////////////////////////////////////////
// ! nparticle.hpp as the basic resource
// ! SFML/Graphics.hpp for SFML structures
// ! vector for list of all nparticles
// ! memory for shared pointer
// ! mutex for thread safety
/////////////////////////////////////////////////////////////////////////////////
#include "nparticle.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <mutex>

/////////////////////////////////////////////////////////////////////////////////
// ! namespace for the nengine
/////////////////////////////////////////////////////////////////////////////////
namespace nengine {

/////////////////////////////////////////////////////////////////////////////////
// ! namespace for the nparticle_system
/////////////////////////////////////////////////////////////////////////////////
namespace nparticle_system {

/////////////////////////////////////////////////////////////////////////////////
// ! namespace using for easier and cleaner programming
/////////////////////////////////////////////////////////////////////////////////
using namespace nengine;
using namespace nengine::nparticle_system;

/////////////////////////////////////////////////////////////////////////////////
// ! the nparticle system
/////////////////////////////////////////////////////////////////////////////////
class nparticle_system : public sf::Drawable
{
	public:
		/////////////////////////////////////////////////////////////////////////////////
		// ! delete default constructor
		/////////////////////////////////////////////////////////////////////////////////
		nparticle_system(const nparticle_system&) = delete;
		/////////////////////////////////////////////////////////////////////////////////
		// ! delete copy constructor
		/////////////////////////////////////////////////////////////////////////////////
		nparticle_system& operator=(const nparticle_system&) = delete;
		/////////////////////////////////////////////////////////////////////////////////
		// ! custom constructor: set's internal variables to basic values
		/////////////////////////////////////////////////////////////////////////////////
		nparticle_system()
			: _gravity(sf::Vector2f(0.0, 0.0))
			, _transparent(sf::Color(0, 0, 0, 0))
			, _max(1000)
			, _mutex()
			, _nparticles()
		{
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! custom constructor: set's internal variables to custom values
		// @param1: gravitational pull x
		// @param2: gravitational pull y
		// @param3: maximum amount of particles
		/////////////////////////////////////////////////////////////////////////////////
		nparticle_system(float gravitation_x, float gravitation_y, unsigned int maximum)
			: _gravity(sf::Vector2f(gravitation_x, gravitation_y))
			, _transparent(sf::Color(0, 0, 0, 0))
			, _max(maximum)
			, _mutex()
			, _nparticles()
		{
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! custom destructor: thread safe clearing
		/////////////////////////////////////////////////////////////////////////////////
		~nparticle_system()
		{
			std::unique_lock<std::mutex> lock(_mutex);
			{ // locked area
				_nparticles.clear();
			} // lock freed
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! adds n nparticles to the nparticle_system
		// @ param1: the amount of new nparticles
		// @ param2: the live span
		// @ param3: the decay rate
		// @ param4: the color
		// @ param5: the x position
		// @ param6: the y position
		// @ param7: the x speed
		// @ param8: the y speed
		/////////////////////////////////////////////////////////////////////////////////
		auto add(unsigned int n, float live_span, float decay_rate, sf::Color color, float pos_x, float pos_y, float speed_x, float speed_y) -> void
		{
			std::unique_lock<std::mutex> lock(_mutex);
			{ // locked area
				if (_nparticles.size() + n >= _max)
				{
					return;
				}
				for(unsigned int i = 0; i <= n; i++)
				{
					_create(live_span, decay_rate, color, pos_x, pos_y, speed_x, speed_y);
				}
			} // lock freed
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! updates all particles: changes position, calculates new health points, etc
		/////////////////////////////////////////////////////////////////////////////////
		auto update(float delta_time) -> void
		{
			std::unique_lock<std::mutex> lock(_mutex);
			{ // locked area
				for(unsigned int i = 0; i < _nparticles.size(); i++)
				{
					_update_health_points(i);
					_update_pos(i, delta_time);
				}
				_delete_dead();
			} // lock freed
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! for accessing the amount of nparticles in the nparticle_system
		// @return: the amount of nparticles
		/////////////////////////////////////////////////////////////////////////////////
		auto get_amount() -> unsigned int
		{
			std::unique_lock<std::mutex> lock(_mutex);
			{ // locked area
				return _nparticles.size();
			} // lock freed
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! sets gravity
		// @param1: gravitational pull x
		// @param2: gravitational pull y
		/////////////////////////////////////////////////////////////////////////////////
		auto set_gravity(float x, float y) -> void
		{
			std::unique_lock<std::mutex> lock(_mutex);
			{ // locked area
				_gravity = sf::Vector2f(x, y);
			} // lock freed
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! sets maximum amount of particles
		// @param1: maximum amount of particles
		/////////////////////////////////////////////////////////////////////////////////
		auto set_max(unsigned int maximum) -> void
		{
			std::unique_lock<std::mutex> lock(_mutex);
			{ // locked area
				_max = maximum;
			} // lock freed
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! gets maximum amount of particles
		// @return: maximum amount of particles
		/////////////////////////////////////////////////////////////////////////////////
		auto set_max() -> unsigned int
		{
			std::unique_lock<std::mutex> lock(_mutex);
			{ // locked area
				return _max;
			} // lock freed
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! clears the internal particle vector
		/////////////////////////////////////////////////////////////////////////////////
		auto clr() -> void
		{
			std::unique_lock<std::mutex> lock(_mutex);
			{ // locked area
				_nparticles.clear();
			} // lock freed
		}
	private:
		/////////////////////////////////////////////////////////////////////////////////
		// ! the gravity applied at every update on every nparticle
		/////////////////////////////////////////////////////////////////////////////////
		sf::Vector2f _gravity;
		/////////////////////////////////////////////////////////////////////////////////
		// ! transparent for resetting the particle color
		// ! DEPRECATED
		/////////////////////////////////////////////////////////////////////////////////
		sf::Color _transparent;
		/////////////////////////////////////////////////////////////////////////////////
		// ! for creating a single nparticle
		/////////////////////////////////////////////////////////////////////////////////
		auto _create(float live_span, float decay_rate, sf::Color color, float pos_x, float pos_y, float speed_x, float speed_y) -> void
		{
			auto particle = std::make_shared<nparticle>();
			particle->vel.x = speed_x;
			particle->vel.y = speed_y;
			particle->pos.color = color;
			particle->pos.position.x = pos_x;
			particle->pos.position.y = pos_y;
			particle->fading = true;
			particle->health_points = live_span;
			particle->decay_rate = decay_rate;
			_nparticles.push_back(particle);
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! for updating a NParticles health_points
		/////////////////////////////////////////////////////////////////////////////////
		inline auto _update_health_points(unsigned int pos) -> void
		{
			_nparticles.at(pos)->health_points -= _nparticles.at(pos)->decay_rate;
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! for updating all positions
		/////////////////////////////////////////////////////////////////////////////////
		inline auto _update_pos(unsigned int pos, float delta_time) -> void
		{
			_nparticles.at(pos)->vel.x += _gravity.x * delta_time;
			_nparticles.at(pos)->vel.y += _gravity.y * delta_time;
			_nparticles.at(pos)->pos.position.x += _nparticles.at(pos)->vel.x * delta_time;
			_nparticles.at(pos)->pos.position.y += _nparticles.at(pos)->vel.y * delta_time;
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! for deleting all dead particles
		/////////////////////////////////////////////////////////////////////////////////
		auto _delete_dead() -> void
		{
			for(auto it = _nparticles.begin(); it != _nparticles.end();)
			{
				if((*it)->health_points <= 0.0)
				{
					it = _nparticles.erase(it);
				}
				else
				{
					it++;
				}
			}
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! maximum amount of particles allowed
		/////////////////////////////////////////////////////////////////////////////////
		unsigned int _max;
		/////////////////////////////////////////////////////////////////////////////////
		// ! for thread safety
		/////////////////////////////////////////////////////////////////////////////////
		std::mutex _mutex;
		/////////////////////////////////////////////////////////////////////////////////
		// ! the storage unit
		/////////////////////////////////////////////////////////////////////////////////
		std::vector<std::shared_ptr<nparticle>> _nparticles;
		/////////////////////////////////////////////////////////////////////////////////
		// ! virtual draw function
		/////////////////////////////////////////////////////////////////////////////////
		void draw(sf::RenderTarget &target, sf::RenderStates states) const
		{
			for(auto const& item : _nparticles)
				target.draw(&item.get()->pos, 1, sf::Points);
		}
}; // end of class nparticle_system

} // end of namespace nparticle_system

} // end of namespace nengine

#endif // end of __NENGINE__NPARTICLE_SYSTEM__NPARTICLE_SYSTEM__
