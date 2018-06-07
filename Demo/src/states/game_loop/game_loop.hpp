#ifndef __GAME_LOOP__
#define __GAME_LOOP__

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "../../../../nlayer/nlayer.hpp"
#include "../../../../nstate_manager/nstate.hpp"
#include "../../../../nanimator/nanimator.hpp"
#include "../../definitions.hpp"
#include "../../game.hpp"

class game_loop : public nengine::nstate_manager::nstate
{
	public:
		game_loop(std::shared_ptr<game_data> data);
		auto init() -> void;
		auto pause() -> void;
		auto resume() -> void;
		auto handle() -> void;
		auto update(float dt) -> void;
		auto draw(float dt) -> void;
	private:
		std::shared_ptr<game_data> _data;
		sf::Clock _clock;
		sf::Clock _popup_clock;
		sf::Clock _health_bar_clock;
		unsigned int _health_bar_cnt;
		bool _show_popup;
		nengine::nlayer::nlayer _popup_layer;
		nengine::nlayer::nlayer _gui_layer;
		sf::Sprite _background;
		sf::Sprite _popup;
		sf::Sprite _health_bar;
		sf::Sprite _health_bar_background;
		sf::Sprite _particles;
		bool _running;
		std::vector<std::shared_ptr<const sf::Texture>> _textures;
		nengine::nanimator::nanimated_sprite _animated;
};

#endif

