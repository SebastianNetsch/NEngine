<a name="top" />

# NAnimator by Sebastian Netsch

### Content-Table:
- [NAnimator](#nanimator)
  - [Constructors](#constructors)
  - [Destructors](#destructors)
  - [External Functions](#external_functions)
  - [Internal Variables](#internal_variables)
  - [Internal Functions](#internal_functions)
  - [How to Use](#howto)
  - [Inspirations](#mentions)

#### <a name="nanimator" /> NAnimator [ [Top] ](#top)
This class is used to easily gain access to animated SFML sprites.

---

#### <a name="constructors" /> Constructors [ [Top] ](#top)
This class uses a custom constructor with initialization list.

---

#### <a name="destructors" /> Destructors [ [Top] ](#top)
This class uses the standard destructor.

---

#### <a name="external_functions" /> External Functions [ [Top] ](#top)
##### auto set_position(float x, float y) -> void
This function is used to set the initial position.

##### auto add(std::string const& key, unsigned int steps, std::shared_ptr<const sf::Texture> texture, float step_duration, int start_x, int start_y, unsigned int row, unsigned int height, unsigned int width) -> bool
This function adds a animation to the nanimated_sprite.

##### auto animate(std::string const& key) -> void
This function is used to play the animation identified by a key.

##### auto stop() -> void
This function is used to stop a animation.

---

#### <a name="internal_variables" /> Internal Variables [ [Top] ](#top)
##### std::mutex _mutex
This variable is needed for thread safety.

##### sf::Sprite _sprite
This is the SFML sprite that is used to draw the animations.

##### std::unordered_map<std::string, unsigned int> _iterators
This is a map of the nanimated_sprites animation iterators. It is used to determine the animations progress.

##### std::unordered_map<std::string, std::shared_ptr<const sf::Texture>> _textures
This is a map of the nanimated_sprites textures. It is used to determine the animations texture.

##### std::unordered_map<std::string, float> _durations
This is a map of the nanimated_sprites animation frame durations. It is used to determine when to switch to the next frame.

##### std::unordered_map<std::string, std::vector<sf::IntRect>> _intrects
This is a map of the nanimated_sprites animation integer rectangles. This is used to identify the rectangle that resembles one animation frame.

##### std::unordered_map<std::string, sf::Clock> _clocks
This is a map of the nanimated_sprites animation clocks. It is used to determine when to switch to the next frame.

##### std::string _last_animation
This stores the last called animation identified by a key.

---

#### <a name="internal_functions" /> Internal Functions [ [Top] ](#top)
##### virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {target.draw(_sprite, states);};
This function is the SFML function for drawing an object.

---

#### <a name="howto" /> How to Use [ [Top] ](#top)
##### Including it in your project
```
#include "nanimator.hpp"
```

##### Creating a animated sprite
```
nengine::nanimator::nanimated_sprite animated_sprite;
```

##### Adding a basic animation from a combined spritesheet
```
// load the texture
sf::Texture texture;
texture.loadFromFile("res/spritesheet.png");

// add the animations
animated_sprite->add("up", 4, texture, 0.2f, 0, 0, 2, 64, 64);
animated_sprite->add("left", 4, texture, 0.2f, 0, 0, 3, 64, 64);
animated_sprite->add("down", 4, texture, 0.2f, 0, 0, 4, 64, 64);
animated_sprite->add("right", 4, texture, 0.2f, 0, 0, 5, 64, 64);
```

##### Activating an animation (here: "up")
```
if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
{
	animated_sprite->animate("up");
}
```

##### Example SFML main to animate a sprite using the nanimated_sprite
```
#include "../nanimator.hpp"

#include <memory>

int main()
{
	// the window
	sf::RenderWindow window(sf::VideoMode(960, 540), "Animator Test");

	// the texture shared pointer
	auto texture = std::make_shared<sf::Texture>();
	texture->loadFromFile("res/spritesheet.png");

	// the animated sprite shared pointer
	auto animated_sprite = std::make_shared<nengine::nanimator::nanimated_sprite>();

	// adding animations
	animated_sprite->add("still", 4, texture, 2.f, 0, 0, 1, 64, 64); // 64*64 animation frames
	animated_sprite->add("up", 4, texture, 0.2f, 0, 0, 2, 64, 64);
	animated_sprite->add("left", 4, texture, 0.2f, 0, 0, 3, 64, 64);
	animated_sprite->add("down", 4, texture, 0.2f, 0, 0, 4, 64, 64);
	animated_sprite->add("right", 4, texture, 0.2f, 0, 0, 5, 64, 64);

	// for action/ reaction
	bool up;
	bool left;
	bool down;
	bool right;

	// main loop
	while (window.isOpen())
	{
		// events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// action
		up = false;
		left = false;
		down = false;
		right = false;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			up = true;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			left = true;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			down = true;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			right = true;
		}

		// reaction
		if(up)
		{
			animated_sprite->animate("up");
		}
		if(left)
		{
			animated_sprite->animate("left");
		}
		if(down)
		{
			animated_sprite->animate("down");
		}
		if(right)
		{
			animated_sprite->animate("right");
		}
		if(!up && !left && !down && !right)
		{
			animated_sprite->stop();
		}

		// drawing
		window.clear(sf::Color::White);
		window.draw(*animated_sprite);
		window.display();
	}

	// end
	return 0;
}

```

---

#### <a name="mentions" /> Inspirations [ [Top] ](#top)
The original animated sprite came as a test by me and a friend of mine while testing walking animations.

Go to [ [Top] ](#top)
