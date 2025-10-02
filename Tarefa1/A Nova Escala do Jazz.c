#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Esse código não funciona bem o suficiente, será recriado

// Comentários e explicações no final da página
int mdc(int a, int b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b != 0) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int main()
{
    int E = 0, A = 0;
    
    // Recebe os valores da escala e acorde
    while ((E < 3 || E > 100000) || (A < 3 || A > 100000) || A > E) {
        scanf("%d %d", &E, &A);
    }
    
    // Alocação dinâmica do vetor X na memória
    int *X = malloc(A * sizeof(int));
    
    // Vetor de distâncias entre pontos será o próprio X
    int *Dist = malloc(A * sizeof(int));
    
    // Recebe as posições
    for (int i = 0; i < A; i++) {
        scanf("%d", &X[i]);
        Dist[i] = 0;
    }

    // Valor booleano utilizado para a resposta final
    bool possible = true;
    
    // Valor das divisões
    float div = (int)E/(int)A;
    
// LÓGICA

    // Calcula as distâncias entre os elementos e coloca elas no vetor Dist
    for (int i = 0; i < A - 1; i++)
    {
        Dist[i] = X[i + 1] - X[i];
    }
    Dist[A - 1] = -((X[A - 1] - E) - X[0]);

    // Calcula o mdc de todas as distâncias
    int g = Dist[0];
    for (int i = 1; i < A; ++i) {
        g = mdc(g, Dist[i]);
        if (g == 1) break; //Caso MDC retorne 1, parar
    }

    // Imprime se é possível ou não
    if (g > 1) printf("S\n");
    else printf("N\n");

    // Libera memória alocada dinamicamente
    free(X);
    free(Dist);
    
    return 0;
}

/* 
Lógica: O algoritmo segue a lógica de que, para atingir o resultado desejado, todas as posições devem ter 
um MDC igual e diferente de 1. Isso ocorre pois a existência do MDC à todas as posições significa
a existência de simetria, em porções de tamanho multiplas do MDC

A complexidade do código é de O(A log E), resultante do calculo dos MDCs, que itera A vezes uma 
função de complexidade O(log E)
*/