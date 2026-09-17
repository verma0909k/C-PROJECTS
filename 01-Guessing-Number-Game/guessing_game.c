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
#define ORANGE "\033[1;38;2;255;165;0m"
#define BYE "\033[1;36;40m"

void print_menu();
int playgame();
void updatehighscore(int attempts);
int getvalidint();
void mainmenu();
void multiplayermode();
void reversemode();

int main() {
   char playagain;
   do {
      mainmenu();
      int choice;
      choice=getvalidint();
      switch (choice)
      {
      case 1:
         srand(time(NULL));
         int attempts=playgame();
         updatehighscore(attempts);
         break;
      case 2:
         reversemode();
         break;
      case 3:
         srand(time(NULL));
         multiplayermode();
         break;
      default:
         printf(RED"ERROR : YOU HAVE EXITED THE GAME\n"RESET);
         return 1;
      }
      printf("\nWANNA PLAY AGAIN ?(Y/N) :");
      scanf(" %c",&playagain);
   } while (playagain=='Y' || playagain=='y');
   printf(BYE"\n \nTHANKS FOR PLAYING.\nDEVELOPER : PIYUSH VERMA\nSTATE     : HARAYANA\n"RESET);
   printf("\n");

   return 0;
}
void reversemode() {
   int range,low=1,high,attempts=0,guess;
   char ch;
   printf("\nWELCOME TO THE WORLD OF GUESSING NUMBERS.\n \n");
   printf(YELLOW"|| REVERSE MODE (instructions) ||\n"RESET);
   printf(WHITE"* Player has to think a number.\n");
   printf("* Computer will guess that number.\n");
   printf("* Respond with 'h' if my guess is lower than the number.\n");
   printf("* Respond with 'l' if my guess is higher than the number.\n");
   printf("* Respond with 'c' if i guess correctly.\n"RESET);
   printf("\nEnter the upper range for the computer to guess within(eg. 100) :");
   range=getvalidint();
   printf(YELLOW"--------------------------------------\n");
   printf("Think of a number between(1 to %d) :\n",range);
   printf("--------------------------------------\n"RESET);
   high=range;
   while (low<=high) {
      guess=(low+high)/2;
      printf("\nMy guess is %d (h/l/c) :",guess);
      attempts++;
      scanf(" %c",&ch);
      if (ch=='h' || ch=='H') {
         low=guess+1;
      } else if (ch=='l' || ch=='L') {
         high=guess-1;
      } else if (ch=='c' || ch=='C') {
         printf(GREEN"I GUESSED IT CORRECTLY !\nYOU CAME UP WITH %d.\nI TOOK %d ATTEMPTS.\n"RESET,guess,attempts);
         return;
      } else {
         printf(RED"YOU ARE TRYING TO CHEAT -_- \n"RESET);
         attempts--;
      }
   }
   printf(RED"EITHER YOU MISUNDERSTOOD THE RULES :( OR YOU WERE TRYING TO CHEAT -_- \n"RESET);
}
void multiplayermode() {
   int attempts1=0,attempts2=0,player=1,range,number,guess;
   printf("\nWELCOME TO THE WORLD OF GUESSING NUMBERS.\n \n");
   printf(YELLOW"|| MULTIPLAYER MODE (instructions) ||\n"RESET);
   printf(WHITE"* There are two players who will guess the number.\n");
   printf("* Each player gets their turn one by one.\n");
   printf("* They can select custom range of their choice.\n");
   printf("* First person to guess correctly wins the game.\n \n"RESET);
   printf("Enter the upper range (eg. 100) : ");
   range=getvalidint();
   number=rand()%range+1;
   time_t start;
   start=time(NULL);
   do {
      printf("\nPLAYER %d TURN ==> enter your guess(1 to %d) :",player,range);
      guess=getvalidint();
      if (player==1) {
         attempts1++;
      } else if (player==2) {
         attempts2++;
      }
      if (number<guess) {
         printf(ORANGE "NUMBER IS SMALLER THAN GUESS\n" RESET);
      } else if (number>guess) {
         printf(BLUE "NUMBER IS GREATER THAN GUESS\n" RESET);
      } else if (number==guess) {
         time_t end;
         end=time(NULL);
         printf(GREEN "PLAYER %d WON !\nTHE NUMBER WAS %d\nTIME TAKEN : %ld SECONDS\n",player,number,(long)difftime(end,start));
         printf("PLAYER 1 ATTEMPTS : %d\n",attempts1);
         printf("PLAYER 2 ATTEMPTS : %d\n"RESET,attempts2);
      }
      player=player==1?2:1;
   } while (number!=guess);
}
void mainmenu() {
   printf(CYAN "+--------------------------------+\n");
   printf("|      "WHITE"GUESSING NUMBER GAME"CYAN"      |\n");
   printf("+--------------------------------+\n");
   printf("| "YELLOW"1. START NEW GAME"CYAN"              |\n");
   printf("+--------------------------------+\n");
   printf("| "YELLOW"2. REVERSE MODE"CYAN"                |\n");
   printf("+--------------------------------+\n");
   printf("| "YELLOW"3. MULTIPLAYER MODE"CYAN"            |\n");
   printf("+--------------------------------+\n" RESET);
   printf("enter your choice :");
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
         printf(ORANGE "NUMBER IS SMALLER THAN GUESS\n" RESET);
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
         printf(RED "GAME OVER !\nTHE NUMBER WAS %d\n" RESET,number);
         Beep(293,1000);
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