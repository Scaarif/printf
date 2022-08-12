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
	int n;
	void *value;

	value = va_arg(arg, void *);
	n = write(1, value, 16);
	return (n);
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
	int n, index1 = 0, index2, i;
	char *str, _str[BUFFER];
	char alphabet[52] = {'A', 'B', 'C', 'D', 'E', 'F',
			     'G', 'H', 'I', 'J', 'K', 'L',
			     'M', 'N', 'O', 'P', 'Q', 'R',
			     'S', 'T', 'U', 'V', 'W', 'X',
			     'Y', 'Z', 'a', 'b', 'c', 'd',
			     'e', 'f', 'g', 'h', 'i', 'j',
			     'k', 'l', 'm', 'n', 'o', 'p',
			     'q', 'r', 's', 't', 'u', 'v',
			     'w', 'x', 'y', 'z'};
	char rot13key[52] = {'N', 'O', 'P', 'Q', 'R', 'S',
			     'T', 'U', 'V', 'W', 'X', 'Y',
			     'Z', 'A', 'B', 'C', 'D', 'E',
			     'F', 'G', 'H', 'I', 'J', 'K',
			     'L', 'M', 'n', 'o', 'p', 'q',
			     'r', 's', 't', 'u', 'v', 'w',
			     'x', 'y', 'z', 'a', 'b', 'c',
			     'd', 'e', 'f', 'g', 'h', 'i',
			     'j', 'k', 'l', 'm'};

	str = va_arg(arg, char *);
	/*cpy str just incase its a string literal*/
	for (i = 0; i <= _strlen(str); i++)
		_str[i] = str[i];
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
	n = write(1, _str, _strlen(str));
	return (n);
}
