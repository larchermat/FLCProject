#ifndef LIST_H_
#define LIST_H_

#include <stdlib.h>
#include <string.h>

#define STRMAX 256

struct symtab {
    char name[STRMAX];
    char type[STRMAX];
    float fvalue;
    int ivalue;
    struct symtab *next;
};

struct symtab *create_table(char *name, char *type, float val);

struct symtab *add(struct symtab *table, char *name, char *type, float val);

int getIVal(struct symtab *table, char *name);

float getFVal(struct symtab *table, char *name);

struct symtab *update_val(struct symtab *table, char *name, float value);

#endif
