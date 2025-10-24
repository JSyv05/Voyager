```mermaid
---
title: Voyager UML
---	

classDiagram
	Rock --o Planet : Constructs
	Voyager --> Game
	MainMenuCommand --o Game : uses
	Command --> Planet : Game.onPlanet
	Command --> Ship : Game.onShip
	Command --> Menu : Game.onMenu
	Planet --> Game
	Ship --> Game
	Menu --> Game
	Command <-- Game
	Ship ..> Planet : (X,Y,Z) coords
	
	class Voyager {
		main() int
	}
	
	class Game{
	    - art_output: string
	    - body_output: string
	    - error_output: string
	    - onMenu: bool
	    - onShip: bool
	    - onPlanet: bool
		- gameover: bool
	    + Game()

	    + setBodyOutput(in: const string&) const
		+ setArtOutput(in: const string&) const
		+ setErrorOutput(in: const string&) const
		+ setMenuFlag(in: const bool&) const
		+ setShipFlag(in: const bool&) const
		+ setPlanetFlag(in: const bool&) const
		+ setGameOverFlag(in: const bool&) const
	    + getBodyOutput() string const
	    + getArtOutput() string const
	    + getErrorOutput() string const
		+ getMenuFlag() bool
		+ getShipFlag() bool
		+ getPlanetFlag() bool
		+ getGameOverFlag() bool
	    + clearScreen() const
		+ checkMenuCommand(in: Command&): MainMenuCommand
		+ displayOutput() const
	    + gameLoop(in: Game&) const
	}
	
	class Command{
		- input: string
		- command: vector string
	    + setInput() const
	    + getInput() vector string
	}
    
	class Menu{
		+ setMainMenu() const
		+ setInstructions() const
		+ setCredits() const
		+ showIntro() const
	}
	
	class Ship {
		- position: vector float
		+ findNearbyPlanets()
	}
	
	class Planet {
		- position: vector float
		- level: int
		- biome: string
	}
	
	class Rock {
		- rarity: int
		- type: string
	}
	class MainMenuCommand{
		<<Enumeration>>
		Start
		Load
		Credits
		Instructions
		Back
		Exit
		Error
	}
```