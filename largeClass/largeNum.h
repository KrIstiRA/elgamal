#ifndef _LARGENUM_H_
#define _LARGENUM_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define BASE 1000000000

struct bigInt
{
	int sizeNum;//размер
	int sign;//знак
	unsigned int* digits;//цифры
};

typedef struct bigInt bigInt;//определение типа, чтобы не писать каждый раз struct bigInt
bigInt getFrombinarFile(const char* filename);
int saveTobinarFile(const char* filename, bigInt A);
bigInt ReadFromTextFile(const char *fileName);
int WriteToTFile(const char *fileName, bigInt A);
struct bigInt createFromString(const char* string);
bigInt createFromInt(long long int value);
char* getString(bigInt a);
bigInt copy(bigInt from);
bigInt DelZeros(bigInt a);
long long int compare(bigInt A, bigInt B);
bigInt sumAndSub(bigInt left, bigInt right);
bigInt sum(bigInt A, bigInt B);
bigInt sub(bigInt A, bigInt B);
bigInt minus(bigInt a);
bigInt mul(bigInt A, bigInt B);
bigInt dividing(bigInt A, bigInt B, bigInt* ost);
bigInt shiftLeft(bigInt a, int s);
bigInt myPow(bigInt base, bigInt exp);
int odd(bigInt a); // четно ли a
bigInt powMod(bigInt base, bigInt exp, bigInt modul);
bigInt GenRandomByLen(int bitlen);
bigInt GenRandomByRange(bigInt max);
bigInt GenRandomOddByLen(int bitlen);
#endif
