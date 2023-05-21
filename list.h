#ifndef LIST_H_
#define LIST_H_

#include <stdlib.h>
#include <string.h>

struct symtab{
    char* name;
    char* type;
    float fvalue;
    int ivalue;
    struct symtab* next;
};

struct symtab* create_table(char* name, char* type, float fval, int ival);
void add(struct symtab* table, char* name, char* type, float fval, int ival);
int getIVal(struct symtab* table, char* name);
#endif
