#ifndef SMBCORE_TYPES_H
#define SMBCORE_TYPES_H

#define BUTTON_A 0x80
#define BUTTON_B 0x40
#define BUTTON_SELECT 0x20
#define BUTTON_START 0x10
#define BUTTON_U 0x08
#define BUTTON_D 0x04
#define BUTTON_L 0x02
#define BUTTON_R 0x01

// Note that `i` is modulo 64 for bounding boxes, hence the `(byte)` cast.

#define BBOX_TOPLEFT_X(i)  BoundingBoxCoords[(byte)((i)*4) + 0]
#define BBOX_TOPLEFT_Y(i)  BoundingBoxCoords[(byte)((i)*4) + 1]
#define BBOX_BOTRIGHT_X(i) BoundingBoxCoords[(byte)((i)*4) + 2]
#define BBOX_BOTRIGHT_Y(i) BoundingBoxCoords[(byte)((i)*4) + 3]

#define NOWRAP_BBOX_TOPLEFT_X(i)  BoundingBoxCoords[(i)*4 + 0]
#define NOWRAP_BBOX_TOPLEFT_Y(i)  BoundingBoxCoords[(i)*4 + 1]
#define NOWRAP_BBOX_BOTRIGHT_X(i) BoundingBoxCoords[(i)*4 + 2]
#define NOWRAP_BBOX_BOTRIGHT_Y(i) BoundingBoxCoords[(i)*4 + 3]

#endif
