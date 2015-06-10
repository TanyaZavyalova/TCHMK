#include "function2.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define block 200


	veryLong::veryLong()
	{
		binary=false;
		sign='+';
		length=0;
		number=NULL;
	}

	int veryLong::rd(char *inputFile)
	{
		length=readd(&number,inputFile,&sign);
		return 0;
	}

	int veryLong::rdb(char *inputFile)
	{
		length=readb(&number,inputFile);
		return 0;
	}

	int veryLong::out(char *out)
	{
		FILE *inputFile;
		if (!binary)
		{
			inputFile=fopen(out,"w");
			if (sign=='+')
				fprintf(inputFile,"%s\n",number);
			else
				fprintf(inputFile,"-%s\n",number);
		}
		else
		{
			inputFile=fopen(out,"wb");
			fwrite(number,length,1,inputFile);
		}
		fclose(inputFile);
		return 0;
	}

	veryLong veryLong::operator+(veryLong n1)
	{
		veryLong n;
		unsigned char *del;
		if (!binary)
		{
			turn(&number);
			turn(&n1.number);
			del=n.number;
			if ((sign=='+')&&(n1.sign=='+'))
			{
				n.number = summ(&number,&n1.number);
				n.sign='+';
			}
			if ((sign=='-')&&(n1.sign=='-'))
			{
				n.number = summ(&number,&n1.number);
				n.sign='-';
			}
			if ((sign=='+')&&(n1.sign=='-'))
			{
				if (cmp(&number,&n1.number) == 1)
					{
						n.number = sub(&number,&n1.number);
						n.sign='+';
					}
					else
					{
						n.number = sub(&n1.number,&number);
						n.sign='-';
					}
			}
			if ((sign=='-')&&(n1.sign=='+'))
			{
				if (cmp(&number,&n1.number) == 1)
					{
						n.number = sub(&number,&n1.number);
						n.sign='-';
					}
					else
					{
						n.number = sub(&n1.number,&number);
						n.sign='+';
					}
			}
			n.length = strlenn(&n.number);
			n.binary=binary;
			turn(&number);
			turn(&n1.number);
			turn(&n.number);
			if (del != NULL)
				free(del);
		}
		else
		{
			n.number = summb(&number,&n1.number,length,n1.length,&n.length);
			n.binary=binary;
		}
		return n;
	}

	veryLong veryLong::operator-(veryLong n1)
	{
		veryLong n;
		if (!binary)
		{
			turn(&number);
			turn(&n1.number);
			if ((sign=='+')&&(n1.sign=='+'))
			{
				if (cmp(&number,&n1.number) == 1)
					{
						n.number = sub(&number,&n1.number);
						n.sign='+';
					}
					else
					{
						n.number = sub(&n1.number,&number);
						n.sign='-';
					}
			}
			if ((sign=='-')&&(n1.sign=='+'))
			{
				if (cmp(&number,&n1.number) == 1)
					{
						n.number = sub(&number,&n1.number);
						n.sign='-';
					}
					else
					{
						n.number = sub(&n1.number,&number);
						n.sign='+';
					}
			}
			if ((sign=='+')&&(n1.sign=='-'))
			{
				n.number = summ(&number,&n1.number);
				n.sign='+';
			}
			if ((sign=='-')&&(n1.sign=='+'))
			{
				n.number = summ(&number,&n1.number);
				n.sign='-';
			}
			n.length = strlenn(&n.number);
			n.binary=binary;
			turn(&number);
			turn(&n1.number);
			turn(&n.number);
		}
		else
		{
			n.number = subb(&number,&n1.number,length,n1.length,&n.length);
			n.binary=binary;
		}
		return n;
	}

	veryLong veryLong::operator*(veryLong n1)
	{
		veryLong n;
		if (!binary)
		{
			turn(&number);
			if (&number != &n1.number)
				turn(&n1.number);
			if (((sign=='+')&&(n1.sign=='+'))||((sign=='-')&&(n1.sign=='-')))
			{
				n.number = mul(&number,&n1.number);
				n.sign='+';
			}
			else
			{
				n.number = mul(&number,&n1.number);
				n.sign='-';
			}
			n.length = strlenn(&n.number);
			n.binary=binary;
			turn(&number);
			if (&number != &n1.number)
				turn(&n1.number);
			turn(&n.number);
		}
		else
		{
			n.number = mulb(&number,&n1.number,length,n1.length,&n.length);
			n.binary=binary;
		}
		return n;
	}

	veryLong veryLong::operator/(veryLong n1)
	{
		veryLong n;
		unsigned char *ostatok;
		int lenOst;
		if (!binary)
		{
			if (((sign=='+')&&(n1.sign=='+'))||((sign=='-')&&(n1.sign=='-')))
			{
				n.number = divv(&number,&n1.number,&ostatok);
				n.sign='+';
			}
			else
			{
				n.number = divv(&number,&n1.number,&ostatok);
				n.sign='-';
			}
			n.length = strlenn(&n.number);
			n.binary=binary;
		}
		else
		{
			turnb(&number,length);
			turnb(&n1.number,n1.length);
			n.number = divvb(&number,&n1.number,length,n1.length,&n.length,&ostatok,&lenOst);
			n.binary=binary;
			turnb(&number,length);
			turnb(&n1.number,n1.length);
			turnb(&n.number,n.length);
		}
		return n;
	}

	veryLong veryLong::operator%(veryLong n1)
	{
		veryLong n;
		unsigned char *ostatok;
		int lenOst;
		if (!binary)
		{
			divv(&number,&n1.number,&n.number);
			n.length = strlenn(&n.number);
			n.binary=binary;
		}
		else
		{
			turnb(&number,length);
			turnb(&n1.number,n1.length);
			divvb(&number,&n1.number,length,n1.length,&lenOst,&n.number,&n.length);
			n.binary=binary;
			turnb(&number,length);
			turnb(&n1.number,n1.length);
			turnb(&n.number,n.length);
		}
		return n;
	}

	veryLong veryLong::operator^(veryLong n1)
	{
		veryLong n;
		if (!binary)
		{
			turn(&number);
			turn(&n1.number);
			n.sign=sign;
			n.number = degree(&number,&n1.number,&n.sign);
			n.length = strlenn(&n.number);
			n.binary=binary;
			turn(&number);
			turn(&n1.number);
			turn(&n.number);
		}
		else
		{
			n.number = degreeb(&number,&n1.number,length,n1.length,&n.length);
			n.binary=binary;
		}
		return n;
	}

	int veryLong::strlenn(unsigned char **s)
	{
		int i=0;
		while(true)
		{
			if ((*s)[i]=='\0')
				break;
			i++;
		}
		return i;
	}

	veryLong veryLong::operator=(veryLong n1)
	{
		if ((*this).number != NULL)
			free((*this).number);
		(*this).number = (unsigned char*) malloc(block);
		(*this).length=n1.length;
		for (int i=0;i<n1.length;i++)
			(*this).number[i]=n1.number[i];
		(*this).number[(*this).length]='\0';
		(*this).binary=n1.binary;
		(*this).sign=n1.sign;
		return *this;		
	}

	bool veryLong::operator==(veryLong n1)
	{
		int i;
		if (!n1.binary)
		{
			i=cmp(&(*this).number,&n1.number);
		}
		else
		{
			i=cmpb(&(*this).number,&n1.number,(*this).length,n1.length);
		}
		if (i==2)
			return true;
		else
			return false;				
	}

	bool veryLong::operator<(veryLong n1)
	{
		int i;
		if (!n1.binary)
		{
			i=cmp(&(*this).number,&n1.number);
		}
		else
		{
			turnb(&(*this).number,(*this).length);
			turnb(&n1.number,n1.length);
			i=cmpb(&(*this).number,&n1.number,(*this).length,n1.length);
			turnb(&(*this).number,(*this).length);
			turnb(&n1.number,n1.length);
		}
		if (i==0)
			return true;
		else
			return false;
	}

	bool veryLong::operator>(veryLong n1)
	{
		int i;
		if (!n1.binary)
		{
			i=cmp(&(*this).number,&n1.number);
		}
		else
		{
			turnb(&(*this).number,(*this).length);
			turnb(&n1.number,n1.length);
			i=cmpb(&(*this).number,&n1.number,(*this).length,n1.length);
			turnb(&(*this).number,(*this).length);
			turnb(&n1.number,n1.length);
		}
		if (i==1)
			return true;
		else
			return false;
	}

	bool veryLong::operator>=(veryLong n1)
	{
		int i;
		if (!n1.binary)
		{
			i=cmp(&(*this).number,&n1.number);
		}
		else
		{
			turnb(&(*this).number,(*this).length);
			turnb(&n1.number,n1.length);
			i=cmpb(&(*this).number,&n1.number,(*this).length,n1.length);
			turnb(&(*this).number,(*this).length);
			turnb(&n1.number,n1.length);
		}
		if (i>0)
			return true;
		else
			return false;
	}
	bool veryLong::operator<=(veryLong n1)
	{
		int i;
		if (!n1.binary)
		{
			i=cmp(&(*this).number,&n1.number);
		}
		else
		{
			turnb(&(*this).number,(*this).length);
			turnb(&n1.number,n1.length);
			i=cmpb(&(*this).number,&n1.number,(*this).length,n1.length);
			turnb(&(*this).number,(*this).length);
			turnb(&n1.number,n1.length);
		}
		if ((i==0) || (i==2))
			return true;
		else
			return false;
	}

	veryLong veryLong::operator=(const char* str)
	{
		int i;
		(*this).number=(unsigned char*)malloc(block);
		for (i=0;i<strlen(str);i++)
			(*this).number[i]=str[i];
		(*this).number[i]='\0';
		(*this).length=strlenn(&(*this).number);
		return *this;
	}

	veryLong::~veryLong()
	{
		free(number);
	}

	veryLong:: veryLong(const veryLong & n)
	{
		int i;
		(*this).binary=n.binary;
		(*this).sign=n.sign;
		(*this).length=n.length;
		(*this).number=(unsigned char*)malloc(block);
		for (i=0;i<n.length;i++)
			(*this).number[i]=n.number[i];
		(*this).number[i]='\0';
	}

