/*
 ============================================================================
 Name        : code1.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "algorithm.h"
#include "agi.h"

//void cardiology1(long r,long c);
//int cardiology2();

int main(int argc, char *argv[])
{
    int a;
    AgiMember *pDemo;

    setvbuf(stdout, NULL, _IONBF, 0);
    a = 2;
    printf("Hello World %d\n",a);
    Cardiology1(7,3);
    Cardiology2(8,3);
    Cardiology1(8,3);
    printf("\n");
    Cardiology1(95,912669);//456335 48 456335 2
    //cardiology1(7,3);
    //cardiology2();

    pDemo = AgiOpen(0);
    DemoTask1(pDemo);

    return 0;
}
