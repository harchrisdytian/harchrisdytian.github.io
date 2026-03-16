#ifndef ARRAY_HEADER_H
#define ARRAY_HEADER_H
// this is a generic tempate header to create behavior simular to c++ template
// 
// ARR_T int
// ARR_NAME_T intArray
// ARR_NEED_BASE_EQAULS 

#include <stdlib.h>
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
#define  ARR_Tequals ARR_T_IMPL(equals)

typedef struct ARR_NAME_T
{
 ARR_T *items; 
 size_t count;
 size_t cap;
} ARR_NAME_T;

void
ARR_push(ARR_NAME_T* arr, ARR_T item);


bool
ARR_equals(ARR_NAME_T a, ARR_NAME_T b);

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
    size_t old_cap = arr->cap;
    size_t new_cap = old_cap ? old_cap * 2 : 4;
    size_t new_size = new_cap * sizeof(ARR_T);
    arr->items = realloc(arr->items, new_size);
    arr->cap = new_cap;
  }
  arr->items[arr->count++] = item;
}



void
ARR_add(ARR_NAME_T* to, ARR_NAME_T* from)
{
  // TODO(Christian) make it so that it realloc better
  // 
  for(size_t index =0;index < from->count; index++)
  {
    ARR_push(to,from->items[index]);
  }
};


bool
ARR_equals(ARR_NAME_T a, ARR_NAME_T b)
{
  if(a.count != b.count)
  {
    return false;
  }

  for(size_t i = 0; i < b.count;i++)
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

#undef ARR_T
#undef ARR_NAME_T
#undef ARR_push
#undef ARR_add
#undef ARR_equals
#undef ARR_Tequals
#undef ARR_NEED_BASE_EQAULS
