#include <stdio.h>
#include <Windows.h>

#define FNV_prime_64 1099511628211                
#define FNV_offset_basis_64 14695981039346656037
#define FNV_prime_32 16777619                                    
#define FNV_offset_basis_32 2166136261

unsigned long hash64(unsigned char* data, int len);
unsigned int hash32(unsigned char* data, int len);



int main(int argc, char *argv[])
{
	
	unsigned char *code;
	//char name[10];

	int psize = 7;
	code = (unsigned char *)malloc(psize);
	if (code == NULL) return(1);
	code[0] = 0xB8;
	code[1] = 0x12;
	code[2] = 0x00;
	code[3] = 0x00;
	code[4] = 0x00;
	code[5] = 0xc3; //ret
	code[6] = 0x90; //nop
	DWORD oldprotect;
	VirtualProtect((LPVOID)code, psize, PAGE_EXECUTE_READWRITE, &oldprotect);
	int val = ((int(*)())code)();
	printf("return: %d, hash: %d\n", val, hash32(code, psize));
	//scanf_s("%s", &name);
	//printf("hash: %ud\n", hash32((unsigned char*)&name, 10));
	int ret;
	scanf("%d", &ret);
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