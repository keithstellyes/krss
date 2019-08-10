#ifndef RSS_H
#define RSS_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

typedef enum rsserr_t {
  SUCCESS,
  ///////////////
  PARSE_ERR_BEGIN,
  RSS_TAG_MISSING,
  CHANNEL_TAG_MISSING,
  PARSE_ERR_END,
  ////////////////
} rsserr_t;

typedef struct rssitem_t {
  char *title;
  char *link;
} rssitem_t;

typedef struct rss_t {
  char *title;
  char *desc;

  int itemc;
  rssitem_t *items;
} rss_t;

rss_t *parse_rss_file(char *fname, rsserr_t *err);

#ifdef __cplusplus
}
#endif /* C++ */
#endif /*RSS_H*/
