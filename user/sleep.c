#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]){
    if(argc < 2){
        write(1, "Usage: sleep <number>\n", strlen("Usage: sleep <number>\n"));
        exit(1);
    }
    sleep(atoi(argv[1]));
    exit(0);
}

