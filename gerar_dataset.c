/*
 * Gerador de Dataset de Teste
 * Cria um arquivo flights.csv simulado para testes do trabalho
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_REGISTROS 10000 // Ajuste conforme necessário

const char *companhias[] = {
    "American Airlines", "Delta Air Lines", "United Airlines",
    "Southwest Airlines", "JetBlue Airways", "Alaska Airlines"};
const int numCompanhias = 6;

const char *aeroportos[] = {
    "JFK", "LAX", "ORD", "DFW", "DEN", "ATL",
    "SFO", "MIA", "SEA", "BOS", "LAS", "PHX"};
const int numAeroportos = 12;

const char *dias[] = {
    "Monday", "Tuesday", "Wednesday", "Thursday",
    "Friday", "Saturday", "Sunday"};
const int numDias = 7;

int main()
{
    FILE *arquivo;
    int i;

    srand((unsigned)time(NULL));

    printf("\n");
    printf("╔════════════════════════════════════════════════════════════════════╗\n");
    printf("║          GERADOR DE DATASET DE TESTE                             ║\n");
    printf("╚════════════════════════════════════════════════════════════════════╝\n\n");

    printf("Gerando arquivo de teste com %d registros...\n\n", NUM_REGISTROS);

    arquivo = fopen("flights.csv", "w");
    if (arquivo == NULL)
    {
        printf("❌ ERRO: Não foi possível criar o arquivo!\n");
        return 1;
    }

    // Escreve cabeçalho (formato original do dataset)
    fprintf(arquivo, "ID,Airline,Flight,AirportFrom,AirportTo,DayOfWeek,Time,Length,Delay\n");

    // Gera registros com dados realistas
    for (i = 1; i <= NUM_REGISTROS; i++)
    {
        int id = i;
        const char *airline = companhias[rand() % numCompanhias];
        int flightNumber = 100 + rand() % 9900;
        const char *from = aeroportos[rand() % numAeroportos];
        const char *to = aeroportos[rand() % numAeroportos];

        // Garante que origem ≠ destino
        while (strcmp(from, to) == 0)
        {
            to = aeroportos[rand() % numAeroportos];
        }

        const char *day = dias[rand() % numDias];
        int timeOfDay = rand() % 2400;

        // Gera tempo de voo com distribuição realista
        int length;
        int dist = rand() % 100;

        if (dist < 40)
        {
            // 40% voos curtos (30-150 min)
            length = 30 + rand() % 120;
        }
        else if (dist < 80)
        {
            // 40% voos médios (150-300 min)
            length = 150 + rand() % 150;
        }
        else
        {
            // 20% voos longos (300-600 min)
            length = 300 + rand() % 300;
        }

        // Calcula probabilidade de atraso baseada no tempo de voo
        // Simulando que voos mais longos têm mais chance de atraso
        int delay;
        int chanceBase = rand() % 100;

        if (length > 300)
        {
            // Voos longos: 50% de chance
            delay = (chanceBase < 50) ? 1 : 0;
        }
        else if (length > 150)
        {
            // Voos médios: 40% de chance
            delay = (chanceBase < 40) ? 1 : 0;
        }
        else
        {
            // Voos curtos: 30% de chance
            delay = (chanceBase < 30) ? 1 : 0;
        }

        // Escreve linha no arquivo
        fprintf(arquivo, "%d,%s,FL%d,%s,%s,%s,%04d,%d,%d\n",
                id, airline, flightNumber, from, to, day, timeOfDay, length, delay);

        // Mostra progresso
        if (i % 1000 == 0)
        {
            printf("   → %d registros gerados...\n", i);
        }
    }

    fclose(arquivo);

    printf("\n");
    printf("✅ Arquivo 'flights.csv' criado com sucesso!\n");
    printf("   📊 Total de registros: %d\n", NUM_REGISTROS);
    printf("   📁 Tamanho estimado: ~%d KB\n", (NUM_REGISTROS * 80) / 1024);
    printf("\n");
    printf("Agora você pode executar o programa de ordenação:\n");
    printf("   gcc ordenacao_voos.c -o ordenacao_voos.exe\n");
    printf("   .\\ordenacao_voos.exe\n");
    printf("\n");

    return 0;
}
