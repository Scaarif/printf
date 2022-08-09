#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include "main.h"


/**
 * is_specifier - check if % is a format
 * initializer
 * @str: printf's first argument
 * @index: the starting index
 * Return: int 1 if true and -1 otherwise
 */

int is_specifier(const char *str, int index)
{
	int i = index;/*where to start next search for specifier*/

	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			if (str[i + 1] != '%' && str[i - 1] != '%')
				return (i + 1); /*true - return the specifier's index*/
		}
		i++;
	}
	index  = 0;
	return (index);/*false*/
}

/**
 * get_indices - returns an array of format_string
 * indices as they appear in the last argument
 * @str: string argument from which the array is derived
 * Return: a pointer to an array of integer indices
 */
int *get_indices(const char *str)
{
	int i = 0, ids = 0, _is, start = 0, *indices;

	/*find out how many specifiers there are;*/
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			if (str[i + 1] != '%' && str[i - 1] != '%')
				ids++;
		}
		i++;
	}
	printf("no of format strings: %d\n", ids);
	/*allocate memory to the array and initialize*/
	indices = malloc(sizeof(int) * (ids + 1));
	if (indices == NULL)
	{
		/*printf("indices: failed");*/
		exit(99);
	}
	else
	{
		/*printf("indices mem allocated\n");*/
		indices[0] = ids;/*array_size*/
		i = 1;
		while (i <= ids)
		{
			/*i need to call is_specifier ids times*/
			_is = is_specifier(str, start);
			/**
			 * printf("start: %d and _is: %d\n", start, _is);
			 * printf("indices[%d] @ %d is: %c\n", i, _is, str[_is])
			 */
			indices[i] = _is;/*store the index not the char at the index*/
			start = _is + 1;
			i++;
		}
	}
	return (indices);
}

/**
 * print_string - writes a string to stdout, 1
 * @s: the string to write
 * @start: starting index
 * @stop: stopping index
 * @str: buffer
 * Description: start and stop demarcate the start and stop
 * indices when writing to std out
 * Return: int number of bytes written
 */
int print_string(const char *s, int start, int stop, char *str)
{
	int n = 0, len, i = 0, temp_stop;

	/*printf("len: %d\n", len);*/
	/*look for double percent characters*/
	i = start;
	for (; i <= stop; i++)
	{
		if (s[i] == '%' && s[i + 1] == '%')
		{
			temp_stop = i;/*write upto first %*/
			len = (temp_stop - start) + 1;
			n += write(1, s + start, len);
			manage_buffer(s, str, start, stop);
			start = i + 2;/*next write starts at 1 past 2nd %*/
		}
	}
	len = stop - start;
	n += write(1, s + start, len);
	manage_buffer(s, str, start, stop);
	return (n);
}
/**
 * print_str - writes a string to stdout, 1
 * @arg: the string to write
 * Description: writes the string passed as optional arg
 * to printf; requires no demarcation
 * Return: int number of bytes written
 */
int print_str(va_list arg, ...)
{
	va_list ap;
	int n, i = 0;
	char *s, *str;

	s = va_arg(arg, char *);
	n = write(1, s, strlen(s));
	va_start(ap, arg);
	str = va_arg(ap, char *);
	for (; s[i] != '\0'; i++)
		manage_buffer_with_pointers(str, s[i]);
	return (n);
}

/**
 * print_char - writes a char to stdout, 1
 * @arg: the char as next argument to write
 * Return: int number of bytes written
 */
int print_char(va_list arg, ...)
{
	va_list ap;
	int n;
	char s, *str;

	s = va_arg(arg, int);
	n = write(1, &s, 1);
	va_start(ap, arg);
	str = va_arg(ap, char *);
	/**
	 * printf("\nVa_arg_str: ");
	 * for (; i <= str[0]; i++)
	 * printf("%c", *(str + i));
	 * printf("\n");
	 */
	manage_buffer_with_pointers(str, s);
	va_end(ap);
	return (n);
}
