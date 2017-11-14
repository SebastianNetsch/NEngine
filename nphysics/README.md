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
This class uses a default constructor with an initialization list for constructing either with a SFML Color or a SFML Texture.

---

#### <a name="destructors" /> Destructors [ [Top] ](#top)
This class uses a standard destructor.

---

#### <a name="external_functions" /> External Functions [ [Top] ](#top)
##### TBA

---

#### <a name="internal_variables" /> Internal Variables [ [Top] ](#top)
##### std::mutex _mutex
This variable is used for thread safe access.

##### TBA

---

#### <a name="internal_functions" /> Internal Functions [ [Top] ](#top)
##### TBA

---

#### <a name="howto" /> How to Use [ [Top] ](#top)
##### Including it in your project
```
#include "nphysics.hpp"
```

---

#### <a name="mentions" /> Inspirations [ [Top] ](#top)
The original was written by the github users "inzombiak" and "pabab".
It was then adjusted for usage in this engine.

Go to [ [Top] ](#top)
