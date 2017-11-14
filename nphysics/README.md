<a name="top" />

# NState Manager by Sebastian Netsch

### Content-Table:
- [NCollision Manager](#ncollision_manager)
  - [NPolygon](#npolygon)
  - [Constructors](#constructors)
  - [Destructors](#destructors)
  - [External Functions](#external_functions)
  - [Internal Variables](#internal_variables)
  - [Internal Functions](#internal_functions)
  - [How to Use](#howto)
  - [Inspirations](#mentions)

---

#### <a name="ncollision_manager" /> NCollision Manager [ [Top] ](#top)
This class is used to manage collisions.

----

#### <a name="npolygon" /> NPolygon [ [Top] ](#top)
This class is used to build a convex polygon that can be tested for collisions.

----

#### <a name="constructors" /> Constructors [ [Top] ](#top)
The included classes are using various own constructors.
The npolygon class uses a default constructor with an initialization list for constructing either with a SFML Color or a SFML Texture.
The ncollision_manager class uses a standard constructor with initialization list.

##### npolygon(std::vector<sf::Vector2f> const& points, sf::Color const& color, sf::Vector2f const& position)
This constructor creates a convex npolygon with a color.

##### npolygon(std::vector<sf::Vector2f> const& points, std::shared_ptr<const sf::Texture> texture, sf::Vector2f const& position)
This constructor creates a convex npolygon with a texture.

---

#### <a name="destructors" /> Destructors [ [Top] ](#top)
This class uses a standard destructor.

---

#### <a name="external_functions" /> External Functions [ [Top] ](#top)
##### auto set_position(sf::Vector2f const& position) -> void

##### auto get_position() const -> sf::Vector2f

##### auto set_color(sf::Color const& color) -> void

##### auto get_color() -> sf::Color

##### auto get_axes() const -> std::vector<sf::Vector2f>

##### auto get_points() const -> const std::vector<sf::Vector2f>

---

#### <a name="internal_variables" /> Internal Variables [ [Top] ](#top)
##### std::mutex _mutex
This variable is used for thread safe access.

##### sf::ConvexShape _convex
This is the SFML ConvexShape used for this npolygon.

##### std::shared_ptr<const sf::Texture> _texture
This is the npolygons shared SFML Texture pointer. It is not set, when the npolygon  only got a color.

##### sf::Vector2f _centroid
This is the npolygons original centroid.

---

#### <a name="internal_functions" /> Internal Functions [ [Top] ](#top)
##### auto _get_drawable_axes() const -> const std::vector<sf::VertexArray>
This function is used to access a npolyons axes as drawables.

##### auto _is_convex(std::vector<sf::Vector2f> const& points) -> bool
This function is needed to find out, if a vector of points really forms a convex shape.

##### auto _create_convex(std::vector<sf::Vector2f> const& points) -> void
This function is used to create the SFML ConvecShape.

##### auto _calculate_centroid() -> void
This function is used to calculate the convec shapes original centroid.

##### virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {[...]}
This function is used for drawing. Altering the boolean value "debug" inside let's you draw the npolygons axes.

---

#### <a name="howto" /> How to Use [ [Top] ](#top)
##### Including it in your project
```
#include "nphysics.hpp"
```

##### Testing the collision between two sprites
```
// declaring and initializing vector of vehicles
std::vector<sf::Sprite> vehicles;

// declaring and adding two sprites into the vector
[...]

// creating a ncollision manager
nengine::nphysics::ncollision_manager collision_manager;

// checking vehicle 0 and 1 against each other (here: not in a loop as it is preferred!)
sf::Vector2f mtv = collision_manager.check(vehicles.at(0), vehicles.at(1), 30.0); // 30.0 is the pushing force taken into the minimum translation vector

// check for having to move at all --> not neccessary!
if((mtv.x != 0) || (mtv.y != 0))
{
	vehicles.at(i)->update_position(mtv.x, -mtv.y); // here update_position operates on the current position and adds the parameter value
	vehicles.at(j)->update_position(-mtv.x, mtv.y); // here update_position operates on the current position and adds the parameter value
}
```

---

#### <a name="mentions" /> Inspirations [ [Top] ](#top)
The original was written by the github users "inzombiak" and "pabab".
It was then adjusted for usage in this engine.

Go to [ [Top] ](#top)
