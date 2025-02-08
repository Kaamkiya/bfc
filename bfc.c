/* SPDX-License-Identifier: Unlicense */
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
	FILE *fp = stdin;

	if (argc >= 2) {
		fp = fopen(argv[1], "r");
		if (fp == NULL) {
			fputs("Error: Cannot open file.", stderr);
			return 1;
		}
	}

	char c;
	char program[1048576];
	strcpy(program, "#include <stdio.h>\nint main(){char t[30000]={0};int p=0;");
	while ((c = fgetc(fp)) != EOF) {
		char *instruction = NULL;
		switch (c) {
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
	fclose(fp);

	strcat(program, "return 0;}");
	puts(program);
	return 0;
}
