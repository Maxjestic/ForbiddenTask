# Forbidden Task - Project Documentation

## Overview

Forbidden Task is a 2D arcade game where the player controls a sphere that must consume weaker enemies to grow stronger while avoiding stronger ones. The game ends when all enemies are consumed (Win) or when the player's strength or speed drops to zero (Lose).

## Core Gameplay Systems (For Programmers)

This section outlines the main C++ architecture.

### Pawn Architecture

The core pawn logic is built on a simple inheritance structure:
* **`AFTBasePawn`**: The abstract base class for all pawns. It handles shared logic for physics-based movement (`HandleMovement`), stats (`Strength`, `Speed`), and size scaling (`UpdateSize`).
* **`AFTPlayerPawn`**: Inherits from `BasePawn` and adds player-specific logic, including the camera, input handling, and delegates (`OnStrengthChanged`, `OnSpeedChanged`) for UI updates.
* **`AFTEnemyPawn`**: Inherits from `BasePawn` and implements the `IFTConsumable` interface, allowing it to be consumed by the player.

### AI System

The AI is driven by Unreal Engine's **Behavior Tree** system.
* **`AFTAIController`**: The "brain" of the AI. On `OnPossess`, it finds its `BehaviorTree` asset and starts the logic.
* **Behavior Tree (`BT_Enemy`)**: The tree is state-driven, using a Blackboard `bool` key `bIsEngaged` to decide between two main behaviors:
    1.  **Engage Player**: If `bIsEngaged` is true, the AI will either chase or flee based on a strength comparison.
    2.  **Idle Patrol**: If `bIsEngaged` is false, the AI moves in a random direction for a set time, then chooses a new direction.
* **Key C++ Nodes:**
    * **Services**: `FindPlayer`, `UpdateEngagementStatus`, `SetRandomMoveDirection`.
    * **Decorators**: `CompareStrength`.
    * **Tasks**: `HandleAwareMovement`, `ApplyForceInDirection`.

### Spawner System

The **`AFTEnemySpawner`** actor handles spawning the initial wave of enemies. It operates in two modes, controlled by the `SpawnerType` enum:
1.  **Normal Mode**: Spawns a set number of enemies in a radius around the player. Stat scaling is controlled by `UCurveFloat` assets.
2.  **Data Asset Mode**: Spawns enemies in concentric rings, with each ring's rules defined in a `UFTSpawnConfigDataAsset`.

### UI System

The UI is managed using a hybrid C++/Blueprint approach with a centralized configuration.
* **`UFTGameInstance`**: Acts as a central repository, holding `TSubclassOf` references to all major UI widget classes.
* **`AFTHUD`**: The HUD class is responsible for creating and displaying the main in-game widget (`WBP_HUD`) with the stat bars.
* **`AFTPlayerController`**: Manages all modal, event-driven UI, including the **Pause Menu** and **End Screen**. It is also responsible for handling all UI-related input.

## Designer's Guide (For Designers)

This section explains how to use the C++ systems in the Unreal Editor.

### How to Create a New Enemy Type

1.  In the Content Browser, right-click on `_BP_BaseEnemy` (your Blueprint base for enemies) and select **"Create Child Blueprint Class"**. Name it appropriately (e.g., `BP_GreenEnemy`).
2.  Open the new Blueprint. In the **Event Graph**, right-click and search for **"Event Attempt To Consume"** and implement it.
3.  Inside this event, use the `Player Pawn` reference to call the `Add Strength`, `Subtract Strength`, `Add Speed`, or `Subtract Speed` functions.

### How to Configure Spawning

1.  Place an **`AFTEnemySpawner`** actor in your level.
2.  In its **Details** panel, choose a **`Spawner Type`**.
3.  **If `Normal`:**
    * Set the `Total Enemies To Spawn` and the `Outer Spawn Radius`.
    * Populate the `Enemy Spawn Infos` array with the enemy Blueprints and their spawn weights.
    * Assign the `UCurveFloat` assets for `Strength Over Distance Curve` and `Speed Over Distance Curve`.
4.  **If `DataAsset`:**
    * Create a `FTSpawnConfigDataAsset` in the Content Browser.
    * Fill out the `Spawn Zones` array inside the data asset.
    * Assign this data asset to the `Spawn Config` property on the spawner actor.

### How to Configure the UI

* All UI widget Blueprints (Main Menu, HUD, Pause Menu, End Screen, Cheats Menu) are assigned in a single, central location: your **`BP_FTGameInstance`** asset. Open this asset to change which widget is used for each part of the game.

## Cheats and Debug Tools

The project includes a cheat system to make testing and debugging easier. These cheats can be accessed in two ways.

### How to Access

* **Console:** In-game, open the console window, then type in the desired command.
* **Debug Widget:** Press the **`1`** key to toggle the graphical cheat menu.

### Available Commands

| Command | Parameters | Description |
| :--- | :--- | :--- |
| `God` | None | Toggles God Mode for the player. While active, the player will not lose strength or speed from consuming enemies. |
| `KillPlayer` | None | Instantly kills the player, triggering the loss condition. |
| `KillAllEnemies` | None | Destroys all currently active enemies, triggering the win condition. |
| `ToggleFreezeEnemies`| None | Toggles the frozen state for all enemies by stopping/restarting their Brain. |
| `SetPlayerStats` | `NewStrength` `NewSpeed` | Sets the player's stats to specific absolute values. Example: `SetPlayerStats 3 2` |
| `AlterPlayerStats` | `StrengthDelta` `SpeedDelta`| Adds or subtracts from the player's current stats. Use negative numbers to subtract. Example: `AlterPlayerStats -2 1` |
