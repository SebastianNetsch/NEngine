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

#ifndef __NENGINE__NRESOURCE_MANAGER__RESOURCE_WRAPPER__
#define __NENGINE__NRESOURCE_MANAGER__RESOURCE_WRAPPER__

/////////////////////////////////////////////////////////////////////////////////
// ! nresource_manager as member
// ! memory for shared pointers
// ! SFML/Graphics.hpp for sfml structures
/////////////////////////////////////////////////////////////////////////////////
#include "nresource_manager.hpp"
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

/////////////////////////////////////////////////////////////////////////////////
// ! namespace for the nengine
/////////////////////////////////////////////////////////////////////////////////
namespace nengine {

/////////////////////////////////////////////////////////////////////////////////
// ! namespace for the nresource_manager
/////////////////////////////////////////////////////////////////////////////////
namespace nresource_manager {

/////////////////////////////////////////////////////////////////////////////////
// ! namespace using for easier and cleaner programming
/////////////////////////////////////////////////////////////////////////////////
using namespace nengine;
using namespace nengine::nresource_manager;

/////////////////////////////////////////////////////////////////////////////////
// ! template class nresource manager for convenience and multiple use
/////////////////////////////////////////////////////////////////////////////////
template <typename VAL>
class nresource_wrapper : public nresource_manager<std::string, VAL>
{
	public:
		/////////////////////////////////////////////////////////////////////////////////
		// ! delete default constructor
		/////////////////////////////////////////////////////////////////////////////////
		nresource_wrapper(const nresource_wrapper&) = delete;
		/////////////////////////////////////////////////////////////////////////////////
		// ! delete copy constructor
		/////////////////////////////////////////////////////////////////////////////////
		nresource_wrapper& operator=(const nresource_wrapper&) = delete;
		/////////////////////////////////////////////////////////////////////////////////
		// ! custom constructor: sets nresource storage to true so calling a clear
		//   manually is useless
		/////////////////////////////////////////////////////////////////////////////////
		nresource_wrapper()
			: _nresources()
		{
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! used to toggle the ability to hold on to resources that are currently
		//   not active
		// @ return: the current status
		/////////////////////////////////////////////////////////////////////////////////
		auto toggle_resource_storage() -> bool
		{
			return _nresources.toggle_resource_storage();
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! used to find out whether or not the nresource storage is active
		// @return: to indicate whether or not the nresource storage is active
		/////////////////////////////////////////////////////////////////////////////////
		auto get_resource_storage() -> bool
		{
			return _nresources.get_resource_storage();
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! adds a key-value pair to the nresource wrapper
		// @param1: the key identifier for the key-value pair
		// @param2: the value of the resource
		// @return: a shared pointer to the resource
		/////////////////////////////////////////////////////////////////////////////////
		auto add(std::string const& key, VAL const& value) -> std::shared_ptr<const VAL>
		{
			return _nresources.add(key, value);
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! adds a key-value pair to the nresource manager
		// @param1: the key identifier for the key-value pair
		// @param2: the value of the resource
		// @return: an indicator if the insertion happened
		/////////////////////////////////////////////////////////////////////////////////
		auto add_if(std::string const& key, VAL const& value) -> bool
		{
			return _nresources.add_if(key, value);
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! for getting a stored nresource
		// @param1: the key identifier for the key-value pair
		// @return: the value as a constant reference
		/////////////////////////////////////////////////////////////////////////////////
		auto get(std::string const& key) -> std::shared_ptr<const VAL>
		{
			if(_nresources.test(key))
			{
				return _nresources.get(key);
			}
			else
			{
				return std::move(std::make_shared<VAL>());
			}
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! for getting the last used stored nresource
		// @return: the value as a constant reference
		/////////////////////////////////////////////////////////////////////////////////
		auto get_last() -> std::shared_ptr<const VAL>
		{
			return _nresources.get_last();
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! for swapping nresource values
		// @param1: the nresource identifier
		// @param2: the nresource new value
		// @return: to indicate whether or not the swap happened
		/////////////////////////////////////////////////////////////////////////////////
		auto swap(std::string const& key, VAL const& value) -> bool
		{
			return _nresources.swap(key, value);
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! for checking the amount of stored resources
		// @return: the amount of stored resources
		/////////////////////////////////////////////////////////////////////////////////
		auto get_size() -> unsigned int
		{
			return (_nresources.get_size() + _ntextures.get_size() + _nfonts.get_size() + _nsoundbuffers.get_size());
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! for deleting a single nresource
		// @return: indicator if the nresource was cleared
		//          --> true:
		//                  - successful clear
		//          --> false:
		//                  - clear did not work
		//                  - nresource storage active
		//                  - nresource not in storage
		/////////////////////////////////////////////////////////////////////////////////
		auto clr(std::string const& key) -> bool
		{
			return _nresources.clr(key);
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! for deleting unused resources
		// CAUTION: deletes every currently unused nresource without checking
		//          nresource storage
		/////////////////////////////////////////////////////////////////////////////////
		auto clr_unused() -> void
		{
			_nresources.clr_unused();
			_ntextures.clr_unused();
			_nfonts.clr_unused();
			_nsoundbuffers.clr_unused();
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! to check whether or not the requested nresource is stored
		// @return: indicates whether or not the requested nresource is stored
		/////////////////////////////////////////////////////////////////////////////////
		auto test(std::string const& key) -> bool
		{
			return _nresources.test(key);
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! loads a sf::Texture
		// @param1: the key identifier
		// @param2: the path to the texture to be loaded
		/////////////////////////////////////////////////////////////////////////////////
		auto load_texture(std::string const& key, std::string const& path) -> void
		{
			sf::Texture tex;
			if(tex.loadFromFile(path))
			{
				_ntextures.add(key, tex);
			}
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! to get a sf::Texture
		// @param1: the key identifier
		// @return: the sf::Texture identified by param1
		/////////////////////////////////////////////////////////////////////////////////
		auto get_texture(std::string const& key) -> sf::Texture const&
		{
			return *_ntextures.get(key);
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! to get a sf::Texture by shared pointer
		// @param1: the key identifier
		// @return: the sf::Texture identified by param1
		/////////////////////////////////////////////////////////////////////////////////
		auto get_texture_p(std::string const& key) -> std::shared_ptr<const sf::Texture>
		{
			return _ntextures.get(key);
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! loads a sf::Font
		// @param1: the key identifier
		// @param2: the path to the font to be loaded
		/////////////////////////////////////////////////////////////////////////////////
		auto load_font(std::string const& key, std::string const& path) -> void
		{
			sf::Font font;
			if(font.loadFromFile(path))
			{
				_nfonts.add(key, font);
			}
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! to get a sf::Font
		// @param1: the key identifier
		// @return: the sf::Font identified by param1
		/////////////////////////////////////////////////////////////////////////////////
		auto get_font(std::string const& key) -> sf::Font const&
		{
			return *_nfonts.get(key);
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! to get a sf::Font by shared pointer
		// @param1: the key identifier
		// @return: the sf::Font identified by param1
		/////////////////////////////////////////////////////////////////////////////////
		auto get_font_p(std::string const& key) -> std::shared_ptr<const sf::Font>
		{
			return _nfonts.get(key);
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! loads a sf::SoundBuffer
		// @param1: the key identifier
		// @param2: the path to the sound to be loaded
		/////////////////////////////////////////////////////////////////////////////////
		auto load_soundbuffer(std::string const& key, std::string const& path) -> void
		{
			sf::SoundBuffer buff;
			if(buff.loadFromFile(path))
			{
				_nsoundbuffers.add(key, buff);
			}
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! to get a sf::SoundSoundBuffer
		// @param1: the key identifier
		// @return: the sf::SoundSoundBuffer identified by param1
		/////////////////////////////////////////////////////////////////////////////////
		auto get_soundbuffer(std::string const& key) -> sf::SoundBuffer const&
		{
			return *_nsoundbuffers.get(key);
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! to get a sf::SoundSoundBuffer by shared pointer
		// @param1: the key identifier
		// @return: the sf::SoundSoundBuffer identified by param1
		/////////////////////////////////////////////////////////////////////////////////
		auto get_soundbuffer_p(std::string const& key) -> std::shared_ptr<const sf::SoundBuffer>
		{
			return _nsoundbuffers.get(key);
		}
	private:
		/////////////////////////////////////////////////////////////////////////////////
		// ! one internal nresource_manager wildcard
		/////////////////////////////////////////////////////////////////////////////////
		nresource_manager<std::string, VAL> _nresources;
		/////////////////////////////////////////////////////////////////////////////////
		// ! internal sf::Texture nresource_manager
		/////////////////////////////////////////////////////////////////////////////////
		nresource_manager<std::string, sf::Texture> _ntextures;
		/////////////////////////////////////////////////////////////////////////////////
		// ! internal sf::Font nresource_manager
		/////////////////////////////////////////////////////////////////////////////////
		nresource_manager<std::string, sf::Font> _nfonts;
		/////////////////////////////////////////////////////////////////////////////////
		// ! internal sf::SoundBuffer nresource_manager
		/////////////////////////////////////////////////////////////////////////////////
		nresource_manager<std::string, sf::SoundBuffer> _nsoundbuffers;
}; // end of class nresource_wrapper

} // end of namespace nresource_manager

} // end of namespace nengine

#endif // end of __NENGINE__NRESOURCE_MANAGER__RESOURCE_WRAPPER__

