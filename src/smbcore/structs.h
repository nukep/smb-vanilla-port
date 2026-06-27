#ifndef STRUCTS_H
#define STRUCTS_H

#include "../base.h"

// AREA

typedef struct struct_ycr07 struct_ycr07;

struct struct_ycr07 {
  u8 y;
  bool c;
  u8 r07;
};


typedef struct struct_yr07 struct_yr07;

struct struct_yr07 {
  u8 y;
  u8 r07;
};


typedef struct struct_yr06r07 struct_yr06r07;

struct struct_yr06r07 {
  u8 y;
  u8 r06;
  u8 r07;
};


// SOUND

typedef struct struct_axyz struct_axyz;

struct struct_axyz {
  u8 a;
  u8 x;
  u8 y;
  bool z;
};


typedef struct struct_ay struct_ay;

struct struct_ay {
  u8 a;
  u8 y;
};


typedef struct struct_axy struct_axy;

struct struct_axy {
  u8 a;
  u8 x;
  u8 y;
};


// OTHER

typedef struct struct_ncr00 struct_ncr00;

struct struct_ncr00 {
  bool n;
  bool c;
  u8 r00;
};


typedef struct struct_ayz struct_ayz;

struct struct_ayz {
  u8 a;
  u8 y;
  bool z;
};


struct blockbuffer_colli_result {
  u8 a;
  u8 r04;

  u16 mt_x;
  u16 mt_y;
};


typedef struct struct_r01r02r03 struct_r01r02r03;

struct struct_r01r02r03 {
  u8 r01;
  u8 r02;
  u8 r03;
};


typedef struct struct_yc struct_yc;

struct struct_yc {
  u8 y;
  bool c;
};

#endif
