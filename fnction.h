#include <stdio.h>
int readd(unsigned char **number,char *file,unsigned char *sign);
int readb(unsigned char **number,char *file);
int cmp(unsigned char **numberOne,unsigned char **numberTwo);
int cmpb(unsigned char **numberOne,unsigned char **numberTwo,int lengthFirst,int lengthSecond);
int turn(unsigned char **number);
int turnb(unsigned char **number,int length);
unsigned char *summ(unsigned char **numberOne,unsigned char **numberTwo);
unsigned char *summb(unsigned char **numberOne,unsigned char **numberTwo,int lengthFirst,int lengthSecond,int *lengthSumm);
unsigned char *sub(unsigned char **numberOne,unsigned char** numberTwo);
unsigned char *subb(unsigned char **numberOne,unsigned char **numberTwo,int lengthFirst,int lengthSecond,int *lengthSumm);
unsigned char *mul(unsigned char **numberOne,unsigned char **numberTwo);
unsigned char *mulb(unsigned char **numberOne,unsigned char **numberTwo,int lengthFirst,int lengthSecond,int *lengthSumm);
unsigned char *divv(unsigned char **numberOne,unsigned char **numberTwo,unsigned char **remainder);
unsigned char *divvb(unsigned char **numberOne,unsigned char **numberTwo,int lengthFirst,int lengthSecond,int *lengthSumm,unsigned char **remainder,int *lengthOst);
unsigned char *degree(unsigned char **numberOne,unsigned char **numberTwo,unsigned char *sign);
unsigned char *degreeb(unsigned char **numberOne,unsigned char **numberTwo,int lengthFirst,int lengthSecond,int *lengthSumm);
