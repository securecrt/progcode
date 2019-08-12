#include <stdio.h>
int fac(int x) 
{
	int f;
 
	if(x==0 || x==1)
		f=1;
	else
		f=fac(x-1)*x;
 
	return f;
}

int main(int argc, char *argv[])
{

    int n = 12;

    printf("%d! = %d\r\n", n, fac(n));

}
