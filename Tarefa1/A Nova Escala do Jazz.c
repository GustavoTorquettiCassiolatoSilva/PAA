#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int E = 0, A = 0;

    // Recebe os valores da escala e acorde, e caso seja maior maior ou menor que 2 entradas, finaliza o programa para evitar erros
    if (scanf("%d %d", &E, &A) != 2) return 0;

    // Alocação dinâmica do vetor X na memória
    int *X = malloc(A * sizeof(int));
    // Recebe as posições no vetor X
    for (int i = 0; i < A; i++) scanf("%d", &X[i]);

    // Valor do número de divisões/blocos
    int div = E / A;

    // Vetor usado para marcar blocos ocupados
    char *Blocos = malloc(A * sizeof(char));

    // Valor booleano utilizado para a resposta final (Se possivel, S, caso contrário, N)
    int possible = 0;

    // LÓGICA
    // Testa todas as rotações possíveis de 0 até div-1 (pois após isso o algoritmo estaria se repetindo)
    for (int x = 0; x < div; x++) {
        memset(Blocos, 0, A); // Isso é necessário para resetar o vetor Blocos e iniciar a comparação novamente
        int valido = 1;

        // Passa por todas as A notas do acorde
        for (int i = 0; i < A; i++) { 
            int t = X[i] - x; // X[i] é a posição original da nota e x é o deslocamento atual 
            if (t < 0) t += E; // Não é possível dar posição negativa, pois é um circulo
            int pos = t / div; // Verifica qual bloco a nota está nessa rotação
            if (Blocos[pos]) // Se já existe uma nota nesse bloco, quebra e dá como impossível.
            { 
                valido = 0; 
                break; 
            }
            Blocos[pos] = 1; // Se não existe, adiciona 1 ao vetor de blocos.
        }
        // Ao final de todo o processo, se nessa rotação deu tudo certo, retorna true e quebra o algoritmo
        if (valido) {
            possible = 1;
            break;
        }
    }

    // Imprime se é possível ou não
    if (possible) printf("S\n");
    else printf("N\n");

    // Libera memória alocada dinamicamente
    free(X);
    free(Blocos);
    return 0;
}

/* 
Lógica: Como E é divisível por A, podemos dividir a escala em div (E/A) blocos iguais.
Então, ao decorrer do código, é necessário verificar quantas notas existem por bloco.
Caso algum bloco tenha uma quantidade diferente de 1, o valor booleano será falso, imprimindo "N", caso todos os blocos tenham somente 1 acorde, o valor retornado será true, imprimindo "S"

E como a verificação é feita:
Primeiro a escala é dividida em blocos iguais de tamanho div (pois após isso, a rotação se torna redundante), começando na posição 0.
Depois esses blocos são rotacionados de 0 até div-1, e em cada rotação é verificado se todos contêm exatamente 1 nota.

Caso após uma rotação completa, em algum momento ocorra a situação desejada (1 nota em cada bloco), o algoritmo se encerra e retorna verdadeiro. 
Se após todo o algoritmo seja rodado, e todos os casos rotacionados, ainda não haver nenhuma situação onde todos os blocos somente contém 1 acorde, o caso é impossível, retornando falso.

Complexidade: O(E), pois, na pior das hipóteses, ocorrerá div * A comparações, que é igual à E.
*/
