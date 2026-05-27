#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>
#include <signal.h>
#include <time.h>
#include <locale.h>
#include <stdlib.h>

#include "bosu.h"

# define FRAME_RATE 60

/**
 * Sleep for a given number of milliseconds
 * \param ms is the number of milliseconds to sleep for
 */
void sleep_ms(size_t ms) {
  struct timespec ts;
  size_t rem = ms % 1000;
  ts.tv_sec = (ms - rem) / 1000;
  ts.tv_nsec = rem * 1000000;

  // Sleep repeatidly as long as nanosleep is interrupted
  while (nanosleep(&ts, &ts) != 0) {}
}


int main() {
  setlocale(LC_ALL, "");

  // Set up ncurses
  initscr();                    // Initializing the standard windwow
  signal(SIGINT, SIG_IGN);      // Ignore the signal <C-c>, do nothing just return
  noecho();                     // No display of keys when they are typed
  curs_set(0);                  // Hides the cursor
  nodelay(stdscr, FALSE);       // Setup blocking input
  scrollok(stdscr, FALSE);      // Disable scrolling

  // Get max dimensions of terminal screen
  int max_x, max_y;
  getmaxyx(stdscr, max_y, max_x);

  int repeats = 6;
  while (repeats != 0) {
    // Iter through the frames in frames array located in frames.h file
    for (int i = 0; i < FRAME_COUNT; i++) {
      clear(); // clear the current window

      int frame_rows = 0;
      while (frames[i][frame_rows] != NULL) frame_rows++;

      int start_y = (max_y - frame_rows) / 2;
      int start_x = (max_x - 44) / 2;

      for (int j = 0; frames[i][j] != NULL; j++) {
          move(start_y + j, start_x);
          addstr(frames[i][j]);
      }

      refresh();
      sleep_ms(400);
    }
    repeats--;
  }
  
  endwin(); // Shutdown
}
