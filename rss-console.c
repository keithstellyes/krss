#include <stdio.h>
#include "rss.h"
#include "shared.h"

int main(int argc, char **argv)
{
  copy_to_cb("Fuck yeah");
  rsserr_t err;
  rss_t *rss = parse_rss_file(argv[1], &err);
  if(err != SUCCESS) {
    printf("Parse error: %d\n", err);
    return 1;
  }

  printf("=== %s ===\n", rss->title);
  printf("(%s)\n", rss->desc);
  printf("ITEMS:\n");
  for(int i = 0; i < rss->itemc; i++) {
    printf("%s (%s)\n", rss->items[i].title, rss->items[i].link);
  }

  return 0;
}
