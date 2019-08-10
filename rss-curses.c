#include <ncurses.h>

#include "rss.h"
#include "shared.h"

typedef struct browse_state_t {
  rss_t *rss;
  int top;
  int selected;
} browse_state_t;

void init_browse_state(browse_state_t *st, rss_t *r);
void draw_browse_state(browse_state_t *st);
void draw_popup(char *text);

int main(int argc, char **argv)
{
  if(argc != 2) {
    printf("USAGE: %s <local RSS file>\n", argv[0]);
    return -1;
  }
  initscr();
  noecho();
  keypad(stdscr, TRUE);
  set_escdelay(25);

  rsserr_t err;
  rss_t *rss = parse_rss_file(argv[1], &err);

  browse_state_t st;
  init_browse_state(&st, rss);
  draw_browse_state(&st);
  int ch;
  while((ch = getch()) != ESC && ch != 'q' && ch != 'Q') {
    int rows, cols;
    getmaxyx(stdscr, rows, cols);

    switch(ch) {
      case KEY_UP:
        if(st.top > 0) {
          st.top--;
        } else if(st.selected > 0) {
          st.selected--;
        } else {
          bell();
        }
        break;
      case KEY_DOWN:
        if(st.selected < rows - 1) {
          st.selected++;
        } else if(st.top + 1 < st.rss->itemc) {
          st.top++;
        }
        break;
      case 'c':
      case 'C':
        copy_to_cb(st.rss->items[st.top + st.selected].link);
        draw_popup("Link copied!");
        break;
      case 'o':
      case 'O':
        open_url(st.rss->items[st.top + st.selected].link);
    }
    clear();
    draw_browse_state(&st);
  }

  endwin();
}

void draw_browse_state(browse_state_t *st)
{
  int rows, cols;
  getmaxyx(stdscr, rows, cols);
  move(0, 0);

  int top = st->top;
  for(int i = top; i < st->rss->itemc && i < top + rows; i++) {
    if(i - top == st->selected) {
      attron(A_REVERSE);
    }

    char *s = trim_str(st->rss->items[i].title, cols);
    printw(s);

    if(i - top == st->selected) {
      int slen = strlen(s);
      for(int i = 0; i < cols - slen - 1; i++) {
        printw(" ");
      }
      attroff(A_REVERSE);
    }
    printw("\n");
  }
}

void init_browse_state(browse_state_t *st, rss_t *r)
{
  st->rss = r;
  st->top = 0;
  st->selected = 0;
}

void draw_popup(char *text)
{
  int rows, cols;
  getmaxyx(stdscr, rows, cols);

  attron(A_REVERSE);
  char spaces[cols + 1];
  memset(spaces, ' ', cols);
  mvprintw(rows - 1, 0, spaces);
  mvprintw(rows - 1, 0, text);
  attroff(A_REVERSE);
  getch();
}
