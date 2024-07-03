
# Head Soccer
--------------------

## Author: 

Yosef Tadesse (ID: 328858048)
Daniel Zalka (ID: 320436603)
Selemon Neguse (ID: 324734433)  

## General Explanation:
--------------------
Head Soccer is a soccer simulation game where players control avatars with special powers to score goals against opponents.
The game features various states, power-ups, and AI-controlled players to provide an engaging gameplay experience.

## Files Created:
--------------------
- **Button.h + Button.cpp**: Handles the creation and functionality of buttons in the UI.
- **Command.h**: Defines an interface for executing commands.
- **Quit.h + Quit.cpp**: Manages the functionality to quit the game or application.
- **Sound.h + Sound.cpp**: Controls sound effects and music playback.
- **SwichScreen.h + SwichScreen.cpp**: Handles switching between different screens or views in the application.
- **StaticFactory.h + StaticFactory.cpp**: Provides a factory pattern for creating static objects.
- **BaseMovePlayerState.h + BaseMovePlayerState.cpp**: Defines a base state for player movements.
- **JumpMoveState.h + JumpMoveState.cpp**: Implements the jumping state for player movements.
- **MovingFactory.h + MovingFactory.cpp**: Provides a factory pattern for creating moving objects.
- **Board.h + Board.cpp**: Manages the game board, including layout and elements.
- **Box2d.h + Box2d.cpp**: Integrates the Box2D physics engine for handling physics simulations.
- **GameModeSelection.h + GameModeSelection.cpp**: Manages the game mode selection screen.
- **Client.h + Client.cpp**: Handles client-side networking functionality.
- **GameResults.h + GameResults.cpp**: Displays and manages game results.
- **GameSetting.h + GameSetting.cpp**: Manages game settings and configurations.
- **GameState.h**: Defines different states the game can be in.
- **Ball.h + Ball.cpp**: Represents the ball object in the game.
- **ComputerPlayer.h + ComputerPlayer.cpp**: Implements the behavior of a computer-controlled player.
- **KickMoveState.h + KickMoveState.cpp**: Implements the kicking state for player movements.
- **Menu.h + Menu.cpp**: Manages the main menu and navigation.
- **GameObject.h + GameObject.cpp**: Defines the base class for all game objects.
- **LeftMoveState.h + LeftMoveState.cpp**: Implements the state for moving left.
- **Pause.h + Pause.cpp**: Manages the pause functionality in the game.
- **Goal.h**: Represents a goal object in the game.
- **GoalBack.h + GoalBack.cpp**: Represents the back part of a goal.
- **RightMoveState.h + RightMoveState.cpp**: Implements the state for moving right.
- **SelectTeam.h + SelectTeam.cpp**: Manages the team selection screen.
- **CMakeLists**: Configuration file for CMake build system.
- **CollisionHandling.h + CollisionHandling.cpp**: Manages collision detection and response.
- **Controller.h + Controller.cpp**: Handles input from controllers.
- **FileException.h**: Defines exceptions related to file handling.
- **Keyboard.h**: Manages keyboard input.
- **Resources.h + Resources.cpp**: Manages game resources like textures and sounds.
- **SoundControl.h + SoundControl.cpp**: Provides additional sound control functionality.
- **Window.h + Window.cpp**: Manages the game window and rendering context.
- **GoalSide.h + GoalSide.cpp**: Represents the side part of a goal.
- **GoalTop.h + GoalTop.cpp**: Represents the top part of a goal.
- **StandPlayerState.h + StandPlayerState.cpp**: Implements the standing state for players.
- **Tutorial.h + Tutorial.cpp**: Manages the tutorial screen and logic.
- **MovingObject.h + MovingObject.cpp**: Represents objects that can move in the game.
- **AvatarPower.h + AvatarPower.cpp**: Implements special powers for avatars.
- **Player.h + Player.cpp**: Represents a player in the game.
- **ScoreBoard.h + ScoreBoard.cpp**: Manages the scoreboard and displays scores.
- **DisappearPower.h + DisappearPower.cpp**: Implements a power that makes objects disappear.
- **StaticObject.h + StaticObject.cpp**: Represents objects that do not move.
- **UserPlayer.h + UserPlayer.cpp**: Implements the behavior of a user-controlled player.
- **DragonPower.h + DragonPower.cpp**: Implements a dragon-related special power.
- **FirePower.h + FirePower.cpp**: Implements a fire-related special power.
- **FistPower.h + FistPower.cpp**: Implements a fist-related special power.
- **InvisiblePower.h + InvisiblePower.cpp**: Implements a power that makes objects invisible.
- **Power.h + Power.cpp**: Defines the base class for all special powers.
- **TornadoPower.h + TornadoPower.cpp**: Implements a tornado-related special power.
- **main.cpp**: Entry point for the application.

## Data Structures:
--------------------
- **Classes**: Defined for game objects, player states, powers, and UI components.
- **Factories**: For creating static and moving objects using the Factory design pattern.
- **State Pattern**: For handling different player movement states.

## Algorithms:
--------------------
- **Collision Detection**: Handled by the `CollisionHandling` class to manage interactions between game objects.
- **Physics Simulation**: Implemented using the Box2D physics engine for realistic movement and interactions.
- **AI Behavior**: For computer-controlled players to simulate opponent actions.

## Design:
--------------------
- **Object-Oriented Design**: Utilizing classes and inheritance to model game objects and behavior.
- **Design Patterns**: Factory pattern for object creation, State pattern for player movements.
- **Modular Architecture**: Separation of concerns with distinct classes for different functionalities,
- **making the codebase easier to maintain and extend.