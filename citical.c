#include <stdio.h>
#include <signal.h>
#include<unistd.h>
int main(){
int (*oldHandler)();
printf("I can be Control-C'ed \n");
sleep(5);
oldHandler = signal(SIGINT, SIG_IGN);
printf("I am protected from Control-C now \n");
sleep(5);
signal(SIGINT, oldHandler);
printf("I can be Control-C'ed again \n");
sleep(5);
printf("Bye!!!!!!!\n");
}