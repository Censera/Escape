#	include	<stdio.h>
#	include	<stdlib.h>
#	include	<unistd.h>
#	include	<string.h>
#	include	<errno.h>

#	define	RED	"\x1b[31m"
#	define	MAGENTA	"\x1b[35m"
#	define	RESET	"\x1b[m"

int	main(int argc, char **argv)
{
	FILE *file;

	if (argc >= 2 && argv[1] != NULL)
	{
		file = fopen(argv[1], "r");
		if (file == NULL)
		{
			fprintf(stderr, "\n[%sERROR%s]\tCannot open %s: %s\n", RED, RESET, argv[1], strerror(errno));

			if (errno == ENOENT)
			{
				fprintf(stderr, "[%sNOTE%s]\tCouldn't find the file\n\n", MAGENTA, RESET);
			}
			else if (errno == EACCES)
			{
				fprintf(stderr, "[%sNOTE%s]\tYou don't have permission to read this file\n\n", MAGENTA, RESET);
			}
			return (1);
		}
	}
	else
	{
		if (isatty(STDIN_FILENO))
		{
			fprintf(stderr, "\n[%sERROR%s]\tNo file argument was provided\n\n", RED, RESET);
			return (1);
		}
		file = stdin;
	}

	int	ch;
	while ((ch = getc(file)) != EOF)
	{

		switch (ch)
		{
			case '\n':	putchar('\\'); putchar('n'); break;
			case '\t':	putchar('\\'); putchar('t'); break;
			case '\b':	putchar('\\'); putchar('b'); break;
			case '\r':	putchar('\\'); putchar('r'); break;
			case '\f':	putchar('\\'); putchar('f'); break;
			case '\'':	putchar('\\'); putchar('\''); break;
			case '\"':	putchar('\\'); putchar('"'); break;
			case '\\':	putchar('\\'); putchar('\\'); break;
			default:	putchar(ch); break;
		}
	}

	putchar('\n');

	if (file != stdin) fclose(file);
	return (0);
}
