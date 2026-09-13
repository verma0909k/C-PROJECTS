#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void print_menu();

int main() {
   print_menu();

    int choice,range;
   scanf("%d",&choice);
   int guess,max_attempts,attempts=0;
   srand(time(NULL));
   
   switch (choice)
   {
   case 1:
      range=50;
      max_attempts=10;
      break;
   case 2:
      range=100;
      max_attempts=7;
      break;
   case 3:
      range=200;
      max_attempts=6;
      break;
   case 4:
      range=500;
      max_attempts=5;
      break;
   default:
      range=100;
      max_attempts=7;
      break;
   }

   int number=rand()%range+1;

   while (attempts<max_attempts) {
      printf("\nGuess a number between(1 to %d) :",range);
      scanf("%d",&guess);
      attempts++;
      if (number>guess) {
         printf("TOO LOW !\n");
      } else if (number<guess) {
         printf("TOO HIGH !\n");
      } else if (number==guess) {
         printf("YOU WON ! The number was %d. you took %d attempts to guess it.\n",number,attempts);
         break;
      }
      if (attempts==max_attempts) {
         printf("\nGAME OVER! ,The number was %d\n",number);
      }
      else {
         printf("ATTEMPTS LEFT :%d\n",max_attempts-attempts);
      }
   }



   return 0;
}
void print_menu() {
   printf("\n-----------------------------\n");
   printf("GUESSING NUMBER GAME\n");
   printf("-----------------------------\n");
   printf("\nWELCOME TO THE WORLD OF GUESSING NUMBERS.\n");
   printf("\nCHOOSE DIFFICULTY :\n");
   printf("1. EASY     (1-50, 10 attempts)\n");
   printf("2. MEDIUM   (1-100, 7 attempts)\n");
   printf("3. HARD     (1-200, 6 attempts)\n");
   printf("4. EXTREME  (1-500, 5 attempts)\n");
   printf("enter your choice: ");
}