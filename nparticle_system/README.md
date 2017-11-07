<a name="top" />
# NParticle System by Sebastian Netsch

### Content-Table:
- [NParticle System](#nparticle_system)
  - [NParticle](#nparticle)
  - [Constructors](#constructors)
  - [Destructors](#destructors)
  - [External Functions](#external_functions)
  - [Internal Variables](#internal_variables)
  - [Internal Functions](#internal_functions)
  - [How to Use](#howto)

---

#### <a name="nparticle_system" /> NParticle System [ [Top] ](#top)
This class is used to add particles to ones program.
It operates on the class NParticle.

---

#### <a name="nparticle" /> NParticle [ [Top] ](#top)
This is the base class for a single particle.

---

#### <a name="constructors" /> Constructors [ [Top] ](#top)
This class has a standard constructor with initialization list that sets standard values and a non standard constructor as followed:

##### nparticle_system(float gravitation_x, float gravitation_y, unsigned int maximum)
This constructor assigns the gravity and the maximum NParticle count as wanted by the user.

---

#### <a name="destructors" /> Destructors [ [Top] ](#top)
This class used a custom but thread safe destructor.

---

#### <a name="external_functions" /> External Functions [ [Top] ](#top)
##### auto add(unsigned int n, float live_span, float decay_rate, sf::Color color, float pos_x, float pos_y, float speed_x, float speed_y) -> void
This function is used to add n amount of NParticles to the NParticle System.

##### auto update(float delta_time) -> void
This function needs to be called to update all NParticles and should be part of your programs main loop.

##### auto get_amount() -> unsigned int
This function is used to look up the current amount of NParticles.
It almost always contains some dead particles as well.

##### auto set_gravity(float x, float y) -> void
This function is used to manually set the gravitational force applied to your NParticles.

##### auto set_max(unsigned int maximum) -> void
This function is used to manually set the maximum amount of NParticles.

##### auto clr() -> void
This function clears **all** particles in the NParticle Manager.
Only call this function if you are absolutely you don't need your NParticles any longer.

---

#### <a name="internal_variables" /> Internal Variables [ [Top] ](#top)
##### sf::Vector2f _gravity
This variable is the gravitational force applied on your NParticles.

##### sf::Color _transparent
This is a SFML color set to transparent to reset a NParticles SFML color.
It currently is DEPRECATED!

##### unsigned int _max
This variable resembles the maximum amount of NParticles your NParticle System can contain.

##### std::mutex _mutex
This variable is used for thread safe operations.

---

#### <a name="internal_functions" /> Internal Functions [ [Top] ](#top)
##### auto _create(float live_span, float decay_rate, sf::Color color, float pos_x, float pos_y, float speed_x, float speed_y) -> void
This function is used to create a new NParticle and add it to the NParticle System. It is called when you add a particle.

##### inline auto _update_health_points(unsigned int pos) -> void
This function updates a NParticles healthpoints/ live span.

##### inline auto _update_pos(unsigned int pos, float delta_time) -> void
This function updates a NParticles position.

##### auto _delete_dead() -> void
This function iterates over all NParticles in the NParticle System and deletes every dead NParticle.

##### void draw(sf::RenderTarget &target, sf::RenderStates states) const {[...]}
This function is used to allow easy drawing of all NParticles by allowing you to call a SFML RenderWindows' draw function on it directly.

---

#### <a name="howto" /> How to Use [ [Top] ](#top)
##### Including it in your project
```
#include "nparticle_system.hpp"
```

##### Constructing a new NParticle System
```
nengine::nparticle_system::nparticle_system particle_system; // construct a NParticle System to allow you to add particles to your program
```

##### Adding NParticles
```
particle_system.add(1, 100.0, 1.0, sf::Color::White, 0.0, 0.0, 0.1, 0.1); // adds 1 white NParticle to your NParticle System that will live for 100 ticks and travels at 0.1 pixels per tick in x and y direction
```

##### Updating your NParticle System
```
particle_system.update(delta_time); // updates all NParticles in your NParticle System with a computed delta_time
```

##### Drawing your NParticle System
```
window.draw(particle_system); // draws all NParticles in your NParticle System with window being a SFML RenderWindow
```

Go to [ [Top] ](#top)
