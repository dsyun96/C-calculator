#include <string.h>
#define SIZE 1000
#pragma warning(disable: 4996)
#pragma warning(disable: 4018)

extern void add(char[], char[]), sub(char[], char[]);
extern void mul(char[], char[]), DIV(char[], char[]);
extern char result[SIZE];
extern int ERROR;

void swap(char arr1[], char arr2[])
{
	for (int i = 0; arr1[i] != 0 || arr2[i] != 0; i++) {
		if (arr1[i] != arr2[i]) {
			arr1[i] ^= arr2[i];
			arr2[i] ^= arr1[i];
			arr1[i] ^= arr2[i];
		}
	}
}
void pushing(char arr[], int n)
{
	for (int i = strlen(arr); i > n; i--) arr[i] = arr[i - 1];
	arr[n] = '0';
}
void pulling(char arr[], int n)
{
	for (int i = n; i < strlen(arr); i++) arr[i] = arr[i + 1];
}
void clean(char arr[]) {
	char *p = NULL;
	p = arr;
	while (*p == '0' && *(p + 1) != '.') pulling(arr, 0);
	strrev(arr);
	while (*p == '0' && strchr(arr, '.') || *p == '.') pulling(arr, 0);
	strrev(arr);
	if (*p == 0) *p = '0';
	if (*p == '.') pushing(p, 0);
	if (strcmp(arr, "-0") == 0) pulling(arr, 0);
}
void arrange(char arr[])
{
	char *p;
	int loc, i, cnt = 0;
	int exit;

	//연산자 정리
	do {
		exit = 0;
		
		if (strstr(arr, "/*") || strstr(arr, "*/") || strstr(arr, "+/") || strstr(arr, "-/") || strstr(arr, "+*") || strstr(arr, "-*")) {
			ERROR = 3;
			break;
		}

		while (strstr(arr, "+-")) {
			p = strstr(arr, "+-");
			loc = (int)(p - arr);

			pulling(arr, loc);
			exit++;
		}

		while (strstr(arr, "-+")) {
			p = strstr(arr, "-+");
			loc = (int)(p - arr);

			pulling(arr, loc + 1);
			exit++;
		}

		while (strstr(arr, "--")) {
			p = strstr(arr, "--");
			loc = (int)(p - arr);

			pulling(arr, loc);
			pulling(arr, loc);
			pushing(arr, loc);
			arr[loc] = '+';
			exit++;
		}

		while (strstr(arr, "++")) {
			p = strstr(arr, "++");
			loc = (int)(p - arr);

			pulling(arr, loc);
			exit++;
		}
	} while (exit);

	//소수점 검토
	for (i = 0; arr[i] != 0; i++) {
		if (arr[i] >= '0' && arr[i] <= '9') continue;
		else if (arr[i] == '.') cnt++;
		else cnt = 0;
		if (cnt > 1) { ERROR = 4; break; }
	}

	if (arr[0] == '+') pulling(arr, 0);
}
void asmd(char arr[], int srt, int fin)
{
	//괄호가 없고 사칙연산만 존재한다
	char temp[SIZE] = { 0 };
	char num1[SIZE] = { 0 }, num2[SIZE] = { 0 };
	char head[SIZE] = { 0 }, tail[SIZE] = { 0 };
	char *p = NULL;
	int loc, start = srt, finish = fin, minus = 0, ct, exit = 0;

	strcpy(temp, arr);

	while (temp[finish + 1] != '\0') { pulling(temp, finish + 1); }
	for (int i = 0; i < start; i++) pulling(temp, 0);

	while (strchr(temp, '/')) {
		for (int i = 0; i < SIZE && head[i] != 0; i++) head[i] = 0;
		for (int i = 0; i < SIZE && tail[i] != 0; i++) tail[i] = 0;
		for (int i = 0; i < SIZE && num1[i] != 0; i++) num1[i] = 0;
		for (int i = 0; i < SIZE && num2[i] != 0; i++) num2[i] = 0;
		p = strchr(temp, '/');
		loc = (int)(p - temp);
		
		for (int i = 1; temp[loc - i] <= '9' && temp[loc - i] >= '0' || temp[loc - i] == '.'; i++) num1[i - 1] = temp[loc - i], start = loc - i;
		while (temp[loc + 1] == '+') pulling(temp, loc + 1);
		if (temp[loc + 1] == '-') {
			for (int i = 2; temp[loc + i] <= '9' && temp[loc + i] >= '0' || temp[loc + i] == '.'; i++)
				num2[i - 2] = temp[loc + i], finish = loc + i;
		}
		else {
			for (int i = 1; temp[loc + i] <= '9' && temp[loc + i] >= '0' || temp[loc + i] == '.'; i++)
				num2[i - 1] = temp[loc + i], finish = loc + i;
		}

		for (int i = 0; i < start; i++) head[i] = temp[i];
		for (int i = finish + 1; i < strlen(temp); i++) tail[i - finish - 1] = temp[i];
		strrev(num1);

		clean(num2);
		if (num2[0] == '0' && num2[1] == '\0') { ERROR = 2; break; }

		if (temp[loc + 1] == '-') {
			DIV(num1, num2);
			pushing(result, 0);
			result[0] = '-';
		}
		else DIV(num1, num2);

		strcat(head, result);
		strcat(head, tail);
		for (int i = 0; i < SIZE && temp[i] != 0; i++) temp[i] = 0;
		strcpy(temp, head);
	}

	while (strchr(temp, '*')) {
		for (int i = 0; i < SIZE && head[i] != 0; i++) head[i] = 0;
		for (int i = 0; i < SIZE && tail[i] != 0; i++) tail[i] = 0;
		for (int i = 0; i < SIZE && num1[i] != 0; i++) num1[i] = 0;
		for (int i = 0; i < SIZE && num2[i] != 0; i++) num2[i] = 0;
		p = strchr(temp, '*');
		loc = (int)(p - temp);
		
		for (int i = 1; temp[loc - i] <= '9' && temp[loc - i] >= '0' || temp[loc - i] == '.'; i++) num1[i - 1] = temp[loc - i], start = loc - i;
		while (temp[loc + 1] == '+') pulling(temp, loc + 1);
		if (temp[loc + 1] == '-') {
			for (int i = 2; temp[loc + i] <= '9' && temp[loc + i] >= '0' || temp[loc + i] == '.'; i++)
				num2[i - 2] = temp[loc + i], finish = loc + i;
		}
		else {
			for (int i = 1; temp[loc + i] <= '9' && temp[loc + i] >= '0' || temp[loc + i] == '.'; i++)
				num2[i - 1] = temp[loc + i], finish = loc + i;
		}

		for (int i = 0; i < start; i++) head[i] = temp[i];
		for (int i = finish + 1; i < strlen(temp); i++) tail[i - finish - 1] = temp[i];
		strrev(num1);

		if (temp[loc + 1] == '-') {
			mul(num1, num2);
			pushing(result, 0);
			result[0] = '-';
		}
		else mul(num1, num2);

		strcat(head, result);
		strcat(head, tail);
		for (int i = 0; i < SIZE && temp[i] != 0; i++) temp[i] = 0;
		strcpy(temp, head);
	}

	while (strchr(temp, '-')) {
		if (temp[0] == '-') {
			pulling(temp, 0);
			if (!strchr(temp, '-')) { pushing(temp, 0), temp[0] = '-'; break; }
			else minus = 1;
		}
		for (int i = 0; i < SIZE && head[i] != 0; i++) head[i] = 0;
		for (int i = 0; i < SIZE && tail[i] != 0; i++) tail[i] = 0;
		for (int i = 0; i < SIZE && num1[i] != 0; i++) num1[i] = 0;
		for (int i = 0; i < SIZE && num2[i] != 0; i++) num2[i] = 0;
		
		do {
			MUST:
			ct = 0;
			p = strchr(temp, '-');
			loc = (int)(p - temp);
			while (temp[loc - 1] == '+') { pulling(temp, loc - 1), ct++; goto MUST; }
			while (temp[loc + 1] == '+') { pulling(temp, loc + 1), ct++; goto MUST; }
			if (temp[loc + 1] == '-') {
				ct++;
				pulling(temp, loc), temp[loc] = '+';
				if (!strchr(temp, '-')) exit++;
			}
		} while (ct && !exit);

		if (exit) break;

		p = strchr(temp, '-');
		loc = (int)(p - temp);
		for (int i = 1; temp[loc - i] <= '9' && temp[loc - i] >= '0' || temp[loc - i] == '.'; i++) num1[i - 1] = temp[loc - i], start = loc - i;
		for (int i = 1; temp[loc + i] <= '9' && temp[loc + i] >= '0' || temp[loc + i] == '.'; i++) num2[i - 1] = temp[loc + i], finish = loc + i;
		for (int i = 0; i < start; i++) head[i] = temp[i];
		for (int i = finish + 1; i < strlen(temp); i++) tail[i - finish - 1] = temp[i];
		strrev(num1);

		if (head[0] == 0 && minus) add(num1, num2);
		else sub(num1, num2);

		if (result[0] == '-' && head[strlen(head) - 1] == '+') pulling(head, strlen(head) - 1);

		strcat(head, result);
		strcat(head, tail);
		for (int i = 0; i < SIZE && temp[i] != 0; i++) temp[i] = 0;
		strcpy(temp, head);
		if (minus) pushing(temp, 0), temp[0] = '-', minus = 0;
	}

	while (strchr(temp, '+')) {
		if (temp[0] == '+') {
			pulling(temp, 0);
			if (!strchr(temp, '+')) break;
		}
		for (int i = 0; i < SIZE && head[i] != 0; i++) head[i] = 0;
		for (int i = 0; i < SIZE && tail[i] != 0; i++) tail[i] = 0;
		for (int i = 0; i < SIZE && num1[i] != 0; i++) num1[i] = 0;
		for (int i = 0; i < SIZE && num2[i] != 0; i++) num2[i] = 0;

		p = strchr(temp, '+');
		loc = (int)(p - temp);
		while (temp[loc + 1] == '+') pulling(temp, loc + 1);

		for (int i = 1; temp[loc - i] <= '9' && temp[loc - i] >= '0' || temp[loc - i] == '.'; i++) num1[i - 1] = temp[loc - i], start = loc - i;
		for (int i = 1; temp[loc + i] <= '9' && temp[loc + i] >= '0' || temp[loc + i] == '.'; i++) num2[i - 1] = temp[loc + i], finish = loc + i;
		for (int i = 0; i < start; i++) head[i] = temp[i];
		for (int i = finish + 1; i < strlen(temp); i++) tail[i - finish - 1] = temp[i];
		strrev(num1);

		if (head[strlen(head) - 1] == '-') pulling(head, strlen(head) - 1), sub(num2, num1);
		else add(num1, num2);

		strcat(head, result);
		strcat(head, tail);
		for (int i = 0; i < SIZE && temp[i] != 0; i++) temp[i] = 0;
		strcpy(temp, head);
	}
	for (int i = 0; i < SIZE && arr[i] != 0; i++) arr[i] = 0;
	strcpy(arr, temp);
}
void bracket(char arr[])
{
	//괄호 안만 계산한다
	int cntop = 0, cntcl = 0;
	int start = 0, finish = 0;
	char head[SIZE] = { 0 }, tail[SIZE] = { 0 };

	for (int i = 0; i < strlen(arr); i++) {
		if (arr[i] == '(') cntop++;
		if (arr[i] == ')') cntcl++;
	}
	if (cntop != cntcl) ERROR = 1;
	else {
		while (strchr(arr, '(') || strchr(arr, ')')) {
			//속괄호에 대해서 사칙연산 한다
			for (int i = 0; i < strlen(arr); i++) {
				if (arr[i] == '(') start = i;
				if (arr[i] == ')') { finish = i; break; }
			}
			for (int i = 0; i < SIZE && head[i] != 0; i++) head[i] = 0;
			for (int i = 0; i < SIZE && tail[i] != 0; i++) tail[i] = 0;
			for (int i = 0; i < start; i++) head[i] = arr[i];
			for (int i = finish + 1; i < strlen(arr); i++) tail[i - finish - 1] = arr[i];
			pulling(arr, finish);
			pulling(arr, start);
			asmd(arr, start, finish - 2);
			if (head[strlen(head) - 1] == '-' && arr[0] == '-') head[strlen(head) - 1] = '+', pulling(arr, 0);
			if (head[strlen(head) - 1] == '+' && arr[0] == '+') head[strlen(head) - 1] = '+', pulling(arr, 0);
			strcat(head, arr);
			strcat(head, tail);
			for (int i = 0; i < SIZE && arr[i] != 0; i++) arr[i] = 0;
			strcpy(arr, head);
		}
	}
}
void explore(char arr[])
{
	char a[SIZE] = { 0 };
	int j = 0;
	
	//빈칸 제거
	for (int i = 0; i < strlen(arr); i++) {
		if (arr[i] != ' ') a[j] = arr[i], j++;
	}

	//연산자 정리 및 소수점 검토
	arrange(a);

	if (ERROR) goto FIN;

	//괄호를 전부 처리한다
	if (strchr(a, '(') || strchr(a, ')')) bracket(a);

	asmd(a, 0, strlen(a) - 1);

	clean(a);

	for (int i = 0; i < SIZE && result[i] != 0; i++) result[i] = 0;

	FIN:
	strcpy(result, a);
}