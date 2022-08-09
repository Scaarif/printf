#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <stdarg.h>
#include "main.h"

/**
 * print_octal - converts unsigned int to octal
 * @arg: the integer to turn into octal(base 8)
 * Return: int number of characters written
 */

int print_octal(va_list arg, ...)
{
	int n = 0;
	long num, i = 1, octal = 0;

	num = va_arg(arg, long);
	if (num < 0)
	{
		num = (long)((unsigned int)INT_MAX + num);
	}
	/*make num octal*/
	while (num != 0)
	{
		octal += (num % 8) * i;
		num /= 8;
		i *= 10;
	}
	/*print the number & get no of chars written*/
	/*printf("octal: %ld\n", octal);*/
	_print_num(octal);
	n += _num(octal);/*count no of chars in the int*/
	return (n);
}
/**
 * make_heX - converts unsigned int to hexadecimal
 * @n: the integer to turn into hexadecimal
 * @c: the idea is to hold x or X?
 * Description: handles both cases (lower and upper)
 * Return: int number of characters written
 */

int make_heX(long n, char c)/*to be worked on!*/
{
	long num, quot;
	int i = 1, j, temp;
	char chars[32];/*hold the hex chars*/

	chars[0] = c;
	num = n;
	quot = num;
	while (quot != 0)
	{
		temp = quot % 16;
		/*convert int to char*/
		if (temp < 10)
		{
			temp += 48;
		}
		else
		{
			temp += 55;/*i.e 10 = A = 65 - 10; for lowercase: +87 (97 = a)*/
		}
		chars[i++] = temp;
		quot /= 16;

	}
	for (j = i - 1; j > 0; j--)
		n += write(1, chars + j, 1);
	return (n);
}

/**
 * print_hex - converts unsigned int to hexadecimal
 * @arg: the integer to turn into hexadecimal
 * Return: int number of characters written
 */

int print_hex(va_list arg, ...)
{
	long num, quot;
	int i = 1, j, temp, n = 0;
	char c[32];/*hold the hex chars*/

	num = va_arg(arg, long);
	quot = num;
	while (quot != 0)
	{
		temp = quot % 16;
		/*convert int to char*/
		if (temp < 10)
		{
			temp += 48;
		}
		else
		{
			temp += 87;/*i.e 10 = A = 65 - 10; for lowercase: +87 (97 = a)*/
		}
		c[i++] = temp;
		quot /= 16;

	}
	for (j = i - 1; j > 0; j--)
		n += write(1, c + j, 1);
	return (n);
}

/**
 * print_heX - converts unsigned int to hexadecimal
 * @arg: the integer to turn into hexadecimal
 * Return: int number of characters written
 */

int print_heX(va_list arg, ...)
{
	long num, quot;
	int i = 1, j, temp, n = 0;
	char c[32];/*hold the hex chars*/

	num = va_arg(arg, long);
	quot = num;
	while (quot != 0)
	{
		temp = quot % 16;
		/*convert int to char*/
		if (temp < 10)
		{
			temp += 48;
		}
		else
		{
			temp += 55;/*i.e 10 = A = 65 - 10; for lowercase: +87 (97 = a)*/
		}
		c[i++] = temp;
		quot /= 16;

	}
	for (j = i - 1; j > 0; j--)
		n += write(1, c + j, 1);
	return (n);
}
