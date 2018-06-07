<a name="top" />

# NResource Manager/ Wrapper by Sebastian Netsch

### Content-Table:
- [Resource Manager/ Wrapper](#nresource_wrapper)
  - [Constructors](#constructors)
  - [Destructors](#destructors)
  - [External Functions](#external_functions)
  - [Internal Variables](#internal_variables)
  - [Internal Functions](#internal_functions)
  - [How to Use](#howto)
  - [Inspirations](#mentions)

#### <a name="nresource_wrapper" /> NResource Manager/ Wrapper [ [Top] ](#top)
The NResource Wrapper is a SFML Wrapper for the NResource Manager.
It operates on a NResource Manager for SFML textures, fonts and soundbuffers and additionally a "wildcard" and therefore contains all base functionalities.

It is possible to use both, but it is recommended using the NResource Wrapper when programming a SFML program.

## INFORMATION
##### In this README only the NResource Wrapper functionalities are explained.
##### For information on parameters, returns, etc. of the NResource Manager view the corresponding .hpp file.

---

#### <a name="constructors" /> Constructors [ [Top] ](#top)
This class uses a standard constructor with an initialization list.

---

#### <a name="destructors" /> Destructors [ [Top] ](#top)
This class uses the thread safe custom destructor of the NResource Manager.

---

#### <a name="external_functions" /> External Functions [ [Top] ](#top)
##### auto toggle_resource_storage() -> bool
This fucntion is used to toggle the resource storage functionality.
If activated it prevents resources from being deleted.
It checks SFML resources and "wildcard" resources.

##### auto get_resource_storage() -> bool
This fucntion is used to access the current status of the resource storage functionality.
If activated it prevents resources from being deleted.
It checks SFML resources and "wildcard" resources.

##### auto add(std::string const& key, VAL const& value) -> std::shared_ptr<const VAL>
This function adds a "wildcard" resource to the NResource Wrapper.

##### auto add_if(std::string const& key, std::string const& path) -> bool
This function adds a "wildcard" resource to the NResource Wrapper and indicates wheter or not the resource was added.

##### auto get(std::string const& key) -> std::shared_ptr<const VAL>
This function accesses the "wildcard" resource identified by key.

##### auto get_last() -> std::shared_ptr<const VAL>
This function accesses and returns the last used "wildcard" resource as a shared pointer.

##### auto swap(std::string const& key, VAL const& value) -> bool
This fucntion swaps the value of two "wildcard" resources.

##### auto get_size() -> unsigned int
This function is used to access the total amount of stored resources.
It checks SFML resources and "wildcard" resources.

##### auto clr(std::string const& key) -> bool
This function is used to erase a single "wildcard" resource.

##### auto clr_unused() -> void
This function is used to clear all unused resources.
It checks SFML resources and "wildcard" resources.

##### auto test(std::string const& key) -> bool
This function is used to test if a "wildcard" resource is in the NResource Wrapper.

##### auto load_texture(std::string const& key, std::string const& path) -> void
This function is used to load a SFML texture.

##### auto get_texture(std::string const& key) -> sf::Texture const&
This function is used to access a SFML texture by const reference.

##### auto get_texture_p(std::string const& key) -> std::shared_ptr<const sf::Texture>
This function is used to access a SFML texture as a shared pointer.

##### auto load_font(std::string const& key, std::string const& path) -> void
This function is used to load a SFML font.

##### auto get_font(std::string const& key) -> sf::Font const&
This function is used to access a SFML font by const reference.

##### auto get_font_p(std::string const& key) -> std::shared_ptr<const sf::Font>
This function is used to access a SFML font as a shared pointer.

##### auto load_soundbuffer(std::string const& key, std::string const& path) -> void
This function is used to load a SFML soundbuffer.

##### auto get_soundbuffer(std::string const& key) -> sf::SoundBuffer const&
This function is used to access a SFML soundbuffer by const reference.

##### auto get_soundbuffer_p(std::string const& key) -> std::shared_ptr<const sf::SoundBuffer>
This function is used to access a SFML soundbuffer as a shared pointer.

---

#### <a name="internal_variables" /> Internal Variables [ [Top] ](#top)
##### nresource_manager<std::string, VAL> _nresources
This variable is the "wildcard" instance of a NResource Manager.

##### nresource_manager<std::string, sf::Texture> _ntextures
This variable is the SFML texture instance of a NResource Manager.

##### nresource_manager<std::string, sf::Font> _nfonts
This variable is the SFML font instance of a NResource Manager.

##### nresource_manager<std::string, sf::SoundBuffer> _nsoundbuffers
This variable is the SFML soundbuffer instance of a NResource Manager.

---

#### <a name="internal_functions" /> Internal Functions [ [Top] ](#top)
##### NONE

---

#### <a name="howto" /> How to Use [ [Top] ](#top)
##### Including it in your project
```
#include "resource_wrapper.hpp"
```

##### Creating a Resource Manager (for std::string)
```
nengine::nresource_manager::nresource_wrapper<"wildcard" /*templated*/ > resource_management; // constructs a NResource Wrapper with keys as std::strings and values as a "wildcard"
```

##### Activating/Deactivating resource storage
```
resource_management.toggle_resource_storage(); // activating/deactivating the resource storage
```

##### Adding a SFML Resource
```
resource_management.add("texture_name", "texture.png"); // adds a SFML texture to the NResource Wrapper
resource_management.add("font_name", "font.otf"); // adds a SFML font to the NResource Wrapper
resource_management.add("sound_name", "sound.wav"); // adds a SFML soundbuffer to the NResource Wrapper
```

##### Retrieving a "wildcard" Resource as shared pointer
```
auto tmp = resource_management.get("wildcard_name"); // retrieves a "wildcard" resource by refernce and assigns it to tmp
```

##### Retrieving a SFML Texture Resource by reference
```
auto tmp = resource_management.get_texture("texture_name"); // retrieves a SFML texture by reference and assigns it to tmp
```

##### Retrieving a SFML Font Resource as shared pointer
```
auto tmp = resource_management.get_texture_p("texture_name"); // retrieves a SFML texture as a shared pointer and assigns it to tmp
```

##### Accessing the amount of all stored resources
```
unsigned int tmp = resource_management.get_size(); // fills tmp with the amount of "wildcard" and all SFML resources stored, if it's empty it will return 0
```

##### Clearing unused resources of all stored resources
```
resource_management.clr_unused(); // resets every pointer and erases every resource that is only pointed to by the resource manager, if _keep_resources was set to true nothing happens
```

---

#### <a name="mentions" /> Inspirations [ [Top] ](#top)
This resource manager is a heavely adjusted form for this engine from the asset manager by the youtube channel "Sonar Systems".

Go to [ [Top] ](#top)
