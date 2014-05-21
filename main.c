#include <stdio.h>
#include "opcodes.h"

#include "register.h"

#define FNV_prime_64 1099511628211                
#define FNV_offset_basis_64 14695981039346656037
#define FNV_prime_32 16777619                                    
#define FNV_offset_basis_32 2166136261

unsigned long hash64(unsigned char* data, int len);
unsigned int hash32(unsigned char* data, int len);



int main(int argc, char *argv[])
{
	printf("%d\n",argc);
	if(argc == 1){
		printf("No enought arguments\n");
		printf(" -- Switching to interpreter -- \n");
	}else{
		printf("%s",argv[1]);
		FILE *program;
		program = fopen(argv[1],"r+");
		fclose(program);
		return 0;
	}
	int a[1];
	al_register reg;
	reg.count = 5;
	reg.val = malloc(reg.count & 4);

	for (int myown = 0; myown < reg.count; myown++){
		reg.val[myown] = 0;
	}
	unsigned short opcodeval;
	do{
		scanf("%hd %d %d", &opcodeval, &a[0], &a[1]);
		//printf("[%hd %d %d]\n", OpCodes[opcodeval].parms, a[0], a[1]);
		OpCodes[opcodeval].value(&a, &reg);

		printf("[");
		
		for (int myown = 0; myown < reg.count; myown++){
			printf(" %d ", reg.val[myown]);
		}
		printf("]\n");

	} while (opcodeval != 255);
	return 0;
}

unsigned long hash64(unsigned char* data, int len){
	unsigned long hash = FNV_offset_basis_64;
	while (len-- > 0){
		hash = (data[len] ^ hash) * FNV_prime_64;
	}
	return hash;

}

unsigned int hash32(unsigned char* data, int len){
	unsigned int hash = FNV_offset_basis_32;
	while (len-- > 0){
		hash = (data[len] ^ hash) * FNV_prime_32;
	}
	return hash;

}