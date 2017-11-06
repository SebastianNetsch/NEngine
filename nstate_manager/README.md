NState Manager by Sebastian Netsch
==================================

Content-Table:
--------------
> NState Manager
> > NState
> > Constructors
> > Destructors
> > External Functions
> > Internal Variables
> > Internal Functions
> > How to Use

NState Manager
--------------
This class is used to manage a programs states.

NState
------
This class is used to build a new state your program can be in.

## Constructors
This class uses a default constructor with an initialization list.

## Destructors
This class uses a thread safe custom destructor.

## External Functions
# auto add(std::unique_ptr<nstate> state, bool replacing) -> void
This function is used to add a NState to the NState Manager.
The new NState can be emplaced on top of the current NState or it can replace it.

# auto remove() -> void
This sets a variable to remove the current NState from the NState Manager.
This remove happens at the next call of the process() function.

# auto process() -> void
This is the central part of the NState Manager. It processes all changes that happened since the last call of this function.
It processes all the removes and adds that happened in the last iteration.

# auto get() -> std::unique_ptr<nstate>&
This function is used to access the current NState.

## Internal Variables
# std::mutex _mutex (_ to counter md systax)
This variable is used for thread safe access.

# std::stack<std::unique_ptr<nstate>> _states (_ to counter md systax)
This is the stack of NStates. Each NState can be viewed as an encapsulated part of your program that needs to be able to run and manage itself on it's own.

# std::unique_ptr<nstate> _state (_ to counter md systax)
This is a unique pointer to the current state on hold.
What happens to it get's decided at the next call of the process() function.

# bool _removing (_ to counter md systax)
This variable is an indicator if the current NState is going to be removed at the next call of the process() function.

# bool _adding (_ to counter md systax)
This variable is an indicator if a new NState is going to be added at the next call of the process() function.

# bool _replacing (_ to counter md systax)
This variable is an indicator if the current NState is going to be replaced with a new one at the next call of the process() function.

## Internal Functions
# NONE

## How to Use
# Including it in your project
```
#include "nstate_manager.hpp"
```

# Standard SFML Main Loop with the NState Manager
```
[...]

nengine::nstate_manager::nstate_manager state_manager; // creates the NState Manager
while(window.isOpen())
{
	state_manager->process(); // process and react to changes made to the NStates
	state_manager->handle(); // handle events in the current state
	state_manager->update(delta_time); // update everything in the state
	state_manager->draw(interpolarization); // draw everything in the state
}

[...]
```

# Standard derived class from NState
new_state.hpp:
```
[...]

#include "nstate.hpp"
class new_state : nenine::nstate_manager::nstate
{
	public:
		new_state(nengine::nstate_manager::nstate_manager& state_manager);
		void init(); // assign values etc
		void pause(); // do something if the state is paused / used mostly for lost focus
		void resume(); // do something if the state is resumed / used mostly for gained focus
		void handle(); // handle all input
		void update(); // update all members
		void draw(); // draw all members
	private:
		nengine::nstate_manager::nstate_manager& _state_manager; // a reference to the state_manager so the NState can add a new NState or remove/ replace itself
		[...] // all your sprites/ texts/ etc
}

[...]
```

new_state.cpp:
```
[...]

#include "new_state.hpp"

new_state(nengine::nstate_manager::nstate_manager& state_manager)
	: _state_manager(state_manager)
{}

void init()
{
	 // assign values etc
}

void pause()
{
	// do something if the state is paused / used mostly for lost focus
}

void resume()
{
	// do something if the state is resumed / used mostly for gained focus
}

void handle()
{
	// handle all input
}

void update()
{
	// update all members
}

void draw()
{
	// draw all members
}

[...]
```
