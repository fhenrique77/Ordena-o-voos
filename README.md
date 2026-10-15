
# Análise de Atrasos de Voos — Algoritmos de Ordenação em C

![C](https://img.shields.io/badge/Language-C-A8B9CC?logo=c&logoColor=black)
![GCC](https://img.shields.io/badge/Compiler-GCC-blue)
![CSV](https://img.shields.io/badge/Data-CSV-green)
![Status](https://img.shields.io/badge/Type-Academic_Project-orange)

Projeto acadêmico desenvolvido em **linguagem C** para implementar, analisar e comparar algoritmos de ordenação aplicados a registros de voos.

O sistema realiza a leitura de arquivos CSV, organiza os registros pelo tempo de voo, calcula estatísticas descritivas relacionadas a atrasos e apresenta métricas de desempenho dos algoritmos implementados.

O trabalho foi desenvolvido no contexto da disciplina de **Estruturas de Dados e Algoritmos**, explorando conceitos de complexidade computacional, manipulação de dados e análise de desempenho.

## Objetivo

Investigar a relação entre a duração dos voos e a ocorrência de atrasos, utilizando algoritmos de ordenação e estatísticas descritivas.

O projeto também busca comparar o comportamento de diferentes algoritmos de ordenação quando aplicados a conjuntos de dados com diferentes quantidades de registros.

### Objetivos específicos

- Implementar quatro algoritmos de ordenação em C.
- Ler registros de voos armazenados em arquivos CSV.
- Organizar os voos em ordem crescente de duração.
- Calcular estatísticas sobre atrasos.
- Comparar tempos médios de voos com e sem atraso.
- Analisar a frequência de atrasos por faixa de duração.
- Medir o desempenho dos algoritmos.
- Exportar os resultados ordenados para CSV.

## Tecnologias utilizadas

| Tecnologia | Finalidade |
| --- | --- |
| C | Implementação dos algoritmos |
| GCC | Compilação do código-fonte |
| CSV | Entrada e saída de dados |
| stdio.h | Leitura, escrita e entrada pelo terminal |
| stdlib.h | Alocação dinâmica e conversões |
| string.h | Manipulação de strings |
| time.h | Medição de tempo de CPU e geração de dados |

Os algoritmos de ordenação foram implementados manualmente, sem utilizar funções prontas de ordenação como `qsort()`.

## Dataset

O programa trabalha com informações de voos de companhias aéreas.

O repositório inclui um arquivo `flights.csv` contendo **10.000 registros sintéticos**, no formato produzido pelo gerador de testes.

O código também foi estruturado para trabalhar com datasets maiores, como conjuntos de dados públicos contendo centenas de milhares de voos.

### Estrutura dos dados

O arquivo de entrada utiliza as seguintes colunas:

| Coluna | Descrição |
| --- | --- |
| ID | Identificador do registro |
| Airline | Companhia aérea |
| Flight | Número do voo |
| AirportFrom | Aeroporto de origem |
| AirportTo | Aeroporto de destino |
| DayOfWeek | Dia da semana |
| Time | Horário do voo |
| Length | Duração do voo em minutos |
| Delay | Indicador de atraso |

### Colunas utilizadas na análise

O programa extrai principalmente:

- **Length:** duração do voo, em minutos.
- **Delay:** indicador binário de atraso.

A variável `Delay` assume os valores:

- `0`: voo sem atraso.
- `1`: voo com atraso.

### Dados sintéticos

O arquivo `gerar_dataset.c` permite criar um conjunto de testes com 10.000 registros.

Os dados gerados incluem companhias aéreas, aeroportos, dias da semana, durações e indicadores de atraso.

**Importante:** o gerador estabelece probabilidades de atraso diferentes conforme a duração do voo. Portanto, tendências observadas nesse conjunto sintético refletem parcialmente as regras utilizadas para gerar os dados e não devem ser tratadas como conclusões sobre a aviação real.

## Algoritmos implementados

Foram implementados quatro algoritmos de ordenação:

### 1. Insertion Sort

O Insertion Sort constrói gradualmente uma sequência ordenada, inserindo cada elemento na posição apropriada.

**Características:**

- Implementação simples.
- Adequado para conjuntos pequenos.
- Bom desempenho em dados quase ordenados.
- Complexidade de tempo O(n²) no caso médio e no pior caso.
- Melhor caso O(n).

### 2. Bubble Sort

O Bubble Sort compara elementos adjacentes e realiza trocas quando necessário.

A implementação inclui uma otimização que encerra o processamento antecipadamente quando não ocorrem trocas em uma passagem.

**Características:**

- Fácil compreensão e implementação.
- Adequado para demonstrações didáticas.
- Complexidade O(n²) no caso médio e no pior caso.
- Melhor caso O(n), com a otimização implementada.

### 3. Selection Sort

O Selection Sort percorre a parte não ordenada do vetor, identifica o menor elemento e o posiciona corretamente.

**Características:**

- Algoritmo simples.
- Realiza no máximo n-1 trocas de posição.
- Complexidade O(n²) mesmo no melhor caso.
- Exige uma quantidade quadrática de comparações.

### 4. Quick Sort

O Quick Sort utiliza a estratégia de divisão e conquista.

O vetor é particionado em relação a um pivô e cada partição é ordenada recursivamente.

Na implementação atual, o pivô é escolhido como o último elemento da partição.

**Características:**

- Complexidade média O(n log n).
- Complexidade O(n²) no pior caso.
- Geralmente eficiente para grandes conjuntos.
- O desempenho depende da distribuição dos valores e da escolha do pivô.

### Comparação de complexidade

| Algoritmo | Melhor caso | Caso médio | Pior caso |
| --- | --- | --- | --- |
| Insertion Sort | O(n) | O(n²) | O(n²) |
| Bubble Sort | O(n) | O(n²) | O(n²) |
| Selection Sort | O(n²) | O(n²) | O(n²) |
| Quick Sort | O(n log n) | O(n log n) | O(n²) |

Para conjuntos grandes, os algoritmos quadráticos podem exigir um tempo de execução elevado.

**Observação:** o Quick Sort implementado utiliza o último elemento como pivô e pode apresentar desempenho ruim em determinadas distribuições, especialmente com muitos valores repetidos ou dados já ordenados.

## Funcionamento do programa

O sistema segue as seguintes etapas:

```text
Arquivo flights.csv
        |
        v
Leitura e identificação das colunas
        |
        v
Carregamento dos registros na memória
        |
        v
Cálculo das estatísticas descritivas
        |
        v
Menu de seleção do algoritmo
        |
        v
Ordenação por duração do voo
        |
        v
Medição do desempenho
        |
        v
Exibição de uma amostra dos dados
        |
        v
Exportação para voos_ordenados.csv
```

A ordenação é realizada em ordem crescente pelo campo `Length`.

## Como executar

### Pré-requisitos

- Compilador GCC instalado.
- Terminal PowerShell, CMD, Bash ou equivalente.
- Git, caso deseje clonar o repositório.

Não é necessário instalar bibliotecas externas de ordenação.

### 1. Clonar o repositório

```bash
git clone https://github.com/fhenrique77/Ordena-o-voos.git
cd Ordena-o-voos
```

### 2. Compilar o programa

**Windows:**

```bash
gcc -O2 -std=gnu11 ordenacao_voos.c -o ordenacao_voos.exe
```

**Linux/macOS:**

```bash
gcc -O2 -std=gnu11 ordenacao_voos.c -o ordenacao_voos
```

A implementação utiliza `strdup()`, função disponível em ambientes POSIX e em diversas configurações GNU. A portabilidade para compiladores estritamente ISO C pode exigir ajustes.

### 3. Executar

No Windows:

```powershell
.\ordenacao_voos.exe
```

No Linux/macOS:

```bash
./ordenacao_voos
```

O programa procura `flights.csv` no diretório de execução.

### 4. Selecionar o algoritmo

O menu apresenta as opções:

```text
SELEÇÃO DO ALGORITMO DE ORDENAÇÃO

[1] Insertion Sort
[2] Bubble Sort
[3] Selection Sort
[4] Quick Sort

[0] Sair
```

Após a seleção, o programa executa o algoritmo, apresenta suas métricas e gera o arquivo de saída.

Para comparar diferentes algoritmos com o mesmo conjunto de dados, execute novamente o programa e escolha outra opção.

## Gerar um novo dataset de teste

O projeto possui um gerador de dados sintéticos em `gerar_dataset.c`.

### Compilar

**Windows:**

```bash
gcc -O2 gerar_dataset.c -o gerar_dataset.exe
```

**Linux/macOS:**

```bash
gcc -O2 gerar_dataset.c -o gerar_dataset
```

### Executar

No Windows:

```powershell
.\gerar_dataset.exe
```

No Linux/macOS:

```bash
./gerar_dataset
```

O programa gera um arquivo `flights.csv` com 10.000 registros.

**Atenção:** a execução do gerador sobrescreve o arquivo `flights.csv` existente no diretório atual. Faça uma cópia caso deseje preservar os dados anteriores.

A quantidade de registros pode ser modificada no código:

```c
#define NUM_REGISTROS 10000
```

## Análise estatística

Além da ordenação, o projeto implementa funções de análise dos registros.

### Estatísticas gerais

O programa calcula:

- Quantidade total de voos.
- Quantidade de voos com atraso.
- Quantidade de voos sem atraso.
- Percentual de voos atrasados.
- Menor duração de voo.
- Maior duração de voo.

### Comparação entre durações médias

O sistema calcula o tempo médio dos voos com atraso e dos voos sem atraso.

Essas estatísticas permitem investigar possíveis associações entre a duração e a frequência de atrasos.

### Análise por faixas

As durações são agrupadas em quatro intervalos:

| Faixa | Duração |
| --- | --- |
| 1 | Menos de 100 minutos |
| 2 | De 100 a menos de 200 minutos |
| 3 | De 200 a menos de 300 minutos |
| 4 | 300 minutos ou mais |

Para cada faixa, são calculados:

- Quantidade de voos.
- Quantidade de voos com atraso.
- Percentual de atrasos.

### Interpretação dos resultados

A pergunta central do trabalho é:

**"O tempo de voo influencia na ocorrência de atrasos?"**

O programa fornece indicadores descritivos para investigar essa questão.

Diferenças entre médias ou percentuais podem indicar associação entre as variáveis, mas não demonstram, isoladamente, uma relação de causa e efeito.

A implementação atual não calcula um coeficiente de correlação nem controla outras variáveis, como clima, aeroporto, companhia aérea ou período do dia.

Para conclusões sobre voos reais, deve-se utilizar um conjunto de dados observacionais apropriado e realizar análises estatísticas adicionais.

## Medição de desempenho

Durante a execução, o programa registra informações sobre o algoritmo selecionado.

| Métrica | Descrição |
| --- | --- |
| Tempo de execução | Tempo de CPU consumido na ordenação |
| Comparações | Operações contabilizadas pelo algoritmo |
| Trocas | Movimentações ou trocas contabilizadas |
| Quantidade de registros | Total de voos processados |

A medição é realizada com `clock()`, da biblioteca `time.h`.

Os contadores foram implementados manualmente. Como a contagem de movimentações varia entre os algoritmos, seus valores devem ser interpretados conforme a implementação, e não como métricas perfeitamente equivalentes.

## Arquivos de saída

Após a ordenação, o sistema gera:

`voos_ordenados.csv`

O arquivo possui o seguinte formato:

```csv
Tempo,Atraso
30,0
30,0
30,1
```

Os registros são organizados em ordem crescente pela duração.

O arquivo exportado contém apenas as colunas `Tempo` e `Atraso`, correspondentes aos campos `Length` e `Delay` da entrada.

**Observação:** uma nova execução de ordenação pode sobrescrever o arquivo de saída existente.

## Estrutura do repositório

```text
Ordena-o-voos/
├── ordenacao_voos.c      # Programa principal
├── gerar_dataset.c       # Gerador de dados sintéticos
├── flights.csv           # Dataset de teste
├── voos_ordenados.csv    # Resultado de uma execução
├── ordenação.c           # Arquivo vazio
├── .gitignore            # Configuração do Git
└── README.md             # Documentação
```

### Arquivos principais

**ordenacao_voos.c**

Contém a implementação dos algoritmos, leitura do CSV, análise estatística, medição de desempenho e exportação.

**gerar_dataset.c**

Permite gerar registros sintéticos para testes.

**flights.csv**

Arquivo de entrada utilizado pelo programa. A versão presente no repositório contém 10.000 registros.

**voos_ordenados.csv**

Exemplo de saída ordenada incluído no repositório.

## Limitações conhecidas

- O carregamento está limitado a 550.000 registros pela constante `MAX_REGISTROS`.
- A leitura do CSV utiliza separação simples por vírgula, não sendo um parser CSV completo.
- Campos vazios ou valores com vírgulas entre aspas podem exigir tratamento adicional.
- A conversão de valores com `atoi()` não oferece validação rigorosa.
- O programa executa um algoritmo de ordenação por execução.
- A escolha do último elemento como pivô pode prejudicar o desempenho do Quick Sort em certos casos.
- A comparação estatística não demonstra causalidade.
- O dataset sintético possui probabilidades de atraso definidas pelo gerador.
- Não há suíte de testes automatizados configurada.

## Melhorias futuras

- Implementar Merge Sort e Heap Sort.
- Adicionar testes automatizados de ordenação.
- Validar os dados de entrada antes do processamento.
- Aprimorar a leitura de arquivos CSV.
- Automatizar a comparação dos quatro algoritmos sobre cópias idênticas do conjunto de dados.
- Exportar relatórios de desempenho.
- Implementar correlação e análises estatísticas adicionais.
- Adicionar gráficos de desempenho.
- Permitir selecionar arquivos por argumento da linha de comando.
- Melhorar a escolha do pivô do Quick Sort.

## Conceitos aplicados

O desenvolvimento envolve conhecimentos de:

- Estruturas de dados.
- Algoritmos de ordenação.
- Análise de complexidade.
- Linguagem C.
- Manipulação de arquivos.
- Ponteiros e alocação dinâmica.
- Estatística descritiva.
- Medição de desempenho computacional.
- Processamento de dados tabulares.

## Referências

- Cormen, T. H. et al. — Introduction to Algorithms.
- Documentação da linguagem C.
- Material acadêmico sobre algoritmos de ordenação.
- Conceitos de estatística descritiva.

## Autor

**Felipe Henrique Oliveira Sousa**

Estudante de Engenharia de Software na Universidade de Brasília (UnB).

GitHub: [@fhenrique77](https://github.com/fhenrique77)

---

Projeto acadêmico desenvolvido para aplicar conceitos de Estruturas de Dados e Algoritmos, análise de desempenho e processamento de arquivos CSV utilizando linguagem C.
