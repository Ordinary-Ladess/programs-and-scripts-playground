#include <stdio.h>
//some defines that could prove useful:
#define clear_screen() printf("\f\033[H\033[J")
#define save_cursor() printf("\033[%d\033[%dH", (y), (x))
#define reset_cursor() printf("\033[s")
#define cursor_pos(x,y) printf("\033[u")

class PROGRAM   { public:
      PROGRAM() {printf("\nElloh world\n\n");} 
     ~PROGRAM() {}};
      PROGRAM  main;