<a name="top" />
# NInput Manager by Sebastian Netsch

### Content-Table:
- [NInput Manager](#ninput_manager)
  - [Constructors](#constructors)
  - [Destructors](#destructors)
  - [External Functions](#external_functions)
  - [Internal Variables](#internal_variables)
  - [Internal Functions](#internal_functions)
  - [How to Use](#howto)

---

#### <a name="ninput_manager" /> NInput Manager [ [Top] ](#top)
This class is used to easily gain access to SFML events and custom key binding.

---

#### <a name="constructors" /> Constructors [ [Top] ](#top)
This class uses standard constructor with initialization list.

---

#### <a name="destructors" /> Destructors [ [Top] ](#top)
This class uses standard destructor.

---

#### <a name="external_functions" /> External Functions [ [Top] ](#top)
##### auto clicked(sf::Sprite const& object, sf::Mouse::Button const& button, sf::RenderWindow const& window) -> bool
This function checks if a sprite (object) was clicked by the mouse button (button) in the RenderWindow (window) and returns a bool to indicate if the click happened on the sprite

##### auto get_mouse_position(sf::RenderWindow const& window) -> sf::Vector2i
This function gets the mouse position (sf::Mouse) relative to the RenderWindow (window) and returns the relative position.

##### auto add_bind(std::string const& key, sf::Keyboard::Key const& input) -> void
This function adds a custom bind a sf::Keyboard::Key.

##### auto add_bind(std::string const& key, sf::Mouse::Button const& input) -> void
This function adds a custom bind a sf::Mouse::Button.

##### auto change_bind(std::string const& key, sf::Keyboard::Key const& input) -> void
This function is used to change a custom bind of a sf::Keyboard::Key.

##### auto change_bind(std::string const& key, sf::Mouse::Button const& input) -> void
This function is used to change a custom bind of a sf::Mouse::Button.

##### auto check_bind(std::string const& key) -> bool
This function checks all custom bindings for a match.

---

#### <a name="internal_variables" /> Internal Variables [ [Top] ](#top)
##### _mutex
This variable is needed for thread safe access.

##### std::unordered_map<std::string, std::shared_ptr<nkey>> _key_bindings
This variable is used for custom key bindings.

---

#### <a name="internal_functions" /> Internal Functions [ [Top] ](#top)
##### NONE

---

#### <a name="howto" /> How to Use [ [Top] ](#top)
##### Including it in your project
```
#include "ninput_manager.hpp"
```

##### Constructing a new NInput Manager
```
nengine::ninput_manager::ninput_manager input_manager; // construct a NInput Manager to handle all SFML Events
```

##### Checking a SFML Mouse click
```
if(input_manager.clicked(sprite, sf::Mouse::Left, window)) // checks if a SFML sprite (sprite) was clicked with the left mouse button in the SFML RenderWindow (window)
{
	// some operations
}
```

##### Adding a custom sf::Keyboard::Key bind
```
// these lines bind the basic wasd movement to the arrow keys
input_manager.add_bind("Forward", sf::Keyboard::Up);
input_manager.add_bind("Left", sf::Keyboard::Left);
input_manager.add_bind("Backward", sf::Keyboard::Down);
input_manager.add_bind("Right", sf::Keyboard::Right);
```

##### Adding a custom sf::Mouse::Button bind
```
// these lines bind the left and right mouse click to it's counterpart
input_manager.add_bind("RightMouseButton", sf::Mouse::Left);
input_manager.add_bind("LeftMouseButton", sf::Mouse::Right);
```

##### Checking a custom bind
```
if(input_manager.check_bind("Forward")) // <-- this eliminates the need for checking (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) or (sf::Mouse::isButtonPressed(sf::Mouse::Left)) etc. That's what it does internally.
{
	// move some stuff
}
```

Go to [ [Top] ](#top)
