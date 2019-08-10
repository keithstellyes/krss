#include <stdlib.h>
#include <string.h>
#include "shared.h"

/* Function to check if x is power of 2*/
bool is_pow2(int n)
{
   if(n==0)
   return false;

   return (ceil(log2(n)) == floor(log2(n)));
}

char *trim_str(char *s, int max)
{
  if(strlen(s) >= max) {
    s[max - 1] = '\0';
    s[max - 2] = '.';
    s[max - 3] = '.';
    s[max - 4] = '.';
  }

  return s;
}

void copy_to_cb(char *s)
{
#ifdef __APPLE__
  char *FMT = "printf '%s' | pbcopy";
  char *buff = alloca(strlen(FMT) + strlen(s) + 1);
  sprintf(buff, FMT, s);
  system(buff);
#endif
}

void open_url(char *url)
{
#ifdef __APPLE__
  char *FMT = "open '%s'";
  char *buff = alloca(strlen(FMT) + strlen(url) + 1);
  sprintf(buff, FMT, url);
  system(buff);
#endif
}

void bell()
{
  printf("\a");
}
