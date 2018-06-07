#include "src/definitions.hpp"
#include "src/game.hpp"

#include <memory>

int main()
{
	// c++14 make_unique workaround
	std::unique_ptr<game> nengine(new game(WIDTH, HEIGHT, "NEngine Test"));
	nengine->run();
	
	return 0;
}

