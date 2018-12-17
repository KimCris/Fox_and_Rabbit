#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


#define DELAY 600000

// decide what type ACM to use, look in the handout for pseudo-code

char slots[3][45]; // 3 slots; add the size of each slot instead of ... 45 because of screen charater
int  w=1, r=2, l=3; // define and initialise the variables as in the handout they have to be different 

void
reader_thread ()
{
  // variable declarations/initialisation, if needed

  while(1)  // reader loop; includes a delay to reduce the output data rate
    {
      r= 1;
      printf ("%s", slots[r]); // access slot; slots[i] is a pointer to slots[i][0]
                               // (slots[i][0],slots[i][1],... is a 0-terminated string)
      //...;   

      usleep(DELAY);     // limit output rate; calculate your own value (>500000)
    }
}

char inp() // getchar() wrapper which checks for End Of File EOF
{
  char c;
  c=getchar();
  if(c==EOF) exit(0); // exit the whole process if input ends
  return c;
}

int
main ()
{
  int j, i;
  pthread_t tid1; // variable declarations/initialisation, if needed

  pthread_create(&tid1,NULL,(void *) &reader_thread,NULL);; // create reader thread

  while (1)  // writer loop
    {
      //...;

// access slot; modify this according to the output format of your game
// in this example I keep reading until '*' appears,
// then the symbol 0 is added, which is the sting terminator.
// The terminator is needed for printf("%s",...) of the reader.
      j = 0;
      while ((slots[i][j++] = inp ()) != '*'); // the actual computation takes place inside the condition
      slots[i][j] = 0; // append the terminating symbol to the string

      //l/=w;
      //w/=!(r,l);
      //create anf if the make sure r l and w are different 
    }

  return 0;
}