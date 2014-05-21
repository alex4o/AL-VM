// hast_debug.cpp : Defines the entry point for the console application.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct entry_s {
	char *key;
	int value;
	int count;
	struct entry_s *next;
};

typedef struct entry_s entry_t;

struct hashtable_s {
	int size;
	struct entry_s **table;
};

typedef struct hashtable_s hashtable_t;


/* Create a new hashtable. */
hashtable_t *ht_create(int size) {

	hashtable_t *hashtable = NULL;
	int i;

	if (size < 1) return NULL;

	/* Allocate the table itself. */
	if ((hashtable = (hashtable_t*)malloc(sizeof(hashtable_t))) == NULL) {
		return NULL;
	}

	/* Allocate pointers to the head nodes. */
	if ((hashtable->table = (entry_s**)malloc(sizeof(entry_t *)* size)) == NULL) {
		return NULL;
	}
	for (i = 0; i < size; i++) {
		hashtable->table[i] = NULL;
	}

	hashtable->size = size;

	return hashtable;
}

/* Hash a string for a particular hash table. */
int ht_hash(hashtable_t *hashtable, char *key) {

	unsigned long int hashval = 0;
	int i = 0;

	/* Convert our string to an integer */
	while (hashval < 64 && i < strlen(key)) {
		hashval = hashval << 8;
		hashval += key[i];
		i++;
	}

	return hashval % hashtable->size;
}

/* Create a key-value pair. */
entry_t *ht_newpair(char *key, int value, int count) {
	entry_t *newpair;

	if ((newpair = (entry_t*)malloc(sizeof(entry_t))) == NULL) {
		return NULL;
	}

	if ((newpair->key = strdup(key)) == NULL) {
		return NULL;
	}

	if ((newpair->value = value) == -1) {
		return NULL;
	}
	
	if ((newpair->count = count) == -1) {
		return NULL;
	}

	newpair->next = NULL;

	return newpair;
}

/* Insert a key-value pair into a hash table. */
void ht_set(hashtable_t *hashtable, char *key, int value, int count) {
	int bin = 0;
	entry_t *newpair = NULL;
	entry_t *next = NULL;
	entry_t *last = NULL;

	bin = ht_hash(hashtable, key);

	next = hashtable->table[bin];

	while (next != NULL && next->key != NULL && strcmp(key, next->key) > 0) {
		last = next;
		next = next->next;
		next->count = count;
	}

	/* There's already a pair.  Let's replace that string. */
	if (next != NULL && next->key != NULL && strcmp(key, next->key) == 0) {

		//free( (void*)next->value );
		next->value = value;
		next->count = count;
		/* Nope, could't find it.  Time to grow a pair. */
	}
	else {
		newpair = ht_newpair(key, value, count);

		/* We're at the start of the linked list in this bin. */
		if (next == hashtable->table[bin]) {
			newpair->next = next;
			hashtable->table[bin] = newpair;

			/* We're at the end of the linked list in this bin. */
		}
		else if (next == NULL) {
			last->next = newpair;

			/* We're in the middle of the list. */
		}
		else  {
			newpair->next = next;
			last->next = newpair;
		}
	}
}

/* Retrieve a key-value pair from a hash table. */
int ht_get(hashtable_t *hashtable, char *key) {
	int bin = 0;
	entry_t *pair;

	bin = ht_hash(hashtable, key);

	/* Step through the bin, looking for our value. */
	pair = hashtable->table[bin];


	while (pair != NULL && pair->key != NULL && strcmp(key, pair->key) > 0) {
		pair = pair->next;
	}

	/* Did we actually find anything? */

	//printf("%d\n\n",pair->value);
	if (pair == NULL || pair->key == NULL || strcmp(key, pair->key) != 0) {
		return -1;

	}
	else {
		return pair->value;
	}

}

int ht_get_count(hashtable_t *hashtable, char *key) {
	int bin = 0;
	entry_t *pair;

	bin = ht_hash(hashtable, key);

	/* Step through the bin, looking for our value. */
	pair = hashtable->table[bin];


	while (pair != NULL && pair->key != NULL && strcmp(key, pair->key) > 0) {
		pair = pair->next;
	}

	/* Did we actually find anything? */

	//printf("%d\n\n",pair->value);
	if (pair == NULL || pair->key == NULL || strcmp(key, pair->key) != 0) {
		return -1;

	}
	else {
		return pair->count;
	}

}
/*
typedef struct opcode{
char name[3];
int parm_count;
short compiled;
UT_hash_handle hh;
} opcode;
*/

typedef struct compiled
{
	short op;
	int* parms;
} compiled;



int main(int argc, char *argv[]){
	char op[3];
	int v;
	int c;
	hashtable_t *hashtable = ht_create(64);
	ht_set(hashtable, (char*)&"mov", 0 ,2);
	ht_set(hashtable, (char*)&"lod", 1, 2);
	ht_set(hashtable, (char*)&"add", 2, 2);
	while (1){

		scanf("%s", &op);
		v = ht_get(hashtable, (char*)&op);
		c = ht_get_count(hashtable, (char*)&op);
		printf("code: %d, count: %d\n", v, c);
	} 


	//FILE *program;
	printf("%Opening [%s]\n", argv[1]);
	//program = fopen(argv[1],"w+");


	//fclose(program);
	return 0;
}
