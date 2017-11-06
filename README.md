NEngine by Sebastian Netsch
===========================

Content-Table:
--------------
> What it is and isn't
> NState Manager/ NState
> NLayer
> NResource Manager/ Wrapper
> NParticle System
> NInput Manager
> NAnimator (not yet implemented)
> NPhysics (not yet implemented)

1) What it is and isn't
-----------------------
This is a simple SFML 2D game engine.
It contains multiple parts to make your programming with SFML much easier.

What it is and what it isn't:
> + it's a SFML wrapper-like ragbag of utilities
> + it's a basic 2d game engine
> + it's a one-header-only include
> + it's thread safe
> + an engine able to animate SFML sprites
> - not a library
> - not a complex one-in-all solution to all problems SFML related
> - not (yet) a physics engine
> - not a system that does everything on its own (can't predict what e.g. happens after an input)

You basically should check this README-file and decide for yourself.

Now that that's out of the way let's look at the first component.

### INFORMATION
### For further information view the corresponding README.md file of each component.
### For detailed information on parameters, returns, etc. view the corresponding .hpp file of each component.

2) NState Manager/ NState
-------------------------
The NState Manager manages your, from the virtual class NState derived, state classes.
A state in the NEngine is a state your program can be in, e.g. a state could be your main menu or your game loop.

The NState is a class with only virtual functions. It acts as a base class.
You have to implement the virtual functions in your derived class.

The NState Manager watches your states, keeps them in storage or deletes them.
With it you can give your program a basic structure.

3) NLayer
---------
A NLayer is a layer over e.g. a NState. It contains and wraps multiple SFML sprites and texts.
You can call a SFML RenderWindows' draw function on it directly.

You should keep a boolean to check if a NLayer should be drawn and/ or if it should handle any input.
The NLayer itself does not handle any input. It doesnt' know what should happen if a specific element is triggered.

4) NResource Manager/ Wrapper
-----------------------------
The NResource Wrapper relies on the NResource Manager and is a SFML wrapper for it.
You can use the NResource Wrapper to store SFML textures, fonts and Soundbuffers. You have one wildcard storage too.

If you use the raw NResource Manager you have use a templated class but can store whatever you want in there.
You have to use multiple NResource Managers to store multiple types of data.

5) NParticle System
-------------------
The NParticle System can display one-pixel-wide particles of any SFML Color. You can assign them a live span that degrades over time.
You have to manually call the update function but this is a one-liner.

You could hand over a shared pointer to the NParticle System so any class you want can emit particles.

For easier use you can just call the SFML RenderWindows' draw function on it as a whole.

6) NInput Manager
-----------------
The NInput Manager is there to check if a click or any SFML Mouse Event occured on a SFML sprite.
You have to stuff the SFML sprite, the wanted SFML Mouse Event and the SFML RenderWindow in the check function and you can then decide on a boolean what to do.

7) NAnimator
----------------------------------
The NAnimator is a multitude of SFML sprite wrapper classes.
All contained classes have one thing in common: They have some sort of animation going on (e.g. one still animation or one still animation and four basic directions).

8) NPhysics (not yet implemented)
---------------------------------

