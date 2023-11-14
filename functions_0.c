#include "main.h"

/* PRINT CHARACTER *************************/
/**
 * print_char - Function prints characters
 * @types: Lists of arguments
 * @buffer: array to handle print
 * @flags: Checks for active flags
 * @width: Fetches Width
 * @precision: fetches precision
 * @size: Fetches size
 * Return: Number of chars printed
 */

int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char s = va_arg(types, int);

	return (handle_write_char(s, buffer, flags, width, precision, size));
}
/* PRINT STRINGS *******/
/**
 * print_string - Funtion for printing strings
 * @types: List of arguments
 * @buffer: array to handle prints
 * @flags: Checks for active flags
 * @width: fetches for width.
 * @precision: fetches precision
 * @size: fetches size
 * Return: Number of characters printed
 */

int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int len = 0, s;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = " ";
	}

	while (str[len] != '\0')
		len++;

	if (precision >= 0 && precision < len)
		len = precision;

	if (width > len)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], len);
			for (s = width - len; s > 0; s--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (s = width - len; s > 0; s--)
				write(1, " ", 1);
			write(1, &str[0], len);
			return (width);
		}
	}

	return (write(1, str, len));
}
/* PRINT PERCENT SIGN *******/
/**
 * print_percent - function prints percent sign
 * @types: Lists of arguments
 * @buffer: array to handle prints
 * @flags: Checks for active flags
 * @width: fetches width.
 * @precision: fetches precision
 * @size: fetches size
 * Return: Number of characters printed
 */

int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/* PRINT INTEGERS *******/
/**
 * print_int - function prints Integers
 * @types: Lists of arguments
 * @buffer: array to handle prints
 * @flags: Checks for active flags
 * @width: fetches width.
 * @precision: fetches precision
 * @size: fetches size
 * Return: Number of integer printed
 */

int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int bf = BUFF_SIZE - 2;
	int is_negative = 0;
	long int f = va_arg(types, long int);
	unsigned long int num;

	f = convert_size_number(f, size);

	if (f == 0)
		buffer[bf--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)f;

	if (f < 0)
	{
		num = (unsigned long int)((-1) * f);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[bf--] = (num % 10) + '0';
		num /= 10;
	}

	bf++;

	return (write_number(is_negative, bf, buffer, flags, width, precision, size));
}

/* PRINT BINARY *********/
/**
 * print_binary - Prints an unsigned number in binary
 * @types: Lists of arguments
 * @buffer: array to handle prints
 * @flags: Checks for active flags
 * @width: fetches width.
 * @precision: fetches precision
 * @size: fetches size
 * Return: Number of binary printed
 */

int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int y, x, i, sum;
	unsigned int a[32];
	int cnt;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	y = va_arg(types, unsigned int);
	x = 2147483648; /* (2 ^ 31) */
	a[0] = y / x;
	for (i = 1; i < 32; i++)
	{
		x /= 2;
		a[i] = (y / x) % 2;
	}
	for (i = 0, sum = 0, cnt = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			cnt++;
		}
	}
	return (cnt);
}
