#ifndef RSS_SHARED_H
#define RSS_SHARED_H
#ifdef __cplusplus
extern "C" {
#endif

#include<stdio.h>
#include<stdbool.h>
#include<math.h>
#include <string.h>

#define streq(a, b) (strcmp((char*)a, (char*)b) == 0)
#define free_nonnull(p) do { if(p != NULL) free(p); } while(0)
#define ESC 27

bool is_pow2(int n);
char *trim_str(char *s, int max);
void copy_to_cb(char *s);
void open_url(char *url);
void bell();

#ifdef __cplusplus
}
#endif /* C++ */
#endif /*RSS_SHARED_H*/
