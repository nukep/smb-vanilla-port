This document describes good to know details about how particular actors are implemented.
WIP.

## Actor state

aka `Enemy_State`, according to the doppelganger disassembly.

Actor state is stored as an 8-bit value. Most actors use the following bit format:

```
KFD_ _xxx
```

Where:
- `K` - kicked
- `F` - falling
- `D` - defeated
- `xxx` - state
  - `0` - normal
  - `1` - falling (again. TODO: clarify)
  - `2` - stun
  - `3` - upside down
  - `4` - stomped
  - `5` - spiny egg
- `_` - unused


Other actors use a different format.

### A_POWERUP

```
0__x xxxx
1F__ ____
```

Where:
- The leading `0` or `1` is emerging and emerged, respectively
- `xxxxx` is a counter that increments as the powerup comes out of the block. Once it reaches 17, the game transitions to emerged.
- `F` is falling
- `_` - unused

### A_HAMMER_BRO

```
__D_ T__J
```

Where:
- `D` - defeated
- `T` - throwing
- `J` - jumping
- `_` - unused

### A_LAKITU

```
__D_ ___L
```

Where:
- `D` - defeated
- `L` - leaving

(note: bitmask below sets bit 1 for stun, but it's unused for lakitu)

### A_LARGEPLATFORM_BALANCE

This is a reference to the actor index of the other opposing platform.
If there is none, it's `-1` (i.e. `0xFF`)

### A_STARFLAG

This is `6 - number of fireworks`. It's simply used as an offset to a later lookup for the fireworks positions.


## Actor state, bitmasks

Disclaimer: This is based on my own testing, and it may not be exhausive or account for glitches.
The methodology I used was "printf on each read of the actor state, then use a Python script to parse the results".

These are the bitmasks of actor states:

```
A_GREEN_KOOPA                        (00): 1110 0111
A_RED_KOOPA_GREENLIKE                (01): 0010 0111
A_BUZZY_BEETLE                       (02): 1110 0111
A_RED_KOOPA                          (03): 1110 0111
A_PIRANHA_PLANT_SMB2J                (04): 0010 0010
A_HAMMER_BRO                         (05): 0010 1011
A_GOOMBA                             (06): 0010 0111
A_BLOOBER                            (07): 0010 0010
A_BULLET_BILL                        (08): 0010 0000
A_CHEEPCHEEP_GRAY                    (0A): 0010 0010
A_CHEEPCHEEP_RED                     (0B): 0010 0010
A_PIRANHA_PLANT                      (0D): 0010 0010
A_LAKITU                             (11): 0010 0011
A_SPINY                              (12): 0010 0111
A_FLYING_CHEEPCHEEP                  (14): 0010 0010
A_LARGEPLATFORM_BALANCE              (24): 1111 1111
A_BOWSER                             (2D): 0110 0000
A_POWERUP                            (2E): 1101 1111
A_STARFLAG                           (31): 0000 0111
A_BULLET_BILL_CANNON                 (33): 0010 0011
```

Actors that don't set actor state are:

```
A_PODOBOO                            (0C): 0000 0000
A_GREEN_PARATROOPA                   (0E): 0000 0000
A_RED_PARATROOPA                     (0F): 0000 0000
A_GREEN_PARATROOPA_HORIZONTAL        (10): 0000 0000
A_BOWSER_FLAME                       (15): 0000 0000
A_BULLET_BILL_OR_CHEEPCHEEP_FRENZY   (17): 0000 0000
A_STOP_FRENZY                        (18): 0000 0000
A_FIREBAR_1                          (1B): 0000 0000
A_FIREBAR_2                          (1C): 0000 0000
A_FIREBAR_3                          (1D): 0000 0000
A_FIREBAR_5                          (1F): 0000 0000
A_LARGEPLATFORM_Y_MOVING             (25): 0000 0000
A_LARGEPLATFORM_LIFT1                (26): 0000 0000
A_LARGEPLATFORM_LIFT2                (27): 0000 0000
A_LARGEPLATFORM_X_MOVING             (28): 0000 0000
A_LARGEPLATFORM_DROP                 (29): 0000 0000
A_LARGEPLATFORM_RIGHT                (2A): 0000 0000
A_SMALLPLATFORM_1                    (2B): 0000 0000
A_SMALLPLATFORM_2                    (2C): 0000 0000
A_VINE                               (2F): 0000 0000
A_JUMPSPRING                         (32): 0000 0000
A_WARPZONE                           (34): 0000 0000
A_RETAINER                           (35): 0000 0000
```
