#ifndef __MAIN_MENU__
#define __MAIN_MENU__

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "../../../../nstate_manager/nstate.hpp"
#include "../../definitions.hpp"
#include "../../game.hpp"

class main_menu : public nengine::nstate_manager::nstate
{
	public:
		main_menu(std::shared_ptr<game_data> data);
		auto init() -> void;
		auto pause() -> void;
		auto resume() -> void;
		auto handle() -> void;
		auto update(float dt) -> void;
		auto draw(float dt) -> void;
	private:
		std::shared_ptr<game_data> _data;
		sf::Clock _clock;
		sf::Sprite _title;
		sf::Sprite _background;
		sf::Sprite _play_button;
		std::vector<std::shared_ptr<const sf::Texture>> _textures;
};

#endif

