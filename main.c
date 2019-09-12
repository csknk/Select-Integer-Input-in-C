#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

struct Option {
	int id;
	char *label;

} options[] = {
	{1, "Low"},
	{2, "Medium"},
	{3, "High"}
};

void selectIntegerFromStdin(struct Option *options, int nOptions, int *selection);

int main()
{
	const int nOptions = sizeof(options) / sizeof(struct Option);
	int selection = 0;
	selectIntegerFromStdin(&options[0], nOptions, &selection);
	printf("You selected %d\n", selection);
	return 0;
}

void selectIntegerFromStdin(struct Option *options, int nOptions, int *selection)
{
	// Dynamically build instructions string.
	char *str = "Please enter an integer in the range 1 to "; 
	int numLen = snprintf(NULL, 0, "%d", (int)nOptions);
	char *num = malloc(numLen + 1);
	snprintf(num, numLen + 1, "%d", nOptions);
	char *instructions = malloc(strlen(str) + strlen(num) + 2);
	strcpy(instructions, str);
	strcat(instructions, num);
	strcat(instructions, ".");
	
	printf("%s\n", instructions);
	for (int i = 0; i < nOptions; i++) {
		printf("Select %d for %s\n", options[i].id, options[i].label);
	}

	char *input = NULL, *endptr = NULL;
	size_t len = 0;
	long val;
	while (1) {
		getline(&input, &len, stdin);

		val = strtol(input, &endptr, 10);
		if (endptr == input) {
			fprintf(stderr, "That doesn't contain digits. Try again.\n");
			printf("%s\n", instructions);
			continue;
		}
		if (val < 1 || val > (int)nOptions) {
			fprintf(stderr, "%ld is outside the required range. Try again.\n", val);
			printf("%s\n", instructions);
			continue;
		}

		*selection = (int)val;
		break;
	}
	free(input);
	free(num);
	free(instructions);
}
