#ifndef STRUCTS_H
#define STRUCTS_H

#include "../base.h"

// AREA

typedef struct struct_ycr07 struct_ycr07;

struct struct_ycr07 {
  byte y;
  bool c;
  byte r07;
};


typedef struct struct_yr07 struct_yr07;

struct struct_yr07 {
  byte y;
  byte r07;
};


typedef struct struct_yr06r07 struct_yr06r07;

struct struct_yr06r07 {
  byte y;
  byte r06;
  byte r07;
};


// SOUND

typedef struct struct_axyz struct_axyz;

struct struct_axyz {
  byte a;
  byte x;
  byte y;
  bool z;
};


typedef struct struct_ay struct_ay;

struct struct_ay {
  byte a;
  byte y;
};


typedef struct struct_axy struct_axy;

struct struct_axy {
  byte a;
  byte x;
  byte y;
};


// OTHER

typedef struct struct_ncr00 struct_ncr00;

struct struct_ncr00 {
  bool n;
  bool c;
  byte r00;
};


typedef struct struct_ayz struct_ayz;

struct struct_ayz {
  byte a;
  byte y;
  bool z;
};


struct blockbuffer_colli_result {
  byte a;
  byte r04;

  u16 mt_x;
  u16 mt_y;
};


typedef struct struct_r01r02r03 struct_r01r02r03;

struct struct_r01r02r03 {
  byte r01;
  byte r02;
  byte r03;
};


typedef struct struct_yc struct_yc;

struct struct_yc {
  byte y;
  bool c;
};

#endif
