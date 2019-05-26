#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>

/*
        Simple Linux Mouse Hack

        Developed by : Malindas Sulochana Silva
        Date         : 26:052019
        
        Free to modify,and use
 */



int main(){

/* 
Code  |	Description
----------------------------------------------------
_________________________________
yo	Y-Axis Overflow
xo	X-Axis Overflow
ys	Y-Axis Sign Bit (9-Bit Y-Axis Relative Offset)
xs	X-Axis Sign Bit (9-Bit X-Axis Relative Offset)
ao	Always One
bm	Button Middle (Normally Off = 0)
br	Button Right (Normally Off = 0)
bl	Button Left (Normally Off = 0)
_________________________________
Xm	X-Axis Movement Value
_________________________________
Ym	Y-Axis Movement Value

details at: https://wiki.osdev.org/PS/2_Mouse

*/
    FILE * fp;
    unsigned char buffer[1024];
    int Xm,Ym;
    bool y0,x0,ys,xs,a0,bm,br,bl;
    
    
    int fd = open("/dev/input/mice",O_RDONLY,0666);
    if(fd < 0){
        printf("Error Opening the file\n");
        return -1;
    }
    while(1){
        if(read(fd,buffer,3)< 0){
            printf("Error while reading the data\n");
        }

        y0 = buffer[0]>>7 & 0x01;
        x0 = buffer[0]>>6 & 0x01;
        ys = buffer[0]>>5 & 0x01;
        xs = buffer[0]>>4 & 0x01;        
        bm = buffer[0]>>2 & 0x01;
        br = buffer[0]>>1 & 0x01;
        bl = buffer[0] & 0x01;

        Xm = buffer[1];
        Ym = buffer[2];
        printf("%X, %X, %X\n",buffer[0],buffer[1], buffer[2]);
        printf("y0::%d, x0::%d, ys::%d, xs::%d, bm::%d, br::%d, bl::%d, Ym::%d, Xm::%d\n",y0,x0,ys,xs,bm,br,bl,Ym,Xm);
        
    }
    close(fd);

    return 0;

}