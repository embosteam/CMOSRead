#include <stdio.h>
#include <unistd.h>
#ifdef __APPLE__
    #include <sys/uio.h>
#else
    #include <sys/io.h>
    #include <sys/perm.h>
#endif


struct tuple{
    unsigned char first;
    unsigned char second;
    unsigned char third;
};

unsigned char readCmos(unsigned char index){
    unsigned char value;
    outb(index,0x70);
    usleep(100);
    value = inb(0x71);
    //printf("[%x]: %x\n",index,value);
    //value = index;
    return value;
}

struct tuple work1(){
    struct tuple result = {0,};
    return result;
}
struct tuple ExampleFunction(){struct tuple result = {0,};return result;}
struct tuple work2(){
    struct tuple result = {0,};
    return result;
}
struct tuple getMinuteAndSecond(){
    struct tuple result = {0,};
    //example
    unsigned char minute = readCmos(0x02);
    //example
    unsigned char second = readCmos(0x0);
    result.first = minute;
    result.second = second;
    return result;
}

int main(){
    int ret;
    ret = iopl(3);
    if(ret!=0){
        fprintf(stderr,"[error]ret: %d\n",ret);
        return ret;
    }
    struct tuple example = ExampleFunction();
    unsigned char value1 = example.first;
    unsigned char value2 = example.second;
    unsigned char century = 0;
    unsigned char year = 0;
    unsigned char month = 0;
    unsigned char day = 0;
    unsigned char hour = 0;
    unsigned char sec = 0;
    unsigned char minute = 0;

    printf("%02x%02x-%02x-%02x %02x:%02x:%02x\n",century,year,month,day,hour,minute,sec);
    return 0;
}
