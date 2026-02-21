/*
 * ════════════════════════════════════════════════════════════════════════════════
 * TRABALHO PRÁTICO - ESTRUTURAS DE DADOS E ALGORITMOS
 * ════════════════════════════════════════════════════════════════════════════════
 *
 * Título: Análise de Atrasos de Voos - Algoritmos de Ordenação
 * Dataset: Registros de voos de companhias aéreas norte-americanas
 * Objetivo: Determinar se o tempo de voo influencia em atrasos
 *
 * Autor: Felipe
 * Data: 24 de Outubro de 2025
 *
 * ════════════════════════════════════════════════════════════════════════════════
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* ════════════════════════════════════════════════════════════════════════════════
 * CONSTANTES E DEFINIÇÕES
 * ════════════════════════════════════════════════════════════════════════════════ */

#define MAX_LINHA 2048
#define MAX_REGISTROS 550000
#define ARQUIVO_ENTRADA "flights.csv"
#define ARQUIVO_SAIDA "voos_ordenados.csv"

/* ════════════════════════════════════════════════════════════════════════════════
 * ESTRUTURAS DE DADOS
 * ════════════════════════════════════════════════════════════════════════════════ */

/**
 * Estrutura Voo
 * Armazena informações essenciais de cada voo
 */
typedef struct
{
    int tempo;  // Tempo de voo em minutos (coluna Length)
    int atraso; // Indicador de atraso: 0=não atrasado, 1=atrasado (coluna Delay)
} Voo;

/* ════════════════════════════════════════════════════════════════════════════════
 * VARIÁVEIS GLOBAIS PARA ANÁLISE DE DESEMPENHO
 * ════════════════════════════════════════════════════════════════════════════════ */

long long comparacoes = 0; // Contador de comparações realizadas
long long trocas = 0;      // Contador de trocas realizadas

/* ════════════════════════════════════════════════════════════════════════════════
 * ALGORITMOS DE ORDENAÇÃO
 * ════════════════════════════════════════════════════════════════════════════════ */

/**
 * INSERT SORT
 * Complexidade: O(n²) pior caso, O(n) melhor caso
 * Eficiente para datasets pequenos ou quase ordenados
 */
void insertSort(Voo *voos, int n)
{
    int i, j;
    Voo chave;

    for (i = 1; i < n; i++)
    {
        chave = voos[i];
        j = i - 1;

        while (j >= 0 && voos[j].tempo > chave.tempo)
        {
            comparacoes++;
            voos[j + 1] = voos[j];
            trocas++;
            j--;
        }

        if (j >= 0)
            comparacoes++;
        voos[j + 1] = chave;
        if (j + 1 != i)
            trocas++;
    }
}

/**
 * BUBBLE SORT
 * Complexidade: O(n²) pior caso
 * Inclui otimização para detectar ordenação antecipada
 */
void bubbleSort(Voo *voos, int n)
{
    int i, j;
    Voo temp;
    int houveTroca;

    for (i = 0; i < n - 1; i++)
    {
        houveTroca = 0;

        for (j = 0; j < n - i - 1; j++)
        {
            comparacoes++;

            if (voos[j].tempo > voos[j + 1].tempo)
            {
                temp = voos[j];
                voos[j] = voos[j + 1];
                voos[j + 1] = temp;
                trocas++;
                houveTroca = 1;
            }
        }

        // Otimização: se não houve troca, o array já está ordenado
        if (!houveTroca)
        {
            break;
        }
    }
}

/**
 * SELECTION SORT
 * Complexidade: O(n²) em todos os casos
 * Realiza o número mínimo de trocas
 */
void selectionSort(Voo *voos, int n)
{
    int i, j, indiceMinimo;
    Voo temp;

    for (i = 0; i < n - 1; i++)
    {
        indiceMinimo = i;

        // Encontra o menor elemento no array não ordenado
        for (j = i + 1; j < n; j++)
        {
            comparacoes++;
            if (voos[j].tempo < voos[indiceMinimo].tempo)
            {
                indiceMinimo = j;
            }
        }

        // Troca o menor elemento encontrado com o primeiro não ordenado
        if (indiceMinimo != i)
        {
            temp = voos[i];
            voos[i] = voos[indiceMinimo];
            voos[indiceMinimo] = temp;
            trocas++;
        }
    }
}

/**
 * QUICK SORT - Função de Particionamento
 * Divide o array em partições menores e maiores que o pivô
 */
int particionar(Voo *voos, int baixo, int alto)
{
    int pivo = voos[alto].tempo;
    int i = baixo - 1;
    int j;
    Voo temp;

    for (j = baixo; j < alto; j++)
    {
        comparacoes++;
        if (voos[j].tempo <= pivo)
        {
            i++;
            temp = voos[i];
            voos[i] = voos[j];
            voos[j] = temp;
            trocas++;
        }
    }

    temp = voos[i + 1];
    voos[i + 1] = voos[alto];
    voos[alto] = temp;
    trocas++;

    return i + 1;
}

/**
 * QUICK SORT - Função Recursiva
 * Aplica o algoritmo recursivamente nas partições
 */
void quickSortRecursivo(Voo *voos, int baixo, int alto)
{
    if (baixo < alto)
    {
        int indicePivo = particionar(voos, baixo, alto);
        quickSortRecursivo(voos, baixo, indicePivo - 1);
        quickSortRecursivo(voos, indicePivo + 1, alto);
    }
}

/**
 * QUICK SORT - Função Principal
 * Complexidade: O(n log n) caso médio, O(n²) pior caso
 * Mais eficiente para grandes datasets
 */
void quickSort(Voo *voos, int n)
{
    if (n > 0)
    {
        quickSortRecursivo(voos, 0, n - 1);
    }
}

/* ════════════════════════════════════════════════════════════════════════════════
 * FUNÇÕES DE MANIPULAÇÃO DE ARQUIVO CSV
 * ════════════════════════════════════════════════════════════════════════════════ */

/**
 * Encontra o índice de uma coluna pelo nome no cabeçalho CSV
 */
int encontrarIndiceColuna(char *linhaCabecalho, const char *nomeColuna)
{
    char *linhaCopia = strdup(linhaCabecalho);
    char *token;
    int indice = 0;

    token = strtok(linhaCopia, ",");
    while (token != NULL)
    {
        // Remove espaços em branco e quebras de linha
        while (*token == ' ' || *token == '\n' || *token == '\r')
            token++;

        // Remove espaços do final
        char *fim = token + strlen(token) - 1;
        while (fim > token && (*fim == ' ' || *fim == '\n' || *fim == '\r'))
        {
            *fim = '\0';
            fim--;
        }

        if (strcmp(token, nomeColuna) == 0)
        {
            free(linhaCopia);
            return indice;
        }

        indice++;
        token = strtok(NULL, ",");
    }

    free(linhaCopia);
    return -1;
}

/**
 * Extrai o valor de uma coluna específica de uma linha CSV
 */
int extrairValorInteiro(char *linha, int indiceColuna)
{
    char *linhaCopia = strdup(linha);
    char *token;
    int indiceAtual = 0;
    int valor = 0;

    token = strtok(linhaCopia, ",");
    while (token != NULL)
    {
        if (indiceAtual == indiceColuna)
        {
            // Remove espaços em branco
            while (*token == ' ')
                token++;
            valor = atoi(token);
            break;
        }
        indiceAtual++;
        token = strtok(NULL, ",");
    }

    free(linhaCopia);
    return valor;
}

/**
 * Lê o arquivo CSV e carrega os dados na memória
 */
int lerArquivoCSV(const char *nomeArquivo, Voo **voos)
{
    FILE *arquivo;
    char linha[MAX_LINHA];
    int contador = 0;
    int indiceLength = -1;
    int indiceDelay = -1;

    // Abre o arquivo
    arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL)
    {
        printf("❌ ERRO: Não foi possível abrir o arquivo '%s'\n", nomeArquivo);
        printf("   Verifique se o arquivo existe no diretório atual.\n");
        return -1;
    }

    printf("📂 Abrindo arquivo '%s'...\n", nomeArquivo);

    // Aloca memória para os registros
    *voos = (Voo *)malloc(MAX_REGISTROS * sizeof(Voo));
    if (*voos == NULL)
    {
        printf("❌ ERRO: Memória insuficiente para alocar %d registros\n", MAX_REGISTROS);
        fclose(arquivo);
        return -1;
    }

    // Lê o cabeçalho e identifica as colunas
    if (fgets(linha, MAX_LINHA, arquivo) != NULL)
    {
        indiceLength = encontrarIndiceColuna(linha, "Length");
        indiceDelay = encontrarIndiceColuna(linha, "Delay");

        if (indiceLength == -1 || indiceDelay == -1)
        {
            printf("❌ ERRO: Colunas necessárias não encontradas no arquivo\n");
            printf("   Coluna 'Length': %s\n", indiceLength != -1 ? "✓ Encontrada" : "✗ Não encontrada");
            printf("   Coluna 'Delay': %s\n", indiceDelay != -1 ? "✓ Encontrada" : "✗ Não encontrada");
            free(*voos);
            fclose(arquivo);
            return -1;
        }

        printf("✓ Colunas identificadas - Length: índice %d, Delay: índice %d\n",
               indiceLength, indiceDelay);
    }

    // Lê os dados linha por linha
    printf("📖 Lendo dados...\n");
    while (fgets(linha, MAX_LINHA, arquivo) != NULL && contador < MAX_REGISTROS)
    {
        (*voos)[contador].tempo = extrairValorInteiro(linha, indiceLength);
        (*voos)[contador].atraso = extrairValorInteiro(linha, indiceDelay);
        contador++;

        // Mostra progresso a cada 100.000 registros
        if (contador % 100000 == 0)
        {
            printf("   → %d registros lidos...\n", contador);
        }
    }

    fclose(arquivo);
    printf("✓ Leitura concluída: %d registros carregados\n\n", contador);

    return contador;
}

/**
 * Escreve o arquivo de saída com os dados ordenados
 */
int escreverArquivoSaida(const char *nomeArquivo, Voo *voos, int n)
{
    FILE *arquivo;
    int i;

    arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL)
    {
        printf("❌ ERRO: Não foi possível criar o arquivo '%s'\n", nomeArquivo);
        return 0;
    }

    printf("📝 Escrevendo arquivo de saída '%s'...\n", nomeArquivo);

    // Escreve cabeçalho
    fprintf(arquivo, "Tempo,Atraso\n");

    // Escreve dados ordenados
    for (i = 0; i < n; i++)
    {
        fprintf(arquivo, "%d,%d\n", voos[i].tempo, voos[i].atraso);

        if ((i + 1) % 100000 == 0)
        {
            printf("   → %d registros escritos...\n", i + 1);
        }
    }

    fclose(arquivo);
    printf("✓ Arquivo criado: %d registros escritos\n\n", n);

    return 1;
}

/* ════════════════════════════════════════════════════════════════════════════════
 * FUNÇÕES DE ANÁLISE ESTATÍSTICA
 * ════════════════════════════════════════════════════════════════════════════════ */

/**
 * Calcula e exibe estatísticas sobre os dados
 */
void exibirEstatisticas(Voo *voos, int n)
{
    int i;
    int voosComAtraso = 0;
    int voosSemAtraso = 0;
    long long somaTempoComAtraso = 0;
    long long somaTempoSemAtraso = 0;
    int menorTempo = voos[0].tempo;
    int maiorTempo = voos[0].tempo;

    // Faixas de tempo para análise
    int faixas[4][2] = {{0}}; // [faixa][sem_atraso, com_atraso]

    for (i = 0; i < n; i++)
    {
        // Contabiliza atrasos
        if (voos[i].atraso == 1)
        {
            voosComAtraso++;
            somaTempoComAtraso += voos[i].tempo;
        }
        else
        {
            voosSemAtraso++;
            somaTempoSemAtraso += voos[i].tempo;
        }

        // Atualiza menor e maior tempo
        if (voos[i].tempo < menorTempo)
            menorTempo = voos[i].tempo;
        if (voos[i].tempo > maiorTempo)
            maiorTempo = voos[i].tempo;

        // Classifica em faixas
        int faixa;
        if (voos[i].tempo < 100)
            faixa = 0;
        else if (voos[i].tempo < 200)
            faixa = 1;
        else if (voos[i].tempo < 300)
            faixa = 2;
        else
            faixa = 3;

        faixas[faixa][voos[i].atraso]++;
    }

    printf("╔════════════════════════════════════════════════════════════════════╗\n");
    printf("║               ESTATÍSTICAS DO DATASET                             ║\n");
    printf("╚════════════════════════════════════════════════════════════════════╝\n\n");

    printf("📊 DADOS GERAIS:\n");
    printf("   Total de voos: %d\n", n);
    printf("   Voos com atraso: %d (%.2f%%)\n", voosComAtraso, (voosComAtraso * 100.0) / n);
    printf("   Voos sem atraso: %d (%.2f%%)\n", voosSemAtraso, (voosSemAtraso * 100.0) / n);
    printf("\n");

    printf("⏱️  TEMPO DE VOO:\n");
    printf("   Menor tempo: %d minutos\n", menorTempo);
    printf("   Maior tempo: %d minutos\n", maiorTempo);
    printf("   Tempo médio COM atraso: %.2f minutos\n",
           voosComAtraso > 0 ? (double)somaTempoComAtraso / voosComAtraso : 0);
    printf("   Tempo médio SEM atraso: %.2f minutos\n",
           voosSemAtraso > 0 ? (double)somaTempoSemAtraso / voosSemAtraso : 0);
    printf("\n");

    printf("📈 ANÁLISE POR FAIXAS DE TEMPO:\n");
    const char *nomesFaixas[] = {"  0-100 min", "100-200 min", "200-300 min", "300+ min   "};

    for (i = 0; i < 4; i++)
    {
        int total = faixas[i][0] + faixas[i][1];
        if (total > 0)
        {
            float percAtraso = (faixas[i][1] * 100.0) / total;
            printf("   %s: %6d voos, %6d com atraso (%.2f%%)\n",
                   nomesFaixas[i], total, faixas[i][1], percAtraso);
        }
    }
    printf("\n");
}

/**
 * Exibe informações sobre o desempenho do algoritmo de ordenação
 */
void exibirDesempenhoOrdenacao(const char *nomeMetodo, double tempoExecucao)
{
    printf("╔════════════════════════════════════════════════════════════════════╗\n");
    printf("║           DESEMPENHO DO ALGORITMO DE ORDENAÇÃO                    ║\n");
    printf("╚════════════════════════════════════════════════════════════════════╝\n\n");

    printf("🔧 Método: %s\n", nomeMetodo);
    printf("⏱️  Tempo de execução: %.3f segundos\n", tempoExecucao);
    printf("📊 Comparações: %lld\n", comparacoes);
    printf("🔄 Trocas: %lld\n", trocas);
    printf("\n");
}

/**
 * Exibe uma amostra dos dados ordenados
 */
void exibirAmostra(Voo *voos, int n)
{
    int i;
    int qtdAmostra = (n < 20) ? n : 20;

    printf("╔════════════════════════════════════════════════════════════════════╗\n");
    printf("║         AMOSTRA DOS DADOS ORDENADOS (primeiros %2d)               ║\n", qtdAmostra);
    printf("╚════════════════════════════════════════════════════════════════════╝\n\n");

    printf("   Tempo (min)  │  Atraso\n");
    printf("  ──────────────┼──────────\n");

    for (i = 0; i < qtdAmostra; i++)
    {
        printf("      %4d      │    %d\n", voos[i].tempo, voos[i].atraso);
    }
    printf("\n");
}

/* ════════════════════════════════════════════════════════════════════════════════
 * INTERFACE DO USUÁRIO
 * ════════════════════════════════════════════════════════════════════════════════ */

/**
 * Exibe o menu de seleção de algoritmo
 */
void exibirMenu()
{
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════════════╗\n");
    printf("║      SELEÇÃO DO ALGORITMO DE ORDENAÇÃO                            ║\n");
    printf("╚════════════════════════════════════════════════════════════════════╝\n\n");

    printf("  Escolha um dos algoritmos abaixo:\n\n");
    printf("  [1] Insert Sort       - Simples, eficiente para pequenos datasets\n");
    printf("  [2] Bubble Sort       - Didático, com otimização\n");
    printf("  [3] Selection Sort    - Número mínimo de trocas\n");
    printf("  [4] Quick Sort        - ⭐ Recomendado para grandes datasets\n");
    printf("\n");
    printf("  [0] Sair\n");
    printf("\n");
    printf("  Opção: ");
}

/**
 * Exibe o cabeçalho do programa
 */
void exibirCabecalho()
{
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                                                    ║\n");
    printf("║    TRABALHO PRÁTICO - ESTRUTURAS DE DADOS E ALGORITMOS            ║\n");
    printf("║                                                                    ║\n");
    printf("║    Análise de Atrasos de Voos                                     ║\n");
    printf("║    Dataset: Companhias Aéreas Norte-Americanas                    ║\n");
    printf("║                                                                    ║\n");
    printf("║    Objetivo: Determinar se o tempo de voo influencia atrasos      ║\n");
    printf("║                                                                    ║\n");
    printf("╚════════════════════════════════════════════════════════════════════╝\n\n");
}

/* ════════════════════════════════════════════════════════════════════════════════
 * FUNÇÃO PRINCIPAL
 * ════════════════════════════════════════════════════════════════════════════════ */

int main()
{
    Voo *voos = NULL;
    int numVoos = 0;
    int opcao;
    clock_t inicio, fim;
    double tempoExecucao;
    char *nomeMetodo;

    // Exibe cabeçalho
    exibirCabecalho();

    // Lê o arquivo CSV
    numVoos = lerArquivoCSV(ARQUIVO_ENTRADA, &voos);

    if (numVoos <= 0)
    {
        printf("⚠️  Encerrando programa devido a erro na leitura do arquivo.\n\n");
        return 1;
    }

    // Exibe estatísticas dos dados não ordenados
    exibirEstatisticas(voos, numVoos);

    // Menu de seleção do algoritmo
    while (1)
    {
        exibirMenu();

        if (scanf("%d", &opcao) != 1)
        {
            printf("❌ Entrada inválida!\n");
            while (getchar() != '\n')
                ; // Limpa buffer
            continue;
        }

        if (opcao == 0)
        {
            printf("\n👋 Encerrando programa...\n\n");
            break;
        }

        if (opcao < 1 || opcao > 4)
        {
            printf("❌ Opção inválida! Escolha entre 1 e 4.\n");
            continue;
        }

        // Reinicia contadores de desempenho
        comparacoes = 0;
        trocas = 0;

        printf("\n🔄 Iniciando ordenação...\n");
        inicio = clock();

        // Executa o algoritmo selecionado
        switch (opcao)
        {
        case 1:
            nomeMetodo = "Insert Sort";
            insertSort(voos, numVoos);
            break;
        case 2:
            nomeMetodo = "Bubble Sort";
            bubbleSort(voos, numVoos);
            break;
        case 3:
            nomeMetodo = "Selection Sort";
            selectionSort(voos, numVoos);
            break;
        case 4:
            nomeMetodo = "Quick Sort";
            quickSort(voos, numVoos);
            break;
        }

        fim = clock();
        tempoExecucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

        printf("✓ Ordenação concluída!\n\n");

        // Exibe resultados
        exibirDesempenhoOrdenacao(nomeMetodo, tempoExecucao);
        exibirAmostra(voos, numVoos);

        // Escreve arquivo de saída
        if (escreverArquivoSaida(ARQUIVO_SAIDA, voos, numVoos))
        {
            printf("╔════════════════════════════════════════════════════════════════════╗\n");
            printf("║                    PROCESSAMENTO CONCLUÍDO                        ║\n");
            printf("╚════════════════════════════════════════════════════════════════════╝\n\n");

            printf("✅ Arquivo '%s' gerado com sucesso!\n\n", ARQUIVO_SAIDA);

            printf("💡 RESPOSTA À QUESTÃO:\n");
            printf("   \"O tempo de voo influencia em atrasos?\"\n\n");
            printf("   Consulte as estatísticas acima e o arquivo gerado\n");
            printf("   para realizar sua análise e conclusão.\n\n");
        }

        break;
    }

    // Libera memória
    if (voos != NULL)
    {
        free(voos);
    }

    printf("Programa finalizado.\n\n");

    return 0;
}
