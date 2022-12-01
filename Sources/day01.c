#include "utils.h"

int main(int argc, char **args)
{
	char puzzle[BUFSIZE];
	if (ReadPuzzleInput("input01", &puzzle)) {
		printf("%s",puzzle);
	}
}