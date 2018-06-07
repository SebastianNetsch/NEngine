#ifndef __GAME__
#define __GAME__

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>

#include "../../ninput_manager/ninput_manager.hpp"
#include "../../nparticle_system/nparticle_system.hpp"
#include "../../nresource_manager/nresource_wrapper.hpp"
#include "../../nstate_manager/nstate_manager.hpp"

using namespace nengine;
using namespace nengine::ninput_manager;
using namespace nengine::nparticle_system;
using namespace nengine::nresource_manager;
using namespace nengine::nstate_manager;

struct game_data
{
	sf::RenderWindow window;
	nengine::ninput_manager::ninput_manager input_manager;
	nengine::nparticle_system::nparticle_system particle_system;
	nengine::nresource_manager::nresource_wrapper<std::string> resource_manager;
	nengine::nstate_manager::nstate_manager state_manager;
};

class game
{
	public:
		game(int width, int height, std::string title);
		auto run() -> void;
	private:
		const float _dt;
		sf::Clock _clock;
		std::shared_ptr<game_data> _data;
};

#endif

