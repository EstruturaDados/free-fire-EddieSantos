// Desafio Código da Ilha – Edição Free Fire - Nível Mestre Completo

#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Para funções de alocação dinâmica
#include <stdbool.h> // Para usar o tipo bool em C

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.
typedef struct{
    char nome[30];     // Nome do item
    char tipo[20];     // Tipo do item (ex: "arma", "kit", "comida", roupa, etc.)
    int quantidade;    // Quantidade do item armazenados.
    int prioridade;    // Prioridade do item (1 = baixa, 5 = alta)
} Item;

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).
typedef enum {
    ordenar_por_nome = 1,
    ordenar_por_tipo = 2,
    ordenar_por_prioridade = 3
} CriterioOrdenacao;

// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).
#define MAX_ITENS 10 // Capacidade máxima da mochila.
Item mochila[MAX_ITENS]; // Vetor que armazena os itens da mochila.
int numItens = 0; // Quantidade atual de itens inicialmente zero.
int comparacoes = 0; // Contador de comparações para análise de desempenho.
bool ordenadaPorNome = false; // Indica se a mochila esta ordenada por nome.

// DECLARAÇÃO DAS FUNÇÕES (PROTÓTIPOS)
// Informa ao compilador sobre a existência e a "assinatura" das funções
// que serão implementadas mais abaixo.

// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.
void limparTela(); // Função que "Limpa" a tela.

// exibirMenu():
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.
int exibirMenu(); // Função que exibe o menu principal e retorna a opção escolhida.

// inserirItem():
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".
void inserirItem(); // Função para inserir um novo item na mochila.

// removerItem():
// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.
void removerItem(); // Função para remover um item da mochila.

// listarItens():
// Exibe uma tabela formatada com todos os componentes presentes na mochila.
void listarItens(); // Função para listar todos os itens da mochila.

// menuDeOrdenacao():
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).
void menuDeOrdenacao();// Função para exibir o menu de ordenação e ordenar conforme escolha.

// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)
void insertionSort(CriterioOrdenacao criterio); // Função de ordenação por inserção (insertion sort) com critério.

// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.
// Funcao para busca binária por nome.
void buscaBinariaPorNome();

// Função Principal Menu (main)
// O programa inicia sua execução aqui, cotrolando o fluxo principal. 
int main() {
    int opcao;
    // Menu principal com opções:
    do {
        limparTela(); // Limpa a tela para melhor visualização.
        opcao = exibirMenu(); // Exibe o menu e captura a opção do usuário.
        limparTela(); // Limpa a tela antes de executar a opção escolhida.
        switch(opcao){
            // 1. Adicionar um item
            case 1: 
                inserirItem();
                break;
            // 2. Remover um item
            case 2:
                removerItem();
                break;
            // 3. Listar todos os itens
            case 3:
                listarItens();
                break;
            // 4. Ordenar os itens por critério (nome, tipo, prioridade)
            case 4:
                menuDeOrdenacao();
                break;
            // 5. Realizar busca binária por nome
            case 5:
                buscaBinariaPorNome();
                break;
            // 0. Sair
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
        if(opcao != 0) {
            printf("\nPressione ENTER para continuar...");
            getchar(); // Aguarda o usuário pressionar ENTER antes de continuar.
        }
    } while(opcao != 0);
    // A estrutura switch trata cada opção chamando a função correspondente.
    // A ordenação e busca binária exigem que os dados estejam bem organizados.
    return 0;
}
//--- IMPLEMENTAÇÃO DAS FUNÇÕES ---
/**
 * @brief limparTela();
 * @details Simula a limpeza da tela imprimindo várias linhas em branco.
 *          Limpa a tela para melhorar a visualização do menu e das informações.
*/
void limparTela() {
    for(int i = 0; i < 1; i++) { // Imprime várias linhas em branco.
        printf("\n");
    }
}

/**
 * @brief exibirMenu();
 * @details Apresenta o menu principal ao jogador, com destaque para status da ordenação.
 *          Retorna a opção escolhida pelo jogador.
 *          Exibe o menu principal com informações sobre a mochila.
*/
int exibirMenu() { // Retorna a opção escolhida pelo usuário.
    printf("==============================\n");
    printf("  MOCHILA DA ILHA - FREE FIRE\n");
    printf("==============================\n");
    printf("Itens na mochila: %d/%d\n", numItens, MAX_ITENS);
    printf("Ordenada por nome: %s\n", ordenadaPorNome ? "Sim" : "Não");
    printf("------------------------------\n");
    printf("1. Adicionar um item\n");
    printf("2. Remover um item\n");
    printf("3. Listar todos os itens\n");
    printf("4. Ordenar os itens\n");
    printf("5. Buscar item por nome (busca binária)\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
    int op;
    scanf("%d", &op);
    getchar(); // Limpa o enter do buffer
    return op; // Retorna a opção escolhida.
}

/** 
 * @brief inserirItem();
 * @details Adiciona um novo componente à mochila se houver espaço.
 *          Solicita nome, tipo, quantidade e prioridade.
 *          Após inserir, marca a mochila como "não ordenada por nome".
 *          Permite ao jogador inserir um novo item na mochila.
 *          Verifica se há espaço antes de adicionar.
*/
void inserirItem() {
    if(numItens >= MAX_ITENS) { // Verifica se a mochila está cheia.
        printf("Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }
    // Solicita os dados do novo item ao jogador.
    Item novo;
    printf("Digite o nome do item: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0'; // Remove o enter
    printf("Digite o tipo do item: ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';
    printf("Digite a quantidade: ");
    scanf("%d", &novo.quantidade);
    printf("Digite a prioridade (1-5): ");
    scanf("%d", &novo.prioridade);
    getchar(); // Limpa o enter
    mochila[numItens++] = novo;
    ordenadaPorNome = false; // Sempre que inserir, perde a ordenação
    printf("Item adicionado com sucesso!\n");
}

/**
 * @brief removerItem();
 * @details Permite remover um componente da mochila pelo nome.
 *          Se encontrado, reorganiza o vetor para preencher a lacuna.
 *          Permite ao jogador remover um item da mochila pelo nome.
*/
void removerItem() {
    if(numItens == 0) { // Verifica se a mochila está vazia.
        printf("Mochila está vazia!\n");
        return;
    }
    // Solicita o nome do item a ser removido.
    char nomeBusca[30];
    printf("Digite o nome do item a remover: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin); 
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0'; // Remove o enter
    // Procura o item pelo nome.
    int i, encontrado = -1;
    for(i = 0; i < numItens; i++) { // Percorre todos os itens da mochila
        if(strcmp(mochila[i].nome, nomeBusca) == 0) { // Item encontrado
            encontrado = i;
            break;
        }
    }
    // Se encontrado, remove o item e reorganiza o vetor.
    if(encontrado != -1) { // Item encontrado
        for(i = encontrado; i < numItens - 1; i++) { // Remove o item e reorganiza o vetor.
            mochila[i] = mochila[i + 1];
        }
        numItens--;
        printf("Item removido com sucesso!\n");
    } else {
        printf("Item não encontrado!\n");
    }
} 

/**
 * @brief listarItens();
 * @details Exibe uma tabela formatada com todos os componentes presentes na mochila.
 *          Permite ao jogador visualizar todos os itens armazenados.
 *          Exibe os detalhes de cada item em formato tabular.
 */
void listarItens() {
    if(numItens == 0) { // Verifica se a mochila está vazia.
        printf("Mochila está vazia!\n");
        return;
    }
    // Exibe o cabeçalho da tabela.
    printf("--------------------------------------------------\n");
    printf("| %-20s | %-10s | %-8s | %-10s |\n", "Nome", "Tipo", "Quantidade", "Prioridade");
    printf("--------------------------------------------------\n");
    // Exibe cada item da mochila.
    for(int i = 0; i < numItens; i++) {
        printf("| %-20s | %-10s | %-8d | %-10d |\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade, mochila[i].prioridade);
    }
    printf("--------------------------------------------------\n");
}

/**
 * @brief menuDeOrdenacao();
 * @details Permite ao jogador escolher como deseja ordenar os itens.
 *          Utiliza a função insertionSort() com o critério selecionado.
 *          Exibe a quantidade de comparações feitas (análise de desempenho).
 *          Exibe o menu de ordenação e ordena os itens conforme a escolha do jogador.
 *          Mostra o número de comparações realizadas durante a ordenação.
 */
void menuDeOrdenacao() {
    printf("\nEscolha o critério de ordenação:\n");
    printf("1. Nome (A-Z)\n");
    printf("2. Tipo (A-Z)\n");
    printf("3. Prioridade (maior para menor)\n");
    printf("Opção: ");
    int op;
    scanf("%d", &op); getchar(); // Limpa o enter do buffer
    if(op < 1 || op > 3) { printf("Opção inválida!\n"); return; }
    insertionSort((CriterioOrdenacao)op); // Chama a função de ordenação com o critério escolhido.
    printf("Itens ordenados! Comparações realizadas: %d\n", comparacoes);
}

/**
 * @brief insertionSort();
 * @details Implementação do algoritmo de ordenação por inserção.
 *          Funciona com diferentes critérios de ordenação:
 *          - Por nome (ordem alfabética)
 *          - Por tipo (ordem alfabética)
 *          - Por prioridade (da mais alta para a mais baixa)
 *          Ordena os itens da mochila conforme o critério selecionado.
 *          Conta o número de comparações realizadas para análise de desempenho.
 */
void insertionSort(CriterioOrdenacao criterio) {
    comparacoes = 0; // Zera o contador
    for(int i = 1; i < numItens; i++) { // Percorre todos os itens a partir do segundo
        Item chave = mochila[i]; // Item chave a ser inserido na parte ordenada
        int j = i - 1;
        while(j >= 0) {
            int cmp = 0;
            if(criterio == ordenar_por_nome)
                cmp = strcmp(chave.nome, mochila[j].nome);
            else if(criterio == ordenar_por_tipo)
                cmp = strcmp(chave.tipo, mochila[j].tipo);
            else if(criterio == ordenar_por_prioridade)
                cmp = chave.prioridade - mochila[j].prioridade; // Decrescente
            comparacoes++;
            // Para nome/tipo: mover enquanto cmp < 0 (chave < mochila[j])
            // Para prioridade: mover enquanto cmp > 0 (chave > mochila[j])
            if((criterio == ordenar_por_prioridade && cmp > 0) ||
               (criterio != ordenar_por_prioridade && cmp < 0)) {
                mochila[j + 1] = mochila[j];
                j--;
            } else {
                break;
            }
        }
        mochila[j + 1] = chave;
    }
    // Marca se está ordenada por nome
    if(criterio == ordenar_por_nome) ordenadaPorNome = true;
    else ordenadaPorNome = false;
}

/**
 * @brief buscaBinariaPorNome();
 * @details Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
 *          Se encontrar, exibe os dados do item buscado.
 *          Caso contrário, informa que não encontrou o item.
 *          Permite ao jogador buscar um item pelo nome usando busca binária.
 */
void buscaBinariaPorNome() {
    if(numItens == 0) { // Verifica se a mochila está vazia.
        printf("Mochila está vazia!\n");
        return;
    }
    if(!ordenadaPorNome) {
        printf("A mochila deve estar ordenada por nome para busca binária!\n");
        return;
    }
    // Solicita o nome do item a ser buscado.
    char nomeBusca[30];
    printf("Digite o nome do item a buscar: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0'; // Remove o enter
    // Realiza a busca binária.
    int ini = 0, fim = numItens - 1, meio, achou = 0; // achou = 0 significa não encontrado
    while(ini <= fim) {
        meio = (ini + fim) / 2; // Calcula o meio do intervalo
        comparacoes++;
        int cmp = strcmp(nomeBusca, mochila[meio].nome); // Compara o nome buscado com o do meio
        // Se encontrou o item
        if(cmp == 0) {
            printf("Item encontrado:\n");
            printf("Nome: %s\nTipo: %s\nQuantidade: %d\nPrioridade: %d\n", mochila[meio].nome, mochila[meio].tipo, mochila[meio].quantidade, mochila[meio].prioridade);
            achou = 1;
            break;
        } else if(cmp < 0) {
            fim = meio - 1;
        } else {
            ini = meio + 1;
        }
    }
    if(!achou) printf("Item não encontrado!\n");
    printf("Comparações realizadas: %d\n", comparacoes);
}
