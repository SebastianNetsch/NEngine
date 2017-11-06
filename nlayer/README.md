NLayer by Sebastian Netsch
==========================

Content-Table:
--------------
> NLayer
> > NSprite
> > NText
> > Constructors
> > Destructors
> > External Functions
> > Internal Variables
> > Internal Functions
> > How to Use

NLayer
------
This class is used to easily group SFML sprites and texts to a layer.

NSprite
-------
This class is the wrapper for a SFML sprite.

NText
-----
This class is the wrapper for a SFML text.

## Constructors
This class uses standard constructor with initialization list.

## Destructors
This class uses standard destructor.

## External Functions
# auto add_sprite(std::string const& key, float x, float y, std::shared_ptr<const sf::Texture> tex) -> void
This function is used to add a SFML sprite to the layer.

# auto add_text(std::string const& key, float x, float y, std::shared_ptr<const sf::Font> font, std::string const& title, unsigned int char_size, sf::Color const& fill_color, unsigned int outline_size, sf::Color const& outline_color) -> void
This function is used to add a SFML text to the layer.

# auto get_sprite(std::string const& key) -> sf::Sprite&
This function is used to return the internal SFML sprite identified by the key.

# auto toggle_visible() -> void
This function is used to toggle the layers visibility.

# auto get_visible() -> bool
This function is used to check if a layer is visible.

## Internal Variables
# std::mutex _mutex (_ to counter md systax)
This variable is needed for thread safe access.

# bool _enabled (_ to counter md systax)
This variable is used to mark the layer as enabled or not.

# std::map<std::string, std::shared_ptr<nsprite>> _nsprites (_ to counter md systax)
This container is used to store shared pointers to NSprites.

# std::map<std::string, std::shared_ptr<ntext>> _ntext (_ to counter md systax)
This container is used to store shared pointers to NTexts.

## Internal Functions
# void draw(sf::RenderTarget &target, sf::RenderStates states) const {[...]}
This function is used to draw all SFML sprites and texts in the layer

## How to Use
# Including it in your project
```
#include "nlayer.hpp"
```

# Constructing a new NLayer
```
nengine::nlayer::nlayer gui_layer; // construct a NLayer for the gui
```

# Adding a Sprite and a Text to the NLayer
```
gui_layer.add_text("Character Name", 10.0, 10.0, gui_name_font, "Fluriman Hansson", 20, sf::Color::White, 1, sf::Color::Black); // add a SFML text, gui_name_font being a SFML Font
gui_layer.add_sprite("GUI Background", 0.0, 0.0, gui_background_texture); // add a SFML Sprite, gui_background_texture being a SFML texture
```

# Drawing the NLayer
```
window.draw(gui_layer); // first all sprites get drawn, then all texts, window being a sf::RenderWindow
```
