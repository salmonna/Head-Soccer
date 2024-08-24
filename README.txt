# Head Soccer


Head Soccer is a soccer simulation game where players control avatars with special powers to score goals against opponents.
The game features various states, power-ups, and AI-controlled players to provide an engaging gameplay experience.

## Author: 


Yosef Tadesse
Daniel Zalka
Selemon Neguse  

## Data Structures:


- **Classes**: Defined for game objects, player states, powers, and UI components.
- **Factories**: For creating static and moving objects using the Factory design pattern.
- **State Pattern**: For handling different player movement states.

## Algorithms:


- **Collision Detection**: Handled by the `CollisionHandling` class to manage interactions between game objects.
- **Physics Simulation**: Implemented using the Box2D physics engine for realistic movement and interactions.
- **AI Behavior**: For computer-controlled players to simulate opponent actions.

## Design:


- **Object-Oriented Design**: Utilizing classes and inheritance to model game objects and behavior.
- **Design Patterns**: Factory pattern for object creation, State pattern for player movements.
- **Modular Architecture**: Separation of concerns with distinct classes for different functionalities,
- **making the codebase easier to maintain and extend.
