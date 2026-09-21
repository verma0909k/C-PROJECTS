#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <signal.h>

#define RED "\033[1;31m"
#define BLUE "\033[1;34m"
#define GREEN "\033[1;32m"
#define RESET "\033[0m"
#define YELLOW "\033[33m"
#define CYAN "\033[1;36m"
#define WHITE "\033[1;37m"
#define ORANGE "\033[1;38;2;255;165;0m"

#ifdef _WIN32
    #include <windows.h>
    #define SLEEP(x) Sleep((x)*1000)
#else
    #include <unistd.h>
    #define SLEEP(x) sleep(x)
#endif

volatile sig_atomic_t running=1;
int format=2;

void filltime(char string[],int format);
void filldate(char string[]);
int getvalidint();
void handler(int signum) {
    running=0;
    signal(SIGINT,handler);
}
void digitalclock();
void printmenu();
void settings();
void timer();
void stopwatch();
void alarm();
int main() {
    signal(SIGINT,handler);
    int choice;
    while (1) {
        printf("\033[2J");
        printf("\033[H");
        printmenu();
        choice=getvalidint();
        switch (choice) {
        case 1:
            digitalclock();
            running=1;
            break;
        case 2:
            stopwatch();
            running=1;
            break;
        case 3:
            timer();
            running=1;
            break;
        case 4:
            /* code */
            break;
        case 5:
            settings();
            break;
        default :
            printf(ORANGE"\n------------------------------------------\n");
            printf("||<<========------EXITED------========>>||\n");
            printf(ORANGE"------------------------------------------------------\n");
            printf("||<<========------THANKS FOR PLAYING------========>>||\n");
            printf("------------------------------------------------------\n"RESET);
            return 1;
        }
    }
    return 0;
}
void stopwatch() {
    printf("\033[2J");
    printf("\033[H");
    char c,sl;
    int seconds=0;
    printf(YELLOW"\n<==========STOPWATCH==========>\n");
    printf("* press 'l'+enter to make a lap.\n");
    printf("* press 's'+enter to stop.\n"RESET);
    printf("\npress enter to start : ");
     if (scanf("%c",&c)) {
        while ((c = getchar()) != '\n' && c != EOF);
    }
    printf("\n");
    printf("\033[?25l");
    while (running) {
        printf(GREEN"+--------------------------+\n");
        printf("| "WHITE"STOPWATCH ==> %02d:%02d:%02d"GREEN"   |\n",seconds/3600,seconds/60,seconds%60);
        printf("+--------------------------+\n"RESET);
        seconds++;
        printf("\033[3A");
        fflush(stdout);
        SLEEP(1);
    }
    printf("\033[?25h");
    printf("stop or lap (s/l) : ");
    scanf("%c",&sl);
}
void timer() {
    printf("\033[2J");
    printf("\033[H");
    int seconds;
    char c;
    printf(YELLOW"\n<==========TIMER==========>\n");
    printf("ENTER DURATION (SECONDS) : "RESET);
    seconds=getvalidint();
    printf("\n");
    printf("\033[J");
    printf("\033[?25l");
    while (running==1 && seconds>=0) {
        printf(GREEN"+-----------------+\n");
        printf("| "WHITE"TIMER : %02d:%02d"GREEN"   |\n",seconds/60,seconds%60);
        printf("+-----------------+\n");
        printf(RED"press ctrl+c to stop.\n"RESET);
        seconds--;
        printf("\033[4A");
        fflush(stdout);
        SLEEP(1);
    }
    printf("\033[?25h");
    printf("\033[5B");
    if (running==1 && seconds<0) {
        printf(GREEN"~~~~~TIMER'S UP~~~~~\n"RESET);
    } else if (running==0 && seconds>0) {
        printf(ORANGE"TIMER IS STOPPED AT "RED"%02d:%02d\n"RESET);
    }
    printf("(press ENTER to confirm.)");
    if (scanf("%c",&c)) {
        while ((c = getchar()) != '\n' && c != EOF);
    }
}
void settings() {
    printf("\033[2J");
    printf("\033[H");
    int choice;
    char c;
    printf(YELLOW"\n\n<==========SETTINGS==========>\n");
    printf("1. 24 HOUR FORMAT\n");
    printf("2. 12 HOUR FORMAT (default)\n"RESET);
    printf("choose the format : ");
    choice=getvalidint();
    if (choice==1 || choice==2) {
        format=choice;
        printf(ORANGE"\n<---FORMAT UPDATED--->\n"RESET);
    } else {
        printf(ORANGE"\n<---INVALID CHOICE, KEEPING CURRENT FORMAT--->\n"RESET);
    }
    printf("(press ENTER to confirm.)");
    if (scanf("%c",&c)) {
        while ((c = getchar()) != '\n' && c != EOF);
    }
}
void printmenu() {
    printf(GREEN"\n+--------------------------------+\n");
    printf("|         "WHITE"DIGITAL CLOCK"GREEN"          |\n");
    printf("+--------------------------------+\n");
    printf("| "YELLOW"1. CLOCK"GREEN"                       |\n");
    printf("+--------------------------------+\n");
    printf("| "YELLOW"2. STOPWATCH"GREEN"                   |\n");
    printf("+--------------------------------+\n");
    printf("| "YELLOW"3. TIMER"GREEN"                       |\n");
    printf("+--------------------------------+\n");
    printf("| "YELLOW"4. ALARM"GREEN"                       |\n");
    printf("+--------------------------------+\n");
    printf("| "YELLOW"5. SETTINGS"GREEN"                    |\n");
    printf("+--------------------------------+\n");
    printf("| "YELLOW"EXIT (ANY NO.)"GREEN"                 |\n");
    printf("+--------------------------------+\n"RESET);
    printf("enter your choice :");
}
void digitalclock() {
    char time[50],date[100];
    printf("\033[2J");
    printf("\033[?25l");
    while(running) {
        printf("\033[H");
        filltime(time,format);
        filldate(date);
        printf(GREEN"\n+-------------------------------+\n");
        printf("|         "YELLOW"DIGITAL CLOCK"GREEN"         |\n");
        printf("+-------------------------------+"RESET"\n");
        printf(GREEN"| "RESET"CURRENT TIME ==>"RESET" %s",time);
        printf(GREEN"+-------------------------------+"RESET"\n");
        printf("[DATE : %s\n",date);
        printf(RED"PRESS CTRL+C TO EXIT.\n"RESET);
        fflush(stdout);
        SLEEP(1);
    }
    printf("\033[?25h");
}
int getvalidint() {
    int choice;
    while (scanf("%d",&choice)!=1) {
        printf(RED"ERROR: INVALID NUMBER\n"RESET);
        printf("enter again : ");
        while (getchar()!='\n');
    }
    return choice;
}
void filldate(char string[100]) {
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo=localtime(&rawtime);
    strftime(string,100,WHITE"%A %d %B %Y"RESET"]\n",timeinfo);
}
void filltime(char string[50],int format) {
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo=localtime(&rawtime);
    if (format==1){
        strftime(string,50,WHITE"%H:%M:"YELLOW"%S"RESET"     "GREEN"|"RESET"\n",timeinfo);
    } else {
        strftime(string,50,WHITE"%I:%M:"YELLOW"%S"WHITE" %p  "GREEN"|"RESET"\n",timeinfo);
    }
}