#include <stdio.h>
#define DELAY 31500 // i still need to know how to calculate 

int main()
{
 char c;
 for(;;)
   {
     c=getc(stdin);
     if (c == EOF) return 0;
     usleep(DELAY); // specify delay for your experiment the number comes from the mathematical calculation
     printf("%c",c);
     fflush(stdout);
   }
 return 0;
}
