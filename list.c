#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "list.h"

struct symtab* create_table(char* name, char* type, float fval, int ival){
    FILE* file;
    file = fopen("diocan.txt","w");
    fprintf(file, "Riga 7\n");
    fclose(file);
    file = fopen("diocan.txt","w");
    struct symtab* table = (struct symtab*)malloc(sizeof(struct symtab));
    strcpy(table->name,name);
    strcpy(table->type,type);
    fprintf(file, "Riga 11\n");
    if(strcmp(type,"int")){
        table->ivalue = ival;
    }else{
        table->fvalue = fval;
    }
    fprintf(file, "Riga 17\n");
    table->next = NULL;
    fclose(file);
    return table;
}

void add(struct symtab* table, char* name, char* type, float fval, int ival){
    printf("Riga 23");
    struct symtab* element = create_table(name,type,fval,ival);
    printf("Riga 25");
    struct symtab* s = table;
    printf("Riga 27");
    if(strcmp(name,table->name)){
        printf("Dio cane non puoi avere gli stessi nomi");
        exit(1);
    }
    printf("Riga 32");
    while(s->next != NULL){
        if(strcmp(name,s->name)){
            printf("Dio cane non puoi avere gli stessi nomi");
            exit(1);
        }
        s = s->next;
    }
    printf("Riga 40");
    s->next = element;
}

int getIVal(struct symtab* table, char* name){
    FILE* file;
    file = fopen("diocan.txt","w");
    fprintf(file, "Riga 45\n");
    if(table == NULL){
        printf("Mona dio can");
        exit(1);
    }
    fprintf(file, "Riga 50\n");
    if(strcmp(table->name,name)){
        return table->ivalue;
    }
    fprintf(file, "Riga 54\n");
    struct symtab* s = table;
    while(s!=NULL && !strcmp(name,s->name)){
        s = s->next;
    }
    fprintf(file, "Riga 59\n");
    if(s == NULL){
        printf("Non è stato trovato niente");
        exit(1);
    }
    fprintf(file, "Riga 64\n");
    fclose(file);
    return s->ivalue;
}