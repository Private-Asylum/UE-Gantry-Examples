# Yardrush mods

Three example mods for Yardrush, built the way anyone outside the studio would build one. The
game never names them: it says only that mods live in `Mods/` next to its `.uproject`
(Project Settings > Gantry Experience > Mod Directories, with Mount Mods At Startup on). Each mod
finds its own place through experience tags.

| Mod | What it shows |
|---|---|
| `LowGravity` | A new round. Its experience sets **Attach To** `Experience.Yard`, so it joins the game's list of rounds, and the lobby can vote for it. It reuses Crate Rush's game feature and adds its own, which makes every character floaty. |
| `ShinyCrates` | An augment to an existing round. Its experience **Extends** `Experience.Yard.CrateRush`, so whenever Crate Rush runs, Shiny Crates joins its chain. Its game feature adds a component to Crate Rush's crates: a random paint, and one crate in eight is gold and worth 3. |
| `LowGravityFuture` | A mod made for a newer game. Its experience's **Metadata > Required Game Version** is 2.0, so on this build Gantry lists it as incompatible, with the reason, and never activates it. |

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
experience tree like the game's own content. A new mod needs its game feature data asset
(Add > Gantry > Game Feature Data, named after the plugin, at the root of its Content folder)
before it can be registered; run `Gantry.Mods.Mount` again after creating it.

## Cooking against a release

Mods are cooked as DLC against a packaged release of the game, so they contain only their own
content:

1. Package the game with `-createreleaseversion=<release>` (BuildCookRun). This writes the
   release's metadata to `Releases/<release>/<Platform>/`.
2. Cook the mod with the stock BuildCookRun:
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

Yardrush looks at `Mods/` every two seconds while it runs (Project Settings > Gantry Experience >
Mod Rescan Interval). A mod folder or `.gantry` file copied in is mounted within a moment; the
game says "Mods installed", and the mod's rounds are offered from the next lobby. Nothing is ever
unmounted while the game runs: removing or replacing a mod takes effect at the next start.

## Code

Mods carry content and Blueprints, which is everything these examples use. A mod with C++
modules (a `.dll` or `.so`) cannot be loaded into a normal packaged game: the game is one
"monolithic" executable, and a library built separately has nothing to link against. Code mods
need a game built "modular" from a source engine, with mods compiled against those exact
binaries; Yardrush, a Blueprint-only example, does not do that.

## Playing with mods over the network

The server decides the round and every client must be able to run the same chain of
experiences. A client without a mod the server is running refuses the round: Gantry reports why,
naming both chains, and Yardrush shows it on its "Can't play this round" screen. Install the same
mods on every machine.

## When two mods ship the same file

Allowed, never silent. After each mount Gantry logs every path more than one mod provides, and
which mod wins: the one that builds on the most others (its `.uplugin` dependencies), as the
more specific of the two. `Gantry.Mods.Report` prints the list again.
