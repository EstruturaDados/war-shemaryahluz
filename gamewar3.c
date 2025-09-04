#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nome[30], cor[10];
    int tropas;
} Territorio;

void atribuirMissao(char** destino, char* missoes[], int total) {
    int i = rand() % total;
    *destino = malloc(strlen(missoes[i]) + 1);
    if (!*destino) { printf("Erro memória\n"); exit(1); }
    strcpy(*destino, missoes[i]);
}

void exibirMissao(char* missao) { printf("Missão: %s\n", missao); }

int verificarMissao(char* missao, Territorio* mapa, int n) {
    if (strcmp(missao, "Conquistar 3 territórios seguidos") == 0)
        for (int i=0; i<n-2; i++)
            if (strcmp(mapa[i].cor, mapa[i+1].cor) == 0 &&
                strcmp(mapa[i].cor, mapa[i+2].cor) == 0 &&
                strcmp(mapa[i].cor, "Nenhum") != 0)
                return 1;
    else if (strcmp(missao, "Eliminar todas as tropas da cor vermelha") == 0)
        for (int i=0; i<n; i++)
            if (strcmp(mapa[i].cor, "Vermelho") == 0 && mapa[i].tropas > 0)
                return 0;
        else return 1;
    else if (strcmp(missao, "Ter mais tropas que o adversário") == 0) {
        int v=0,a=0;
        for (int i=0; i<n; i++) {
            if (strcmp(mapa[i].cor,"Vermelho")==0) v+=mapa[i].tropas;
            else if (strcmp(mapa[i].cor,"Azul")==0) a+=mapa[i].tropas;
        }
        if (a > v) return 1;
    }
    else if (strcmp(missao, "Conquistar o território 'Fortaleza'") == 0)
        for (int i=0; i<n; i++)
            if (strcmp(mapa[i].nome,"Fortaleza")==0 && strcmp(mapa[i].cor,"Azul")==0)
                return 1;
    else if (strcmp(missao, "Ter pelo menos 10 tropas em um território") == 0)
        for (int i=0; i<n; i++)
            if (mapa[i].tropas >= 10) return 1;
    return 0;
}

void atacar(Territorio* atacante, Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0 || atacante->tropas < 2) {
        printf("Ataque inválido.\n");
        return;
    }
    int dadoA = rand()%6+1, dadoD = rand()%6+1;
    printf("Ataque: %s (%d) vs %s (%d)\n", atacante->nome, dadoA, defensor->nome, dadoD);
    if (dadoA > dadoD) {
        int t = atacante->tropas/2;
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = t;
        atacante->tropas -= t;
        printf("Atacante venceu! Transferiu %d tropas.\n", t);
    } else {
        atacante->tropas--;
        printf("Defensor venceu! Atacante perde 1 tropa.\n");
    }
}

void exibirMapa(Territorio* mapa, int n) {
    printf("\nÍndice\tNome\t\tCor\tTropas\n");
    for (int i=0; i<n; i++)
        printf("%d\t%-15s %-10s %d\n", i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    printf("\n");
}

void liberarMemoria(char* m1, char* m2, Territorio* mapa) {
    free(m1); free(m2); free(mapa);
}

void ataqueAutomático(Territorio* mapa, int n) {
    for (int i=0; i<n; i++)
        if (strcmp(mapa[i].cor,"Azul")==0 && mapa[i].tropas>=2)
            for (int j=0; j<n; j++)
                if (strcmp(mapa[j].cor,"Vermelho")==0) {
                    printf("\nJogador 2 ataca:\n");
                    atacar(&mapa[i], &mapa[j]);
                    return;
                }
    printf("\nJogador 2 não pode atacar.\n");
}

int main() {
    srand(time(NULL));
    char* missoes[] = {
        "Conquistar 3 territórios seguidos",
        "Eliminar todas as tropas da cor vermelha",
        "Ter mais tropas que o adversário",
        "Conquistar o território 'Fortaleza'",
        "Ter pelo menos 10 tropas em um território"
    };
    int n=6;
    Territorio* mapa = calloc(n, sizeof(Territorio));
    if (!mapa) { printf("Erro memória\n"); return 1; }

    strcpy(mapa[0].nome,"Fortaleza"); strcpy(mapa[0].cor,"Vermelho"); mapa[0].tropas=5;
    strcpy(mapa[1].nome,"Colina"); strcpy(mapa[1].cor,"Vermelho"); mapa[1].tropas=3;
    strcpy(mapa[2].nome,"Vale"); strcpy(mapa[2].cor,"Azul"); mapa[2].tropas=4;
    strcpy(mapa[3].nome,"Planície"); strcpy(mapa[3].cor,"Azul"); mapa[3].tropas=6;
    strcpy(mapa[4].nome,"Floresta"); strcpy(mapa[4].cor,"Nenhum"); mapa[4].tropas=0;
    strcpy(mapa[5].nome,"Montanha"); strcpy(mapa[5].cor,"Nenhum"); mapa[5].tropas=0;

    char *missao1=NULL, *missao2=NULL;
    atribuirMissao(&missao1, missoes, 5);
    atribuirMissao(&missao2, missoes, 5);

    printf("Jogador 1 (Vermelho), sua missão:\n");
    exibirMissao(missao1);
    printf("Jogador 2 (Azul) recebeu sua missão.\n");

    int vencedor=0, turno=1;
    while (!vencedor && turno<=50) {
        printf("\n=== Turno %d ===\n", turno);
        exibirMapa(mapa,n);

        int opcao;
        do {
            printf("1-Atacar 2-Verificar missão 3-Sair\nOpção: ");
            scanf("%d",&opcao);
            if (opcao==1) {
                printf("Territórios seus (>=2 tropas):\n");
                for (int i=0; i<n; i++)
                    if (strcmp(mapa[i].cor,"Vermelho")==0 && mapa[i].tropas>=2)
                        printf("%d - %s (%d)\n", i, mapa[i].nome, mapa[i].tropas);
                int a,b;
                printf("Índice atacante: "); scanf("%d",&a);
                if (a<0 || a>=n || strcmp(mapa[a].cor,"Vermelho")!=0 || mapa[a].tropas<2) {
                    printf("Inválido.\n"); continue;
                }
                printf("Territórios inimigos:\n");
                for (int i=0; i<n; i++)
                    if (strcmp(mapa[i].cor,"Azul")==0)
                        printf("%d - %s (%d)\n", i, mapa[i].nome, mapa[i].tropas);
                printf("Índice defensor: "); scanf("%d",&b);
                if (b<0 || b>=n || strcmp(mapa[b].cor,"Azul")!=0) {
                    printf("Inválido.\n"); continue;
                }
                atacar(&mapa[a], &mapa[b]);
                break;
            } else if (opcao==2) {
                if (verificarMissao(missao1,mapa,n)) {
                    printf("Você cumpriu sua missão!\n");
                    vencedor=1; break;
                } else printf("Missão não cumprida.\n");
            } else if (opcao==3) {
                printf("Saindo...\n");
                liberarMemoria(missao1, missao2, mapa);
                return 0;
            } else printf("Opção inválida.\n");
        } while(1);

        if (vencedor) break;

        ataqueAutomático(mapa,n);
        if (verificarMissao(missao2,mapa,n)) {
            printf("Jogador 2 cumpriu sua missão e venceu!\n");
            vencedor=2; break;
        }
        turno++;
    }

    if (!vencedor) printf("Fim do jogo: empate.\n");
    else if (vencedor==1) printf("Jogador 1 venceu!\n");

    liberarMemoria(missao1, missao2, mapa);
    return 0;
}