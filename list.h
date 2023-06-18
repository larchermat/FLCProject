#ifndef LIST_H_
#define LIST_H_

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define STRMAX 256

struct symtab {
    char name[STRMAX];
    char type[STRMAX];
    float fvalue;
    int ivalue;
    bool bvalue;
    struct symtab *next;
};


struct symtab *create_table(char *name, char *type, char *val);

struct symtab *add_new(struct symtab *table, char *name, char *type, char *val);

float getFVal(struct symtab *table, char *name);

bool getBVal(struct symtab *table, char *name);

struct symtab *update_val(struct symtab *table, char *name, char *value);

void print_list(struct symtab *table);

void print_element(struct symtab *table, char *name);

void empty_check(struct symtab *table);

void dup_check(struct symtab *table, char *name);

void type_check(char* type, char* value);

#endif
