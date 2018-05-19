#include <stdio.h>
#include <stdlib.h>
#define SIZE 1000
#pragma warning(disable: 4996)

void reverse(char arr[]);
void add(char arr1[], char arr2[]);
void sub(char arr1[], char arr2[]);
void mul(char arr1[], char arr2[]);
void DIV(char a[], char b[]);
void copy(char arr1[], char arr2[]);
void swap(char arr1[], char arr2[], int n);
void pushing(char arr[], int n);
void pulling(char arr[], int n);
void explore(char arr[]);
void part_ex(char arr[], int start, int finish);

char add_store[SIZE] = { 0 }, sub_store[SIZE] = { 0 }, mul_store[SIZE] = { 0 }, div_store[SIZE] = { 0 }, result[SIZE] = { 0 };
int sign;

int main() {
	while (1) {
		char num1[SIZE] = { 0 }, num2[SIZE] = { 0 }, Express[SIZE] = { 0 };

		sign = 0;

		printf("Type polynomial expression\n");
		scanf("%s", &Express);

		explore(Express);
		if (sign) printf("-");
		printf("%s\n", Express);

		system("pause");
		system("cls");
	}
	return 0;
}

void reverse(char arr[])
{
	int i, cnt = -1;
	for (i = 0; i < SIZE; i++) {
		if (arr[i] != 0) cnt++;
		else break;
	}
	for (i = 0; i <= cnt / 2; i++) {
		if (arr[i] != arr[cnt - i]) {
			arr[i] ^= arr[cnt - i];
			arr[cnt - i] ^= arr[i];
			arr[i] ^= arr[cnt - i];
		}
	}
}
void add(char arr1[], char arr2[])
{
	char a[SIZE] = { 0 }, b[SIZE] = { 0 };
	int i, pointA = 0, pointB = 0, tmp;
	for (i = 0; i < SIZE && add_store[i] != 0; i++) add_store[i] = 0;

	copy(arr1, a);
	copy(arr2, b);

	for (i = 0; i < SIZE; i++) {
		if (a[i] == 46) break;
		else if (a[i] == 0) { a[i] = 46; break; }
	}
	for (i = 0; i < SIZE; i++) {
		if (b[i] == 46) break;
		else if (b[i] == 0) { b[i] = 46; break; }
	}

	reverse(a);
	reverse(b);

	for (i = 0; i < SIZE; i++) {
		if (a[i] == 46) pointA = i;
		if (b[i] == 46) pointB = i;
		if (a[i] == 0 && b[i] == 0) break;
	}

	if (pointA > pointB) {
		for (i = 1; i <= pointA - pointB; i++) pushing(b, 0);
	}
	else if (pointA < pointB) {
		for (i = 1; i <= pointB - pointA; i++) pushing(a, 0);
	}

	for (i = 0; i < SIZE; i++) {
		if (a[i] == 0 && b[i] == 0) break;
		else if (a[i] == 46) { add_store[i] = 46; continue; }
		else {
			add_store[i] += a[i] + b[i] - 0x30;
			if (a[i] == 0 || b[i] == 0) add_store[i] += 0x30;
			if (add_store[i] > 0x39) {
				add_store[i] -= 10;
				if (a[i + 1] == 46) add_store[i + 2]++;
				else add_store[i + 1]++;
			}
		}
	}
	if (add_store[i] == 1) add_store[i] = 49;

	if (pointA > pointB) {
		for (i = 1; i <= pointA - pointB; i++) pulling(b, 0);
	}
	else if (pointA < pointB) {
		for (i = 1; i <= pointB - pointA; i++) pulling(a, 0);
	}

	reverse(a);
	reverse(b);
	reverse(add_store);

	for (i = 0; i < SIZE; i++) {
		if (add_store[i] == 0) { tmp = i - 1; break; }
	}
	for (i = tmp; i >= 0; i--) {
		if (add_store[i] == 48) add_store[i] = 0;
		else if (add_store[i] == 46) { add_store[i] = 0; break; }
		else break;
	}
}
void sub(char arr1[], char arr2[])
{
	char a[SIZE] = { 0 }, b[SIZE] = { 0 };
	int i, dgnum_A, dgnum_B, compare = 0, pointA = 0, pointB = 0, tmp;
	for (i = 0; i < SIZE && sub_store[i] != 0; i++) sub_store[i] = 0;

	copy(arr1, a);
	copy(arr2, b);

	for (i = 0; i < SIZE; i++) {
		if (a[i] == 46) break;
		else if (a[i] == 0) { a[i] = 46; break; }
	}
	for (i = 0; i < SIZE; i++) {
		if (b[i] == 46) break;
		else if (b[i] == 0) { b[i] = 46; break; }
	}

	for (i = 0; i < SIZE; i++) {
		if (a[i] == 46) { dgnum_A = i; break; }
	}
	for (i = 0; i < SIZE; i++) {
		if (b[i] == 46) { dgnum_B = i; break; }
	}
	for (i = 0; i < SIZE; i++) { //a와 b의 크기 비교
		if (a[i] < b[i]) { compare = 1; break; }
		if (a[i] > b[i]) { compare = 0; break; }
	}
	if (dgnum_A < dgnum_B || (dgnum_A == dgnum_B && compare)) {
		for (i = 0; i < SIZE; i++) { //b가 더 클 경우 a와 b를 맞바꿔어 계산 후 -를 붙인다
			if (a[i] != b[i]) swap(a, b, i);
			if (a[i] == 0 && b[i] == 0) break;
		}
		sign++;
	}

	reverse(a);
	reverse(b);

	for (i = 0; i < SIZE; i++) {
		if (a[i] == 46) pointA = i;
		if (b[i] == 46) pointB = i;
		if (a[i] == 0 && b[i] == 0) break;
	}

	if (pointA > pointB) {
		for (i = 1; i <= pointA - pointB; i++) pushing(b, 0);
	}
	else if (pointA < pointB) {
		for (i = 1; i <= pointB - pointA; i++) pushing(a, 0);
	}

	for (i = 0; i < SIZE; i++) {
		if (a[i] == 0 && b[i] == 0) break;
		else if (a[i] == 46) { sub_store[i] = 46; continue; }
		else {
			sub_store[i] += a[i] - b[i] + 0x30;
			if (b[i] == 0) sub_store[i] -= 0x30;
			if (sub_store[i] < 0x30) {
				sub_store[i] += 10;
				if (a[i + 1] == 46) sub_store[i + 2]--;
				else sub_store[i + 1]--;
			}
		}
	}
	while (sub_store[i - 1] == 48) {
		if (i == 1) break;
		sub_store[--i] = 0;
	}

	if (pointA > pointB) {
		for (i = 1; i <= pointA - pointB; i++) pulling(b, 0);
	}
	else if (pointA < pointB) {
		for (i = 1; i <= pointB - pointA; i++) pulling(a, 0);
	}

	reverse(a);
	reverse(b);
	reverse(sub_store);

	for (i = 0; i < SIZE; i++) {
		if (sub_store[i] == 0) { tmp = i - 1; break; }
	}
	for (i = tmp; i >= 0; i--) {
		if (sub_store[i] == 48) sub_store[i] = 0;
		else if (sub_store[i] == 46) { sub_store[i] = 0; break; }
		else break;
	}
	if (sub_store[0] == 0) sub_store[0] = '0';
	if (sub_store[0] == 46) pushing(sub_store, 0), sub_store[0] = '0';
	if (sign) {
		for (i = 0; i < SIZE; i++) {
			if (a[i] != b[i]) swap(a, b, i);
			if (a[i] == 0 && b[i] == 0) break;
		}
	}
}
void mul(char arr1[], char arr2[])
{
	char a[SIZE] = { 0 }, b[SIZE] = { 0 };
	char temp[SIZE] = { 0 };
	int cursor, zero = -1, point_over_count = 0, point_under_count = 0, tmp = 0;
	int i = 0, dgnum_A, dgnum_B, compare = 0;
	for (int i = 0; i < SIZE && mul_store[i] != 0; i++) mul_store[i] = 0;

	copy(arr1, a);
	copy(arr2, b);

	while (1) {
		if (a[i] == 48 && a[i + 1] != 46) pulling(a, 0);
		else break;
	}

	while (1) {
		if (b[i] == 48 && b[i + 1] != 46) pulling(b, 0);
		else break;
	}

	for (i = 0; i < SIZE; i++) {
		if (a[i] == 46) break;
		else if (a[i] == 0) { a[i] = 46; break; }
	}
	for (i = 0; i < SIZE; i++) {
		if (b[i] == 46) break;
		else if (b[i] == 0) { b[i] = 46; break; }
	}
	for (i = 0; i < SIZE; i++) {
		if (a[i] == 46) {
			pulling(a, i);
			for (int j = i; j < SIZE; j++) {
				if (a[j] != 0) point_under_count++;
				else { i = SIZE; break; }
			}
		}
	}
	for (i = 0; i < SIZE; i++) {
		if (b[i] == 46) {
			pulling(b, i);
			for (int j = i; j < SIZE; j++) {
				if (b[j] != 0) point_under_count++;
				else { i = SIZE; break; }
			}
		}
	}
	i = 0;
	while (1) {
		if (a[i] == 48) pulling(a, 0);
		else break;
	}
	while (1) {
		if (b[i] == 48) pulling(b, 0);
		else break;
	}

	for (i = 0; i < SIZE; i++) {
		if (a[i] == 0) { dgnum_A = i; break; }
	}
	for (i = 0; i < SIZE; i++) {
		if (b[i] == 0) { dgnum_B = i; break; }
	}
	for (i = 0; i < SIZE; i++) { //a와 b의 크기 비교
		if (a[i] < b[i]) { compare = 1; break; }
		if (a[i] > b[i]) { compare = 0; break; }
		if (a[i] == 0 && b[i] == 0) break;
	}
	if (dgnum_A < dgnum_B || (dgnum_A == dgnum_B && compare)) {
		for (i = 0; i < SIZE; i++) { //b가 더 클 경우 a와 b를 맞바꿔어 계산 후 -를 붙인다
			if (a[i] != b[i]) swap(a, b, i);
			if (a[i] == 0 && b[i] == 0) break;
		}
	}
	for (int i = 0; i < SIZE; i++) { //b의 마지막 수의 위치를 cursor에 저장
		if (b[i] == 0) { cursor = i - 1; break; }
	}

	while (cursor != -1) {
		copy(a, temp);
		for (int i = 0; i < b[cursor] - 49; i++) {
			add(a, temp);
			copy(add_store, temp);
		}
		zero++;

		if (b[cursor] == 48) NULL;
		else {
			for (int i = 1; i <= zero; i++) { //0을 집어넣어준다
				for (int j = 0; j < SIZE; j++) {
					if (temp[j] == 0 || temp[j] == 46) { temp[j] = 48; break; }
				}
			}
			add(mul_store, temp);
			copy(add_store, mul_store);
		}
		cursor--;
	}

	for (i = 0; i < SIZE; i++) {
		if (mul_store[i] == 0) { tmp = i; break; }
	}

	while (1) {
		if (tmp < point_under_count) pushing(mul_store, 0), tmp++;
		else break;
	}

	pushing(mul_store, tmp - point_under_count);
	mul_store[tmp - point_under_count] = 46;

	if (mul_store[0] == 46) pushing(mul_store, 0), mul_store[0] = 48;

	for (i = 0; i < SIZE; i++) {
		if (mul_store[i] == 0) { tmp = i - 1; break; }
	}

	for (i = tmp; i > 0; i--) {
		if (mul_store[i] == 48) mul_store[i] = 0;
		else if (mul_store[i] == 46) { mul_store[i] = 0; break; }
		else break;
	}
	while (1) {
		if (mul_store[i] == 48 && mul_store[i + 1] != 46) pulling(mul_store, 0);
		else break;
	}
}
void DIV(char a[], char b[])
{
	int i, pow = 0, cursor = 0, tmp = 0, pos_point = 0, pos_num = 1;
	char k[3] = "9";
	for (i = 0; i < SIZE && div_store[i] != 0; i++) div_store[i] = 0;

	for (i = 0; i < SIZE; i++) {
		if (a[i] == 46 || a[i] == 0) {
			pos_point = i; break;
		}
	}

	pow -= pos_point - 1;
	pulling(a, pos_point);
	pushing(a, 1);
	a[1] = 46;

	if (b[0] == 48 && b[1] == 46) {
		for (i = 2; i < SIZE; i++) {
			if (b[i] != 48) {
				pos_num = i; break;
			}
		}
	}

	if (b[0] == 48 && b[1] == 46) {
		pow -= pos_num - 1;
		pulling(b, 1);
		pushing(b, pos_num);
		b[pos_num] = 46;
	}
	i = 0;
	while (1) {
		if (b[i] == 48) pulling(b, 0);
		else break;
	}

	while (cursor < 80) {
		k[0] = 57;
		sub(a, b);
		if (sign) {
			sign--;
			for (i = 0; i < SIZE; i++) {
				if (a[i] == 0) {
					div_store[cursor] = 48;
					mul(a, "10");
					copy(mul_store, a);
					break;
				}
			}
		}
		else {
			while (k[0] >= 49) {
				mul(b, k);
				sub(a, mul_store);
				if (sign) sign--;
				else {
					div_store[cursor] = k[0];
					copy(sub_store, a);
					mul(a, "10");
					copy(mul_store, a);
					break;
				}
				k[0]--;
			}
		}
		pow++;
		cursor++;
	}

	for (i = 0; i < SIZE; i++) {
		if (div_store[i] == 0) { tmp = i; break; }
	}
	while (1) {
		if (tmp < pow) pushing(div_store, 0), tmp++;
		else break;
	}

	pushing(div_store, tmp - pow + 1);
	div_store[tmp - pow + 1] = 46;

	if (div_store[0] == 46) pushing(div_store, 0), div_store[0] = 48;

	for (i = 0; i < SIZE; i++) {
		if (div_store[i] == 0) { tmp = i - 1; break; }
	}

	for (i = tmp; i > 0; i--) {
		if (div_store[i] == 48) div_store[i] = 0;
		else if (div_store[i] == 46) { div_store[i] = 0; break; }
		else break;
	}
	i = 0;
	while (1) {
		if (div_store[i] == 48 && div_store[i + 1] != 46) pulling(div_store, 0);
		else break;
	}
}
void copy(char arr1[], char arr2[])
{
	for (int i = 0; i < SIZE && arr2[i] != 0; i++) arr2[i] = 0;
	for (int i = 0; i < SIZE; i++)
		arr2[i] = arr1[i];
}
void swap(char arr1[], char arr2[], int n)
{
	if (arr1[n] != arr2[n]) {
		arr1[n] ^= arr2[n];
		arr2[n] ^= arr1[n];
		arr1[n] ^= arr2[n];
	}
}
void pushing(char arr[], int n)
{
	int tmp;
	for (int i = 0; i < SIZE; i++) {
		if (arr[i] == 0) { tmp = i; break; }
	}
	for (int i = tmp; i > n; i--) {
		arr[i] = arr[i - 1];
	}
	arr[n] = 48;
}
void pulling(char arr[], int n)
{
	for (int i = n; i < SIZE; i++) {
		if (arr[i] != 0) arr[i] = arr[i + 1];
		else break;
	}
}
void explore(char arr[])
{
	int i, j, start = 0, finish = 0, count = 0;
	for (int k = 0; k < SIZE; k++) {
		if (arr[k] == '(') { start = k + 1; continue; }
		else if (arr[k] == ')') finish = k - 1, part_ex(arr, start, finish);
		else if (arr[k] == 0) break;
		else continue;

		start--, finish++;
		k = -1;
		if (start != finish) {
			for (i = start; i < SIZE - start; i++) {
				if (result[i - start] == 0) break;
				pushing(arr, i);
				arr[i] = result[i - start];
			}
			for (j = i; arr[j] != ')'; ) {
				pulling(arr, j);
			}
			pulling(arr, j);
		}
	}

	start = 0, finish = 0;

	for (int k = 0; k < SIZE; k++) {
		if (count == 0 && (arr[k] == '+' || arr[k] == '-')) { start = k + 1; continue; }
		else if (count == 0 && (arr[k] == '*' || arr[k] == '/')) { count++; continue; }
		else if (count != 0 && (arr[k] < '0' || arr[k] > '9') && arr[k] != 46) finish = k - 1, part_ex(arr, start, finish);
		else if (arr[k] == 0) break;
		else continue;

		k = -1;
		if (start != finish) {
			for (i = start; i < SIZE - start; i++) {
				if (result[i - start] == 0) break;
				pushing(arr, i);
				arr[i] = result[i - start];
			}
			j = i;
			for (int c = 0; c < finish - start + 1; c++) {
				pulling(arr, j);
			}
			if (arr[j] == '=') pulling(arr, j);
		}

		count = 0;
	}

	start = 0, finish = 0;
	count = 0;

	for (int k = 0; k < SIZE; k++) {
		if (count == 0 && (arr[k] == '+' || arr[k] == '-')) { start = 0, count++; continue; }
		else if (count != 0 && (arr[k] < '0' || arr[k] > '9') && arr[k] != 46) finish = k - 1, part_ex(arr, start, finish);
		else if (arr[k] == 0) break;
		else continue;

		k = -1;
		if (start != finish) {
			for (i = start; i < SIZE - start; i++) {
				if (result[i - start] == 0) break;
				pushing(arr, i);
				arr[i] = result[i - start];
			}
			j = i;
			for (int c = 0; c < finish - start + 1; c++) {
				pulling(arr, j);
			}
			if (arr[j] == '=') pulling(arr, j);
		}

		count = 0;
	}
}
void part_ex(char arr[], int start, int finish)
{
	int i, j, count = 0;
	char number1[SIZE] = { 0 }, number2[SIZE] = { 0 }, temp[SIZE] = { 0 };
	for (i = 0; i < SIZE && result[i] != 0; i++) result[i] = 0;
	for (i = start; i <= finish; i++) {
		temp[i - start] = arr[i];
		if (arr[i] == '+' || arr[i] == '-' || arr[i] == '*' || arr[i] == '/') count++;
	}
	if (count >= 2) explore(temp), copy(temp, result);
	else {
		for (i = start; arr[i] == 46 || arr[i] >= '0' && arr[i] <= '9'; i++) number1[i - start] = arr[i];
		if (arr[i] == '*') {
			for (int j = i + 1; j <= finish || arr[i] == 46 || arr[j] >= '0' && arr[j] <= '9'; j++) {
				number2[j - i - 1] = arr[j];
			}
			mul(number1, number2);
			copy(mul_store, result);
		}
		else if (arr[i] == '/') {
			for (int j = i + 1; j <= finish || arr[i] == 46 || arr[j] >= '0' && arr[j] <= '9'; j++) {
				number2[j - i - 1] = arr[j];
			}
			DIV(number1, number2);
			copy(div_store, result);
		}
		else if (arr[i] == '+') {
			for (int j = i + 1; j <= finish || arr[i] == 46 || arr[j] >= '0' && arr[j] <= '9'; j++) {
				number2[j - i - 1] = arr[j];
			}
			add(number1, number2);
			copy(add_store, result);
		}
		else if (arr[i] == '-') {
			for (int j = i + 1; j <= finish || arr[i] == 46 || arr[j] >= '0' && arr[j] <= '9'; j++) {
				number2[j - i - 1] = arr[j];
			}
			sub(number1, number2);
			copy(sub_store, result);
		}
	}
}