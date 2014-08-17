#ifndef NVIM_MAP_DEFS_H
#define NVIM_MAP_DEFS_H

#include "nvim/types.h"

#define Map(T, U) Map_##T##_##U
#define PMap(T) Map(T, ptr_t)

#endif  // NVIM_MAP_DEFS_H
