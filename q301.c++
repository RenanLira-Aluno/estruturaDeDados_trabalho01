
#include <stdlib.h>
#include <string.h>
#include <cctype>
#include <stdio.h>

typedef struct pilha
{
    char *v;
    int topo, max;
} *Pilha;

// função para criar uma pilha
Pilha pilha(int max)
{
    Pilha p = (Pilha)malloc(sizeof(struct pilha));
    p->v = (char *)malloc(max * sizeof(char));
    p->topo = 0;
    p->max = max;
    return p;
}

// função para desempilhar um caractere da pilha
char desempilha(Pilha p)
{
    if (p->topo > 0)
    {
        return p->v[--p->topo];
    }
    return '\0'; // retorne o caractere nulo se a pilha estiver vazia
}

// função para empilhar um caractere na pilha
void empilha(char c, Pilha p)
{
    if (p->topo < p->max)
    {
        p->v[p->topo++] = c;
    }
}

// função para verificar se a pilha está vazia
int vaziap(Pilha p)
{
    return p->topo == 0;
}

// função para retornar o caractere no topo da pilha
char topo(Pilha p)
{
    if (!vaziap(p))
    {
        return p->v[p->topo - 1];
    }
    return '\0'; // Retorna o caractere nulo se a pilha estiver vazia
}

// função para destruir a pilha
void destroip(Pilha p)
{
    free(p->v);
    p->topo = 0;
    p->max = 0;
}

// figura 3.5
int prio(char o)
{
    switch (o)
    {
    case '(':
        return 0;
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    }

    return -1;
}

// figura 3.6
char *posfixa(char *e)
{
    static char s[256];
    int j = 0;
    Pilha P = pilha(256);

    for (int i = 0; e[i]; i++)
    {
        if (e[i] == '(')
            empilha('(', P);
        else if (isdigit(e[i]))
            s[j++] = e[i];
        else if (strchr("+-*/", e[i]))
        {
            while (!vaziap(P) && prio(topo(P)) >= prio(e[i]))
                s[j++] = desempilha(P);
            empilha(e[i], P);
        }
        else if (e[i] == ')')
        {
            while (topo(P) != '(')
                s[j++] = desempilha(P);
            desempilha(P);
        }
    }
    while (!vaziap(P))
        s[j++] = desempilha(P);
    s[j] = '\0';
    destroip(P);

    return s;
}

// figura 3.8
int valor(char *e)
{
    Pilha P = pilha(256);
    for (int i = 0; e[i]; i++)
    {
        if (isdigit(e[i]))
            empilha(e[i] - '0', P);
        else
        {
            int y = desempilha(P);
            int x = desempilha(P);
            switch (e[i])
            {
            case '+':
                empilha(x + y, P);
                break;
            case '-':
                empilha(x - y, P);
                break;
            case '*':
                empilha(x * y, P);
                break;
            case '/':
                empilha(x / y, P);
                break;
            }
        }
    }
    int z = desempilha(P);
    destroip(P);
    return z;
}

int main()
{

    char *e = "(2+3)*4";
    char *p = posfixa(e);
    printf("%s = %d\n", p, valor(p));
    return 0;
}