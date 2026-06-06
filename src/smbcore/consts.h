#ifndef SMBCORE_CONSTS
#define SMBCORE_CONSTS

// The term "enemy" is too specific.
// Something like "actor" is more general for this case.
// TODO: consider updating this concept across the codebase

enum actor_id {
  A_GREEN_KOOPA=0,
  A_RED_KOOPA_GREENLIKE,        // red, but falls off ledges
  A_BUZZY_BEETLE,
  A_RED_KOOPA,
  A_PIRANHA_PLANT_SMB2J,
  A_HAMMER_BRO,
  A_GOOMBA,
  A_BLOOBER,
  A_BULLET_BILL,
  A_GREEN_PARATROOPA_INPLACE,   // flies in place (doesn't move)
  A_CHEEPCHEEP_GRAY,
  A_CHEEPCHEEP_RED,
  A_PODOBOO,
  A_PIRANHA_PLANT,
  A_GREEN_PARATROOPA,           // hops horizontally
  A_RED_PARATROOPA,             // flies vertically
  A_GREEN_PARATROOPA_HORIZONTAL,
  A_LAKITU,
  A_SPINY,
  A_UNK_0x13,                   // corrupted graphics
  A_FLYING_CHEEPCHEEP,
  A_BOWSER_FLAME,
  A_FIREWORKS,
  A_BULLET_BILL_OR_CHEEPCHEEP_FRENZY,
  A_STOP_FRENZY,
  A_UNK_0x19,
  A_UNK_0x1A,
  A_FIREBAR_1,
  A_FIREBAR_2,
  A_FIREBAR_3,
  A_FIREBAR_4,
  A_FIREBAR_5,
  A_FIREBAR_6,
  A_FIREBAR_7,
  A_FIREBAR_8,
  A_UNK_0x23,
  A_LARGEPLATFORM_BALANCE,
  A_LARGEPLATFORM_Y_MOVING,
  A_LARGEPLATFORM_LIFT1,
  A_LARGEPLATFORM_LIFT2,
  A_LARGEPLATFORM_X_MOVING,
  A_LARGEPLATFORM_DROP,
  A_LARGEPLATFORM_RIGHT,
  A_SMALLPLATFORM_1,
  A_SMALLPLATFORM_2,
  A_BOWSER,
  A_POWERUP,
  A_VINE,
  A_FLAGPOLE,
  A_STARFLAG,
  A_JUMPSPRING,
  A_UNK_0x33,
  A_WARPZONE,
  A_RETAINER,
  A_UNK_0x36,
};

static inline bool is_actor_valid(const u8 id) {
  return id <= 0x3f;
}

static inline bool is_actor_enemy(const u8 id) {
  return id <= A_FLYING_CHEEPCHEEP;
}

static inline bool is_actor_unknown_class(const u8 id) {
  // I'm not sure what this is
  return id >= 0x18;
}

static inline bool is_actor_groupenemy(const u8 id) {
  return id >= 0x37 && id <= 0x3e;
}

static inline u8 actor_groupenemy(const u8 id) {
  return id - 0x37;
}

static inline bool is_actor_even(const u8 id) {
  return (id & 1) == 0;
}

static inline bool is_actor_firebar(const u8 id) {
  return id >= A_FIREBAR_1 && id <= A_FIREBAR_8;
}

static inline bool is_actor_firebar_short(const u8 id) {
  return id >= A_FIREBAR_1 && id <= A_FIREBAR_4;
}

static inline bool is_actor_firebar_long(const u8 id) {
  return id >= A_FIREBAR_5 && id <= A_FIREBAR_8;
}

static inline bool is_actor_platform_large(const u8 id) {
  return id >= A_LARGEPLATFORM_BALANCE && id <= A_LARGEPLATFORM_RIGHT;
}


#endif
