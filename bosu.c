#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>
#include <signal.h>
#include <time.h>

# define FRAME_RATE 60
# define FRAME_COUNT 3

const char *frames[] = {
  "    ()    ",
  "   (  )   ",
  " (      ) ",
};

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
  // Set up ncurses
  initscr();                    // Initializing the standard windwow
  // signal(SIGINT, SIG_IGN);   // Ignore the signal <C-c>, do nothing just return
  noecho();                     // No display of keys when they are typed
  curs_set(0);                  // Hides the cursor
  nodelay(stdscr, FALSE);       // Setup blocking input
  scrollok(stdscr, FALSE);      // Disable scrolling

  
  // Get max dimensions of terminal screen
  int max_x, max_y;
  getmaxyx(stdscr, max_y, max_x);
  
  int reps = 13;
  while (reps != 0) {
    for (int i=0; i < FRAME_COUNT; i++) {
      clear();
      mvprintw(max_y / 2, max_x / 2, frames[i]);
      refresh();
      sleep_ms(150);
    }
    reps--;
  }

  
  endwin(); // Shutdown

}
