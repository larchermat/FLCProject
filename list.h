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
 * Crea e ritorna un oggetto symtab con le caratteristiche specificate
 * @param name nome della variabile da aggiungere
 * @param type tipo della variabile da aggiungere
 * @param val valore della variabile da aggiungere
 * @return puntatore ad un oggetto symtab contenente una variabile con le caratteristiche specificate e il puntatore
 * next = null
 */
struct symtab *create_table(char *name, char *type, char *val);

/**
 * Aggiunge un nuovo elemento alla esistente lista/symbol table passata in input o ne crea una nuova se quella passata
 * e' vuota
 * @param table symbol table preesistente (null se vuota)
 * @param name nome della variabile da aggiungere
 * @param type tipo della variabile da aggiungere
 * @param val valore della variabile da aggiungere
 * @return puntatore alla testa della symbol table aggiornata; manda il sistema in errore nel caso esistesse gia' un
 * elemento della symbol table con ID name
 */
struct symtab *add_new(struct symtab *table, char *name, char *type, char *val);

/**
 * Ritorna il valore float associato alla variabile con ID name
 * @param table la symbol table
 * @param name ID della variabile ricercata
 * @return il valore float della variabile ricercata; se questa fosse di tipo int, il valore verra' castato a float,
 * mentre nel caso in cui fosse di tipo bool o la lista fosse vuota allora il sistema andra' in errore; 0 se la
 * variabile non viene trovata
 */
float getFVal(struct symtab *table, char *name);

/**
 * Ritorna il valore bool associato alla variabile con ID name
 * @param table la symbol table
 * @param name ID della variabile ricercata
 * @return il valore booleano della variabile ricercata; se questa fosse di tipo int o float o la symbol table fosse
 * vuota, il sistema andra' in errore; 0 se la variabile non viene trovata
 */
bool getBVal(struct symtab *table, char *name);

/**
 * Aggiorna il valore associato alla variabile con ID name
 * @param table la symbol table
 * @param name ID della variabile da aggiornare
 * @param value valore della variabile da aggiornare
 * @return puntatore alla testa della symbol table aggiornata; il sistema va in errore nel caso in cui la table fosse
 * vuota o nel caso in cui il tipo fornito non corrispondesse al tipo della variabile, a parte per i valori flaot e int
 * che vengono castati
 */
struct symtab *update_val(struct symtab *table, char *name, char *value);

/**
 * Stampa in output tutta la symbol table
 * @param table la symbol table
 */
void print_list(struct symtab *table);

/**
 * Stampa in output una singola variabile contenuta nella symbol table, se trovato; il sistema va in errore nel caso in
 * cui la table fosse vuota
 * @param table la symbol table
 * @param name ID della variabile
 */
void print_element(struct symtab *table, char *name);

/**
 * Controlla se la table sia vuota, e nel caso lo fosse manda il sistema in errore
 * @param table la symbol table
 */
void empty_check(struct symtab *table);

/**
 * Controlla se esista gia' un elemento della symbol table con ID name, e in caso positivo manda il sistema in errore
 * @param table la symbol table
 * @param name ID della variabile da cercare
 */
void dup_check(struct symtab *table, char *name);

/**
 * Controlla che il tipo del valore fornito corrisponda a type, in caso negativo manda il sistema in errore
 * @param type stringa che indica il tipo
 * @param value valore il cui tipo va controllato
 */
void type_check(char* type, char* value);

#endif
