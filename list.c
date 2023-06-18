#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "list.h"

struct symtab *create_table(char *name, char *type, char *val) {
    struct symtab *table = (struct symtab *) malloc(sizeof(struct symtab));
    strcpy(table->name, name);
    strcpy(table->type, type);
    if (strcmp(type, "int") == 0) {
        table->ivalue = atoi(val);
    } else if (strcmp(table->type, "float") == 0) {
        table->fvalue = atof(val);
    } else {
        if (strcmp(val, "true") == 0) {
            table->bvalue = true;
        } else {
            table->bvalue = false;
        }
    }
    table->next = NULL;
    return table;
}

struct symtab *add_new(struct symtab *table, char *name, char *type, char *val) {
    struct symtab *element = create_table(name, type, val);
    if (table == NULL) {
        return element;
    }
    struct symtab *s = table;
    dup_check(table, name);
    while (s->next != NULL) {
        s = s->next;
    }
    s->next = element;
    return table;
}

float getFVal(struct symtab *table, char *name) {
    empty_check(table);
    if (strcmp(table->name, name) == 0) {
        if (strcmp(table->type, "bool") == 0) {
            fprintf(stderr, "Errore, il tipo di %s e' bool", name);
            exit(1);
        }
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
        return 0;
    }
    if (strcmp(s->type, "bool") == 0) {
        fprintf(stderr, "Errore, il tipo di %s e' bool", name);
        exit(1);
    }
    if (strcmp(s->type, "int") == 0) {
        return (float) s->ivalue;
    }
    return s->fvalue;
}

bool getBVal(struct symtab *table, char *name) {
    empty_check(table);
    if (strcmp(table->name, name) == 0) {
        if (strcmp(table->type, "bool") != 0) {
            fprintf(stderr, "Tipi incompatibili: %s e bool", table->type);
            exit(1);
        }
        return table->bvalue;
    }
    struct symtab *s = table;
    while (s != NULL && strcmp(name, s->name) != 0) {
        s = s->next;
    }
    if (s == NULL) {
        printf("Non è stato trovato niente per %s\n", name);
        return 0;
    }
    if (strcmp(s->type, "bool") != 0) {
        fprintf(stderr, "Tipi incompatibili: %s e bool", s->type);
        exit(1);
    }
    return s->bvalue;
}

struct symtab *update_val(struct symtab *table, char *name, char *value) {
    empty_check(table);
    if (strcmp(table->name, name) == 0) {
        type_check(table->type, value);
        if (strcmp(table->type, "int") == 0) {
            table->ivalue = atoi(value);
        } else if (strcmp(table->type, "float") == 0) {
            table->fvalue = atof(value);
        } else {
            if (strcmp(value, "true") == 0) {
                table->bvalue = true;
            } else {
                table->bvalue = false;
            }
        }
        return table;
    }
    struct symtab *s = table;
    while (s != NULL && strcmp(name, s->name) != 0) {
        s = s->next;
    }
    if (s == NULL) {
        printf("Non è stato trovato niente per %s\n", name);
        return table;
    }
    type_check(s->type, value);
    if (strcmp(s->type, "int") == 0) {
        s->ivalue = atoi(value);
    } else if (strcmp(s->type, "float") == 0) {
        s->fvalue = atof(value);
    } else {
        if (strcmp(value, "true") == 0) {
            s->bvalue = true;
        } else {
            s->bvalue = false;
        }
    }
    return table;
}

void print_list(struct symtab *table) {
    printf("\n-----\nPrinting whole table:\n");
    struct symtab *s = table;
    while (s != NULL) {
        if (strcmp(s->type, "float") == 0) {
            printf("%s = %2.2f\n", s->name, s->fvalue);
        } else if (strcmp(s->type, "int") == 0) {
            printf("%s = %d\n", s->name, s->ivalue);
        } else {
            if (s->bvalue == true) {
                printf("%s = true\n", s->name);
            } else {
                printf("%s = false\n", s->name);
            }
        }
        s = s->next;
    }
    printf("-----\n");
}

void print_element(struct symtab *table, char *name) {
    empty_check(table);
    struct symtab *s = table;
    while (s != NULL && strcmp(name, s->name) != 0) {
        s = s->next;
    }
    if (s == NULL) {
        printf("Elemento %s non trovato\n", name);
    } else {
        if (strcmp(s->type, "float") == 0) {
            printf("%s = %2.2f\n", s->name, s->fvalue);
        } else if (strcmp(s->type, "int") == 0) {
            printf("%s = %d\n", s->name, s->ivalue);
        } else {
            if (s->bvalue == true) {
                printf("%s = true\n", s->name);
            } else {
                printf("%s = false\n", s->name);
            }
        }
    }
}

void empty_check(struct symtab *table) {
    if (table == NULL) {
        fprintf(stderr, "La lista è vuota\n");
        exit(1);
    }
}

void dup_check(struct symtab *table, char *name) {
    empty_check(table);
    struct symtab *s = table;
    while (s != NULL && strcmp(name, s->name) != 0) {
        s = s->next;
    }
    if (s != NULL) {
        fprintf(stderr, "Non puoi avere due variabili con lo stesso nome: %s\n", name);
        exit(1);
    }
}

void type_check(char *type, char *value) {
    if (strcmp(type, "bool") == 0) {
        if (strcmp(value, "true") != 0 && strcmp(value, "false") != 0) {
            fprintf(stderr, "Tipo richiesto bool, valore inserito %s\n", value);
            exit(1);
        }
    } else if (strcmp(value, "true") == 0 || strcmp(value, "false") == 0) {
        fprintf(stderr, "Tipo richiesto %s, valore inserito %s\n", type, value);
        exit(1);
    }
}