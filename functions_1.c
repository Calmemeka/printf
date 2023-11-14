#include "main.h"

/* PRINT UNSIGNED NUMBER *******/
/**
 * print_unsigned - functions prints unsigned numbers
 * @types: Lists of arguments
 * @buffer: array to handle print
 * @flags: Checks active flags
 * @width: get width
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of characters printed.
 */

int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int bf = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[bf--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[bf--] = (num % 10) + '0';
		num /= 10;
	}

	bf++;

	return (write_unsgnd(0, bf, buffer, flags, width, precision, size));
}

/* PRINT UNSIGNED NUMBER IN OCTAL ********/
/**
 * print_octal - Functions prints unsigned num in octal.
 * @types: Lists of arguments
 * @buffer: array to handle prints
 * @flags: Checks for active flags
 * @width: fetches width
 * @precision: fetches precision
 * @size: Fetches size
 * Return: Number of characters printed
 */

int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int bf = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_n = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[bf--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[bf--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && init_n != 0)
		buffer[bf--] = '0';

	bf++;

	return (write_unsgnd(0, bf, buffer, flags, width, precision, size));
}

/* PRINT UNSIGNED NUMBER IN HEXADECIMAL *******/
/**
 * print_hexadecimal - Function prints unsigned num in hexadec
 * @types: Lists of arguments
 * @buffer: array to handle prints
 * @flags: Checks active flags
 * @width: fetches width
 * @precision: fetches precision
 * @size: Fetches size
 * Return: Number of characters printed
 */

int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/* PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL ******/
/**
 * print_hexa_upper - Function prints unsigned num in upper hexadec
 * @types: Lists of arguments
 * @buffer: array to handle prints
 * @flags: Checks active flags
 * @width: Fetches width
 * @precision: Fetches precision
 * @size: Fetchws size
 * Return: Number of characters printed
 */

int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}

/* PRINT HEX NUMBER IN LOWER / UPPER **************/
/**
 * print_hexa - Prints hexadec num in lower or upper
 * @types: Lists of arguments
 * @map_to: Array of values to map the number to
 * @buffer: array to handle prints
 * @flags: Checks active flags
 * @flag_ch: Checks active flags
 * @width: fetch width
 * @precision: fetch precision
 * @size: Fetch Size
 * Return: Number of chars printed
 */

int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int bf = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_n = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[bf--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[bf--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_n != 0)
	{
		buffer[bf--] = flag_ch;
		buffer[bf--] = '0';
	}

	bf++;

	return (write_unsgnd(0, bf, buffer, flags, width, precision, size));
}
