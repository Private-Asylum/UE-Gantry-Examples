# Yardrush: the Gantry Blueprint example

A shipping-yard party game in two teams, with bots filling the yard to four players. Each round is
a Gantry experience the crane delivers: the next round is chosen in the lobby, the yard changes, and
it loads without leaving the map. Everything is Blueprint; there is no C++ in this project.

This is the Blueprint companion to [Railhead, the C++ example](https://github.com/Private-Asylum/UE-Gantry-Code-Example).

## Requirements

- Unreal Engine 5.6, 5.7 or 5.8, with [Gantry from Fab][gantry-fab] (or copied into `Plugins/`).
- The project is set up for 5.6. For 5.7 or 5.8, right-click `GantryExamples.uproject` and choose
  Switch Unreal Engine Version (or change `EngineAssociation` in it).

## Opening it

The editor opens on `L_GantryStart`: a short walkable guide to Gantry and to this project, with a
portal into the game. A packaged game starts on the main menu (`L_MainMenu`): play solo, host a
game, join one, open the settings or the guide.

- **Move** WASD or the left stick; **look** the mouse or the right stick; **jump** Space or the
  bottom face button; **interact** E or the right face button.
- **Next round:** Q (or d-pad right) steps your choice to the next round mode, R (or d-pad left)
  picks a random one. In a game a player hosts, the host's choice is the one that counts; on a
  dedicated server, players vote.
- **Tab** (or the gamepad's Menu button) opens the menu: host, play solo, join, settings, the main
  menu, back to the guide, and the next-round choices.

## What is in it

| Content | Where | What it shows |
|---|---|---|
| The lobby and the rounds: Crate Rush, Hot Crate, King of the Container, Tag | `Content/Yardrush`, `Plugins/GameFeatures` | Each round is an experience plus a game feature plugin. Experiences share stages and differ in data. |
| Night Shift | `Plugins/GameFeatures/YardNightShift` | An optional dependency: Tag plays at night when it is installed, in daylight when it is not. |
| Demolition | `Plugins/GameFeatures/YardDemolition` | A round still being made: playable in the editor, listed as not installed in packaged games. |
| Loading screen, settings, menus | `Content/Yardrush` | Gantry's tracked loading, per-player settings (including a Mods page) and UI extension slots, all built in Blueprint. |
| Example mods | `Mods/`, `ModsWithProblems/` | A new round, an augment, a hook listener, and mods Gantry refuses on purpose. See [Mods/README.md](Mods/README.md). |

## Credits

Third-party content is listed in [CREDITS.md](CREDITS.md).

[gantry-fab]: https://www.fab.com/listings/308b7a4a-7b05-45f6-8cf8-b05dec2779a6
