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

void add_item(string8 *website,string8 *pageName);
string8 HTMLbegin;
string8 HTMLend;

#define str string_lit


int main()
{
  HTMLbegin = string_lit(
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
  
  
  HTMLend = str("</body>");
  string8 homepage = string8_copy(HTMLend);
  
  string8Array files = file_list();
  for(usize index = 0; index < files.count ; index++)
  {
    File file ={0};
    make_file(files.items[index], &file);
    string8_println(files.items[index]);
    if (file.state == INVALID)
    {
      string8 msg = string_lit("failed to write");
      string8_println(msg);
      continue;
    }

    string8 msg2 = string_lit("storm\0");
    string8_println(msg2);
    string8 ext = string_lit("md");
    if(!string8_equals(file.file_extention, ext))
    {
      string8_println(file.file_extention);
      continue;
    }

    string8 help = {0};
    File_read(&file,&help );
    
    string8_println(help);
    cmark_node* head = cmark_parse_document(help.items, help.count, CMARK_OPT_DEFAULT);
    
    
    string8 content = string_lit( cmark_render_html(head, CMARK_OPT_DEFAULT));


    string8 webpage = string8_copy( HTMLbegin);
    string8_add(&webpage, &content);
    string8_add(&webpage, &HTMLend);
    printf("file name");
    string8_println(file.file_name);    

    string8 postpage_name = string8_copy(file.file_name);

    add_item(&homepage,&postpage_name);
    
    string8 _html = str(".html");
    string8_add(&postpage_name,&_html);
    
    
    File webFile;
    make_file(postpage_name, &webFile);
    

    string8_println(postpage_name);

    if(File_write(&webFile, &webpage) == INVALID)
    {
      string8_println(string_lit("WRITE FAILED"));
    }
    File_write(&webFile,&webpage);
    
    string8_println(webpage);
    
    // enl:
    // fclose(file.file);
  }
  string8_add(&homepage, &HTMLend);
  File Homepage_html;
  string8 index_name = string_lit("index.html");
  make_file(index_name,&Homepage_html );
  File_write(&Homepage_html, &homepage);
  // string8_println(name);
  return 0;
}

void add_item(string8 *website,string8 *pageName)
{
  
  string8 before = string_lit(
      "<li><a href=\"");
  
  string8 mid = string_lit(".html\">");
  string8 after = string_lit(
      "</li>\n");
  string8_add(website, &before);
  string8_add(website, pageName);
  string8_add(website, &mid);
  string8pair name = split(*pageName, '/');
  string8_add(website, &name.second);
  string8_add(website, &after);
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
      
      if (strcmp(entry->d_name , ".") == 0 ||strcmp(entry->d_name ,"..") == 0)
      {
        continue;
      }
      string8 mes = string_lit(entry->d_name);
      string8_println(mes);
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


