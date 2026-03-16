// #include <stdint.h>
#include <cmark.h>
#include "include/base.h"
#include "include/string.h"

#define ARR_T string8
#define ARR_NAME_T string8Array
#include "generics/array.h"

#include "include/file.h"
#include <dirent.h>
#include <stddef.h>
#include <stdio.h>

string8Array file_list();

string8 indexHTML;



int main()
{
  indexHTML = string_lit(
   "<!DOCTYPE html>\n"
    "<html lang=\"en\">\n"
    "<head>\n"
    "    <meta charset=\"UTF-8\">\n"
    "    <meta name=\"viewport\" content=\"width=device-width initial-scale=1.0\">\n"
    "    <title>Page Title</title>\n"
    "    <link rel=\"stylesheet\" href=\"styles.css\">\n"
    "</head>\n"
    "<body>\n"
  );
  // string8_println(indexHTML);
  // string8 name = string_lit("hellow\n");


  // string8_push(&name,'\0');
  string8Array files = file_list();
  // string8_println(indexHTML);
  for(usize index = 0; index < files.count ; index++)
  {
    
    // string8_println(files.items[index]);
    // FILE* file= read_file(files.items[index]);
    

    
    
    File file ={0};
    make_file(files.items[index], &file);
    
    
    // printf("string %s",file.file_extention.items);
    if (file.state == INVALID)
    {
      string8 msg = string_lit("failed to write");
      string8_println(msg);
      // fclose(file);
      continue;
    }

    // printf("\n");
    string8 msg2 = string_lit("storm\0");
    string8_println(msg2);
    string8 ext = string_lit("md");
    string8_push(&ext,'\0');
    // string8 curr_file_extention = file_extention(files.items[index]);;
    // string8_println(file.file_extention);
    if(string8_equals(file.file_extention, ext))
    {
      
      string8_println(file.file_extention);
      continue;;
    }

    string8 help = {0};
    File_read(&file,&help );
    
    string8_println(help);
    cmark_node* head = cmark_parse_document(help.items, help.count, CMARK_OPT_DEFAULT);
    
    string8 print = string_lit( cmark_render_html(head, CMARK_OPT_DEFAULT));

  
    string8 homepage = string_lit("indexer.html");
    string8_println(homepage);

    File index = {0};
    
    make_file(homepage, &index);
    
    File_write(&index, &print);
    
    string8_println(print);
    
    
    // enl:
    // fclose(file.file);
  }
  // string8_println(name);
  return 0;
}


string8Array file_list()
{

    // string8 hm = string_lit("lghkjghkj \n");
    // string8_println(hm);
    string8Array out = {0};
    DIR *dir;

    dir =opendir("Posts");
    
    struct dirent *entry;
    
    while((entry = readdir(dir))!= NULL)
    {
      
      
      string8 prefix_filename = string_lit("Posts/");
      // string8 
      string8 entryName= string_lit(entry->d_name);
      
      string8_println(prefix_filename);
      string8_add(&prefix_filename, &entryName);
      // string8_push(&prefix_filename, '\0');
      // string8_println(prefix_filename);
      string8Array_push(&out, prefix_filename);
      
    }
    
    // string8_println(hm);
    return out;
}


