#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main() {
   printf("\n-----------------------------\n");
   printf("GUESSING NUMBER GAME\n");
   printf("-----------------------------\n");
   printf("\nWELCOME TO WORLD OF GUESSING NUMBERS.\n");
   srand(time(NULL));
   int secret=rand()%100+1;
   int guess;
   do {
      printf("\nGuess a number between(1 to 100) :");
      scanf("%d",&guess);
      if (secret>guess) {
         printf("TOO LOW !\n");
      } else if (secret<guess) {
         printf("TOO HIGH !\n");
      } else if (secret==guess) {
         printf("CORRECT !, The number is %d\n",secret);
      }
   } while (guess!=secret);



   return 0;
}