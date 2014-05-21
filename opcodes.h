#include "register.h"
#define size 3

typedef struct OpCode
{
	//unsigned char value;
	unsigned short parms;
	void(*value)(int*,al_register*);
} OpCode;

OpCode OpCodes[size];