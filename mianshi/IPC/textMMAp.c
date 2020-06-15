#include <func.h>

int main(){
    int fd=open("file",O_CREAT|O_RDWR,0600);
    ftruncate(fd,1<<20);
    char* p=(char*)mmap(NULL,1<<20,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if(!fork()){
        /* *addr='a'; */
        printf("%s\n",p);
    }
    else{
        strcpy(p,"hello");
        wait(NULL);
        /* puts(addr); */
        /* printf("%s",addr); */
    }
    /* munmap(p,1<<20); */

}

