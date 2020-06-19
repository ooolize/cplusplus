#include <func.h>

int main(int argc,char*argv[])
{
    int fd=open("fifo1.pip",O_RDONLY);
    char buf[128]={0};
    if(read(fd,buf,sizeof(buf))>0){
        puts(buf);
    }
    close(fd);
}

