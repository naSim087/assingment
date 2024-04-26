#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<signal.h>
int main(){
alarm(5) ;
printf("Looping forever ...\n") ;
while(1) ;
printf("This line should never be executed.\n") ;
}