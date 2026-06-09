/*
 * File: GND.h
 * Author: vididvidid 
 * Created: 2026-06-09 14:51:01
 */

#ifndef GND_H
#define GND_H

#include <stdlib.h>
#include <stddef.h>

/*
 * =================================================== *
 * C GENERIC DYNAMIC ARRAY TEMPLATE                    *
 * =================================================== *
 */

#define gnd(Type) struct { Type *items; size_t count; size_t capacity; }

#define push(nm, item) do {\
    if ((nm).count >= (nm).capacity) {\
  (nm).capacity = ((nm).capacity == 0) ? 128 : (nm).capacity * 2;\
        (nm).items = realloc((nm).items, (nm).capacity * sizeof(*(nm).items));\
    }\
    (nm).items[(nm).count++] = (item);\
} while(0)

#define pull(nm) ((nm).items[--(nm).count])

#define free_gnd(nm) do {\
    free((nm).items);\
    (nm).items = NULL;\
    (nm).count = (nm).capacity = 0;\
} while(0)

#endif


