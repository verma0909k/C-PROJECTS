#include <stdio.h>
#include <time.h>

#define RED "\033[1;31m"
#define BLUE "\033[1;34m"
#define GREEN "\033[1;32m"
#define RESET "\033[0m"
#define YELLOW "\033[33m"
#define CYAN "\033[1;36m"
#define WHITE "\033[1;37m"

#ifdef _WIN32
    #include <windows.h>
    #define CLEAR "cls"
    #define SLEEP(x) Sleep((x)*1000)
#else
    #include <unistd.h>
    #define CLEAR "clear"
    #define SLEEP(x) Sleep(x)
#endif

void filltime(char string[],int format);
void filldate(char string[]);
int main() {
    printf(YELLOW"\nCHOOSE THE TIME FORMAT:\n");
    printf("1. 24 hour format\n");
    printf("2. 12 hour format(default)\n"RESET);
    printf("make a choice(1/2) :");
    int format;
    char time[50],date[100];
    scanf("%d",&format);
    while(1) {
        filltime(time,format);
        filldate(date);
        system(CLEAR);
        printf(CYAN"+-------------------------------+\n");
        printf("|         "WHITE"DIGITAL CLOCK"CYAN"         |\n");
        printf("+-------------------------------+"RESET"\n");
        printf(CYAN"| "RESET"CURRENT TIME ==>"RESET" %s",time);
        printf(CYAN"+-------------------------------+"RESET"\n");
        printf("[DATE : %s\n",date);
        printf(RED"PRESS CTRL+C TO EXIT."RESET);
        SLEEP(1);
    }
    return 0;
}
void filldate(char string[100]) {
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo=localtime(&rawtime);
    strftime(string,100,"%A %B %Y]\n",timeinfo);
}
void filltime(char string[50],int format) {
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo=localtime(&rawtime);
    if (format==1){
        strftime(string,50,"%H:%M:"YELLOW"%S"RESET"     "CYAN"|"RESET"\n",timeinfo);
    } else {
        strftime(string,50,"%I:%M:"YELLOW"%S"RESET" %p  "CYAN"|"RESET"\n",timeinfo);
    }
}