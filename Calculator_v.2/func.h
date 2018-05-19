#include <string.h>
#define SIZE 1000
#pragma warning(disable: 4996)

extern char result[SIZE];
extern void swap(char[], char[]), clean(char[]);
extern void pushing(char[], int), pulling(char[], int);

void add(char arr1[], char arr2[])
{
	char a[SIZE] = { 0 }, b[SIZE] = { 0 }, add_store[SIZE] = { 0 };
	char *pa = NULL, *pb = NULL;
	int i, loca, locb;

	for (i = 0; i < SIZE && result[i] != 0; i++) result[i] = 0;

	//원본 배열을 다루지 않고 사본을 다룬다
	strcpy(a, arr1);
	strcpy(b, arr2);

	clean(a);
	clean(b);

	//소수점이 없다면 소수점을 넣어준다
	if (!strchr(a, '.')) strcat(a, ".0");
	if (!strchr(b, '.')) strcat(b, ".0");

	strrev(a);
	strrev(b);

	//소수점의 위치 파악 및 통일
	pa = strchr(a, '.'), loca = (int)(pa - a);
	pb = strchr(b, '.'), locb = (int)(pb - b);
	if (loca > locb) { for (i = 0; i < loca - locb; i++) pushing(b, 0); }
	else if (loca < locb) { for (i = 0; i < locb - loca; i++) pushing(a, 0); }

	for (i = 0; i < SIZE; i++) {
		if (a[i] == 0 && b[i] == 0) break;
		else if (a[i] == '.') { add_store[i] = '.'; continue; }
		else {
			add_store[i] += a[i] + b[i] - 48;
			if (a[i] == 0 || b[i] == 0) add_store[i] += 48;
			if (add_store[i] > '9') {
				add_store[i] -= 10;
				if (a[i + 1] == '.') add_store[i + 2]++;
				else add_store[i + 1]++;
			}
		}
	}
	if (add_store[i] == 1) add_store[i] = '1';

	strrev(add_store);
	clean(add_store);
	strcpy(result, add_store);
}
void sub(char arr1[], char arr2[])
{
	char a[SIZE] = { 0 }, b[SIZE] = { 0 }, sub_store[SIZE] = { 0 };
	char *pa = NULL, *pb = NULL;
	int i, sign = 0, loca, locb;

	for (i = 0; i < SIZE && result[i] != 0; i++) result[i] = 0;

	strcpy(a, arr1);
	strcpy(b, arr2);

	clean(a);
	clean(b);

	if (!strchr(a, '.')) strcat(a, ".0");
	if (!strchr(b, '.')) strcat(b, ".0");

	pa = strchr(a, '.'), loca = (int)(pa - a);
	pb = strchr(b, '.'), locb = (int)(pb - b);
	if (loca > locb) { for (i = 0; i < loca - locb; i++) pushing(b, 0); }
	else if (loca < locb) { for (i = 0; i < locb - loca; i++) pushing(a, 0); }

	//a가 b보다 항상 크게 만들어준다
	if (strcmp(a, b) < 0) swap(a, b), sign++;

	strrev(a);
	strrev(b);

	pa = strchr(a, '.'), loca = (int)(pa - a);
	pb = strchr(b, '.'), locb = (int)(pb - b);
	if (loca > locb) { for (i = 0; i < loca - locb; i++) pushing(b, 0); }
	else if (loca < locb) { for (i = 0; i < locb - loca; i++) pushing(a, 0); }

	for (i = 0; i < SIZE; i++) {
		if (a[i] == 0 && b[i] == 0) break;
		else if (a[i] == '.') { sub_store[i] = '.'; continue; }
		else {
			sub_store[i] += a[i] - b[i] + 48;
			if (sub_store[i] < '0') {
				sub_store[i] += 10;
				if (a[i + 1] == '.') sub_store[i + 2]--;
				else sub_store[i + 1]--;
			}
		}
	}

	strrev(sub_store);
	clean(sub_store);

	strrev(sub_store);
	if (sign) strcat(sub_store, "-");
	strrev(sub_store);

	strcpy(result, sub_store);
}
void mul(char arr1[], char arr2[])
{
	char a[SIZE] = { 0 }, b[SIZE] = { 0 }, mul_store[SIZE] = { 0 };
	int cursor, tmp = 0;
	char *zero = NULL, *pa = NULL, *pb = NULL;
	int i, loca, locb, pow = 0;

	for (i = 0; i < SIZE && result[i] != 0; i++) result[i] = 0;

	strcpy(a, arr1);
	strcpy(b, arr2);

	if (!strchr(a, '.')) strcat(a, ".0");
	if (!strchr(b, '.')) strcat(b, ".0");

	clean(a);
	clean(b);

	if (strchr(a, '.')) pa = strchr(a, '.'), loca = (int)(pa - a), pow += strlen(a) - loca - 1, pulling(a, loca);
	if (strchr(b, '.')) pb = strchr(b, '.'), locb = (int)(pb - b), pow += strlen(b) - locb - 1, pulling(b, locb);

	if (strlen(a) < strlen(b)) swap(a, b);

	//소수점을 제거한 후에도 숫자 정리를 해준다
	clean(a);
	clean(b);

	cursor = strlen(b) - 1;

	while (cursor != -1) {
		char temp[SIZE] = { 0 };
		strcpy(temp, a);
		for (int i = 0; i < b[cursor] - 49; i++) {
			add(a, temp);
			for (int j = 0; j < SIZE && temp[j] != 0; j++) temp[j] = 0;
			strcpy(temp, result);
		}
		if (b[cursor] == '0') NULL;
		else {
			for (int i = 1; i < strlen(b) - cursor; i++) strcat(temp, "0");
			add(mul_store, temp);
			for (i = 0; i < SIZE && mul_store[i] != 0; i++) mul_store[i] = 0;
			strcpy(mul_store, result);
		}
		cursor--;
	}

	tmp = strlen(mul_store) - pow;
	while (tmp < 0) pushing(mul_store, 0), tmp++;
	pushing(mul_store, tmp);
	mul_store[tmp] = '.';

	clean(mul_store);

	for (i = 0; i < SIZE && result[i] != 0; i++) result[i] = 0;
	strcpy(result, mul_store);
}
void DIV(char arr1[], char arr2[])
{
	char a[SIZE] = { 0 }, b[SIZE] = { 0 }, div_store[SIZE] = { 0 };
	char *zero = NULL, *pa = NULL, *pb = NULL;
	int i, loca, locb, pow = 0;
	int cursor = 0, tmp = 0;

	for (i = 0; i < SIZE && result[i] != 0; i++) result[i] = 0;

	strcpy(a, arr1);
	strcpy(b, arr2);

	if (!strchr(a, '.')) strcat(a, ".0");

	pa = strchr(a, '.');
	loca = (int)(pa - a);
	pow -= loca - 1;
	pulling(a, loca);
	pushing(a, 1);
	a[1] = '.';

	clean(b);

	//b가 0.xxx일 경우
	if (b[0] == '0' && b[1] == '.') {
		for (i = 2; i < SIZE; i++) {
			if (b[i] != '0') break;
		}
		pow -= i - 1;
		pulling(b, 1);
		pushing(b, i);
		b[i] = '.';
	}

	clean(b);

	while (cursor < 50) {
		char k[2] = "9";
		sub(a, b);
		if (result[0] == '-') {
			for (i = 0; i < SIZE; i++) {
				if (a[i] == 0) {
					div_store[cursor] = '0';
					mul(a, "10");
					for (i = 0; i < SIZE && a[i] != 0; i++) a[i] = 0;
					strcpy(a, result);
					break;
				}
			}
		}
		else {
			while (k[0] >= '1') {
				char temp[SIZE] = { 0 };
				mul(b, k);
				strcpy(temp, result);
				sub(a, temp);
				if (result[0] != '-') {
					div_store[cursor] = k[0];
					for (i = 0; i < SIZE && a[i] != 0; i++) a[i] = 0;
					strcpy(a, result);
					mul(a, "10");
					for (i = 0; i < SIZE && temp[i] != 0; i++) temp[i] = 0;
					strcpy(temp, result);
					for (i = 0; i < SIZE && a[i] != 0; i++) a[i] = 0;
					strcpy(a, temp);
					break;
				}
				k[0]--;
			}
		}
		pow++;
		cursor++;
	}

	tmp = strlen(div_store) - pow + 1;

	while (1) {
		if (strlen(div_store) < pow) pushing(div_store, 0), tmp++;
		else break;
	}

	pushing(div_store, tmp);
	div_store[tmp] = '.';

	clean(div_store);
	for (i = 0; i < SIZE && result[i] != 0; i++) result[i] = 0;
	strcpy(result, div_store);
}