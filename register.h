#ifndef registr
#define registr
/*
union val {
	int number;
	char* string;
	void* unknow;
	func* func;
} Value;
*/
typedef struct reg
{
	int count;
	int *val;
} al_register;
#endif

