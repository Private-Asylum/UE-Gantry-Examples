# Yardrush mods

Four example mods for Yardrush, built the way anyone outside the studio would build one. The
game never names them: it says only that mods live in `Mods/` next to its `.uproject` (Project
Settings > Plugins > Gantry Experience > Mod Directories, with Mount Mods At Startup on). Each mod
finds its own place through experience tags.

| Mod | What it shows |
|---|---|
| `LowGravity` | A new round. Its experience sets **Attach To** `Experience.Yard`, so it joins the game's list of rounds, and the lobby can vote for it. It reuses Crate Rush's game feature and adds its own, which makes every character floaty. |
| `ShinyCrates` | An augment to an existing round. Its experience **Extends** `Experience.Yard.CrateRush`, so whenever Crate Rush runs, Shiny Crates joins its chain. Its game feature adds a component to Crate Rush's crates: a random paint, and one crate in eight is gold and worth 3. |
| `DoubleScore` | A mod that hooks the game. Its experience **Extends** `Experience.Yard.CrateRush`; its one stage (Server Only) listens to the game's **Crate Scored** hook (`Yard.Hook.CrateScored`) with Listen For Hook, and doubles the points each crate carries before the crate scores them. The game declares the hook and runs it; the mod needs nothing else from it. |
| `LowGravityFuture` | A mod made for a newer game. Its experience's **Metadata > Required Game Version** is 2.0, so on this build Gantry lists it as incompatible, with the reason, and never activates it. |

## What the game offers mods

- **Channels.** Yardrush declares its channels in a Channel Set (`DA_YR_Channels`, listed in
  Project Settings > Plugins > Gantry Core > Channel Sets): `Yard.Message.RoundStarted`, sent as
  each round starts, and `Yard.Hook.CrateScored`, a hook every scored crate runs on the server with
  the crate, the team and the points (`S_YR_CrateScore`). A listener may change the points, or cancel and the
  crate scores nothing. With Warn On Undeclared Channels on, anything sending on a channel nobody
  declared is logged.
- **The API manifest.** Blueprint types carry no markup, so the game lists what it offers in Gantry
  Core's API Allowlist: the channel payloads with all their fields, the character with Interact and
  On Interact, and the crate with Points, Score and Scored. The editor writes it, with the
  channels, into `Config/DefaultGantryAPI.ini`.
- **Components.** Characters and bots are in Gantry Experience's Automatic Receiver Classes, so game
  features (and mods) add components to them without either registering itself. Crate Rush's
  crates register themselves: they belong to its game feature.
- **Data patches.** A mod's game feature can carry a Patch Data action: values of assets or class
  defaults, and DataTable rows, changed while it is active and put back after.

## Turning mods off

Settings > Mods lists every mod found, with a toggle each (built in Blueprint, `BP_YR_ModsProvider`).
A mod turned off stays in `Mods/` and is not loaded, nor is anything that builds on it; the choice
is the player's, in `Saved/Config/<platform>/GantryMods.ini`. `Gantry.Mods.Disable <Mod>` and
`Gantry.Mods.Enable <Mod>` do the same from the console.

## A mod's folder

```
Mods/
  LowGravity/
    LowGravity.uplugin        a game feature plugin (Explicitly Loaded, Built In Initial State Registered)
    Config/Tags/*.ini         the mod's own gameplay tags, read when it is registered
    Content/                  its assets, authored in the editor
    Content/Paks/<Platform>/  what cooking produces; the only content a packaged game reads
```

Each folder holds exactly one `.uplugin`. A mod's dependencies on other mods (`Plugins` in the
`.uplugin`) decide the mount order: a mod that builds on another mounts after it.

## Placing a mod in the tree

- **Attach To**: the experience's parent. Every mod experience needs one, because nothing in the
  game lists it. A round goes under `Experience.Yard`; anything else (an augment, for instance)
  goes under the root, `Experience.Base`.
- **Extends**: experiences this one joins whenever they run, ordered after them. This is how a mod
  changes a round without the round knowing. Extends is not a parent: set Attach To as well.
- **Optional Dependencies**: experiences this one runs after when they are installed, and without
  when they are not. (Yardrush's Tag round does this with Night Shift.)

## Authoring in the editor

The editor mounts mods on request: run `Gantry.Mods.Mount` in the console. Mods then appear in the
experience tree like the game's own content. A new mod cannot register until it has its game
feature data asset, so the first mount only opens its content folder and says so: create the
asset there (Add > Gantry > Game Feature Data, named after the plugin, at the folder's root), then
run `Gantry.Mods.Mount` again.

`Gantry.Mods.Unmount` (every mod, or one by name) and `Gantry.Mods.Remount` take mods out and put
them back without restarting the editor. A mod whose experience is running stays, and the log
says why.

## Cooking against a release

Mods are cooked as DLC against a packaged release of the game, so they contain only their own
content:

1. Package the game with `-createreleaseversion=<release>` (BuildCookRun). This writes the
   release's metadata to `Releases/<release>/<Platform>/`.
2. Cook the mod with the stock BuildCookRun (a mod can use the game's content and its own; the
   cook refuses anything else):
   `-cook -stage -pak -dlcname=<path to the mod's .uplugin> -basedonreleaseversion=<release>`,
   plus `-server -noclient` or `-client` for dedicated server and client builds. Gantry mounts the
   mod (and the mods it builds on) inside the cook so the cooker can find it.
3. Copy the staged containers (`.pak`, `.utoc`, `.ucas`) from the mod's `Saved/StagedBuilds` into
   its `Content/Paks/<Platform>/`, where `<Platform>` is `Linux`, `LinuxServer`, `LinuxClient`,
   `Windows`, `WindowsServer` and so on.
4. Copy the mod folder (`.uplugin`, `Config`, `Content/Paks`) into the packaged game's `Mods/`,
   or pack it as one file (below) and copy that.

## One file: `.gantry`

A `.gantry` file is a mod's folder as a single file to hand to players: a zip of its `.uplugin`,
`Config/` and `Content/Paks/<Platform>/`, with the entries stored, not compressed (the paks inside
are compressed already). For example, on Linux:

```
cd Mods/LowGravity && zip -0 -r ../LowGravity.gantry LowGravity.uplugin Config Content/Paks/Linux
```

Dropped into the game's `Mods/`, Gantry unpacks it into a `LowGravity/` folder beside it (the paks
were cooked against that folder) and mounts it like any other mod. Take the file away and the
unpacked folder goes with it, at the next look or the next start. A file is one platform's mod:
make one per platform you ship.

## Dropping a mod in while the game runs

Yardrush looks at `Mods/` every two seconds while it runs (Project Settings > Plugins > Gantry
Experience > Mod Rescan Interval). A mod folder or `.gantry` file copied in is mounted within a moment; the
game says "Mods installed", and the mod's rounds are offered from the next lobby. Removing or
replacing a mod takes effect at the next start, or at `Gantry.Mods.Remount` (a mod whose round is
running stays until the round ends).

## Code

Mods carry content and Blueprints, which is everything these examples use, and content mods work
in every build of the game. A mod with C++ modules (a `.dll` or `.so`) needs a game that can load
code: the editor, or a game built "modular" from a source engine with each mod compiled against
those exact binaries. A normal packaged game is one "monolithic" executable, and there Gantry
refuses a mod with modules before mounting anything of it, saying that this game takes content
mods only. Yardrush, a Blueprint-only example, is always the latter.

## Playing with mods over the network

The server decides the round and every client must be able to run the same chain of
experiences. A client without a mod the server is running refuses the round: Gantry reports why,
naming both chains, and Yardrush shows it on its "Can't play this round" screen. So does a client
whose copy of a mod in the chain is another version from the server's: Gantry names the mod and
both content ids. A mod's content id is the same for every platform, and for server and client
cooks of the same source. Install the same mods, in the same versions, on every machine.

## When Gantry refuses a mod

A mod is judged before anything of it is mounted. Gantry refuses one, with the reason in the log
and in `Gantry.Mods.Report`, when:

- its `.uplugin` is not Explicitly Loaded;
- its name belongs to another plugin or content root (the game's, the engine's or another mod's);
- it carries code the game cannot load (see Code);
- it was cooked against a different build of the game: a package it uses is not in this one;
- it is incompatible (its game feature data or experience needs another game version).

A mod refused after mounting is unmounted again, so none of its content stays in the game.

## When two mods ship the same thing

Allowed, never silent. After each mount Gantry lists, and `Gantry.Mods.Report` prints again:

- **assets** more than one mod provides, or a mod provides in place of the game's own, and which
  copy the game reads: the mod mounted highest (a mod that builds on another mounts above it; a mod
  mounted later mounts above everything before it);
- **experiences** sharing a tag, a guid or an asset name (the experience tree keeps the first);
- **config** keys two mods set differently, or a mod sets differently from the game, and
  **redirects** that rename content outside the mod's own folder.

Cooked the stock way, a mod holds only its own content: the cook refuses anything it uses that the
release does not already hold, another mod's content included. So the usual clash is not two
copies of one asset but two mods claiming one identity. `ModsWithProblems/LowGravityTwin` is
exactly that: Low Gravity's folder copied and the plugin renamed (with a description that says
so), nothing else, so its experience keeps Low Gravity's tag, guid and asset name. It sits outside
`Mods/` so ordinary runs never see it; add `ModsWithProblems` to Mod Directories (Project
Settings > Plugins > Gantry Experience) and mount, and Gantry reports all three clashes while the
round list keeps the original.
