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

#ifndef __NENGINE__NRESOURCE_MANAGER__RESOURCE_MANAGER__
#define __NENGINE__NRESOURCE_MANAGER__RESOURCE_MANAGER__

/////////////////////////////////////////////////////////////////////////////////
// ! memory for shared pointers
// ! mutex for thread safety
// ! unordered map as storage container
/////////////////////////////////////////////////////////////////////////////////
#include <memory>
#include <mutex>
#include <unordered_map>

/////////////////////////////////////////////////////////////////////////////////
// ! namespace for the nengine
/////////////////////////////////////////////////////////////////////////////////
namespace nengine {

/////////////////////////////////////////////////////////////////////////////////
// ! namespace for the nresource_manager
/////////////////////////////////////////////////////////////////////////////////
namespace nresource_manager {

/////////////////////////////////////////////////////////////////////////////////
// ! template class nresource for convenience and multiple use
/////////////////////////////////////////////////////////////////////////////////
template <typename VAL>
class nresource {
	public:
		/////////////////////////////////////////////////////////////////////////////////
		// ! custom constructor: initializes value with param1
		// @param1: a shared pointer to the value
		/////////////////////////////////////////////////////////////////////////////////
		nresource(std::shared_ptr<VAL> val)
			: _val(std::move(val))
		{
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! to get the resources value
		// @return: a shared pointer to the value
		/////////////////////////////////////////////////////////////////////////////////
		inline auto get() -> std::shared_ptr<VAL> {return _val;}
		/////////////////////////////////////////////////////////////////////////////////
		// ! to change the resources value
		// @param1: a reference to the new value
		/////////////////////////////////////////////////////////////////////////////////
		inline auto set(VAL const& val) -> void {*_val = val;}
		/////////////////////////////////////////////////////////////////////////////////
		// ! to find out if the value is unique
		// @return: indicator if the value is unique
		/////////////////////////////////////////////////////////////////////////////////
		inline auto is_unique() -> bool {return _val.unique();}
	private:
		/////////////////////////////////////////////////////////////////////////////////
		// ! shared pointer to the value
		/////////////////////////////////////////////////////////////////////////////////
		std::shared_ptr<VAL> _val;
};

/////////////////////////////////////////////////////////////////////////////////
// ! template class nresource manager for convenience and multiple use
/////////////////////////////////////////////////////////////////////////////////
template <typename KEY, typename VAL>
class nresource_manager
{
	public:
		/////////////////////////////////////////////////////////////////////////////////
		// ! delete default constructor
		/////////////////////////////////////////////////////////////////////////////////
		nresource_manager(const nresource_manager&) = delete;
		/////////////////////////////////////////////////////////////////////////////////
		// ! delete copy constructor
		/////////////////////////////////////////////////////////////////////////////////
		nresource_manager& operator=(const nresource_manager&) = delete;
		/////////////////////////////////////////////////////////////////////////////////
		// ! custom constructor: sets nresource storage to true so calling a clear
		//   manually is useless
		/////////////////////////////////////////////////////////////////////////////////
		nresource_manager()
			: _resources()
			, _last_requested_resource()
			, _mutex()
			, _keep_resources(true)
		{
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! custom destructor: resets every pointed to nresource and the key-value pair
		// ! use carefully --> if nresource manager is destroyed too early in respect
		//   of your programs' logic all resources are lost
		/////////////////////////////////////////////////////////////////////////////////
		~nresource_manager()
		{
			std::unique_lock<std::mutex> lock(_mutex);
			{ // locked area
				_resources.clear();
			} // lock freed
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! used to toggle the ability to hold on to resources that are currently
		//   not active
		// @ return: the current status
		/////////////////////////////////////////////////////////////////////////////////
		auto toggle_resource_storage() -> bool
		{
			std::unique_lock<std::mutex> lock(_mutex);
			{ // locked area
				return (_keep_resources = !_keep_resources);
			} // lock freed
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! used to find out whether or not the nresource storage is active
		// @return: to indicate whether or not the nresource storage is active
		/////////////////////////////////////////////////////////////////////////////////
		auto get_resource_storage() -> bool
		{
			std::unique_lock<std::mutex> lock(_mutex);
			{ // locked area
				return _keep_resources;
			} // lock freed
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! adds a key-value pair to the nresource manager
		// @param1: the nresource identifier
		// @param2: the nresource acting as the value part of the key-value pair
		// @return: the shared pointer to the nresource
		/////////////////////////////////////////////////////////////////////////////////
		auto add(KEY const& key, VAL const& value) -> std::shared_ptr<const VAL>
		{
			std::unique_lock<std::mutex> lock(_mutex);
			{ // locked area
				if(_in_use(key))
					return _resources.at(key).get();
				auto tmp = std::make_shared<VAL>(value);
				_resources.insert(std::make_pair(key, nresource<VAL>(tmp)));
				return tmp;
			} // lock freed
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! adds a key-value pair to the nresource manager
		// @param1: the nresource identifier
		// @param2: the nresource acting as the value part of the key-value pair
		// @return: to indicate if the key-value pair could be inserted
		/////////////////////////////////////////////////////////////////////////////////
		auto add_if(KEY const& key, VAL const& value) -> bool
		{
			std::unique_lock<std::mutex> lock(_mutex);
			{ // locked area
				// second holds an boolean whether or not the insertion happened
				return _resources.insert(std::make_pair(key, nresource<VAL>(std::make_shared<VAL>(value)))).second;
			} // lock freed
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! for getting a stored nresource
		// @param1: the key identifier for the key-value pair
		// @return: the value as a constant reference
		/////////////////////////////////////////////////////////////////////////////////
		auto get(KEY const& key) -> std::shared_ptr<const VAL>
		{
			std::unique_lock<std::mutex> lock(_mutex);
			{ // locked area
				if(_in_use(key))
				{
					_last_requested_resource = key;
					return _resources.at(key).get();
				}
				else
				{
					return std::move(std::make_shared<VAL>());
				}
			} // lock freed
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! for getting the last used stored nresource
		// @return: the value as a constant reference
		/////////////////////////////////////////////////////////////////////////////////
		auto get_last() -> std::shared_ptr<const VAL>
		{
			std::unique_lock<std::mutex> lock(_mutex);
			{ // locked area
				if(_in_use(_last_requested_resource))
					return _resources.at(_last_requested_resource).get();
				else
					return std::move(std::make_shared<VAL>());
			} // lock freed
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! for swapping nresource values
		// @param1: the nresource identifier
		// @param2: the nresource new value
		// @return: to indicate whether or not the swap happened
		/////////////////////////////////////////////////////////////////////////////////
		auto swap(KEY const& key, VAL const& value) -> bool
		{
			std::unique_lock<std::mutex> lock(_mutex);
			{ // locked area
				if(_in_use(key))
				{
					auto tmp = *_resources.at(key).get(); // get value of type VAL
					_resources.at(key).set(value);
					if(tmp != *_resources.at(key).get()) // old vs new value
						return true;
					else
						return false;
				}
				else
				{
					return false;
				}
			} // lock freed
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! for checking the amount of stored resources
		// @return: the amount of stored resources
		/////////////////////////////////////////////////////////////////////////////////
		auto get_size() -> unsigned int
		{
			std::unique_lock<std::mutex> lock(_mutex);
			{ // locked area
				return _resources.size();
			} // lock freed
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
		auto clr(KEY const& key) -> bool
		{
			std::unique_lock<std::mutex> lock(_mutex);
			{ // locked area
				if(_keep_resources)
					return false;
				else
					if(_in_use(key))
						if(_resources.erase(key) == 1)
							return true;
						else
							return false;
					else
						return false;
				// return (_keep_resources) ? false : ((_in_use(key)) ? ((_resources.erase(key) == 1) ? true : false) : false); <-- one line return!!!
			} // lock freed
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! for deleting unused resources
		// CAUTION: deletes every currently unused nresource without checking
		//          nresource storage
		/////////////////////////////////////////////////////////////////////////////////
		auto clr_unused() -> void
		{
			std::unique_lock<std::mutex> lock(_mutex);
			{ // locked area
				for(auto it = _resources.begin(); it != _resources.end();)
				{
					if(it->second.is_unique())
						it = _resources.erase(it);
					else
						it++;
				}
			} // lock freed
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! to check whether or not the requested nresource is stored
		// @return: indicates whether or not the requested nresource is stored
		/////////////////////////////////////////////////////////////////////////////////
		auto test(KEY const& key) -> bool
		{
			std::unique_lock<std::mutex> lock(_mutex);
			{ // locked area
				return _in_use(key);
			} // lock freed
		}
	private:
		/////////////////////////////////////////////////////////////////////////////////
		// ! for thread safety
		/////////////////////////////////////////////////////////////////////////////////
		std::mutex _mutex;
		/////////////////////////////////////////////////////////////////////////////////
		// ! the storage structure
		/////////////////////////////////////////////////////////////////////////////////
		std::unordered_map<KEY, nresource<VAL>> _resources;
		/////////////////////////////////////////////////////////////////////////////////
		// ! the last used key-value pair by key
		/////////////////////////////////////////////////////////////////////////////////
		KEY _last_requested_resource;
		/////////////////////////////////////////////////////////////////////////////////
		// ! decides whether resources that aren't in use at the moment should remain in
		//   the nresource manager
		/////////////////////////////////////////////////////////////////////////////////
		bool _keep_resources;
		/////////////////////////////////////////////////////////////////////////////////
		// ! test if nresource is already in the storage unit
		// @param1: the key to identify the key-value pair by per reference
		// @return: indicates whether the nresource is already in the storage unit or not
		/////////////////////////////////////////////////////////////////////////////////
		inline auto _in_use(KEY const& key) -> bool {return (_resources.find(key) != _resources.end()) ? true : false;}
}; // end of class nresource_manager

} // end of namespace nresource_manager

} // end of namespace nengine

#endif // end of __NENGINE__NRESOURCE_MANAGER__RESOURCE_MANAGER__
