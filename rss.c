#include <libxml/parser.h>
#include <libxml/tree.h>
#include <stdio.h>

#include "rss.h"
#include "shared.h"

xmlNode *get_node(xmlNode *root, char *title)
{
  for(xmlNode *cur_node = root; cur_node != NULL; cur_node = cur_node->next) {
    if(cur_node->type == XML_ELEMENT_NODE && streq(cur_node->name, title)) {
      return cur_node;
    }
  }

  return NULL;
}

char *perma_content(xmlNode *node)
{
  char *read_content = (char*) xmlNodeGetContent(node);
  char *ret_content = malloc(strlen(read_content) + 1);
  strcpy(ret_content, read_content);
  return ret_content;
}

char *get_content_for_node_if_exists(xmlNode *node, char *title)
{
  xmlNode *retNode = get_node(node, title);
  if(retNode != NULL) {
    return perma_content(retNode);
  } else {
    return NULL;
  }
}

rss_t *parse_rss_file(char *fname, rsserr_t *err)
{
  xmlDoc *doc = xmlReadFile(fname, NULL, 0);
  xmlNode *root = xmlDocGetRootElement(doc);

  rss_t *rss = malloc(sizeof(rss_t));
  rss->title = NULL;
  rss->desc = NULL;
  rss->items = malloc(sizeof(rssitem_t) * 8);
  rss->itemc = 0;

  xmlNode *rss_node = get_node(root, "rss");

  if(rss_node == NULL) {
    *err = RSS_TAG_MISSING;
    goto ERR;
  }

  xmlNode *channel_node = get_node(rss_node->children, "channel");

  if(channel_node == NULL) {
    *err = CHANNEL_TAG_MISSING;
    goto ERR;
  }

  rss->title = get_content_for_node_if_exists(channel_node->children, "title");
  rss->desc = get_content_for_node_if_exists(channel_node->children, "description");

  for(xmlNode *cur_node = channel_node->children; cur_node != NULL; cur_node = cur_node->next) {
    if(cur_node->type != XML_ELEMENT_NODE) continue;
    if(streq(cur_node->name, "item")) {
      if(rss->itemc >= 8 && is_pow2(rss->itemc)) {
        rss->items = realloc(rss->items, rss->itemc * 2 * sizeof(rssitem_t));
      }

      rss->items[rss->itemc].title = get_content_for_node_if_exists(cur_node->children, "title");
      rss->items[rss->itemc].link = get_content_for_node_if_exists(cur_node->children, "link");
      rss->itemc++;
    }
  }

  *err = SUCCESS;
  return rss;

ERR:
  free_nonnull(rss->title);
  free_nonnull(rss->desc);
  return NULL;
}
