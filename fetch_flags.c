#include "main.h"

/**
 * get_flags - Evaluates for active flags
 * @format: Formatted string in which to print arguments
 * @i: receives a parameter.
 * Return: Flags:
 */

int get_flags(const char *format, int *i)
{
	int d, current_i;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (current_i = *i + 1; format[current_i] != '\0'; current_i++)
	{
		for (d = 0; FLAGS_CH[d] != '\0'; d++)
			if (format[current_i] == FLAGS_CH[d])
			{
				flags |= FLAGS_ARR[d];
				break;
			}

		if (FLAGS_CH[d] == 0)
			break;
	}

	*i = current_i - 1;

	return (flags);
}
