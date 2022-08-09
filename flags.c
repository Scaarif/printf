#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include "main.h"


/**
 * is_flag - check if character after % is a format
 * initializer or a flag
 * @arr: format arg of _printf
 * @i: identified possible 'format string' index
 * Return: int 1 if true and -1 otherwise
 */

int is_flag(const char *arr, int i)
{
	/*check if index contains a non-alphabet char, in which case that's a flag*/
	if ((arr[i] < 'a' || arr[i] > 'z')
			&& (arr[i] < 'A' || arr[i] > 'Z'))
		/*printf("indices[%d] is: %c a flag\n", i, arr[i]);*/
		return (i); /*true - return the flag's index*/
	/*printf("NOT a flag!\n");*/
	return (-1);/*false otherwise*/
}

/**
 * get_flags - return index of actual format string
 * @arr: identified 'format strings' array
 * @ids: actual 'format strings' array
 * @fmt: _printf's required argument
 * Return: an array of flag indices
 */

int *get_flags(const char *fmt, int *arr, int *ids)
{
	int i = 1, j = 1, flags = 0, *f_arr, _next;

	/*check the array for flags and append them to the flags array*/
	while (arr[i])
	{
		if (is_flag(fmt, arr[i]) >= 0)
		{
			flags += ids[i] - arr[i];
			/*get other flags before actual specifier*/
		}
		i++;
	}
	/*alloc mem & initialize an array of flags*/
	f_arr = malloc(sizeof(int) * (flags + 1));
	if (f_arr == NULL)
	{
		printf("f_arr failed");
		exit(99);
	}
	/*first value in f_arr = no of flags*/
	f_arr[0] = flags;
	i = 1;
	while (arr[i])
	{
		if (is_flag(fmt, arr[i]) >= 0)
		{
			f_arr[j] = arr[i];/*the index*/
			/*printf("flag[%d] - %c\n", j, fmt[arr[i]]);*/
			j++;
			/*add the other flags before actual f_str*/
			_next = arr[i] + 1;
			for (; _next < ids[i]; _next++, j++)
			{
				f_arr[j] = _next;
				/*printf("flag[%d] - %c\n", j, fmt[_next]);*/
			}
		}
		i++;
	}
	return (f_arr);
}

/**
 * actual_specifier - return index of actual format string
 * @fmt: _printf's required argument
 * @idx: flag's index
 * Return: index of actual specifier
 */

int actual_specifier(const char *fmt, int idx)
{

	/*check for specifier starting at identified flag's index*/
	while (fmt[idx])
	{
		idx++;
		/*check for first alphabet character after flag*/
		if ((fmt[idx] >= 'a' && fmt[idx] <= 'z')
		||
		(fmt[idx] >= 'A' && fmt[idx] <= 'Z'))
		{
				return (idx); /*true - return that first index - that's the f_str*/
		}
	}
	exit(99);
}

/**
 * get_actual_specifiers - return array of actual format strings
 * @arr: identified possible 'format strings' array
 * @fmt: first argument of _printf
 * Return: an array of actual indices
 */

int *get_actual_specifiers(const char *fmt, int *arr)
{
	int i = 1, j = 1, *a_arr;

	/*a_arr will have the same size as arr - in arr[0]*/
	a_arr = malloc(sizeof(int) * arr[0]);
	if (a_arr == NULL)
	{
		printf("a_arr failed");
		exit(99);
	}
	a_arr[0] = arr[0];
	/*else get the actual specifier, check that what we have isn't a flag*/
	while (arr[i])
	{
		if (is_flag(fmt, arr[i]) >= 0)
		{
			a_arr[j] = actual_specifier(fmt, arr[i]);
			/*printf("actual_indices[%d] @ %d is: %c\n", a_arr[j], j, fmt[a_arr[j]]);*/
		}
		else
		{
			a_arr[j] = arr[i];
		}
		j++;
		i++;
	}
	return (a_arr);
}
/**
 * handle_flag - literally
 * @c: flag character
 * @str: buffer
 * Description: format is a string and contains
 * the optional format strings
 * Return: int number of bytes written
 */
int handle_flag(char c, char *str)
{
	int n = 0, num, last_index;
	char filler = '*';

	switch (c)
	{
		case '+':
			n += write(1, &c, 1);
			manage_buffer_with_pointers(str, c);
			break;
		case ' ':
			n += write(1, &c, 1);
			manage_buffer_with_pointers(str, c);
			break;
		case '#':
			n += write(1, &c, 1);
			manage_buffer_with_pointers(str, c);
			break;
		case '.':
			n += write(1, &c, 1);
			manage_buffer_with_pointers(str, c);
			break;
		case '0':
			n += write(1, &c, 1);
			manage_buffer_with_pointers(str, c);
			break;
		default:
			/*an integer for width specification*/
			num = c - '0';
			last_index = str[0];
			if (str[last_index] == '0')
				str[0] = last_index - 1;/*overwrite the appended 0*/
			for (; num > 0; num--)
			{
				n += write(1, &filler, 1);
				manage_buffer_with_pointers(str, filler);
			}
	}
	return (n);
}
