#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct stazione stazione;
#define DIMENSIONE_ARRAY 513
#define NUMERO_MAX_MACCHINE 512

struct node{
    int dato;
    int max_autonomia;
    int numero_passi;
    int stazione_precedente;
    struct node *next;
};
struct node *inserisci_testa(struct node *head, int distanza){
    struct node *new_head = (struct node *) malloc(sizeof(struct node));
    new_head->dato = distanza;
    new_head->next = head;
    return new_head;
}
struct node *inverti_lista(struct node *head){
    struct node *prev = NULL;
    struct node *current = head;
    struct node *next = NULL;
    while(current != NULL){
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    return prev;
}
struct node *inserisci_ordinato(struct node *testa, int nuova_distanza, int autonomia_max) {
    struct node *nuovo_nodo = (struct node *)malloc(sizeof(struct node));
    nuovo_nodo->dato = nuova_distanza;
    nuovo_nodo->max_autonomia = autonomia_max;
    nuovo_nodo->numero_passi = 100000;
    nuovo_nodo->stazione_precedente = 0;
    nuovo_nodo->next = NULL;

    if (testa == NULL || nuova_distanza < testa->dato) {
        nuovo_nodo->next = testa;
        return nuovo_nodo;
    }
    struct node *corrente = testa;
    while (corrente->next != NULL && corrente->next->dato < nuova_distanza) {
        corrente = corrente->next;
    }
    nuovo_nodo->next = corrente->next;
    corrente->next = nuovo_nodo;
    return testa;
}
void stampa_lista(struct node *testa) {
    struct node *corrente = testa;

    while (corrente != NULL) {
        printf("%d ", corrente->dato);
        corrente = corrente->next;
    }
}
struct stazione{
    int distanza;
    int num_auto;
    int autonomia[DIMENSIONE_ARRAY];
    struct stazione *left;
    struct stazione *right;
};

struct stazione* aggiungi_root(int dist, int numero_auto,  const int autonomie[]){
    struct stazione *root;
    root = malloc(sizeof(struct stazione));
    root->distanza = dist;
    root->num_auto = numero_auto;

    for(int i = 0; i < numero_auto; i++){
        root->autonomia[i] = autonomie[i];
    }
    root->left = NULL;
    root->right = NULL;
    printf("aggiunta\n");
    return root;
}


void aggiungi_stazione(struct stazione **binary_tree, int dist, int num_auto, int autonomia[]) {
    struct stazione *tmp = NULL;

    if(!(*binary_tree)) {
        tmp = (struct stazione *)malloc(sizeof(struct stazione));
        tmp->left = NULL;
        tmp->right = NULL;
        tmp->distanza = dist;
        tmp->num_auto = num_auto;
        for(int i = 0; i < NUMERO_MAX_MACCHINE; i++){
            tmp->autonomia[i] = 0;
        }
        if(num_auto != 0){
            for(int i = 0; i < num_auto; i++){
                tmp->autonomia[i] = autonomia[i];
            }
        }

        *binary_tree = tmp;
        printf("aggiunta\n");
        return;
    }
    if(dist < (*binary_tree)->distanza) {
        aggiungi_stazione(&(*binary_tree)->left, dist, num_auto, autonomia);
    } else if(dist > (*binary_tree)->distanza) {
        aggiungi_stazione(&(*binary_tree)->right, dist, num_auto, autonomia);
    }
    if(dist == (*binary_tree)->distanza){
        printf("non aggiunta\n");
        return;
    }
}

struct stazione *trova_stazione(struct stazione *binary_tree, int dist) {
    if (binary_tree == NULL) {
        return NULL;
    }

    if (dist == binary_tree->distanza) {
        return binary_tree;
    } else if (dist < binary_tree->distanza) {
        return trova_stazione(binary_tree->left, dist);
    } else if (dist > binary_tree->distanza) {
        return trova_stazione(binary_tree->right, dist);
    }
    return NULL;
}

int cerca_stazione(struct stazione **binary_tree, int dist) {
    if(!(*binary_tree)) {
        return 0;
    }
    if(dist == (*binary_tree)->distanza) {
        return 1;
    } else if(dist < (*binary_tree)->distanza) {
        return cerca_stazione(&((*binary_tree)->left), dist);
    } else if(dist > (*binary_tree)->distanza){
        return cerca_stazione(&((*binary_tree)->right), dist);
    }
    return 0;
}

struct stazione* find_minimum(struct stazione *root)
{
    if(root == NULL)
        return NULL;
    else if(root->left != NULL)
        return find_minimum(root->left);
    return root;
}
struct stazione *demolisci_root(struct stazione *root, int distanza) {
    if (root == NULL) {
        printf("non demolita\n");
        return NULL;
    }
    struct stazione *current = root;
    struct stazione *parent = NULL;


    if (root->distanza == distanza) {
        if (root->left == NULL && root->right == NULL) {
            free(root);
            printf("demolita\n");
            return NULL;
        }
        if (root->left == NULL) {
            root = root->right;
            free(current);
            printf("demolita\n");
            return root;
        } else if (root->right == NULL) {
            root = root->left;
            free(current);
            printf("demolita\n");
            return root;
        } else {
            parent = root;
            struct stazione *successore = root->right;

            while (successore->left != NULL) {
                parent = successore;
                successore = successore->left;
            }


            for (int k = 0; k < root->num_auto; k++) {
                root->autonomia[k] = 0;
            }
            root->distanza = successore->distanza;
            root->num_auto = successore->num_auto;
            for (int h = 0; h < successore->num_auto; h++) {
                root->autonomia[h] = successore->autonomia[h];
            }
            if (parent->distanza != root->distanza) {
                parent->left = successore->right;
            } else {
                root->right = successore->right;
            }
            free(successore);
            printf("demolita\n");
            return root;
        }
    }
    return NULL;
}

void demolisci_stazione(struct stazione *root, int distanza) {
    if (root == NULL) {
        printf("non demolita\n");
        return;
    }
    struct stazione* current = root;
    struct stazione* parent = NULL;


    while (current != NULL) {
        if (distanza < current->distanza) {
            parent = current;
            current = current->left;
        } else if (distanza > current->distanza) {
            parent = current;
            current = current->right;
        } else {
            if(current->left == NULL && current->right == NULL){
                if(current->distanza > parent->distanza){
                    parent->right = NULL;
                }else{
                    parent->left = NULL;
                }
                free(current);
                printf("demolita\n");
                return;
            }

            if(current->left == NULL) {
                if(parent->distanza > current->distanza){
                    parent->left = current->right;
                }else{
                    parent->right = current->right;
                }
                free(current);
                printf("demolita\n");
                return;
            }else if(current->right == NULL){
                if(parent->distanza > current->distanza){
                    parent->left = current->left;
                }else{
                    parent->right = current->left;
                }
                free(current);
                printf("demolita\n");
                return;
            }else{
                parent = current;
                struct stazione *successore = current->right;

                while (successore->left != NULL){
                    parent = successore;
                    successore = successore->left;
                }
                for (int i = 0; i < current->num_auto; i++) {
                    current->autonomia[i] = 0;
                }
                current->distanza = successore->distanza;
                current->num_auto = successore->num_auto;
                for (int i = 0; i < successore->num_auto; i++) {
                    current->autonomia[i] = successore->autonomia[i];
                }
                if(parent != current){
                    parent->left = successore->right;
                }else{
                    current->right = successore->right;
                }

                free(successore);
                printf("demolita\n");
                return;
            }
        }
    }

    printf("non demolita\n");
}

void aggiungi_auto(struct stazione *binary_tree, int distanza, int autonomia){

    if (!binary_tree) {
        printf("non aggiunta\n");
        return;
    }
    if (distanza < binary_tree->distanza) {
        aggiungi_auto(binary_tree->left, distanza, autonomia);
    } else if (distanza > binary_tree->distanza) {
        aggiungi_auto(binary_tree->right, distanza, autonomia);
    } else {
        if (binary_tree->num_auto < NUMERO_MAX_MACCHINE) {
            binary_tree->autonomia[binary_tree->num_auto] = autonomia;
            binary_tree->num_auto++;
            printf("aggiunta\n");
            return;
        } else {
            printf("non aggiunta\n");
            return;
        }
    }
}

void rottama_auto(struct stazione *binary_tree, int distanza, int autonomia){

    int j = 0;
    if (binary_tree == NULL) {
        printf("non rottamata\n");
        return;
    }
    if (distanza < binary_tree->distanza) {
        rottama_auto(binary_tree->left, distanza, autonomia);
    } else if (distanza > binary_tree->distanza) {
        rottama_auto(binary_tree->right, distanza, autonomia);
    } else {
        for (int i = 0; i < binary_tree->num_auto; i++) {
            if (binary_tree->autonomia[i] == autonomia) {
                for (j = i; j < binary_tree->num_auto - 1; j++) {
                    binary_tree->autonomia[j] = binary_tree->autonomia[j + 1];
                }
                binary_tree->autonomia[j+1] = 0;
                binary_tree->num_auto--;
                printf("rottamata\n");
                return;
            }
        }
        printf("non rottamata\n");
        return;
    }
}

int trova_autonomia_maggiore(struct stazione *stazione){
    if(stazione == NULL || stazione->num_auto == 0){
        return 0;
    }
    int max_autonomia = stazione->autonomia[0];

    for (int i = 1; i < stazione->num_auto; i++) {
        if(stazione->autonomia[i] > max_autonomia){
            max_autonomia = stazione->autonomia[i];
        }
    }
    return max_autonomia;
}


struct node *memorizza_stazioni (struct stazione *current,int distanza_stazione_partenza, int distanza_stazione_arrivo, struct node *lista_stazioni){
    if (current == NULL) {
        return lista_stazioni;
    }
    if(distanza_stazione_partenza > distanza_stazione_arrivo){
        if(current->distanza <= distanza_stazione_partenza && current->distanza >= distanza_stazione_arrivo){
            int max_autonomia = trova_autonomia_maggiore(current);
            lista_stazioni = inserisci_ordinato(lista_stazioni, current->distanza, max_autonomia);
        }
        if(current->distanza <= distanza_stazione_partenza){
            lista_stazioni = memorizza_stazioni(current->right, distanza_stazione_partenza, distanza_stazione_arrivo, lista_stazioni);
        }
        if(current->distanza >= distanza_stazione_arrivo){
            lista_stazioni = memorizza_stazioni(current->left, distanza_stazione_partenza, distanza_stazione_arrivo, lista_stazioni);
        }
        return lista_stazioni;
    }
    if(distanza_stazione_partenza < distanza_stazione_arrivo){
        if (distanza_stazione_partenza <= current->distanza && current->distanza <= distanza_stazione_arrivo) {
            int max_autonomia = trova_autonomia_maggiore(current);
            lista_stazioni = inserisci_ordinato(lista_stazioni, current->distanza, max_autonomia);
        }

        if(current->distanza >= distanza_stazione_partenza){
            lista_stazioni = memorizza_stazioni(current->left, distanza_stazione_partenza, distanza_stazione_arrivo, lista_stazioni);
        }

        if(current->distanza <= distanza_stazione_arrivo){
            lista_stazioni = memorizza_stazioni(current->right, distanza_stazione_partenza, distanza_stazione_arrivo, lista_stazioni);
        }

        return lista_stazioni;
    }
    return NULL;
}
struct node *pianifica_percorso(struct stazione *binary_tree, int distanza1, int distanza2){
    struct node *lista_stazioni = NULL;
    struct node *corrente = NULL;
    struct node *temp = NULL;
    lista_stazioni = memorizza_stazioni(binary_tree,distanza1, distanza2, lista_stazioni);
    if(distanza1 > distanza2){
        lista_stazioni = inverti_lista(lista_stazioni);
    }
    temp = lista_stazioni;
    if(distanza1 > distanza2){
        while (lista_stazioni != NULL && lista_stazioni->dato != distanza2) {

            corrente = lista_stazioni;
            int max_autonomia = corrente->max_autonomia;
            if (corrente->dato == distanza1) {
                corrente = corrente->next;
                while (corrente != NULL && corrente->dato >= lista_stazioni->dato - max_autonomia) {
                    corrente->numero_passi = 1;
                    corrente->stazione_precedente = lista_stazioni->dato;
                    corrente = corrente->next;
                }
            } else {
                corrente = corrente->next;
                while (corrente != NULL && corrente->dato >= lista_stazioni->dato - max_autonomia) {
                    if (lista_stazioni->numero_passi + 1 > corrente->numero_passi) {
                        corrente = corrente->next;
                    } else {
                        if(lista_stazioni->numero_passi + 1 == corrente->numero_passi){
                            corrente->stazione_precedente = lista_stazioni->dato;
                            corrente = corrente->next;
                        }else{
                            corrente->numero_passi = 1 + lista_stazioni->numero_passi;
                            corrente->stazione_precedente = lista_stazioni->dato;
                            corrente = corrente->next;
                        }
                    }
                }
            }
            lista_stazioni = lista_stazioni->next;
        }
        if(lista_stazioni->numero_passi == 100000){
            printf("nessun percorso\n");
            return NULL;
        } else{
            struct node *lista_finale = NULL;
            lista_finale = inserisci_testa(lista_finale, lista_stazioni->dato);
            int val = lista_stazioni->stazione_precedente;
            lista_stazioni = inverti_lista(temp);
            while(val != distanza1){
                while(lista_stazioni->dato != val){
                    lista_stazioni = lista_stazioni->next;
                }
                lista_finale = inserisci_testa(lista_finale, val);
                val = lista_stazioni->stazione_precedente;
            }
            lista_finale = inserisci_testa(lista_finale, distanza1);
            return lista_finale;
        }
    }else{
        while (lista_stazioni != NULL && lista_stazioni->dato != distanza2) {

            corrente = lista_stazioni;
            int max_autonomia = corrente->max_autonomia;
            if (corrente->dato == distanza1) {
                corrente = corrente->next;
                while (corrente != NULL && corrente->dato <= lista_stazioni->dato + max_autonomia) {
                    corrente->numero_passi = 1;
                    corrente->stazione_precedente = lista_stazioni->dato;
                    corrente = corrente->next;
                }
            } else {
                corrente = corrente->next;
                while (corrente != NULL && corrente->dato <= lista_stazioni->dato + max_autonomia) {
                    if (lista_stazioni->numero_passi + 1 >= corrente->numero_passi) {
                        corrente = corrente->next;
                    } else {
                        corrente->numero_passi = 1 + lista_stazioni->numero_passi;
                        corrente->stazione_precedente = lista_stazioni->dato;
                        corrente = corrente->next;
                    }
                }
            }
            lista_stazioni = lista_stazioni->next;
        }
        if(lista_stazioni->numero_passi == 100000){
            printf("nessun percorso\n");
            return NULL;
        } else{
            struct node *lista_finale = NULL;
            lista_finale = inserisci_testa(lista_finale, lista_stazioni->dato);
            int val = lista_stazioni->stazione_precedente;
            lista_stazioni = inverti_lista(temp);
            while(val != distanza1){
                while(lista_stazioni->dato != val){
                    lista_stazioni = lista_stazioni->next;
                }
                lista_finale = inserisci_testa(lista_finale, val);
                val = lista_stazioni->stazione_precedente;
            }
            lista_finale = inserisci_testa(lista_finale, distanza1);
            return lista_finale;
        }
    }
}

int main() {
    struct stazione *stazione_tree = NULL;
    char comando[30];
    int distanza, numero_auto;
    int autonomie[DIMENSIONE_ARRAY];
    int distanza2;
    int autonomia;
    int stazione1 = 0;
    int stazione2 = 0;
    struct node *head = NULL;
    int i = 1;

    while (scanf("%s", comando)!= EOF) {

        if (strcmp("aggiungi-stazione", comando) == 0) {
            if(scanf("%d %d", &distanza, &numero_auto) == 2){
                for(i = 0; i < numero_auto; i++){
                    if(scanf("%d", &autonomie[i]) == 1){
                        continue;
                    }
                }
                if(stazione_tree == NULL){
                    stazione_tree = aggiungi_root(distanza, numero_auto, autonomie);
                }else{
                    aggiungi_stazione(&stazione_tree, distanza, numero_auto, autonomie);
                }
            }else{
                return 0;
            }
        } else if (strcmp("demolisci-stazione", comando) == 0) {
            if(scanf("%d", &distanza) == 1){
                if(stazione_tree != NULL && stazione_tree->distanza == distanza){
                    stazione_tree = demolisci_root(stazione_tree, distanza);
                }else{
                    demolisci_stazione(stazione_tree, distanza);
                }

            }

        } else if (strcmp("aggiungi-auto", comando) == 0) {
            if(scanf("%d %d", &distanza, &autonomia) == 2)
                aggiungi_auto(stazione_tree, distanza, autonomia);

        } else if (strcmp("rottama-auto", comando) == 0) {
            if(scanf("%d %d", &distanza, &autonomia) == 2)
                rottama_auto(stazione_tree, distanza, autonomia);

        } else if (strcmp("pianifica-percorso", comando) == 0) {
            if(scanf("%d %d", &distanza, &distanza2) == 2){
                stazione1 = cerca_stazione(&stazione_tree, distanza);
                stazione2 = cerca_stazione(&stazione_tree, distanza2);
            }

            if(stazione1 == 0 || stazione2 == 0 || distanza == distanza2){
                printf("nessun percorso");
                return 0;
            }
            head = pianifica_percorso(stazione_tree, distanza, distanza2);
            stampa_lista(head);
        }
    }
    return 0;
}
