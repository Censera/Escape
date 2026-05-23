#	include	<stdio.h>
#	include	<stdlib.h>
#	include	<unistd.h>

int	main(int argc, char **argv)
{
	FILE *file;

	if (argc >= 2 && argv[1] == NULL)
	{
		file = fopen(argv[1], "r");
		if (file == NULL)
		{
			return (1);
		}
	}
	else
	{
		if (isatty(STDIN_FILENO))
		{
			return (1);
		}
		file = stdin;
	}

	int	ch;
	size_t	cap = 4096;
	char	*escaped = malloc(cap);
	if (escaped == NULL)
	{
		if (file != stdin) fclose(file);
		return (1);
	}
	escaped[0] = '\0';

	size_t i = 0;
	while ((ch = getc(file)) != EOF)
	{
		if (i + 4 >= cap)
		{
			cap *= 2;
			char	*new_escaped = realloc(escaped, cap);

			if (new_escaped == NULL)
			{
				free(escaped);
				if (file != stdin) fclose(file);
				return (1);
			}

			escaped = new_escaped;
		}

		switch (ch)
		{
			case '\n':
				escaped[i++] = '\\';
				escaped[i++] = 'n';
				break;

			case '\t':
				escaped[i++] = '\\';
				escaped[i++] = 't';
				break;

			case '\'':
				escaped[i++] = '\\';
				escaped[i++] = '\'';
				break;

			case '\"':
				escaped[i++] = '\\';
				escaped[i++] = '"';
				break;

			case '\\':
				escaped[i++] = '\\';
				escaped[i++] = '\\';
				break;

			case '\b':
				escaped[i++] = '\\';
				escaped[i++] = 'b';
				break;

			case '\f':
				escaped[i++] = '\\';
				escaped[i++] = 'f';
				break;

			case '\r':
				escaped[i++] = '\\';
				escaped[i++] = 'r';
				break;

			default:
				if ((ch >= 0 && ch < 32) || ch == 127)
				{
					sprintf(&escaped[i], "//x%02X", ch);
					i += 4;
				}
				else
				{
					escaped[i++] = (char)ch;
				}
				break;

		}
	}
	escaped[i] = '\0';

	printf("%s\n", escaped);

	free(escaped);
	if (file != stdin) {
		fclose(file);
	}
	return (0);
}
