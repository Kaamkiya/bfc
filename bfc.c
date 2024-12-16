/* SPDX-License-Identifier: Unlicense */
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
	FILE *fp;

	if (argc < 2) {
		fp = stdin;
	} else {
		fp = fopen(argv[1], "r");
		if (fp == NULL) {
			fputs("Error: Cannot open file.", stderr);
			return 1;
		}
	}

	char code[1048576];
	char c;
	unsigned int i = 0;
	while ((c = fgetc(fp)) != EOF) {
		if (c == '>' ||
			c == '<' ||
			c == '+' ||
			c == '-' ||
			c == '.' ||
			c == ',' ||
			c == '[' ||
			c == ']') {
			code[i] = c;
			i++;
		}
	}
	fclose(fp);

	char program[1048576];
	strcpy(program, "#include <stdio.h>\nint main(){char t[30000]={0};int p=0;");

	for (i = 0; i < strlen(code); i++) {
		char *instruction = NULL;
		switch (code[i]) {
		case '>': instruction = "p++;";            break;
		case '<': instruction = "p--;";            break;
		case '+': instruction = "t[p]++;";         break;
		case '-': instruction = "t[p]--;";         break;
		case '.': instruction = "putchar(t[p]);";  break;
		case ',': instruction = "t[p]=getchar();"; break;
		case '[': instruction = "while(t[p]!=0){"; break;
		case ']': instruction = "}";               break;
		default:  instruction = "";                break;
		}
		strcat(program, instruction);
	}

	strcat(program, "return 0;}");
	puts(program);
	return 0;
}
