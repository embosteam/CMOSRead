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
    usleep(5);
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
//To improve legibility
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

struct tuple getYearAndMonth()
{
    struct tuple result = {0,};
    //example
    unsigned char year = readCmos(0x09);
    //example
    unsigned char month = readCmos(0x08);

    result.first = year;
    result.second = month;
    
    return result;
}

struct tuple getCenturyDayAndHour()
{
    struct tuple result = {0,};
    //example
    unsigned char century = readCmos(0x32);
    unsigned char day = readCmos(0x07);
    unsigned char hour = readCmos(0x04);


    result.first = century;
    result.second = day;
    result.third = hour;
    
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

    struct tuple minute_and_second = getMinuteAndSecond();
    struct tuple year_and_month = getYearAndMonth();
    struct tuple century_day_and_hour = getCenturyDayAndHour();
    unsigned char century = century_day_and_hour.first;
    unsigned char year = year_and_month.first;
    unsigned char month = year_and_month.second;
    unsigned char day = century_day_and_hour.second;
    unsigned char hour = century_day_and_hour.third;
    unsigned char sec = minute_and_second.second;
    unsigned char minute = minute_and_second.first;

    printf("%02x%02x-%02x-%02x %02x:%02x:%02x\n",century,year,month,day,hour,minute,sec);
    return 0;
}
