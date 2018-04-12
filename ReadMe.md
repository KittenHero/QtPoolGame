# Qt Pool

Qt Pool is a simple pool game written in C++ with Qt5.  The code is structured
into 3 main layer.  The control layer, consisting of the SceneManager which
provides a high level interface for updating and rendering the scene.
A game object layer, SimpleBall and SimpleTable, which holds data object
specific drawing code.  And a layer for interfacing between them, consisting
of abstract Ball, Table and Creator classes, the Graphic interface and
the SimpleCreator and SceneBuilder class.

![Digram of classes involved in the project](class.png)

The SceneManager acts as a facade between the client and implementation
of objects by providing a simple interface for controlling
the physics and rendering the scene. The main physics logic is contained
within this class and relies on the abstract ball and table which exposes
their members as public.  On the other hand, rendering is delegated to
each object contained in the scene, using the composite pattern,
so it can easily be modifed or extended by switching out the concrete classes.

The facade pattern implemented by the SceneManager provides a low cost
abstraction for the coupling between the movement of the balls and the friction
of the table.  Combined with the composite pattern, it makes the code base
much easier to read and maintain, however it also limits the extent to which
the top level object can control the scene.

The Creator class facilitates easy instantiation of the scene without
coupling with the concrete ball and table classes, by providing a template
factory method for instantiating the scene and two factory method interface
for instatiating the ball and table.  This allows the client to switch between
various types of balls and tables simply by inheriting from the Creator and
implementing the initailisation logic of the concrete classes.

The use of the abstact factory and builder patterns in the Creator class
is also beneficial in removing a telescoping constructor antipattern
by providing JSON interface for configuring the scene and each object.
