#include "main.h"

/* PRINT POINTER *********/
/**
 * print_pointer - function prints the value of a pointer variable
 * @types: Lists of arguments
 * @buffer: array to handle prints
 * @flags: Checks for active flags
 * @width: fetches width.
 * @precision: fetches precision
 * @size: fetches size
 * Return: Number or value printed
 */

int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_c = 0, padding = ' ';
	int ind = BUFF_SIZE - 2, length = 2, padd_st = 1;
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		buffer[ind--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padding = '0';
	if (flags & F_PLUS)
		extra_c = '+', length++;
	else if (flags & F_SPACE)
		extra_c = ' ', length++;

	ind++;

	return (write_pointer(buffer, ind, length,
		width, flags, padding, extra_c, padd_st));
}

/************************* PRINT NON PRINTABLE *************************/
/**
 * print_non_printable - function prints ascii codes in
 * hexadec of non printable chars
 * @types: Lists of arguments
 * @buffer: array to handle prints
 * @flags: Checks for active flags
 * @width: fetches width.
 * @precision: fetches precision
 * @size: fetches size
 * Return: Number of characters printed
 */

int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int c = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[c] != '\0')
	{
		if (is_printable(str[c]))
			buffer[c + offset] = str[c];
		else
			offset += append_hexa_code(str[c], buffer, c + offset);

		c++;
	}

	buffer[c + offset] = '\0';

	return (write(1, buffer, c + offset));
}

/* PRINT REVERSE ********/
/**
 * print_reverse - Prints strings in reverse.
 * @types: Lists of arguments
 * @buffer: array to handle prints
 * @flags: Checks for active flags
 * @width: fetches width.
 * @precision: fetches precision
 * @size: fetches size
 * Return: Number of characters printed
 */

int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int c, cnt = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (c = 0; str[c]; c++)
		;

	for (c = c - 1; c >= 0; c--)
	{
		char z = str[c];

		write(1, &z, 1);
		cnt++;
	}
	return (cnt);
}
/* PRINT A STRING IN ROT13 ********/
/**
 * print_rot13string - Print string in ROT13.
 * @types: Lists of arguments
 * @buffer: array to handle prints
 * @flags: Checks for active flags
 * @width: fetches width.
 * @precision: fetches precision
 * @size: fetches size
 * Return: Number of characters printed
 */

int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char x;
	char *str;
	unsigned int i, j;
	int cnt = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (i = 0; str[i]; i++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[i])
			{
				x = out[j];
				write(1, &x, 1);
				cnt++;
				break;
			}
		}
		if (!in[j])
		{
			x = str[i];
			write(1, &x, 1);
			cnt++;
		}
	}
	return (cnt);
}
