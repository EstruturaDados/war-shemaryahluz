#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

int rolarDado() {
    return rand() % 6 + 1;
}

void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\n%s (Atacante) ataca %s (Defensor)\n", atacante->nome, defensor->nome);
    int dadoAtacante = rolarDado();
    int dadoDefensor = rolarDado();
    printf("Dado do atacante: %d\nDado do defensor: %d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        defensor->tropas -= 2;
        atacante->tropas -= 1;
        if (defensor->tropas <= 0) {
            defensor->tropas = 1;
            strcpy(defensor->cor, atacante->cor);
            atacante->tropas -= 1;
        }
    } else {
        atacante->tropas -= 2;
        defensor->tropas -= 1;
    }

    if (atacante->tropas < 0) atacante->tropas = 0;
    if (defensor->tropas < 0) defensor->tropas = 0;

    printf("Status pós-combate:\n%s - Tropas: %d\n%s - Tropas: %d\n",
           atacante->nome, atacante->tropas, defensor->nome, defensor->tropas);
}

int main() {
    srand(time(NULL));

    int n = 5; // número fixo de territórios

    // Alocação dinâmica
    Territorio* mapa = malloc(n * sizeof(Territorio));
    if (!mapa) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    // Inicialização dos territórios pré-definidos
    strcpy(mapa[0].nome, "Oceania");
    strcpy(mapa[0].cor, "Amarelo");
    mapa[0].tropas = 3;

    strcpy(mapa[1].nome, "Equador");
    strcpy(mapa[1].cor, "Azul");
    mapa[1].tropas = 5;

    strcpy(mapa[2].nome, "Asia");
    strcpy(mapa[2].cor, "Verde");
    mapa[2].tropas = 2;

    strcpy(mapa[3].nome, "Europa");
    strcpy(mapa[3].cor, "Cinza");
    mapa[3].tropas = 5;

    strcpy(mapa[4].nome, "America");
    strcpy(mapa[4].cor, "Vermelho");
    mapa[4].tropas = 1;

    printf("Territórios disponíveis:\n");
    for (int i = 0; i < n; i++)
        printf("%d) %s - Cor: %s - Tropas: %d\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);

    int atacanteIdx, defensorIdx; // armazenar os números dos territórios que foi escolhido pelo usuário.
    printf("\nEscolha o território atacante (1 a %d): ", n);
    scanf("%d", &atacanteIdx);
    printf("Escolha o território defensor (1 a %d): ", n);
    scanf("%d", &defensorIdx);

    if (atacanteIdx < 1 || atacanteIdx > n || defensorIdx < 1 || defensorIdx > n || atacanteIdx == defensorIdx) {
        printf("Índices inválidos.\n");
        free(mapa);
        return 1;
    }

    atacar(&mapa[atacanteIdx - 1], &mapa[defensorIdx - 1]);// para acessar o número correspondente no vetor dinnâmico dos territórios.

    printf("\nTerritórios após o ataque:\n");
    for (int i = 0; i < n; i++)
        printf("%d) %s - Cor: %s - Tropas: %d\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
 
    free(mapa);
    return 0;
}