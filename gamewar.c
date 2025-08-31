#include <stdio.h>
#include <string.h>

typedef struct {
    char nome [30];
    char cor [10];
    int tropas;
} Territorio;

int main() {
    Territorio territorios[5];
    
    int i;

    for (i = 0; i < 5; i++) {
        printf("\n--- Cadastro do Território %d ---\n", i + 1);
       
        printf("Digite a cor do território:\n");
        scanf("%9s", territorios[i].cor);

        printf("Digite o nome do território:\n");
        scanf("%29s", territorios[i].nome);

        printf("Digite o número de tropas:\n");
            scanf("%d", &territorios[i].tropas);
        
    }
    printf("\n-- Territórios Salvos --\n");
    for (i = 0; i < 5; i++) {

        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor: %s\n", territorios[i].cor);
        printf("Tropas: ");
        
        printf("\n");
    }
    return 0;
}