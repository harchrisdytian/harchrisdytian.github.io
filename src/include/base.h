#ifndef BASE_HEADER
#define  BASE_HEADER

#include <stdlib.h>
#include <stdint.h>

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef uint8_t  ui8;

typedef uint16_t ui16;
typedef uint32_t ui32;
typedef uint64_t ui64;

typedef i8 b8;
typedef size_t usize;

typedef float f32;

// TODO(christian) create a good mem system 
#define ch_malloc(data) malloc(data)
#define ch_realloc(data,size) realloc( data , size )
#define ch_free(data) free(data)
#define ch_memcpy(to,from,size) memcpy( to , from , size)



#endif // BASE_HEADER
