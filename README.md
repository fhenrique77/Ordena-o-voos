# 📊 Trabalho Prático - Análise de Atrasos de Voos

## 📝 Descrição
Trabalho da disciplina de **Estruturas de Dados e Algoritmos** que implementa e compara diferentes algoritmos de ordenação aplicados a um dataset real de voos de companhias aéreas norte-americanas.

**Objetivo**: Determinar se o tempo de voo influencia em atrasos.

---

## 🎯 Especificações do Trabalho

### Dataset
- **Fonte**: Registros de voos de companhias aéreas norte-americanas
- **Instâncias**: 539.383 linhas
- **Tamanho**: ~18.5 MB (descompactado)
- **Formato**: CSV
- **Colunas utilizadas**:
  - `Length`: Tempo de voo em minutos
  - `Delay`: Indicador de atraso (0=não, 1=sim)

### Requisitos
✅ Leitura do arquivo CSV original (sem pré-processamento)  
✅ Implementação de 4 algoritmos de ordenação  
✅ Saída ordenada pela coluna Tempo  
✅ Solução 100% em C (sem bibliotecas prontas)  

---

## 🚀 Como Usar

### 1️⃣ Compilação

**Windows (PowerShell/CMD):**
```bash
gcc ordenacao_voos.c -o ordenacao_voos.exe
```

**Linux/Mac:**
```bash
gcc ordenacao_voos.c -o ordenacao_voos -O2
```

### 2️⃣ Preparação do Dataset

Opção A - **Dataset Real**:
1. Baixe o dataset de voos
2. Renomeie para `flights.csv`
3. Coloque na pasta `Ordenação`

Opção B - **Dataset de Teste**:
```bash
# Compile o gerador
gcc gerar_dataset.c -o gerar_dataset.exe

# Execute
.\gerar_dataset.exe

# Será criado flights.csv com 10.000 registros
```

### 3️⃣ Execução

```bash
.\ordenacao_voos.exe
```

Siga o menu interativo para escolher o algoritmo.

---

## 🔧 Algoritmos Implementados

| Algoritmo      | Complexidade (Médio) | Melhor Para | Recomendado |
|----------------|---------------------|-------------|-------------|
| **Insert Sort**   | O(n²) | Pequenos datasets | < 10k registros |
| **Bubble Sort**   | O(n²) | Fins didáticos | < 5k registros |
| **Selection Sort**| O(n²) | Mínimo de trocas | < 10k registros |
| **Quick Sort**    | O(n log n) | Grandes datasets | ⭐ > 10k registros |

---

## 📁 Arquivos Gerados

### `voos_ordenados.csv`
Arquivo de saída com formato:
```csv
Tempo,Atraso
30,0
45,1
60,0
...
```

**Características**:
- ✅ Ordenado pela coluna Tempo (crescente)
- ✅ Contém todos os registros processados
- ✅ Formato compatível com Excel/Calc

---

## 📊 Análises Fornecidas

O programa exibe automaticamente:

1. **📈 Estatísticas Gerais**
   - Total de voos
   - Percentual de atrasos
   - Tempos mínimo e máximo

2. **⏱️ Comparação de Tempos**
   - Tempo médio de voos COM atraso
   - Tempo médio de voos SEM atraso

3. **📊 Análise por Faixas**
   - 0-100 min
   - 100-200 min
   - 200-300 min
   - 300+ min

4. **🔧 Desempenho do Algoritmo**
   - Tempo de execução
   - Número de comparações
   - Número de trocas

---

## 💡 Como Responder à Questão

### "O tempo de voo influencia em atrasos?"

Analise os dados fornecidos:

**✅ SIM, se:**
- Tempo médio COM atraso > Tempo médio SEM atraso
- Percentual de atraso aumenta nas faixas maiores
- Correlação positiva entre tempo e atraso

**❌ NÃO, se:**
- Tempos médios são similares
- Percentual de atraso uniforme em todas as faixas
- Sem padrão claro nos dados ordenados

**⚠️ PARCIALMENTE, se:**
- Diferença pequena entre tempos médios
- Variação inconsistente entre faixas

---

## 🧪 Exemplo de Uso

```
╔════════════════════════════════════════════════════════════════════╗
║    TRABALHO PRÁTICO - ESTRUTURAS DE DADOS E ALGORITMOS            ║
║    Análise de Atrasos de Voos                                     ║
╚════════════════════════════════════════════════════════════════════╝

📂 Abrindo arquivo 'flights.csv'...
✓ Colunas identificadas - Length: índice 7, Delay: índice 8
📖 Lendo dados...
   → 100000 registros lidos...
✓ Leitura concluída: 539383 registros carregados

╔════════════════════════════════════════════════════════════════════╗
║               ESTATÍSTICAS DO DATASET                             ║
╚════════════════════════════════════════════════════════════════════╝

📊 DADOS GERAIS:
   Total de voos: 539383
   Voos com atraso: 216321 (40.12%)
   Voos sem atraso: 323062 (59.88%)

⏱️  TEMPO DE VOO:
   Menor tempo: 20 minutos
   Maior tempo: 695 minutos
   Tempo médio COM atraso: 135.42 minutos
   Tempo médio SEM atraso: 128.76 minutos

[... continua ...]
```

---

## ⚙️ Personalização

### Ajustar Limite de Registros
Arquivo `ordenacao_voos.c`, linha 24:
```c
#define MAX_REGISTROS 550000  // Ajuste conforme sua RAM
```

### Mudar Nomes dos Arquivos
Linhas 25-26:
```c
#define ARQUIVO_ENTRADA "seu_arquivo.csv"
#define ARQUIVO_SAIDA "saida_personalizada.csv"
```

---

## 🐛 Solução de Problemas

### ❌ "Não foi possível abrir o arquivo"
- Verifique se `flights.csv` está na pasta `Ordenação`
- Confirme o nome exato do arquivo

### ❌ "Memória insuficiente"
- Reduza `MAX_REGISTROS`
- Feche outros programas
- Use dataset menor para testes

### ❌ "Colunas não encontradas"
- Verifique o cabeçalho do CSV
- Confirme que existem colunas `Length` e `Delay`

### ⏱️ Programa muito lento
- **Use Quick Sort** (opção 4)
- Evite Bubble/Insert/Selection para > 50k registros
- Compile com otimização: `gcc -O2`

---

## 📂 Estrutura de Arquivos

```
Ordenação/
├── ordenacao_voos.c      # Código principal
├── gerar_dataset.c       # Gerador de dados de teste
├── README.md             # Este arquivo
├── flights.csv           # Dataset (você fornece)
└── voos_ordenados.csv    # Saída gerada
```

---

## 🎓 Conceitos Abordados

- ✅ Algoritmos de ordenação (4 implementações)
- ✅ Análise de complexidade
- ✅ Manipulação de arquivos CSV
- ✅ Alocação dinâmica de memória
- ✅ Análise estatística de dados
- ✅ Medição de desempenho

---

## 👨‍💻 Autor

**Felipe**  
Trabalho Prático - Estruturas de Dados e Algoritmos  
Data: 24 de Outubro de 2025

---

## 📚 Referências

- Cormen et al., "Introduction to Algorithms"
- Dataset: Registros de voos de companhias aéreas
- Conceitos de Estatística Descritiva

---

## 📌 Observações Importantes

✅ **Conformidade Total** com os requisitos do trabalho  
✅ **Solução 100% em C** (sem bibliotecas prontas)  
✅ **4 Algoritmos** implementados conforme especificado  
✅ **Leitura direta** do CSV original  
✅ **Saída ordenada** pela coluna Tempo  
✅ **Análise completa** para responder à questão  

---

**Bom trabalho! 🚀**
