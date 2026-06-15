# Technical debt

Here are some topics relating to the technical debt of this project.


## "Sprite Object" should be renamed to "Entity", "Enemy" should be renamed to "Actor"

The original names come from the doppelganger disassembly.

"Sprite Object" is confusing, because it doesn't represent a graphical sprite in the way it's widely understood, but rather an entity in the game.

The concept of "enemy" includes a variety of non-enemy things, like powerups, the jumpspring, cannons and whirlpools, and toad/princess.

I believe "Sprite Object" and "Enemy" are the wrong primitives.

It's really modeled more as a class-like hierarchy. Something like:

- Entity (formerly Sprite Object)
  - Player
  - Actor (formerly Enemy)
    - Enemy
      - Koopa
      - Goomba
      - etc
    - Platform
    - Power-Up
    - Jumpspring
    - Toad/Princess
    - etc
  - Fireball
  - Block
  - Misc (should probably be renamed too?)
  - Bubble


## Renaming things in general

I want to make code cross-referencable to disassemblies.
This requirement has made it difficult to rename variables and subroutines that I believe make the code harder to understand.

I'm unsure what's the best approach. Some possible ideas:

a) Annotate the doppelganger name in function comments
  - Pro: self-evident
  - Con: noise for those who don't need to cross-reference
  - Con: would lead to doing the same for other existing disassemblies

b) Create a separate manifest somewhere and have a tool that's able to search it for us
  - Pro: structured, scriptable
  - Pro: doesn't clutter code comments with info that might be irrelevant to casual hackers
  - Con: can easily be overlooked or bitrotted. "you just moved the problem out of sight"
  - Con: requires creating two tools: one to validate C functions against the manifest, and another to do the searching
  - Con: those who cross-reference experience extra friction with tooling


## The SMB1 and SMB2J uber-modules should be phased out

Currently, the smbvanilla executable bundles both games.
They're compiled as two "uber-modules", smb1.cpp and smb2j.cpp, and linked into one library.

And very confusingly, they also `#include` other .c files, such as common.c.
To avoid name collisions between the two games, I used `#define` to rename symbols in common.c. e.g. `DrawPowerUp()` becomes `smb1_DrawPowerUp()`, but only if `smb1.h` is included.

This was a compromise I made to get something working as soon as possible.
But it made things painful in several ways:

- The clangd LSP has a hard time understanding `common.c`, because many symbols are defined by `smb1.cpp` or `smb2j.cpp`. I have a local workaround for this.
- Retargeting to an embedded platform, or only using one game (likely SMB1), is hard.
- Reasoning about the code in general is hard.

Early on, I had hoped that differences in behavior between SMB1 and SMB2J could be configured at runtime. Later on, as the complexity became evident, I settled on compile-time with `#ifdef SMB1_MODE` and `#ifdef SMB2J_MODE`.

There are jumptables and enumerations that have different values for SMB1 and SMB2J (e.g. area parsing). As these are tied into the functions that use them, it makes less sense to have a mix of both run-time and compile-time switches for SMB1 and SMB2J.

I think it's architecturally simpler to compile two _libraries_, one for each game.
Run-time selection of both games could be done by dynamically loading one, or by creating two different executables.


## Separate common.c

It's over 10K lines of code!

I had previously separated it out into area.c and common_sound.c, but the remaining code is harder.

The rest of it seems to have high coupling. When I separated out area.c, I had done a callgraph analysis to show modularity classes, which showed the high coupling. The area decoding was the only thing remaining that wasn't highly coupled.

Players and enemies (actors) could also potentially be separated, but it's a majority (80% or so) of the code. Separating it as one module would create a Jane-Jetson-Takes-Wallet situation.

I believe that looking at the callgraph is probably inadequate here. The enemy (actor) code is mostly polymorphic (via jumptables, detecting classes of actors), so I think we need to attack it that way.
