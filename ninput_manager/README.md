# NInput Manager by Sebastian Netsch
---

### Content-Table:
- NInput Manager
  - Constructors
  - Destructors
  - External Functions
  - Internal Variables
  - Internal Functions
  - How to Use

---

#### NInput Manager
This class is used to easily gain access to SFML events.

---

#### Constructors
This class uses standard constructor with initialization list.

---

#### Destructors
This class uses standard destructor.

---

#### External Functions
##### auto clicked(sf::Sprite const& object, sf::Mouse::Button const& button, sf::RenderWindow const& window) -> bool
This function checks if a sprite (object) was clicked by the mouse button (button) in the RenderWindow (window) and returns a bool to indicate if the click happened on the sprite

##### auto get_mouse_position(sf::RenderWindow const& window) -> sf::Vector2i
This function gets the mouse position (sf::Mouse) relative to the RenderWindow (window) and returns the relative position.

---

#### Internal Variables
##### _mutex
This variable is needed for thread safe access.

---

#### Internal Functions
##### NONE

#### How to Use
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
