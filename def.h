#ifndef DEF_H_INCLUDED
#define DEF_H_INCLUDED

#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

#define WHITE 255,255,255
#define BLACK 0,0,0
#define DARKBLUE 0,0,100
#define LINECOLOUR DARKBLUE

#define PI 3.14159265358979323846
#define DELTA 5
#define LINEWIDTH 2

#define TRUE 1
#define FALSE 0

enum UpperLowerEnum { NOTOVER, UPPERPART, LOWERPART, NODE };

typedef struct {
	int x;
	int y;
} pos;

typedef int BOOL;
typedef unsigned char uchar;
typedef unsigned long int uint;

#endif