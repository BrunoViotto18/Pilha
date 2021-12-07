#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>

struct Node
{
    int num;
    struct Node *prox;
};

typedef struct Node node;
int tam;

int menu(void);
void inicia(node *PILHA);
void opcao(node *PILHA, int op);
bool vazia(node *PILHA);
node* aloca();
void exibe(node *PILHA);
void libera(node *PILHA);
void push(node *PILHA);
node* pop(node *PILHA);


int main(void)
{
    setlocale(LC_ALL, "");

    node *PILHA = (node*)malloc(sizeof(node));
    if (!PILHA)
    {
        printf("Sem memória disponível!\n");
        exit(1);
    }
    else
    {
        inicia(PILHA);
        int opt;
        do
        {
            opt = menu();
            opcao(PILHA, opt);
        } while (opt);
        free(PILHA);
    }

    return 0;
}

void inicia(node *PILHA)
{
    PILHA->prox = NULL;
    tam = 0;
}

int menu(void)
{
    int opt;
    printf("Escolha a opção\n");
    printf("0. Sair\n");
    printf("1. Zerar PILHA\n");
    printf("2. Exibir PILHA\n");
    printf("3. PUSH\n");
    printf("4. POP\n");
    printf("Opção: ");
    fflush(stdin);
    scanf("%d", &opt);
    return opt;
}

void opcao(node *PILHA, int op)
{
    node *tmp;
    switch(op)
    {
        case 0:
            libera(PILHA);
            break;
        case 1:
            libera(PILHA);
            inicia(PILHA);
            break;
        case 2:
            exibe(PILHA);
            break;
        case 3:
            push(PILHA);
            break;
        case 4:
            tmp = pop(PILHA);
            if (tmp != NULL)
            {
                printf("Retirado: %3d\n\n", tmp->num);
            }
            free(tmp);
            break;
        default:
            printf("Comando inválido!\n\n");
            break;
    }
}

bool vazia(node *PILHA)
{
    if (PILHA->prox == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

node* aloca()
{
    node *novo = (node*)malloc(sizeof(node));
    if (!novo)
    {
        printf("Sem memória disponível!\n");
        exit(1);
    }
    else
    {
        printf("Novo elemento: ");
        fflush(stdin);
        scanf("%d", &novo->num);
        return novo;
    }
}

void exibe(node *PILHA)
{
    if (vazia(PILHA))
    {
        printf("PILHA vazia!\n\n");
        return;
    }

    node *tmp;
    tmp = PILHA->prox;

    printf("PILHA: ");
    while(tmp != NULL)
    {
        printf("%5d", tmp->num);
        tmp = tmp->prox;
    }
    printf("\n");

    printf("       ");
    int count;
    for(count = 0; count < tam; count++)
    {
        printf("%5c", '^');
    }

    printf("\nOrdem: ");
    for(count = 0; count < tam; count++)
    {
        printf("%5d", count);
    }
    printf("\n\n");
}

void libera(node *PILHA)
{
    if (!vazia(PILHA))
    {
        node *proxNode, *atual;
        atual = PILHA->prox;
        while (atual != NULL)
        {
            proxNode = atual->prox;
            free(atual);
            atual = proxNode;
        }
    }
}

void push(node *PILHA)
{
    node *novo = aloca();
    novo->prox = NULL;

    if (vazia(PILHA))
    {
        PILHA->prox = novo;
    }
    else
    {
        node *tmp = PILHA->prox;
        while(tmp->prox != NULL)
        {
            tmp = tmp->prox;
        }
        tmp->prox = novo;
    }
    tam++;
}

node* pop(node *PILHA)
{
    if (PILHA->prox == NULL)
    {
        printf("PILHA já está vazia!\n\n");
        return NULL;
    }
    else
    {
        node *ultimo = PILHA->prox, *penultimo = PILHA;

        while(ultimo->prox != NULL)
        {
            penultimo = ultimo;
            ultimo = ultimo->prox;
        }
        penultimo->prox = NULL;
        tam--;
        return ultimo;
    }
}
