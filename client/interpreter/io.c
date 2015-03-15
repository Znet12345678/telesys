#include <stdio.h>
#include <string.h>
char *cat(const char *path)
{
  char ch[1024];
  char filec[1024];
  int c;
  long length;
  char *buffer;
  FILE *f = fopen(path,"r"); 
  if (f)
	{
		fseek(f,0,SEEK_END);
		length = ftell(f);
		fseek(f,0,SEEK_SET);
		buffer = malloc(length);
		if(buffer)
		{
			fread(buffer,1,length,f);
		}
	}
  return buffer;
}
