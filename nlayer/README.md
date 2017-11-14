<a name="top" />

# NLayer by Sebastian Netsch

### Content-Table:
- [NLayer](#nlayer)
  - [NSprite](#nsprite)
  - [NText](#ntext)
  - [Constructors](#constructors)
  - [Destructors](#destructors)
  - [External Functions](#external_functions)
  - [Internal Variables](#internal_variables)
  - [Internal Functions](#internal_functions)
  - [How to Use](#howto)
  - [Inspirations](#mentions)

---

#### <a name="nlayer" /> NLayer [ [Top] ](#top)
This class is used to easily group SFML sprites and texts to a layer.

---

#### <a name="nsprite" /> NSprite [ [Top] ](#top)
This class is the wrapper for a SFML sprite.

---

#### <a name="ntext" /> NText [ [Top] ](#top)
This class is the wrapper for a SFML text.

---

#### <a name="constructors" /> Constructors [ [Top] ](#top)
This class uses standard constructor with initialization list.

---

#### <a name="destructors" /> Destructors [ [Top] ](#top)
This class uses standard destructor.

---

#### <a name="external_functions" /> External Functions [ [Top] ](#top)
##### auto add_sprite(std::string const& key, float x, float y, std::shared_ptr<const sf::Texture> tex) -> void
This function is used to add a SFML sprite to the layer.

##### auto add_text(std::string const& key, float x, float y, std::shared_ptr<const sf::Font> font, std::string const& title, unsigned int char_size, sf::Color const& fill_color, unsigned int outline_size, sf::Color const& outline_color) -> void
This function is used to add a SFML text to the layer.

##### auto get_sprite(std::string const& key) -> sf::Sprite&
This function is used to return the internal SFML sprite identified by the key.

##### auto toggle_visible() -> void
This function is used to toggle the layers visibility.

##### auto get_visible() -> bool
This function is used to check if a layer is visible.

---

#### <a name="internal_variables" /> Internal Variables [ [Top] ](#top)
##### std::mutex _mutex
This variable is needed for thread safe access.

##### bool _enabled
This variable is used to mark the layer as enabled or not.

##### std::map<std::string, std::shared_ptr<nsprite>> _nsprites
This container is used to store shared pointers to NSprites.

##### std::map<std::string, std::shared_ptr<ntext>> _ntext
This container is used to store shared pointers to NTexts.

---

#### <a name="internal_functions" /> Internal Functions [ [Top] ](#top)
##### void draw(sf::RenderTarget &target, sf::RenderStates states) const {[...]}
This function is used to draw all SFML sprites and texts in the layer

---

#### <a name="howto" /> How to Use [ [Top] ](#top)
##### Including it in your project
```
#include "nlayer.hpp"
```

##### Constructing a new NLayer
```
nengine::nlayer::nlayer gui_layer; // construct a NLayer for the gui
```

##### Adding a Sprite and a Text to the NLayer
```
gui_layer.add_text("Character Name", 10.0, 10.0, gui_name_font, "Fluriman Hansson", 20, sf::Color::White, 1, sf::Color::Black); // add a SFML text, gui_name_font being a SFML Font
gui_layer.add_sprite("GUI Background", 0.0, 0.0, gui_background_texture); // add a SFML Sprite, gui_background_texture being a SFML texture
```

##### Drawing the NLayer
```
window.draw(gui_layer); // first all sprites get drawn, then all texts, window being a sf::RenderWindow
```

---

#### <a name="mentions" /> Inspirations [ [Top] ](#top)
The original idea for grouping together drawable objects came from a friend of mine who used this in a own Test-C#-RPG a while back.

Go to [ [Top] ](#top)
