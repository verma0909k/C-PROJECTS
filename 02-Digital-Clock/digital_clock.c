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

#ifdef _WIN32
    #include <windows.h>
    #define SLEEP(x) Sleep((x)*1000)
#else
    #include <unistd.h>
    #define SLEEP(x) sleep(x)
#endif

volatile sig_atomic_t running=1;

void filltime(char string[],int format);
void filldate(char string[]);
void handler(int signum) {
    running=0;
}
int main() {
    signal(SIGINT,handler);
    printf(YELLOW"\nCHOOSE THE TIME FORMAT:\n");
    printf("1. 24 hour format\n");
    printf("2. 12 hour format(default)\n"RESET);
    printf("make a choice(1/2) :");
    int format;
    char time[50],date[100];
    while (scanf("%d",&format)!=1) {
        printf(RED"ERROR: INVALID NUMBER\n"RESET);
        printf("enter again : ");
        while (getchar()!='\n'); 
    }
    printf("\033[2J");
    printf("\033[?25l");
    while(running) {
        printf("\033[H");
        filltime(time,format);
        filldate(date);
        printf(CYAN"\n\n+-------------------------------+\n");
        printf("|         "YELLOW"DIGITAL CLOCK"CYAN"         |\n");
        printf("+-------------------------------+"RESET"\n");
        printf(CYAN"| "RESET"CURRENT TIME ==>"RESET" %s",time);
        printf(CYAN"+-------------------------------+"RESET"\n");
        printf("[DATE : %s\n",date);
        printf(RED"PRESS CTRL+C TO EXIT."RESET);
        fflush(stdout);
        SLEEP(1);
    }
    printf("\033[?25h");
    return 0;
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
        strftime(string,50,WHITE"%H:%M:"YELLOW"%S"RESET"     "CYAN"|"RESET"\n",timeinfo);
    } else {
        strftime(string,50,WHITE"%I:%M:"YELLOW"%S"WHITE" %p  "CYAN"|"RESET"\n",timeinfo);
    }
}