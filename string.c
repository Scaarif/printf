#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include "main.h"

/**
 * print_Str - writes a string to stdout, 1
 * @arg: the string to write
 * Description: writes the string passed as optional arg
 * to printf and handles non printable characters by
 * printing '\x' followed by their ascii code value in hex
 * (Uppercase - always 2 characters)
 * Return: int number of bytes written
 */
int print_Str(va_list arg, ...)
{
	int n = 0, i = 0;
	char *s, *_char = "\\x";
	int num, quot, k = 1, j, temp;
	char hold = '0', c[32];

	s = va_arg(arg, char *);
	while (s[i] != '\0')
	{
		if ((s[i] > 0 && s[i] < 32) || s[i] >= 127)
		{
			/*printf("unprintable char: %c\n", s[i]);*/
			n += write(1, _char, _strlen(_char));
			/*get & print the ascii code for the value*/
			num = s[i];
			if (num < 16)
				n += write(1, &hold, 1);
			quot = num;
			while (quot != 0)
			{
				temp = quot % 16;
				/*convert int to char*/
				if (temp < 10)
					temp += 48;
				else
					temp += 55;
				c[k++] = temp;
				quot /= 16;
			}
			for (j = k - 1; j > 0; j--)
				n += write(1, c + j, 1);
		}
		else
		{
			n += write(1, s + i, 1);
		}
		i++;
	}
	return (n);
}

/**
 * print_pointer - prints the address of arg
 * @arg: the variable whose address to print
 * Return: int number of characters written (8)?
 */

int print_pointer(va_list arg, ...)
{
	/*char extra_c = 0, padd = ' ';*/
	int ind = BUFFER - 2, length = 2; /* length=2, for '0x': OK */
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef", buffer[BUFFER];
	void *addrs = va_arg(arg, void *);/*OK*/

	/*UNUSED(width);*/
	/*UNUSED(size);*/
	if (addrs == NULL)
		return (write(1, "(nil)", 5));/*OK*/
	buffer[BUFFER - 1] = '\0';
	/*UNUSED(precision);*/
	num_addrs = (unsigned long)addrs;/*OK*/
	while (num_addrs > 0)
	{
		buffer[ind--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		length++;
	}
	/*if ((flags & F_ZERO) && !(flags & F_MINUS))*/
		/*padd = '0';*/
	/*if (flags & F_PLUS)*/
		/*extra_c = '+', length++;*/
	/*else if (flags & F_SPACE)*/
		/*extra_c = ' ', length++;*/
	ind++;
	/*return (write(1, &buffer[i], BUFF_SIZE - i - 1));*/
	/**
	 * return (write_pointer(buffer, ind, length,
	 * width, flags, padd, extra_c, padd_start));
	 */
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	return (write(1, &buffer[ind], length));
}

/**
 * rev_str - reverses a string
 * @s: string
 * Return: reversed string
 */

char *rev_str(char *s)
{
	int i, c, l;
	char hold, *str;

	for (i = 0; s[i] != '\0'; i++)
		;

	l = i;
	str = malloc(sizeof(char) * l);
	if (str == NULL)
		exit(99);
	for (i = 0; i < l; i++)
		str[i] = s[i];
	for (i--, c = 0; c < l / 2; i--, c++)
	{
		hold = str[c];
		str[c] = str[i];
		str[i] = hold;
	}
	return (str);
}

/**
 * print_reverse_string - prints a string in reverse
 * @arg: the variable whose address to print
 * Return: int number of characters written (8)?
 */

int print_reverse_string(va_list arg, ...)
{
	va_list ap;
	int n = 0, i = 0;
	char *str, *buff_str;

	str = va_arg(arg, char *);
	str = rev_str(str);/*reversed string*/
	n += write(1, str, _strlen(str));
	va_start(ap, arg);/*this'll give the buffer str*/
	buff_str = va_arg(ap, char *);
	va_end(ap);
	/*what i want is to call print_str with the reversed-string*/
	for (i = 0; str[i] != '\0'; i++)
		manage_buffer_with_pointers(buff_str, str[i]);
	return (n);
}

/**
 * rot13 - encodes a string with rot13
 * Description: rotate each letter to the 13th letter from it
 * @arg: the string
 * Return: string
 */
int rot13(va_list arg, ...)
{
	int n;
	int index1 = 0, index2, i;
	char *str;
	char _str[BUFFER];
	char alphabet[52] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char rot13key[52] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(arg, char *);
	/*copy str to _str incase its a literal string -incase we cant modify it*/
	for (i = 0; i <= _strlen(str); i++)
		_str[i] = str[i];/*copy including null character*/
	while (_str[index1])
	{
		for (index2 = 0; index2 < 52; index2++)
		{
			if (_str[index1] == alphabet[index2])
			{
				_str[index1] = rot13key[index2];
				break;
			}
		}
		index1++;
	}
	/*printf("rotated str: %s\n", _str);*/
	n = write(1, _str, _strlen(str));
	return (n);
}
