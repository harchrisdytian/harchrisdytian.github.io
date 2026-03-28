#ifdef PAIR_H
#define PAIR_H

// this is a generic tempate header to create behavior simular to c++ template
// 

#define PAIR_IMPL(word) PAIR_COMB(PAIR_NAME_T,word) 

#define PAIR_subtype(word) PAIR_COMB(PAIR_T,word) 

#define PAIR_COMB(pre,word) PAIR_COMB2(pre,word)
#define PAIR_COMB2(pre,word) pre##_##word 
#endif


#ifndef PAIR_T
#error "PAIR_T must be defined"
#endif

#ifndef PAIR_NAME_T
#error "ARR_T must be defined"
#endif


typedef struct PAIR_NAME_T
{
  PAIR_T first;
  PAIR_T second;
} PAIR_NAME_T;

#undef PAIR_T
#undef PAIR_NAME_T
