#include <func.h>

int main(int argc,char*argv[])
{
    int fd=open("fifo1.pip",O_WRONLY);
    write(fd,"hello",5);
    close(fd);
    return 0;
}

