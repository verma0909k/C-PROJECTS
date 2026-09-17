#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

#define RED "\033[1;31m"
#define BLUE "\033[1;34m"
#define GREEN "\033[1;32m"
#define RESET "\033[0m"
#define YELLOW "\033[1;33m"
#define MAGENTA "\033[1;35m"
#define CYAN "\033[1;36m"
#define BLACK "\033[1;30m"
#define WHITE "\033[1;37m"

void print_menu();
int playgame();
void updatehighscore(int attempts);
int getvalidint();
void mainmenu();

int main() {
   mainmenu();
   int choice;
   char playagain;
   choice=getvalidint();
   switch (choice)
   {
   case 1:
      srand(time(NULL));
      do {
         int attempts=playgame();
         updatehighscore(attempts);
         printf("\nWANNA PLAY AGAIN ?(Y/N) :");
         scanf(" %c",&playagain);
      } while (playagain=='Y' || playagain=='y');
      printf("THANKS FOR PLAYING\n");
      break;
   case 2:
      
      break;
   default:
      printf("EXIT : YOU ENTERED OTHER CHOICE");
      break;
   }



   // char playagain;
   // srand(time(NULL));
   // do {
   //    int attempts=playgame();
   //    updatehighscore(attempts);
   //    printf("\nWANNA PLAY AGAIN ?(Y/N) :");
   //    scanf(" %c",&playagain);
   // } while (playagain=='Y' || playagain=='y');
   // printf("THANKS FOR PLAYING\n");

   return 0;
}
void mainmenu() {
   printf(CYAN "+--------------------------------+\n");
   printf("|      "WHITE"GUESSING NUMBER GAME"CYAN"      |\n");
   printf("+--------------------------------+\n");
   printf("| "YELLOW"1. START NEW GAME"CYAN"              |\n");
   printf("+--------------------------------+\n");
   // printf("| "YELLOW"2. MULTIPLAYER"CYAN"                 |\n");
   // printf("+--------------------------------+\n");
   printf("| "YELLOW"2. REVERSE MODE"CYAN"                |\n");
   printf("+--------------------------------+\n");
   // printf("| "YELLOW"2. YOUR STATS"CYAN"                  |\n");
   // printf("+--------------------------------+\n");
   printf("|      "YELLOW"EXIT (ANY OTHER NO.)"CYAN"      |\n");
   printf("+--------------------------------+\n" RESET);
   printf("\nenter your choice :");
}
int getvalidint() {
   int value;
   while (scanf("%d",&value)!=1) {
      printf("ERROR :enter valid number\n");
      while (getchar()!='\n');
      printf("enter again :");
   }
   return value;
}
void updatehighscore(int attempts) {
   int best=-1;
   FILE *ptr;
   ptr=fopen("highscore.txt","r");
   if (ptr!=NULL) {
      fscanf(ptr,"%d",&best);
      fclose(ptr);
   }
   if (attempts>0 && (best==-1 || attempts<best)) {
      ptr=fopen("highscore.txt","w");
      if (ptr!=NULL) {
         fprintf(ptr,"%d",attempts);
         fclose(ptr);
         printf("\nNEW HIGHSCORE : %d\n",attempts);
      }
   } else if (best!=-1) {
      printf("\nBEST SCORE SO FAR IS %d ATTEMPTS\n",best);
   }
}
int playgame() {
   print_menu();

   int choice,range;
   choice=getvalidint();
   int guess,max_attempts,attempts=0;
   
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
   int prevdistance=-1;
   time_t start;
   start=time(NULL);
   while (attempts<max_attempts) {
      printf("\nGuess a number between(1 to %d) :",range);
      guess=getvalidint();
      attempts++;
      int distance=abs(number-guess);
      if (number>guess && attempts!=max_attempts) {
         printf(BLUE "NUMBER IS GREATER THAN GUESS\n" RESET);
      } else if (number<guess && attempts!=max_attempts) {
         printf(RED "NUMBER IS SMALLER THAN GUESS\n" RESET);
      } else if (number==guess) {
         time_t end;
         end=time(NULL);
         printf(GREEN "YOU WON !\nTHE NUMBER WAS %d.\nYOU TOOK %d ATTEMPTS TO GUESS IT.\n" RESET,number,attempts);
         printf(GREEN "TIME TAKEN : %ld SECONDS\n" RESET,(long)difftime(end,start));
         return attempts;
      }
      if (prevdistance!=-1 && attempts!=max_attempts) {
         if (distance<prevdistance) {
            printf("(hint--you are getting warmer)\n");
         } else if (distance>prevdistance) {
            printf("(hint--you are getting colder)\n");
         } else if (distance==prevdistance) {
            printf("(hint--you are same as before)\n");
         }
      }
      prevdistance=distance;
      if (attempts==max_attempts) {
         printf(MAGENTA "GAME OVER !\nTHE NUMBER WAS %d\n" RESET,number);
         Beep(750,1000);
      }
      else {
         printf("ATTEMPTS LEFT :%d\n",max_attempts-attempts);
      }
   }
   return -1;
}
void print_menu() {
   printf("\nWELCOME TO THE WORLD OF GUESSING NUMBERS.\n");
   printf(YELLOW "\nCHOOSE DIFFICULTY :\n");
   printf("1. EASY     (1-50, 10 attempts)\n");
   printf("2. MEDIUM   (1-100, 7 attempts)\n");
   printf("3. HARD     (1-200, 6 attempts)\n");
   printf("4. EXTREME  (1-500, 5 attempts)\n" RESET);
   printf("enter your choice: ");
}