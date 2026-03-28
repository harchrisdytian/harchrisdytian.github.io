#ifndef ARRAY_HEADER_H
#define ARRAY_HEADER_H
// this is a generic tempate header to create behavior simular to c++ template
// 
// ARR_T int
// ARR_NAME_T intArray
// ARR_NEED_BASE_EQAULS 

#include <stdlib.h>
#include <string.h>
#include "../include/base.h"
#ifdef TESTING
#define ARR_T int
#define ARR_NAME_T intArray
#define ARR_NEED_BASE_EQAULS 
#endif
// #include <cstddef>
// #include <cstdlib>o
#define ARR_IMPL(word) ARR_COMB(ARR_NAME_T,word) 
#define ARR_T_IMPL(word) ARR_COMB(ARR_T,word) 

#define ARR_subtype(word) ARR_COMB(ARR_T,word) 

#define ARR_COMB(pre,word) ARR_COMB2(pre,word)
#define ARR_COMB2(pre,word) pre##_##word 


#endif //ARRAY_HEADER_H

#ifndef ARR_T
#error "ARR_T must be defined"
#endif

#ifndef ARR_NAME_T
#error "ARR_T must be defined"
#endif

#define  ARR_push ARR_IMPL(push)
#define  ARR_add ARR_IMPL(add)
#define  ARR_equals ARR_IMPL(equals)
#define  ARR_copy ARR_IMPL(copy)
#define  ARR_Tequals ARR_T_IMPL(equals)

typedef struct ARR_NAME_T
{
 ARR_T *items; 
 usize count;
 usize cap;
} ARR_NAME_T;

void
ARR_push(ARR_NAME_T* arr, ARR_T item);


bool
ARR_equals(ARR_NAME_T a, ARR_NAME_T b);


ARR_NAME_T
ARR_copy(ARR_NAME_T in);


#ifdef  ARR_NEED_BASE_EQAULS
bool
ARR_Tequals(ARR_T a,ARR_T b)
{
  return a == b;
}
#endif

void
ARR_push(ARR_NAME_T* arr, ARR_T item)
{
  if(arr->count >= arr->cap)
  {
    usize old_cap = arr->cap;
    usize new_cap = old_cap ? old_cap * 2 : 4;
    usize new_size = new_cap * sizeof(ARR_T);
    arr->items = ch_realloc(arr->items, new_size);
    arr->cap = new_cap;
  }
  arr->items[arr->count++] = item;
}



void
ARR_add(ARR_NAME_T* to, ARR_NAME_T* from)
{
  // TODO(Christian) make it so that it ch_realloc better
  usize new_count = to->count + from->count;
  if(new_count > to->cap)
  {
    usize new_cap = to->cap ? to->cap : 4;
    while(new_cap < new_count) new_cap *= 2;
    to->items  = ch_realloc(to->items, new_cap * sizeof(ARR_T));
    to->cap = new_cap;
  }
  ch_memcpy(to->items + to->count,from->items, from->count * sizeof(ARR_T));
  to->count = new_count;
};


bool
ARR_equals(ARR_NAME_T a, ARR_NAME_T b)
{
  if(a.count != b.count)
  {
    return false;
  }

  for(usize i = 0; i < b.count;i++)
  {
    ARR_T aVal = a.items[i];
    ARR_T bVal = b.items[i];
    if(!ARR_Tequals(aVal, bVal))
    {
      return false;
    }
  }

  return true;
  
  // return memcmp(a->items, b->items, sizeof(ARR_T) * a->count);
  
}
ARR_NAME_T
ARR_copy(ARR_NAME_T in)
{
  ARR_NAME_T temp = {0};
  ARR_add(&temp, &in);
  return temp;
  
}

#undef ARR_T
#undef ARR_NAME_T
#undef ARR_push
#undef ARR_add
#undef ARR_equals
#undef ARR_Tequals
#undef ARR_NEED_BASE_EQAULS
