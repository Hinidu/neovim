#include <stdlib.h>
#include <stdbool.h>

#include "nvim/set.h"
#include "nvim/set_defs.h"
#include "nvim/vim.h"
#include "nvim/memory.h"

#include "nvim/lib/khash.h"

#define cstr_t_hash kh_str_hash_func
#define cstr_t_eq kh_str_hash_equal
#define uint64_t_hash kh_int64_hash_func
#define uint64_t_eq kh_int64_hash_equal

#define SET_IMPL(T)                                                           \
  __KHASH_IMPL(T##_set,, T, char, 0, T##_hash, T##_eq)                        \
                                                                              \
  Set(T) *set_##T##_new()                                                     \
  {                                                                           \
    Set(T) *rv = xmalloc(sizeof(Set(T)));                                     \
    rv->table = kh_init(T##_set);                                             \
    return rv;                                                                \
  }                                                                           \
                                                                              \
  void set_##T##_free(Set(T) *set)                                            \
  {                                                                           \
    kh_destroy(T##_set, set->table);                                          \
    free(set);                                                                \
  }                                                                           \
                                                                              \
  bool set_##T##_has(Set(T) *set, T key)                                      \
  {                                                                           \
    return kh_get(T##_set, set->table, key) != kh_end(set->table);            \
  }                                                                           \
                                                                              \
  void set_##T##_put(Set(T) *set, T key)                                      \
  {                                                                           \
    int ret;                                                                  \
    kh_put(T##_set, set->table, key, &ret);                                   \
  }                                                                           \
                                                                              \
  void set_##T##_del(Set(T) *set, T key)                                      \
  {                                                                           \
    khiter_t k;                                                               \
                                                                              \
    if ((k = kh_get(T##_set, set->table, key)) != kh_end(set->table)) {       \
      kh_del(T##_set, set->table, k);                                         \
    }                                                                         \
  }

SET_IMPL(cstr_t)
SET_IMPL(uint64_t)
