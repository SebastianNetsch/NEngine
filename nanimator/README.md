# NAnimator by Sebastian Netsch
---

### Content-Table:
- NAnimator
  - NPose
  - Constructors
  - Destructors
  - External Functions
  - Internal Variables
  - Internal Functions
  - How to Use

#### NAnimator
This class is used to easily gain access to animated SFML sprites.

---

#### NPose
This enum class resembles the sprites pose.

---

#### Constructors
This class uses a custom constructor with initialization list.

---

#### Destructors
This class uses the standard destructor.

---

#### External Functions
##### auto set_position(float x, float y) -> void
This function is used to set the initial position.

##### auto still() -> void
This function is used to display the still animation.

##### auto left() -> void
This function is used to cycle through the left animation.

##### auto right() -> void
This function is used to cycle through the right animation.

##### auto up() -> void
This function is used to cycle through the up animation.

##### auto down() -> void
This function is used to cycle through the down animation.

##### auto add_still(unsigned int steps, std::shared_ptr<const sf::Texture> texture, unsigned int step_size, float step_duration, int x_coordinate, int y_coordinate, int width, int height) -> void
This function is used to add a still animation on a seperated spritesheet.

##### auto add_still(unsigned int steps, std::shared_ptr<const sf::Texture> texture, unsigned int step_size, unsigned int sheet_row, float step_duration, int x_coordinate, int y_coordinate, int width, int height) -> void
This function is used to add a still animation on a combinded spritesheet where every animation is in a single row.

##### auto add_left(unsigned int steps, std::shared_ptr<const sf::Texture> texture, unsigned int step_size, float step_duration, int x_coordinate, int y_coordinate, int width, int height) -> void
This function is used to add a still animation on a seperated spritesheet.

##### auto add_left(unsigned int steps, std::shared_ptr<const sf::Texture> texture, unsigned int step_size, unsigned int sheet_row, float step_duration, int x_coordinate, int y_coordinate, int width, int height) -> void
This function is used to add a still animation on a combinded spritesheet where every animation is in a single row.

##### auto add_right(unsigned int steps, std::shared_ptr<const sf::Texture> texture, unsigned int step_size, float step_duration, int x_coordinate, int y_coordinate, int width, int height) -> void
This function is used to add a still animation on a seperated spritesheet.

##### auto add_right(unsigned int steps, std::shared_ptr<const sf::Texture> texture, unsigned int step_size, unsigned int sheet_row, float step_duration, int x_coordinate, int y_coordinate, int width, int height) -> void
This function is used to add a still animation on a combinded spritesheet where every animation is in a single row.

##### auto add_up(unsigned int steps, std::shared_ptr<const sf::Texture> texture, unsigned int step_size, float step_duration, int x_coordinate, int y_coordinate, int width, int height) -> void
This function is used to add a still animation on a seperated spritesheet.

##### auto add_up(unsigned int steps, std::shared_ptr<const sf::Texture> texture, unsigned int step_size, unsigned int sheet_row, float step_duration, int x_coordinate, int y_coordinate, int width, int height) -> void
This function is used to add a still animation on a combinded spritesheet where every animation is in a single row.

##### auto add_down(unsigned int steps, std::shared_ptr<const sf::Texture> texture, unsigned int step_size, float step_duration, int x_coordinate, int y_coordinate, int width, int height) -> void
This function is used to add a still animation on a seperated spritesheet.

##### auto add_down(unsigned int steps, std::shared_ptr<const sf::Texture> texture, unsigned int step_size, unsigned int sheet_row, float step_duration, int x_coordinate, int y_coordinate, int width, int height) -> void
This function is used to add a still animation on a combinded spritesheet where every animation is in a single row.

---

#### Internal Variables
##### std::mutex _mutex
This variable is needed for thread safety.

##### std::vector<sf::IntRect> _still_animation
A vector of sf::IntRect used to access and cycle through the animation spritesheet.

##### std::vector<sf::IntRect> _left_animation
A vector of sf::IntRect used to access and cycle through the animation spritesheet.

##### std::vector<sf::IntRect> _right_animation
A vector of sf::IntRect used to access and cycle through the animation spritesheet.

##### std::vector<sf::IntRect> _up_animation
A vector of sf::IntRect used to access and cycle through the animation spritesheet.

##### std::vector<sf::IntRect> _down_animation
A vector of sf::IntRect used to access and cycle through the animation spritesheet.

##### std::shared_ptr<const sf::Texture> _still_texture
This variable is the texture used for the still animation.

##### std::shared_ptr<const sf::Texture> _left_texture
This variable is the texture used for the left animation.

##### std::shared_ptr<const sf::Texture> _right_texture
This variable is the texture used for the right animation.

##### std::shared_ptr<const sf::Texture> _up_texture
This variable is the texture used for the up animation.

##### std::shared_ptr<const sf::Texture> _down_texture
This variable is the texture used for the down animation.

##### unsigned int _still_iterator
This variable resembles the iterator used to cycle through the animation.

##### unsigned int _left_iterator
This variable resembles the iterator used to cycle through the animation.

##### unsigned int _right_iterator
This variable resembles the iterator used to cycle through the animation.

##### unsigned int _up_iterator
This variable resembles the iterator used to cycle through the animation.

##### unsigned int _down_iterator
This variable resembles the iterator used to cycle through the animation.

##### float _still_duration
This is the amount of time, in seconds, used for one animation cycle.

##### float _left_duration
This is the amount of time, in seconds, used for one animation cycle.

##### float _right_duration
This is the amount of time, in seconds, used for one animation cycle.

##### float _up_duration
This is the amount of time, in seconds, used for one animation cycle.

##### float _down_duration
This is the amount of time, in seconds, used for one animation cycle.

##### sf::Clock _animation_clock
This is the animation clock.

##### sf::Sprite _sprite
This is the SFML sprite that is used to draw the animations.

##### pose _pose
This variable determines which pose the sprite is in.

---

#### Internal Functions
##### virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {target.draw(_sprite, states);};
This function is the SFML function for drawing an object.

---

#### How to Use
##### Including it in your project
```
```
