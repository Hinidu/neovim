#ifndef NVIM_SET_H
#define NVIM_SET_H

#include <stdbool.h>

#include "nvim/lib/khash.h"
#include "nvim/types.h"
#include "nvim/set_defs.h"

#define SET_DECLS(T)                                                          \
  KHASH_DECLARE(T##_set, T, char)                                             \
                                                                              \
  typedef struct {                                                            \
    khash_t(T##_set) *table;                                                  \
  } Set(T);                                                                   \
                                                                              \
  Set(T) *set_##T##_new(void);                                                \
  void set_##T##_free(Set(T) *set);                                           \
  bool set_##T##_has(Set(T) *set, T elem);                                    \
  void set_##T##_put(Set(T) *set, T elem);                                    \
  void set_##T##_del(Set(T) *set, T elem);

SET_DECLS(cstr_t)
SET_DECLS(uint64_t)

#define set_new(T) set_##T##_new
#define set_free(T) set_##T##_free
#define set_has(T) set_##T##_has
#define set_put(T) set_##T##_put
#define set_del(T) set_##T##_del

#endif  // NVIM_SET_H
