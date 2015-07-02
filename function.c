#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define block 200

int readd(unsigned char **number,char *file,unsigned char *sign)
{
    unsigned char Char;
    FILE *inputFile=fopen(file,"r");
    int i = 0;
    int k = 1;
	(*number) = (unsigned char *)malloc(block);
	fscanf(inputFile,"%c",&Char);
	if (Char == '-')
		(*sign)='-';
	else
	{
		(*sign)='+';
		fseek(inputFile,0,SEEK_SET);
	}
    while (fscanf(inputFile,"%c",&Char) > 0)
    {
          if (i == block*k-5)//200*1-5
          {
            k++;
            (*number) = (unsigned char *)realloc((*number),block*k*sizeof(char));
          }
          if ((Char <48) || (Char > 57))
              break;
          (*number)[i] = Char;
          i++;
    }
    (*number)[i]='\0';
    fclose(inputFile);
    return i;
}

int readb(unsigned char **number,char *file)
{
    FILE *inputFile=fopen(file,"rb");
    int i = 0;
    int k = 1;
	(*number) = (unsigned char *)malloc(block);
    while (fread(&(*number)[i],1,1,inputFile) > 0)
    {
        if (i == block*k-5)
        {
            k++;
            (*number) = (unsigned char *)realloc((*number),block*k*sizeof(char));
        }
        i++;
    }
    fclose(inputFile);
    return i;
}

int cmp(unsigned char **numberOne,unsigned char **numberTwo) //1 - ïåðâîå ÷èñëî áîëüøå, 0 - âòîðîå ÷èñëî áîëüøå èëè ðàâíû
{
	int i;
	if (strlen((*numberOne)) > strlen ((*numberTwo)))
		return 1;
	if (strlen((*numberOne)) < strlen ((*numberTwo)))
		return 0;
	for(i=0;i<strlen((*numberOne));i++)
	{
		if ((*numberOne)[i] > (*numberTwo)[i])
			return 1;
		if ((*numberOne)[i] < (*numberTwo)[i])
			return 0;
	}
	return 2;	
}

int cmpb(unsigned char **numberOne,unsigned char **numberTwo,int lengthFirst,int lengthSecond)
{
	int i;
	if (lengthFirst > lengthSecond)
		return 1;
	if (lengthFirst < lengthSecond)
		return 0;
	for(i=0;i<lengthFirst;i++)
	{
		if ((*numberOne)[i] > (*numberTwo)[i])
			return 1;
		if ((*numberOne)[i] < (*numberTwo)[i])
			return 0;
	}
	return 2;
}

int turn(unsigned char **number)
{
	char Char;
	int it,len=strlen((*number))-1;
	for (it=0;it<=len/2;it++)
		{
			Char = (*number)[it];
			(*number)[it] = (*number)[len-it];
			(*number)[len-it] = Char;
		}
	return 0;
}

int turnb(unsigned char **number,int length)
{
	char Char;
	int it,len=length-1;
	for (it=0;it<=len/2;it++)
		{
			Char = (*number)[it];
			(*number)[it] = (*number)[len-it];
			(*number)[len-it] = Char;
		}
	return 0;
}

unsigned char *summ(unsigned char **numberOne,unsigned char **numberTwo)
{
    unsigned char *result;
    int temp,i,carry = 0;
    int k = 1;
    result = (unsigned char*) malloc(block*sizeof(char));
    i=0;
    while(1)
    {
        if ((*numberOne)[i] == '\0')
        {
            temp=1;
            break;
        }
        if ((*numberTwo)[i] == '\0')
        {
            temp=2;
            break;
        }
        temp = (*numberOne)[i] + (*numberTwo)[i]-96;
        result[i] = (temp+carry) % 10+48;
        carry = (temp+carry) / 10;
        i++;
        if (i == block*k-5)
        {
          k++;
          result = (unsigned char *)realloc(result,block*k*sizeof(char));
        }
    }
    if (temp == 1)
        while(1)
        {
            if ((*numberTwo)[i] == '\0')
            {
                break;
            }
            result[i] = ((*numberTwo)[i]+carry-48) % 10 + 48;
            carry = ((*numberTwo)[i]+carry-48) / 10;
            i++;
            if (i == block*k-5)
            {
              k++;
              result = (unsigned char *)realloc(result,block*k*sizeof(char));
            }
        }
    else
        while(1)
        {
            if ((*numberOne)[i] == '\0')
            {
                break;
            }
            result[i] = ((*numberOne)[i]+carry-48) % 10 + 48;
            carry = ((*numberOne)[i]+carry-48) / 10;
            i++;
            if (i == block*k-5)
            {
              k++;
              result = (unsigned char *)realloc(result,block*k*sizeof(char));
            }
        }
    if (carry != 0)
    {
        result[i]=carry+48;
        result[i+1]='\0';
    }
    else
        result[i]='\0';
    return result;
}


unsigned char *summb(unsigned char **numberOne,unsigned char **numberTwo,int lengthFirst,int lengthSecond,int *lengthSumm)
{
    unsigned char *result;
    int temp,i,carry = 0;
    int k = 1;
    result = (unsigned char*) malloc(block*sizeof(char));
    i=0;
    while(1)
    {
        if (i == lengthFirst)
        {
            temp=1;
            break;
        }
        if (i == lengthSecond)
        {
            temp=2;
            break;
        }
        temp = (*numberOne)[i] + (*numberTwo)[i];
        result[i] = (temp+carry) % 256;
        carry = (temp+carry)/256;
        i++;
        if (i == block*k-5)
        {
          k++;
          result = (unsigned char *)realloc(result,block*k*sizeof(char));
        }
    }
    if (temp == 1)
        while(1)
        {
            if (i == lengthSecond)
            {
                break;
            }
            result[i] = ((*numberTwo)[i]+carry) % 256;
            carry = ((*numberTwo)[i]+carry) / 256;
            i++;
            if (i == block*k-5)
            {
              k++;
              result = (unsigned char *)realloc(result,block*k*sizeof(char));
            }
        }
    else
        while(1)
        {
            if (i == lengthFirst)
            {
                break;
            }
            result[i] = ((*numberOne)[i]+carry) % 256;
            carry = ((*numberOne)[i]+carry) / 256;
            i++;
            if (i == block*k-5)
            {
              k++;
              result = (unsigned char *)realloc(result,block*k*sizeof(char));
            }
        }
    if (carry != 0)
    {
        result[i]=carry;
        *lengthSumm=i+1;
    }
    else
    {
        *lengthSumm=i;
    }

    return result;
}

unsigned char *sub(unsigned char **numberOne,unsigned char **numberTwo)
{
    unsigned char *result;
    int i = 0, carry = 0;
    result = (unsigned char*) malloc(strlen(*numberOne)+5);
    while(1)
    {
        if((*numberTwo)[i] == '\0')
        {
            break;
        }
        if (((*numberOne)[i] - carry) >= (*numberTwo)[i])
        {
            result[i] = (*numberOne)[i]-carry-(*numberTwo)[i] +48;
            carry = 0;
        }
        else
        {
            result[i] = (*numberOne)[i]-carry-(*numberTwo)[i] +58;
            carry = 1;
        }
        i++;
    }
    while(1)
    {
        if((*numberOne)[i] == '\0')
        {
            break;
        }
        if (((*numberOne)[i] - carry) >= 48)
        {
            result[i] = (*numberOne)[i]-carry;
            carry = 0;
        }
        else
        {
            result[i] = (*numberOne)[i]-carry+10;
            carry = 1;
        }
        i++;
    }
    for (i=i-1;i>0;i--)
        if (result[i] != '0')
            break;
    result[i+1]='\0';
    return result;
}

unsigned char *subb(unsigned char **numberOne,unsigned char **numberTwo,int lengthFirst,int lengthSecond,int *lengthSumm)
{
    unsigned char *result;
    int i = 0, carry = 0,temp1, temp2;
    result = (unsigned char*) malloc(lengthFirst+5);
    while(1)
    {
        if(i == lengthSecond)
        {
            break;
        }
        temp1 = (*numberOne)[i] - carry+500;
        temp2 = (*numberTwo)[i]+500;
        if (temp1 >= temp2)
        {
            result[i] = (*numberOne)[i]-carry-(*numberTwo)[i];
            carry = 0;
        }
        else
        {
            result[i] = (*numberOne)[i]-carry-(*numberTwo)[i];
            carry = 1;
        }
        i++;
    }
    while(1)
    {
        if(i == lengthFirst)
        {
            break;
        }
        temp1 = (*numberOne)[i] - carry+500;
        temp2 = 500;
        if (temp1 >= temp2)
        {
            result[i] = (*numberOne)[i]-carry;
            carry = 0;
        }
        else
        {
            result[i] = (*numberOne)[i]-carry;
            carry = 1;
        }
        i++;
    }
    //for (i=i-1;i>0;i--)
       // if (result[i] != 0)
         //   break;
    *lengthSumm = i+1;
    return result;
}

unsigned char *mul(unsigned char **numberOne,unsigned char **numberTwo)
{
    unsigned char *result,*help,*del;
    int i,j,carry,temp;
    result = (unsigned char*)malloc(strlen((*numberOne))*strlen((*numberTwo))*sizeof(char)+5);
	for (i=0;i<strlen((*numberOne))*strlen((*numberTwo))+5;i++)
		result[i]='0';
	i=0;
    help = (unsigned char*)malloc(strlen((*numberOne))*strlen((*numberTwo))+5);
    while (1)
    {
        if ((*numberTwo)[i] == '\0')
            break;
        for (j=0;j<i;j++)
            help[j]='0';
        j=0;carry=0;
        while(1)
        {
            if ((*numberOne)[j] == '\0')
                break;
            temp = ((*numberTwo)[i]-48)*((*numberOne)[j]-48);
            help[i+j] = (temp+carry)%10+48;
            carry = (temp+carry) / 10;
            j++;
        }
		if (carry != 0)
		{
			help[i+j] = carry+48;
			help[i+j+1]='\0';
		}
		else
			help[i+j] = '\0';
		if (i != 0)
		{
			del=result;
			result = summ(&result,&help);
			free(del);
		}
		else
			strncpy(result,help,strlen(help)+1);
        i++;
    }
	free(help);
    return result;
}

unsigned char *mulb(unsigned char **numberOne,unsigned char **numberTwo,int lengthFirst,int lengthSecond,int *lengthSumm)
{
    unsigned char *result,*help,*helpresult;
    int i,j,carry,temp,resultlength,it;
    result = (unsigned char*)malloc(lengthFirst*lengthSecond+5);
    for (i=0;i<lengthFirst*lengthSecond+5;i++)
        result[i]=0;
    i=0;
    help = (unsigned char*)malloc(lengthFirst*lengthSecond+5);
    while (1)
    {
        if (i == lengthSecond)
            break;
        for (j=0;j<i;j++)
            help[j]=0;
        j=0;carry=0;
        while(1)
        {
            if (j == lengthFirst)
                break;
            temp = (*numberTwo)[i]*(*numberOne)[j];
            help[i+j] = (temp+carry)%256;
            carry = (temp+carry)/256;
            j++;
        }
        if (carry != 0)
		{
            help[i+j] = carry;
			if (i != 0)
			{
				helpresult = summb(&result,&help,resultlength,i+j+1,&resultlength);
				free(result);
				result=helpresult;
			}
			else
			{
				for (it=0;it<i+j+1;it++)
					result[it]=help[it];;
				resultlength=i+j+1;
			}
		}
		else
		{
			if (i != 0)
			{
				helpresult = summb(&result,&help,resultlength,i+j,&resultlength);
				free(result);
				result=helpresult;
			}
			else
			{
				for (it=0;it<i+j;it++)
					result[it]=help[it];;
				resultlength=i+j;
			}
		}
        i++;
    }
    *lengthSumm = resultlength;
    return result;
}

unsigned char *divv(unsigned char **numberOne,unsigned char **numberTwo,unsigned char **remainder)
{
	int i,j,k,q;
	unsigned char *dividend,*divisor,*answer;
	dividend = (unsigned char*)malloc(2*strlen((*numberOne)));
	divisor = (unsigned char*)malloc(2*strlen((*numberTwo)));
	answer = (unsigned char*)malloc(2*strlen((*numberOne)));
	q=0;
	i=0;j=0;
	while(1)
	{
		if ((*numberOne)[i]=='\0')
			break;
		if ((j != 0) || ((*numberOne)[i] != '0'))
		{
			dividend[j]=(*numberOne)[i];
			dividend[j+1]='\0';
		}
		else
			j--;
		if (cmp(&dividend,&(*numberTwo)) > 0)
		{
			for (k=0;k<=strlen((*numberTwo));k++)
				divisor[k]=(*numberTwo)[k];
			k=1;
			while(1)
			{
				if (cmp(&divisor,&dividend) > 0)
				{
					if (strcmp(divisor,dividend) != 0)
					{
					if (strlen(divisor) != 1)
						turn(&divisor);
					if ((strlen(*numberTwo)) != 1)
						turn(&(*numberTwo));
					divisor = sub(&divisor,&(*numberTwo));
					if (strlen(divisor) != 1)
						turn(&divisor);
					if ((strlen(*numberTwo)) != 1)
						turn(&(*numberTwo));
					k--;
					}
					answer[q]=k+48;
					q++;
					break;
				}
				else
				{
					if (strlen(divisor) != 1)
						turn(&divisor);
					if ((strlen(*numberTwo)) != 1)
						turn(&(*numberTwo));
					divisor=summ(&divisor,&(*numberTwo));
					if (strlen(divisor) != 1)
						turn(&divisor);
					if ((strlen(*numberTwo)) != 1)
						turn(&(*numberTwo));
					k++;
				}
			}
			if (strlen(dividend) != 1)
				turn(&dividend);
			if (strlen(divisor) != 1)
				turn(&divisor);
			dividend = sub(&dividend,&divisor);
			if (strlen(dividend) != 1)
				turn(&dividend);
			if (strlen(divisor) != 1)
				turn(&divisor);
			j=strlen(dividend);
			if ((strlen(dividend) == 1) && (dividend[0]=='0'))
				j=0;
			i++;
		}
		else
		{
			if (q != 0)
			{
				answer[q]='0';
				q++;
			}
			j++;
			i++;
		}

	}
	if (q != 0)
		answer[q]='\0';
	else
	{
		answer[0]='0';
		answer[1]='\0';
	}
	if (j != 0)
		(*remainder)=dividend;
	else
	{
		(*remainder)=dividend;
		(*remainder)[1]='\0';
	}

	return answer;
}

unsigned char *divvb(unsigned char **numberOne,unsigned char **numberTwo,int lengthFirst,int lengthSecond,int *lengthSumm,unsigned char **remainder,int *lengthOst)
{
	int i,j,k,q,lengthdivisor,c,z=0;
	unsigned char *dividend,*divisor,*answer,*helpdivisor;
	dividend = (unsigned char*)malloc(lengthFirst);
	divisor = (unsigned char*)malloc(lengthSecond+lengthSecond/2);
	answer = (unsigned char*)malloc(lengthFirst);
	q=0;
	i=0;j=0;
	while(1)
	{
	        if ((*numberTwo)[i] == 0)
	        {
	            answer[i]=0;
	            z++;
	            i++;
	        }
	        else break;
	}
	i=0;
	while(1)
	{
	        if ((*numberOne)[i] == 0)
	        {
	            answer[i]=0;
	            z++;
	            i++;
	        }
	        else
	        {
	           answer[i]=0;
	            z++;
	           break;
	        }
	 }
	 q=z;
	while(1)
	{
		if (i == lengthFirst)
			break;
		if ((j != 0) || ((*numberOne)[i] != 0))
			dividend[j]=(*numberOne)[i];
		else
			j--;
		j++;
		if (cmpb(&dividend,&(*numberTwo),j,lengthSecond) > 0)
		{
			for (k=0;k<lengthSecond;k++)
				divisor[k]=(*numberTwo)[k];
			lengthdivisor=k;
			k=1;
			if (lengthSecond != 1)
				turnb(&(*numberTwo),lengthSecond);
			while(1)
			{
				c=cmpb(&divisor,&dividend,lengthdivisor,j);
				if (c >0)
				{
					if (c == 1)
					{
						if (lengthdivisor != 1)
							turnb(&divisor,lengthdivisor);
						//if (lengthSecond != 1)
							//turnb(&(*numberTwo),lengthSecond);
						helpdivisor = subb(&divisor,&(*numberTwo),lengthdivisor,lengthSecond,&lengthdivisor);
						free(divisor);
						divisor=helpdivisor;
						if (lengthdivisor != 1)
							turnb(&divisor,lengthdivisor);
						//if (lengthSecond != 1)
							//turnb(&(*numberTwo),lengthSecond);
						k--;
					}
					answer[q]=k;
					q++;
					break;
				}
				else
				{
					if (lengthdivisor != 1)
						turnb(&divisor,lengthdivisor);
					//if (lengthSecond != 1)
						//turnb(&(*numberTwo),lengthSecond);
					helpdivisor=summb(&divisor,&(*numberTwo),lengthdivisor,lengthSecond,&lengthdivisor);
					free(divisor);
					divisor=helpdivisor;
					if (lengthdivisor != 1)
						turnb(&divisor,lengthdivisor);
					//if (lengthSecond != 1)
						//turnb(&(*numberTwo),lengthSecond);
					k++;
				}
			}
			if (lengthSecond != 1)
				turnb(&(*numberTwo),lengthSecond);
			if (j != 1)
				turnb(&dividend,j);
			if (lengthdivisor != 1)
				turnb(&divisor,lengthdivisor);
			dividend = subb(&dividend,&divisor,j,lengthdivisor,&j);
			if (j != 1)
				turnb(&dividend,j);
			if (lengthdivisor != 1)
				turnb(&divisor,lengthdivisor);;
			if ((j == 1) && (dividend[0]==0))
				j=0;
			i++;
		}
		else
		{
			if (q != 0)
			{
				answer[q]=0;
				q++;
			}
			i++;
		}

	}
	if (q == 0)
	{
		answer[0]='0';
		q++;
	}
	*lengthSumm=q;
	if (j != 0)
	{
		(*remainder)=dividend;
		*lengthOst=j;
	}
	else
	{
		(*remainder)=dividend;
		*lengthOst=1;
	}
	return answer;
}

unsigned char *degree(unsigned char **numberOne,unsigned char **numberTwo,unsigned char *sign)
{
	int i,flag;
	unsigned  char *firstNumber,*st,*incr;
	firstNumber = (unsigned char*)malloc(strlen((*numberOne)+2));
	st = (unsigned char*)malloc(block);
	incr = (unsigned char*)malloc(4);
	st[0]='0';
	st[1]='\0';
	incr[0]='1';
	incr[1]='\0';
	if ((*sign)=='+')
		flag=0;
	else
		flag=1;
	strcpy(firstNumber,(*numberOne));
	while(1)
	{
		st = summ(&st,&incr);
		if (strcmp(st,(*numberTwo)) == 0)
			break;
		if (flag==1)
			if ((*sign)=='+')
				(*sign)='-';
			else
				(*sign)='+';
		firstNumber = mul(&(*numberOne),&firstNumber);
	}
	return firstNumber;
}

unsigned char *degreeb(unsigned char **numberOne,unsigned char **numberTwo,int lengthFirst,int lengthSecond,int *lengthSumm)
{
	int i,length,lengthSt;
	unsigned  char *firstNumber,*st,*incr;
	firstNumber = (unsigned char*)malloc(lengthFirst+2);
	st = (unsigned char*)malloc(block);
	incr = (unsigned char*)malloc(4);
	st[0]=1;
	incr[0]=1;
	lengthSt=1;
	for (i=0;i<lengthFirst;i++)
		firstNumber[i]=(*numberOne)[i];
	length=lengthFirst;
	while(1)
	{
		if (cmpb(&st,&(*numberTwo),lengthSt,lengthSecond) == 2)
			break;
		firstNumber = mulb(&firstNumber,&(*numberOne),length,lengthFirst,&length);
		st=summb(&st,&incr,lengthSt,1,&lengthSt);
	}
	*lengthSumm=length;
	return firstNumber;
}
