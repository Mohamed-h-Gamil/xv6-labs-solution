#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]){
    int p1[2], p2[2];
    pipe(p1);
    pipe(p2);
    
    if (fork() == 0)
    {
        char* recieved_ping;

        close(p1[1]);
        close(0);
        dup(p1[0]);
        close(p1[0]);
        
        if (read(0, &recieved_ping, 1) == 0)
        {
            write(1, "ERRROR: No byte ping recieved\n", strlen("ERRROR: No byte recieved\n"));
            exit(1);
        }
        else{
            printf("%d: received ping\n", getpid());
            write(p2[1], "l", 1);
            close(p2[1]);
        }
    }
    else
    {
        write(p1[1], "k", 1);
        close(p1[1]);
        close(p2[1]);
        close(0);
        dup(p2[0]);
        close(p2[0]);
        char* recieved_pong;
        wait(0);
        if (read(0, &recieved_pong, 1) == 0)
        {
            write(1, "ERRROR: No byte pong recieved\n", strlen("ERRROR: No byte recieved\n"));
            exit(1);
        }
        else{
            printf("%d: received pong\n", getpid());
        }
    }
    
}