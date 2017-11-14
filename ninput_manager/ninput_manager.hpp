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
#ifndef __NENGINE__NINPUT_MANAGER__NINPUT_MANAGER__
#define __NENGINE__NINPUT_MANAGER__NINPUT_MANAGER__

/////////////////////////////////////////////////////////////////////////////////
// ! SFML/Graphics.hpp for SFML structures
// ! mutex for thread safety
// ! unordered_map for custom key bindings
// ! memory for shared pointer
/////////////////////////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <mutex>
#include <unordered_map>
#include <memory>

/////////////////////////////////////////////////////////////////////////////////
// ! namespace for the nengine
/////////////////////////////////////////////////////////////////////////////////
namespace nengine {

/////////////////////////////////////////////////////////////////////////////////
// ! namespace for the ninput_manager
/////////////////////////////////////////////////////////////////////////////////
namespace ninput_manager {

/////////////////////////////////////////////////////////////////////////////////
// ! namespace using for easier and cleaner programming
/////////////////////////////////////////////////////////////////////////////////
using namespace nengine;
using namespace nengine::ninput_manager;

/////////////////////////////////////////////////////////////////////////////////
// ! the ninput_type
/////////////////////////////////////////////////////////////////////////////////
enum class ninput_type
{
	KEYBOARD,
	MOUSE
};

/////////////////////////////////////////////////////////////////////////////////
// ! the nkey
/////////////////////////////////////////////////////////////////////////////////
struct nkey
{
	ninput_type _type;
	sf::Keyboard::Key _key;
	sf::Mouse::Button _button;
	auto change_bind_keyboard(sf::Keyboard::Key const& input) -> void {_key = input;};
	auto change_bind_mouse(sf::Mouse::Button const& input) -> void {_button = input;};
};

/////////////////////////////////////////////////////////////////////////////////
// ! the ninput_manager
/////////////////////////////////////////////////////////////////////////////////
class ninput_manager
{
	public:
		/////////////////////////////////////////////////////////////////////////////////
		// ! delete default constructor
		/////////////////////////////////////////////////////////////////////////////////
		ninput_manager(const ninput_manager&) = delete;
		/////////////////////////////////////////////////////////////////////////////////
		// ! delete copy constructor
		/////////////////////////////////////////////////////////////////////////////////
		ninput_manager& operator=(const ninput_manager&) = delete;
		/////////////////////////////////////////////////////////////////////////////////
		// ! custom constructor: with initialization list
		/////////////////////////////////////////////////////////////////////////////////
		ninput_manager()
			: _mutex()
		{
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! to check if a sprite was clicked
		// @param1: the sf::Sprite that needs to be checked
		// @param2: the sf::Mouse button event
		// @param3: the sf::RenderWindow where this click presumably takes place
		// @return: indicator if the sprite was clicked
		/////////////////////////////////////////////////////////////////////////////////
		auto clicked(sf::Sprite const& object, sf::Mouse::Button const& button, sf::RenderWindow const& window) -> bool
		{
			std::unique_lock<std::mutex> lock(_mutex);
			{ // locked area
				if(sf::Mouse::isButtonPressed(button))
				{
					sf::IntRect tmp_rect(object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width, object.getGlobalBounds().height);
					if(tmp_rect.contains(sf::Mouse::getPosition(window)))
					{
						return true;
					}
				}
				return false;
			} // lock freed
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! get sf::Mouse position relative to the sf::RenderWindow
		// @param1: the sf::RenderWindow to get the relative sf::Mouse position from
		// @return: a sf::Vector2i that indicates the sf::Mouse position relative
		//          to the sf::RenderWindow
		/////////////////////////////////////////////////////////////////////////////////
		auto get_mouse_position(sf::RenderWindow const& window) -> sf::Vector2i
		{
			std::unique_lock<std::mutex> lock(_mutex);
			{ // locked area
				return sf::Mouse::getPosition(window);
			} // lock freed
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! used to add a key binding
		/////////////////////////////////////////////////////////////////////////////////
		auto add_bind(std::string const& key, sf::Keyboard::Key const& input) -> void
		{
			std::unique_lock<std::mutex> lock(_mutex);
			{ // locked area
				if(_key_bindings.find(key) == _key_bindings.end()) // not yet inserted
				{
					auto tmp = std::make_shared<nkey>();
					tmp->_type = ninput_type::KEYBOARD;
					tmp->_key = input;
					_key_bindings.insert(std::make_pair(key, tmp));
				}
			} // lock freed
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! used to add a button binding
		/////////////////////////////////////////////////////////////////////////////////
		auto add_bind(std::string const& key, sf::Mouse::Button const& input) -> void
		{
			std::unique_lock<std::mutex> lock(_mutex);
			{ // locked area
				if(_key_bindings.find(key) == _key_bindings.end()) // not yet inserted
				{
					auto tmp = std::make_shared<nkey>();
					tmp->_type = ninput_type::MOUSE;
					tmp->_button = input;
					_key_bindings.insert(std::make_pair(key, tmp));
				}
			} // lock freed
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! used to change a key binding
		// ! does NOT add if not found
		/////////////////////////////////////////////////////////////////////////////////
		auto change_bind(std::string const& key, sf::Keyboard::Key const& input) -> void
		{
			std::unique_lock<std::mutex> lock(_mutex);
			{ // locked area
				if(_key_bindings.find(key) != _key_bindings.end()) // already inserted
				{
					if(_key_bindings.at(key)->_type == ninput_type::KEYBOARD)
					{
						_key_bindings.at(key)->change_bind_keyboard(input);
					}
				}
			} // lock freed
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! used to change a button binding
		// ! does NOT add if not found
		/////////////////////////////////////////////////////////////////////////////////
		auto change_bind(std::string const& key, sf::Mouse::Button const& input) -> void
		{
			std::unique_lock<std::mutex> lock(_mutex);
			{ // locked area
				if(_key_bindings.find(key) != _key_bindings.end()) // already inserted
				{
					if(_key_bindings.at(key)->_type == ninput_type::MOUSE)
					{
						_key_bindings.at(key)->change_bind_mouse(input);
					}
				}
			} // lock freed
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! used to check a key or button binding
		/////////////////////////////////////////////////////////////////////////////////
		auto check_bind(std::string const& key) -> bool
		{
			std::unique_lock<std::mutex> lock(_mutex);
			{ // locked area
				if(_key_bindings.find(key) != _key_bindings.end()) // already inserted
				{
					if((_key_bindings.at(key)->_type == ninput_type::KEYBOARD) && (sf::Keyboard::isKeyPressed(_key_bindings.at(key)->_key)))
					{
						return true;
					}
					if((_key_bindings.at(key)->_type == ninput_type::MOUSE) && (sf::Mouse::isButtonPressed(_key_bindings.at(key)->_button)))
					{
						return true;
					}
				}
				return false;
			} // lock freed
		}
	private:
		/////////////////////////////////////////////////////////////////////////////////
		// ! for thread safety
		/////////////////////////////////////////////////////////////////////////////////
		std::mutex _mutex;
		/////////////////////////////////////////////////////////////////////////////////
		// ! used to store custom key configuration
		/////////////////////////////////////////////////////////////////////////////////
		std::unordered_map<std::string, std::shared_ptr<nkey>> _key_bindings;
}; // end of class ninput_manager

} // end of namespace ninput_manager

} // end of namespace nengine

#endif // end of __NENGINE__NINPUT_MANAGER__NINPUT_MANAGER__
