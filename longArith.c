#include <stdio.h>
#include <stdlib.h>
#include "function.h"

int main(int argc, char *argv[])
{
    FILE *output;
    char *inputFirst,*inputSecond,*inputThird;
    int lengthFirst,lengthSecond,i,binary,module,lengthModule;
    unsigned char *numberOne,*numberTwo,*remainder,*numModule;
	unsigned char sign1,sign2,sign3;
	char sign;
	if (argc < 5 )
	{
		printf("\nEnter correct parameters\n");
		return 0;
	}
    if (argc < 6)
	{
		binary=0;
		module=0;
	}
    if (argc == 6)
	{
		if (strcmp(argv[5],"-b") == 0)
		{
			binary=1;
			module=0;
		}
		else
		{
			binary=0;
			module=1;
			inputThird=argv[5];
			lengthModule = readd(&numModule,inputThird,&sign3);
		}
	}
	if (argc == 7)
	{
		binary=1;
		module=1;
		inputThird=argv[6];
		lengthModule = readb(&numModule,inputThird);
	}
	
	inputFirst =argv[1];
    inputSecond=argv[3];

    if(!binary)
    {

        output = fopen(argv[4],"w");
    }
    else
    {
        output = fopen(argv[4],"wb");
    }

	sign=argv[2][0];
	switch(sign)
	{
		case '+' :
			if (!binary)
			{
				lengthFirst = readd(&numberOne,inputFirst,&sign1);
				lengthSecond = readd(&numberTwo,inputSecond,&sign2);
				turn(&numberOne);
				turn(&numberTwo);
				if ((sign1=='+')&&(sign2=='+'))
				{
					numberOne = summ(&numberOne,&numberTwo);
					turn(&numberOne);
					fprintf(output,"%s",numberOne);
					break;
				}
				if ((sign1=='-')&&(sign2=='-'))
				{
					numberOne = summ(&numberOne,&numberTwo);
					turn(&numberOne);
					fprintf(output,"-%s",numberOne);
					break;
				}
				if ((sign1=='+')&&(sign2=='-'))
				{
					if (cmp(&numberOne,&numberTwo) == 1)
					{
						numberOne = sub(&numberOne,&numberTwo);
						turn(&numberOne);
						fprintf(output,"%s",numberOne);
					}
					else
					{
						numberOne = sub(&numberTwo,&numberOne);
						turn(&numberOne);
						fprintf(output,"-%s",numberOne);
					}
					break;
				}
				if ((sign1=='-')&&(sign2=='+'))
				{
					if (cmp(&numberOne,&numberTwo) == 1)
					{
						numberOne = sub(&numberOne,&numberTwo);
						turn(&numberOne);
						fprintf(output,"-%s",numberOne);
					}
					else
					{
						numberOne = sub(&numberTwo,&numberOne);
						turn(&numberOne);
						fprintf(output,"%s",numberOne);
					}
					break;
				}
			}
			else
			{
				lengthFirst = readb(&numberOne,inputFirst);
				lengthSecond = readb(&numberTwo,inputSecond);
				numberOne=summb(&numberOne,&numberTwo,lengthFirst,lengthSecond,&lengthFirst);
				fwrite(numberOne,lengthFirst,1,output);
			}
			break;

		case '-' :
			if (!binary)
			{
				lengthFirst = readd(&numberOne,inputFirst,&sign1);
				lengthSecond = readd(&numberTwo,inputSecond,&sign2);
				turn(&numberOne);
				turn(&numberTwo);
				if ((sign1=='+')&&(sign2=='+'))
				{
					if (cmp(&numberOne,&numberTwo) == 1)
					{
						numberOne = sub(&numberOne,&numberTwo);
						turn(&numberOne);
						fprintf(output,"%s",numberOne);
					}
					else
					{
						numberOne = sub(&numberTwo,&numberOne);
						turn(&numberOne);
						fprintf(output,"-%s",numberOne);
					}
					break;
				}
				if ((sign1=='-')&&(sign2=='-'))
				{
					if (cmp(&numberOne,&numberTwo) == 1)
					{
						numberOne = sub(&numberOne,&numberTwo);
						turn(&numberOne);
						fprintf(output,"-%s",numberOne);
					}
					else
					{
						numberOne = sub(&numberTwo,&numberOne);
						turn(&numberOne);
						fprintf(output,"%s",numberOne);
					}
					break;
				}
				if ((sign1=='+')&&(sign2=='-'))
				{
					numberOne = summ(&numberOne,&numberTwo);
					turn(&numberOne);
					fprintf(output,"%s",numberOne);
					break;
				}
				if ((sign1=='-')&&(sign2=='+'))
				{
					numberOne = summ(&numberOne,&numberTwo);
					turn(&numberOne);
					fprintf(output,"-%s",numberOne);
					break;
				}
			}
			else
			{
				lengthFirst = readb(&numberOne,inputFirst);
				lengthSecond = readb(&numberTwo,inputSecond);
				numberOne=subb(&numberOne,&numberTwo,lengthFirst,lengthSecond,&lengthFirst);
				fwrite(numberOne,lengthFirst,1,output);
			}
			break;

		case '*' :
			if (!binary)
			{
				lengthFirst = readd(&numberOne,inputFirst,&sign1);
				lengthSecond = readd(&numberTwo,inputSecond,&sign2);
				turn(&numberOne);
				turn(&numberTwo);
				if (((sign1=='+')&&(sign2=='+'))||((sign1=='-')&&(sign2=='-')))
				{
					numberOne=mul(&numberOne,&numberTwo);
					turn(&numberOne);
					fprintf(output,"%s",numberOne);
				}
				else
				{
					numberOne=mul(&numberOne,&numberTwo);
					turn(&numberOne);
					fprintf(output,"-%s",numberOne);
				}
			}
			else
			{
				lengthFirst = readb(&numberOne,inputFirst);
				lengthSecond = readb(&numberTwo,inputSecond);
				numberOne=mulb(&numberOne,&numberTwo,lengthFirst,lengthSecond,&lengthFirst);
				fwrite(numberOne,lengthFirst,1,output);
			}
			break;

		case '/' :
			if (!binary)
			{
				lengthFirst = readd(&numberOne,inputFirst,&sign1);
				lengthSecond = readd(&numberTwo,inputSecond,&sign2);
				if (((sign1=='+')&&(sign2=='+'))||((sign1=='-')&&(sign2=='-')))
				{
					fprintf(output,"%s",divv(&numberOne,&numberTwo,&remainder));
				}
				else
				{
					fprintf(output,"-%s",divv(&numberOne,&numberTwo,&remainder));
				}
			}
			else
			{
				lengthFirst = readb(&numberOne,inputFirst);
				lengthSecond = readb(&numberTwo,inputSecond);
				turnb(&numberOne,lengthFirst);
				turnb(&numberTwo,lengthSecond);
				numberOne=divvb(&numberOne,&numberTwo,lengthFirst,lengthSecond,&lengthFirst,&remainder,&lengthSecond);
				turnb(&numberOne,lengthFirst);
				fwrite(numberOne,lengthFirst,1,output);
			}
			break;

		case '%' :
			if (!binary)
			{
				lengthFirst = readd(&numberOne,inputFirst,&sign1);
				lengthSecond = readd(&numberTwo,inputSecond,&sign2);
				divv(&numberOne,&numberTwo,&remainder);
				fprintf(output,"%s",remainder);
			}
			else
			{
				lengthFirst = readb(&numberOne,inputFirst);
				lengthSecond = readb(&numberTwo,inputSecond);
				turnb(&numberOne,lengthFirst);
				turnb(&numberTwo,lengthSecond);
				divvb(&numberOne,&numberTwo,lengthFirst,lengthSecond,&lengthFirst,&remainder,&lengthSecond);
				turnb(&remainder,lengthSecond);
				fwrite(remainder,lengthSecond,1,output);
				free(remainder);
			}
			break;

		case '^' :
			if (!binary)
			{
				lengthFirst = readd(&numberOne,inputFirst,&sign1);
				lengthSecond = readd(&numberTwo,inputSecond,&sign2);
				turn(&numberOne);
				turn(&numberTwo);
				numberOne=degree(&numberOne,&numberTwo,&sign1);
				turn(&numberOne);
				if (sign1=='+')
					fprintf(output,"%s",numberOne);
				else
					fprintf(output,"-%s",numberOne);
			}
			else
			{
				lengthFirst = readb(&numberOne,inputFirst);
				lengthSecond = readb(&numberTwo,inputSecond);
				numberOne=degreeb(&numberOne,&numberTwo,lengthFirst,lengthSecond,&lengthFirst);
				fwrite(numberOne,lengthFirst,1,output);
			}
			break;
		default:
			break;
	}

    fclose(output);

	if (module)
	{
		if(!binary)
		{
			output = fopen(argv[4],"w");
			divv(&numberOne,&numModule,&remainder);
			fprintf(output,"%s",remainder);
		}
		else
		{
			output = fopen(argv[4],"wb");
			turnb(&numberOne,lengthFirst);
			turnb(&numModule,lengthModule);
			divvb(&numberOne,&numModule,lengthFirst,lengthModule,&lengthFirst,&remainder,&lengthModule);
			turnb(&remainder,lengthModule);
			fwrite(remainder,lengthModule,1,output);
		}
		fclose(output);
	    
	}
    return 0;
}
