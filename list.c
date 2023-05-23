#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "list.h"

struct symtab *create_table(char *name, char *type, float val) {
    struct symtab *table = (struct symtab *) malloc(sizeof(struct symtab));
    strcpy(table->name, name);
    strcpy(table->type, type);
    if (strcmp(type, "int") == 0) {
        table->ivalue = (int) val;
    } else {
        table->fvalue = val;
    }
    table->next = NULL;
    return table;
}

struct symtab *add(struct symtab *table, char *name, char *type, float val) {
    struct symtab *element = create_table(name, type, val);
    if (table == NULL) {
        return element;
    }
    struct symtab *s = table;
    if (strcmp(name, table->name) == 0) {
        printf("Non puoi avere gli stessi nomi");
        exit(1);
    }
    while (s->next != NULL) {
        if (strcmp(name, s->name) == 0) {
            printf("Non puoi avere gli stessi nomi");
            exit(1);
        }
        s = s->next;
    }
    s->next = element;
    return table;
}

int getIVal(struct symtab *table, char *name) {
    if (table == NULL) {
        printf("Errore");
        exit(1);
    }
    if (strcmp(table->name, name) == 0) {
        if (strcmp(table->type, "float") == 0) {
            return (int) table->fvalue;
        }
        return table->ivalue;
    }
    struct symtab *s = table;
    while (s != NULL && strcmp(name, s->name) != 0) {
        s = s->next;
    }
    if (s == NULL) {
        printf("Non è stato trovato niente per %s\n", name);
        exit(1);
    }
    if (strcmp(s->type, "float") == 0) {
        return (int) s->fvalue;
    }
    return s->ivalue;
}

float getFVal(struct symtab *table, char *name) {
    if (table == NULL) {
        printf("Errore");
        exit(1);
    }
    if (strcmp(table->name, name) == 0) {
        if (strcmp(table->type, "int") == 0) {
            return (float) table->ivalue;
        }
        return table->fvalue;
    }
    struct symtab *s = table;
    while (s != NULL && strcmp(name, s->name) != 0) {
        s = s->next;
    }
    if (s == NULL) {
        printf("Non è stato trovato niente per %s\n", name);
        exit(1);
    }
    if (strcmp(s->type, "int") == 0) {
        return (float) s->ivalue;
    }
    return s->fvalue;
}

struct symtab *update_val(struct symtab *table, char *name, float value) {
    if (table == NULL) {
        printf("Errore");
        exit(1);
    }
    if (strcmp(table->name, name) == 0) {
        if (strcmp(table->type, "float") == 0) {
            table->fvalue = value;
        } else {
            table->ivalue = (int) value;
        }
        return table;
    }
    struct symtab *s = table;
    while (s != NULL && strcmp(name, s->name) != 0) {
        s = s->next;
    }
    if (s == NULL) {
        printf("Non è stato trovato niente per %s\n", name);
        exit(1);
    }
    if (strcmp(s->type, "float") == 0) {
        s->fvalue = value;
    } else {
        s->ivalue = (int) value;
    }
    return table;
}

void print_list(struct symtab *table) {
    printf("-----\nPrinting whole table:\n");
    struct symtab *s = table;
    while (s != NULL) {
        if (strcmp(s->type, "float") == 0) {
            printf("%s = %2.2f\n", s->name, s->fvalue);
        } else {
            printf("%s = %d\n", s->name, s->ivalue);
        }
        s = s->next;
    }
    printf("-----\n");
}