#include "opcodes.h"

typedef struct reg al_register;

void lod(int *parms,al_register *reg){
		reg->val[*parms] = (int)*(parms + 1);
}

void mov(int *parms, al_register *reg){
	reg->val[*parms] = reg->val[*(parms + 1)];
}

void add(int *parms,al_register *reg){
	reg->val[*parms] = reg->val[*parms] + reg->val[*(parms + 1)];
}



OpCode OpCodes[size] =
{
	{ 2, mov },	//mov
	{ 2, lod },	//lod
	{ 2, add }	//add
};


