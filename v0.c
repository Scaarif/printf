#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "main.h"

/**
 *_num - returns number of characters in an int
 * @n: the integer
 * Return: int number of characters
 */

int _num(long n)
{
	int num = 1;

	for (; (n / 10) > 0; num++)
	{
		n = n / 10;
	}
	return (num);
}
/**
 * _print_num - prints an int as a character
 * @n: the integer
 * Return: int number of bytes written
 */

void _print_num(long n, ...)
{
	va_list ap;
	char *str;
	int num;

	if ((n / 10) > 0)
	{
		_print_num(n / 10);
	}
	num = '0' + (n % 10);
	write(1, &num, 1);
	va_start(ap, n);
	str = va_arg(ap, char *);
	/*printf("_num:%i - %c\n", _num, _num);*/
	manage_buffer_with_pointers(str, num);
	va_end(ap);

}

/**
 * print_int - writes a int to stdout, 1
 * @arg: int to write - an optional argument
 * Return: int number of bytes written
 */
int print_int(va_list arg, ...)
{
	va_list ap;
	int n = 0, num, last_index, num_len;
	char neg, *str;

	/*think I need to int to convert to char (ascii)?*/
	num = va_arg(arg, int);
	va_start(ap, arg);
	str = va_arg(ap, char *);
	/*check if num is negative*/
	if (num < 0)
	{
		neg = '-';
		n += write(1, &neg, 1);
		/*check last char in str, if + replace it;*/
		last_index = str[0];
		/*printf("last_index: %d\n", last_index);*/
		if (str[last_index] == '+' || str[last_index] == ' ' ||
		str[last_index] == '#' || str[last_index] == '0')
		{
			str[0] -= 1;
			/*printf("Removed a + or [space]!\n");*/
		}
		manage_buffer_with_pointers(str, neg);
		last_index = str[0];
		/*printf("updated_last_index: %d with: %c\n", str[0], str[last_index]);*/
		num *= -1;
	}
	/*printf("num: %d\n", num);*/
	num_len = _num((long)num);
	/*if extra stars, overwrite*/
	_print_num((long)num, str);
	n += num_len;
	return (n);
}


/**
 * print_binary - converts unsigned int to binary
 * @arg: the integer to turn into binary
 * Return: int number of characters written
 */

int print_binary(va_list arg, ...)
{
	int num, n = 0, i, k;
	char c;

	num = va_arg(arg, int);
	/*assuming size of 7 bits*/
	for (i = 7; i >= 0; i--)
	{
		k = num >> i; /*right shift*/
		if (k & 1)
		{
			c = '1';
			n += write(1, &c, 1);
		}
		else
		{
			c = '0';
			n += write(1, &c, 1);
		}
	}
	return (n);
}

/**
 * make_unsigned - converts unsigned int to unsigned
 * @arg: the integer to turn into binary
 * Return: int number of characters written
 */

int make_unsigned(va_list arg, ...)
{
	int n = 0;
	long num;

	num = va_arg(arg, long);
	if (num < 0)
		num = 4294967296 + num;
	/*print the number & get no of chars written*/
	_print_num(num);
	n += _num(num);/*count no of chars in the int*/
	return (n);
}
