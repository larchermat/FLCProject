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

/**
 * <b><h3>Deprecated</h3></b>
 */
struct symtab *create_table(char *name, char *type, float val);

struct symtab *create_table_new(char *name, char *type, char *val);

/**
 * <b><h3>Deprecated</h3></b>
 */
struct symtab *add(struct symtab *table, char *name, char *type, float val);

struct symtab *add_new(struct symtab *table, char *name, char *type, char *val);

int getIVal(struct symtab *table, char *name);

float getFVal(struct symtab *table, char *name);

bool getBVal(struct symtab *table, char *name);

/**
 * <b><h3>Deprecated</h3></b>
 */
struct symtab *update_val(struct symtab *table, char *name, float value);

struct symtab *update_val_new(struct symtab *table, char *name, char *value);

void print_list(struct symtab *table);

void print_element(struct symtab *table, char *name);

void empty_check(struct symtab *table);

void dup_check(struct symtab *table, char *name);

void type_check(char* type, char* value);

#endif
