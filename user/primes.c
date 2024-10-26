#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    int prime = 2;
    int x = 2;
    char forked = 0;

    int p[2];
    pipe(p);
    

    for (int i = 3; i < 130; i++)
    {
        write(p[1], &i, 4);
    }
    int stop = 0;


    if(fork() == 0){
        close(0);
        dup(p[0]);  //fd 0
        close(p[0]);

        do
        {
            if(!forked){
                prime = x;
                pipe(p);
            } 
            
            if (!forked && fork() == 0)
            {
                if (prime == stop)
                {
                    close(p[1]);
                    close(p[0]);
                    exit(0);
                }
                printf("prime %d\n", prime);
                close(p[1]);
                close(0);
                dup(p[0]);
                close(p[0]);
               
            }
            else
            {
                if (prime == stop)
                {
                    close(p[1]);
                    close(p[0]);
                    break;;
                }
                forked = 1;
                close(p[0]);
                if(x%prime != 0 || x == stop) write(p[1], &x, 4);
                if (x == stop)
                {
                    close(p[1]);
                    break;
                }
                
            }
        } while (read(0, &x, 4) > 0);
        //close(p[1]);
        exit(0);
    }
    else
    {
        close(p[0]);
        for (int j = 1; j < 6; j++)
        {
            for (int i = j*130; i < (j+1)*130; i++)
            {
                write(p[1], &i, 4);
            }
        }
        write(p[1], &stop, 4);
        close(p[1]);
        //exit(0);
    }   
    exit(0);
}

