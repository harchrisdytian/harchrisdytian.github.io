#ifndef STRING_HEADER
#define STRING_HEADER
#include "base.h"
#include <string.h>
#include <stdio.h>

#define ARR_T char
#define ARR_NAME_T string8
#define  ARR_NEED_BASE_EQAULS 

#include "../generics/array.h"

#define PAIR_T string8
#define PAIR_NAME_T string8pair
#include "../generics/pair.h"
// static inline
string8 string_lit (char* data);

void string8_print(string8 string);

string8 file_extention(string8 file);

void write_file(string8 path, string8 text);

string8pair split(string8 str, char n);

FILE* open_file(string8 path);

FILE* open_file_read(string8* Path)
{
  return fopen(Path->items,"r");
}

FILE* open_file_write(string8* Path)
{
  return fopen(Path->items,"w");
}

void string8_print(string8 string)
{
  
  if(string.count > 0)
  {
    printf("%s", string.items);
  }
}
void string8_println(string8 string)
{
  
  if(string.count > 0)
  {
    printf("%s", string.items);
    printf("\n");
  }
}
// static inline
string8 string_lit (char* data)
{
  string8 out = {0};
  for(size_t index = 0; index < strlen(data); index++)
  {
    string8_push(&out, data[index]);
  }
  
  return out;
}

string8 file_extention(string8 file)
{
  string8 out = {};
  char* dot = strchr(file.items, '.');
  
  if(dot)
  {
    out = string_lit(dot + 1);
  }
  return out;
}

string8pair split(string8 str, char n)
{
  string8pair out = {};
  
  // out.first = {}; 
  // out.second = {}; 
  bool foundChar =false;;
  for (usize index = 0; index < str.count; index++)
  {
    if(foundChar)
    {
      string8_push(&out.second, str.items[index]);
    }
    else
    {
      string8_push(&out.first, str.items[index]);
    }
    if(str.items[index] == n)
    {
      foundChar = true;
    }
  }
  return out;
}


// void write_file(string8 path, string8 text)
// {

// }

#endif

