#ifndef FILE_HEADER
#define FILE_HEADER
#include <stdio.h>
#include "base.h"
#include "string.h"


typedef enum FileState
{
  INIT,
  OPEN,
  READ,
  WRITE,
  INVALID
} FileState;

typedef struct File {
  string8 path;
  string8 file_extention;
  string8 file_name;
  FileState state;
  FILE* file;
} File;

void make_file(string8 inPath, File* file);

FileState File_read(File* file, string8* out);
FileState File_write(File* file, string8* content);

void make_file(string8 InPath, File* file)
{
  printf("make file with");
  string8_println(InPath);
  string8 something = string_lit("invalid file \n");
  string8 something1 = string_lit("neerr \n");
  string8 something2 = string_lit("perr \n");
  
  // string8_print(something1);
  File out = {0};
  string8 inPath = string8_copy(InPath);
  if(inPath.count < 0)
  {
    string8 err = string_lit("to small \n");
    string8_print(err);
    string8_print(InPath);
    
    file->state = INVALID;  
    return;
  }
  if( inPath.items[inPath.count - 1] == '.')
  {
    string8 err = string_lit("ends in dot \n");
    string8_print(err);
    printf("\n\n");
    string8 blunk = string8_copy(inPath);
    string8_print(inPath);
    
    printf("\n\n");
    file->state = INVALID;  
    return;
  }
  if (inPath.items[inPath.count - 1] == '.')
  {
    string8 err = string_lit("ends in dot one less \n");
    string8_print(something);
    
    file->state = INVALID;  
    return;
  }

  string8_print(something2);
  string8 a = {0};
  file->file_extention = a;
  file->path = string8_copy(inPath);

  file->state = INIT;
  // string8_print(inPath);
  // string8_print(inPath);

  // file->file_extention = {0};
  b8 SawDot = false;
  printf("inPath.count = %zu\n", inPath.count);
  for(usize index =0; index < inPath.count;index++)
  {
    printf("%c", InPath.items[index]);
    if (SawDot) {
      string8_push(&file->file_extention, inPath.items[index]);
      // string8_print(file->file_extention);
    }
     if(inPath.items[index] == '.')
     {
       string8 FileName = string8_copy(inPath);
       FileName.count = index;
       file->file_name = string8_copy(FileName);

       string8_print(FileName);
       SawDot=true;
     }
  }
  if (file->file_extention.count < 2)
  {
    file->state = INVALID;
  }
  
  string8_print(something2);
}

FileState File_read(File* file, string8* out)
{ 

  string8_print(file->path);

  file->file = open_file_read(&file->path);
  // return READ;
  if(file->file == NULL)
  {
    string8_println(file->path);
    file->state = INVALID; 
    return INVALID;
  };
  
  
  char c;
  while((c = fgetc(file->file)) !=EOF)
  {
    // putchar(c);
    string8_push(out,(char)c);
  }
  

  // rewind(file->file);

  file->state = READ;
  fclose(file->file);
  return READ;
}


FileState File_write(File* file, string8* _content)
{
  
  string8 content = *_content;
  string8_push(&content, '\0');
  string8_push(&file->path, '\0');
  string8_print(file->path);

  file->file = open_file_write(&file->path);

  if(file->file == NULL)
  {
    return INVALID;
  }
  fwrite(content.items, sizeof (char), content.count, file->file);  
  
  fclose(file->file);
  file->state = WRITE;
  return WRITE;
}



#endif
