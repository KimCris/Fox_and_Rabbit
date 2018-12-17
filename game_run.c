#include <stdio.h>
#include <termios.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define width  40      // the max charater can eairt can be eaither one digit or two for the max vlaue of the coordenate 
#define height 18
#define buf_length (width*height)
#define fox_init_x (width/3*2)
#define fox_init_y (height/2)
#define fox_init_dir 'u'
#define rabbit_init_x (width/3*1)
#define rabbit_init_y (height/2)
#define rabbit_init_dir 'd'


//---- set keyboard mode -- please copy and use this function
struct termios
tty_prepare ()
{
  struct termios tty_attr_old, tty_attr;
  tcgetattr (0, &tty_attr);
  tty_attr_old = tty_attr;
  tty_attr.c_lflag &= ~(ECHO | ICANON);
  tty_attr.c_cc[VMIN] = 1;
  tcsetattr (0, TCSAFLUSH, &tty_attr);
  return tty_attr_old;
}

//---- restore keyboard mode -- please copy and use this function
void
tty_restore (struct termios tty_attr)
{
  tcsetattr (0, TCSAFLUSH, &tty_attr);
}

//---- fox direction
char fox_dir = fox_init_dir;

//---- keyboard thread function
void
keys_thread ()
{
while(1){
if (getchar() == '\033') { // if the first value is esc
    getchar(); // skip the [
    switch(getchar()) { // the real value
        case 0x41:  fox_dir = 'u';  
        break;
        case 0x42: fox_dir = 'd'; 
        break;
        case 0x44:  fox_dir = 'l'; 
        break;
        case 0x43: fox_dir = 'r'; 
        break;
    }
}
}
// Use getchar() to read the keyboard
// Each arrow key generates a sequence of 3 symbols
// the first two are always 0x1b and 0x5b
// the third is
// 0x41 -- up
// 0x42 -- down
// 0x43 -- right
// 0x44 -- left
// Update the global variable fox_dir appropriately 
}

//---- update x and y coord-s according to direction; used in main()
void
update_coord (int *x_ptr, int *y_ptr, char dir) // call by reference to x and y
{
  switch (dir)
    {
    case 'u': if (*y_ptr > 1) (*y_ptr)--; break; // *y_ptr is called "dereference",
// which is the target pointed at by the pointer
    case 'd': if (*y_ptr < height) (*y_ptr)++; break;
    case 'l': if (*x_ptr > 1) (*x_ptr)--; break;
    case 'r': if (*x_ptr < width) (*x_ptr)++; break;

    }
}


//---- the program starts its execution from here
int
main ()
{
  pthread_t t1;
  struct termios term_back;
  int fox_x = fox_init_x, fox_y = fox_init_y; // variable declarations and initialisation
  int rabbit_x = rabbit_init_x, rabbit_y = rabbit_init_y, rabbit_dir = rabbit_init_dir;

  term_back = tty_prepare ();
  pthread_create (&t1,NULL, (void*)&keys_thread, NULL) ; // create the keyboard thread

  //temp zone
  FILE * fp;
  //////////////////////
  
  while (1)
    {
      usleep (500000);

      update_coord (&fox_x, &fox_y, fox_dir);

      //... // generate the rabbit direction at random
      for (int c = 1; c <= 4; c++) { //this generate 4 random numbers
          int n = rand() % 4 + 1;
        switch (n)
        {
          case 1: rabbit_dir = 'u'; break; 
          case 2: rabbit_dir = 'd'; break;
          case 3: rabbit_dir = 'r'; break;
          case 4: rabbit_dir = 'l'; break;
        }
          
                                   }   

      update_coord (&rabbit_x, &rabbit_y, rabbit_dir);

      printf ("\033[2J\033[%d;%dH@\033[%d;%dH*", fox_y, fox_x, rabbit_y, rabbit_x); // max value of 45 for screen outuput 
      // //temp
      fp = fopen("/Users/CMcacombe/Documents/t.txt", "a"); // This file is for debug 
      fprintf(fp, "f_x = %d, f_y = %d | r_x = %d, r_y = %d\n", fox_x, fox_y, rabbit_x, rabbit_y);
      fclose(fp);
     
      if(fox_y == rabbit_y && fox_x-1 == rabbit_x) { // this terminate the program 
        break;
      }
      fflush (stdout);
 
    }

  pthread_cancel (t1);
  tty_restore (term_back);

  return 0;
}

