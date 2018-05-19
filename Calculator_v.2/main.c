#include <stdio.h>
#include <stdlib.h>
#include "func.h"
#include "tool.h"
#define SIZE 1000

extern void explore(char[]);
char result[SIZE] = { 0 };
int ERROR;
// ERROR 1 : Bracket error
// ERROR 2 : Can't divide by 0
// ERROR 3 : Operator error
// ERROR 4 : Point error

int main() {
	while (1) {
		char Express[SIZE] = { 0 };

		ERROR = 0;

		puts("忙式式式式式式式式式式式式式忖");
		puts("弛        2016/02/23        弛");
		puts("弛        Made by YG        弛");
		puts("戌式式式式式式式式式式式式式戎");
		printf(">> Type polynomial expression\n");
		gets(Express);
		explore(Express);

		puts("\nANSWER >> ");
		if (!ERROR) printf("%s\n\n", result);
		else {
			if (ERROR == 1) puts("Bracket error\n");
			else if (ERROR == 3) puts("Operator error\n");
			else if (ERROR == 4) puts("Point error\n");
			else puts("Can't divide by 0\n");
		}
		system("pause");
		system("cls");
	}
	return 0;
}

