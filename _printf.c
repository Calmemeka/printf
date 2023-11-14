#include "main.h"

/**
 * _printf - Printf main function
 * @format: possible format.
 * Return: Printed characters.
 */

int _printf(const char *format, ...)
{
	int c, printed = 0, printed_chars = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (c = 0; format && format[c] != '\0'; c++)
	{
		if (format[c] != '%')
		{
			buffer[buff_ind++] = format[c];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);

			printed_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			flags = get_flags(format, &c);
			width = get_width(format, &c, list);
			precision = get_precision(format, &c, list);
			size = get_size(format, &c);
			++c;
			printed = handle_print(format, &c, list, buffer,
				flags, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}

	print_buffer(buffer, &buff_ind);

	va_end(list);

	return (printed_chars);
}

/**
 * print_buffer - Function prints the contents of the buffer if exists
 * @buffer: Array of characters
 * @buff_ind: Index at which to add next char, represents the length.
 */

void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}
