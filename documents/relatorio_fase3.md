# Relatório Fase 3 - Etapas de uma Máquina Agrícola

## FarmTech Solutions - Banco de Dados Oracle

## 1. Introdução

Este relatório apresenta o passo a passo realizado pelo grupo **FarmTech Solutions** para a entrega da Fase 3 do projeto, cujo objetivo foi trabalhar com conceitos iniciais de banco de dados a partir dos dados coletados na Fase 2.

Na fase anterior, o grupo desenvolveu uma simulação no **Wokwi** utilizando o **ESP32** para representar um sistema de irrigação inteligente aplicado à cultura do **milho**. O sistema simulava a leitura da umidade do solo, do pH por meio de um LDR, dos nutrientes NPK e do status da bomba de irrigação.

Nesta etapa, os dados gerados pela simulação foram organizados em formato **CSV** e importados para o banco de dados **Oracle**, utilizando o **Oracle SQL Developer**. Após a importação, foram realizados testes com comandos SQL para verificar se os dados foram gravados corretamente.

---

## 2. Objetivo da atividade

O objetivo desta atividade foi importar os dados coletados pelos sensores da Fase 2 para um banco de dados relacional Oracle.

Para isso, foram realizadas as seguintes etapas:

1. Duplicação do projeto original no Wokwi;
2. Ajuste do código do ESP32 para gerar os dados em formato de tabela;
3. Cópia dos dados gerados no Serial Monitor;
4. Criação de um arquivo CSV com os dados do Wokwi;
5. Criação/importação da tabela no Oracle SQL Developer;
6. Execução de comandos SQL para testar e consultar os dados;
7. Registro de prints para comprovar o funcionamento;
8. Organização dos arquivos no GitHub.

---

## 3. Ferramentas utilizadas

As ferramentas utilizadas no desenvolvimento desta etapa foram:

- Wokwi;
- ESP32 DevKitC V4;
- Linguagem C/C++ para o código do ESP32;
- Serial Monitor do Wokwi;
- Visual Studio Code;
- Arquivo CSV;
- Oracle SQL Developer;
- Banco de dados Oracle da FIAP;
- Git e GitHub.

---

## 4. Duplicação do projeto no Wokwi

O primeiro passo foi duplicar o projeto desenvolvido anteriormente no Wokwi.

Essa duplicação foi feita para preservar a versão original da Fase 2 e permitir que o grupo realizasse alterações específicas para a Fase 3, sem perder o funcionamento anterior da simulação.

Após duplicar o projeto, mantivemos a estrutura principal do circuito, composta por:

- ESP32;
- Sensor DHT22 para simular a umidade;
- LDR para simular a leitura relacionada ao pH;
- Botões para representar os nutrientes NPK;
- Relé para representar a bomba de irrigação;
- LED indicador para representar visualmente o acionamento da bomba.

### Print do circuito no Wokwi

![Circuito no Wokwi](../assets/wokwi-circuito.png)

---

## 5. Ajuste do código do Wokwi

Após duplicar o projeto, o código do ESP32 foi ajustado.

Na versão anterior, o Serial Monitor mostrava as informações em formato mais descritivo, como um painel para o usuário acompanhar a situação do sistema.

Exemplo do formato anterior:

```text
Umidade do solo: 36.00%
Situação da umidade: SOLO SECO
Valor do LDR: 2529
Situação do pH: ADEQUADO
Resultado final: IRRIGAÇÃO ATIVADA
```

Esse formato era bom para leitura humana, mas não era o melhor formato para importar os dados em uma planilha ou banco de dados.

Por isso, o código foi adaptado para gerar uma saída em formato de tabela, separando os campos por ponto e vírgula. Dessa forma, cada leitura do sistema passou a representar uma linha, e cada informação passou a representar uma coluna.

Exemplo do novo formato gerado no Serial Monitor:

```csv
Leitura;Tempo de simulacao (s);Cultura monitorada;Umidade do solo (%);Situacao da umidade;Valor do LDR;pH simulado;Situacao do pH;Nitrogenio (N);Fosforo (P);Potassio (K);Total de nutrientes bons;Status da bomba;Decisao do sistema
1;2;Milho;36.00;Solo seco;2529;Adequado;pH adequado;Bom;Baixo;Bom;2;Irrigacao ativada;Bomba ligada porque o solo esta seco, o pH esta adequado e ha nutrientes suficientes
```

Com essa mudança, ficou possível copiar os dados do Serial Monitor e colar em um arquivo CSV.

### Print do Serial Monitor com os dados organizados

![Serial Monitor CSV](../assets/serial-monitor-csv.png)

---

## 6. Criação do arquivo CSV

Depois de executar a simulação no Wokwi, os dados gerados no Serial Monitor foram copiados e colados em um arquivo CSV.

O arquivo foi salvo dentro da pasta `src` do projeto.

Nome do arquivo utilizado:

```text
src/dados_wokwi.csv
```

O CSV foi utilizado como ponte entre o Wokwi e o banco de dados Oracle.

A estrutura do arquivo seguiu o seguinte padrão:

```csv
Leitura;Tempo de simulacao (s);Cultura monitorada;Umidade do solo (%);Situacao da umidade;Valor do LDR;pH simulado;Situacao do pH;Nitrogenio (N);Fosforo (P);Potassio (K);Total de nutrientes bons;Status da bomba;Decisao do sistema
```

Cada linha abaixo do cabeçalho representa uma leitura realizada pelo sistema.

### Print do arquivo CSV no VS Code

![Arquivo CSV no VS Code](../assets/csv-vscode.png)

---

## 7. Criação da conexão com o banco Oracle

Após preparar o arquivo CSV, o próximo passo foi acessar o **Oracle SQL Developer**.

Foi criada uma conexão com o banco Oracle da FIAP, utilizando os dados de acesso fornecidos pela instituição.

No SQL Developer, a conexão foi configurada com:

- Nome da conexão: FIAP;
- Usuário: RM do aluno;
- Senha: senha cadastrada;
- Host: oracle.fiap.com.br;
- Porta: 1521;
- SID: ORCL.

Depois de preencher os dados, a conexão foi testada. Com o teste realizado com sucesso, foi possível conectar ao banco e iniciar a importação dos dados.

---

## 8. Importação dos dados no Oracle SQL Developer

Com a conexão ativa no Oracle SQL Developer, foi realizada a importação dos dados do arquivo CSV.

O passo a passo seguido foi:

1. Abrir o Oracle SQL Developer;
2. Conectar no banco Oracle da FIAP;
3. Localizar a opção **Tabelas (Filtrado)**;
4. Clicar com o botão direito em **Tabelas (Filtrado)**;
5. Selecionar a opção **Importar Dados**;
6. Escolher o arquivo `dados_wokwi.csv`;
7. Avançar na tela de visualização dos dados;
8. Definir o nome da tabela;
9. Conferir os nomes das colunas;
10. Finalizar a importação.

O nome definido para a tabela foi:

```sql
DADOS_SENSORES
```

A tabela foi criada com os campos correspondentes aos dados gerados pela simulação no Wokwi.

---

## 9. Estrutura da tabela criada

A tabela `DADOS_SENSORES` foi criada no banco Oracle para armazenar as leituras dos sensores simulados.

As colunas criadas foram:

| Coluna | Descrição |
|---|---|
| `LEITURA` | Número da leitura realizada |
| `TEMPO_DE_SIMULACAO` | Tempo da simulação em segundos |
| `CULTURA_MONITORADA` | Cultura analisada no projeto |
| `UMIDADE_DO_SOLO` | Umidade simulada do solo |
| `SITUACAO_DA_UMIDADE` | Indica se o solo está seco ou úmido |
| `VALOR_DO_LDR` | Valor lido pelo LDR |
| `PH_SIMULADO` | Classificação simbólica do pH |
| `SITUACAO_DO_PH` | Indica se o pH está adequado ou fora da faixa ideal |
| `NITROGENIO_N` | Situação do Nitrogênio |
| `FOSFORO_P` | Situação do Fósforo |
| `POTASSIO_K` | Situação do Potássio |
| `TOTAL_DE_NUTRIENTES_BONS` | Quantidade de nutrientes em boas condições |
| `STATUS_DA_BOMBA` | Indica se a irrigação foi ativada ou desligada |
| `DECISAO_DO_SISTEMA` | Explica o motivo da decisão tomada pelo sistema |

### Print da estrutura da tabela no Oracle

![Estrutura da tabela Oracle](../assets/oracle-colunas.png)

---

## 10. Validação dos dados importados

Após a importação, foi necessário validar se os dados foram realmente inseridos na tabela.

Para isso, a tabela `DADOS_SENSORES` foi aberta no Oracle SQL Developer, na aba **Dados**.

Nessa aba foi possível visualizar os registros importados a partir do arquivo CSV.

### Print dos dados importados

![Dados importados no Oracle](../assets/oracle-dados.png)

---

## 11. Teste com comandos SQL

Depois de confirmar que a tabela foi criada, foram executados comandos SQL para consultar e analisar os dados.

### 11.1 Consulta geral dos dados

O primeiro comando utilizado foi:

```sql
SELECT * FROM DADOS_SENSORES;
```

Esse comando retorna todos os registros e todas as colunas da tabela.

Ele foi utilizado para comprovar que os dados do arquivo CSV foram importados corretamente para o banco Oracle.

### Print da consulta SELECT geral

![Consulta SELECT](../assets/select-dados-sensores.png)

---

### 11.2 Consulta dos principais campos da irrigação

Também foi realizada uma consulta selecionando apenas os campos principais do sistema:

```sql
SELECT 
    LEITURA,
    CULTURA_MONITORADA,
    UMIDADE_DO_SOLO,
    SITUACAO_DA_UMIDADE,
    STATUS_DA_BOMBA
FROM DADOS_SENSORES;
```

Essa consulta facilita a visualização da relação entre a umidade do solo e o acionamento da bomba.

---

### 11.3 Consulta por status da bomba

Foi executada uma consulta para contar quantas vezes a bomba apareceu em cada status:

```sql
SELECT 
    STATUS_DA_BOMBA,
    COUNT(*) AS QUANTIDADE
FROM DADOS_SENSORES
GROUP BY STATUS_DA_BOMBA;
```

Essa consulta permite verificar quantas leituras tiveram irrigação ativada e quantas tiveram irrigação desligada.

### Print da consulta por status da bomba

![Consulta Status da Bomba](../assets/consulta-status-bomba.png)

---

### 11.4 Consulta da média de umidade do solo

Também foi utilizada uma consulta para calcular a média da umidade do solo:

```sql
SELECT 
    AVG(UMIDADE_DO_SOLO) AS MEDIA_UMIDADE
FROM DADOS_SENSORES;
```

Essa consulta mostra como os dados armazenados no banco podem ser utilizados para análises simples.

---

### 11.5 Consulta das leituras com solo seco

Por fim, foi realizada uma consulta para filtrar apenas os registros em que o solo foi identificado como seco:

```sql
SELECT 
    LEITURA,
    UMIDADE_DO_SOLO,
    SITUACAO_DA_UMIDADE,
    VALOR_DO_LDR,
    SITUACAO_DO_PH,
    DECISAO_DO_SISTEMA
FROM DADOS_SENSORES
WHERE SITUACAO_DA_UMIDADE = 'Solo seco';
```

Essa consulta ajuda a entender quais decisões foram tomadas pelo sistema quando a umidade estava baixa.

---

## 12. Organização dos arquivos no GitHub

Após a validação no banco, os arquivos do projeto foram organizados no repositório GitHub.

A estrutura utilizada foi:

```text
cursotiao-pbl-fase3/
│
├── README.md
│
├── assets/
│   ├── wokwi-circuito.png
│   ├── serial-monitor-csv.png
│   ├── csv-vscode.png
│   ├── oracle-colunas.png
│   ├── oracle-dados.png
│   ├── select-dados-sensores.png
│   └── consulta-status-bomba.png
│
├── document/
│   └── relatorio_fase3.md
│
├── scripts/
│   ├── criar_tabela.sql
│   └── consultas_sql.sql
│
└── src/
    ├── codigo_wokwi.ino
    ├── diagram.json
    └── dados_wokwi.csv
```

A pasta `assets` foi utilizada para guardar os prints do projeto.

A pasta `src` foi utilizada para armazenar o código do Wokwi, o arquivo do circuito e o CSV com os dados.

A pasta `scripts` foi utilizada para armazenar os comandos SQL executados no banco.

A pasta `document` foi utilizada para armazenar este relatório.

O arquivo `README.md` ficou na raiz do projeto, servindo como guia principal da entrega.

---

## 13. Atualização do repositório

Depois de organizar os arquivos, os dados foram enviados para o GitHub pelo terminal do VS Code.

Os comandos utilizados foram:

```bash
git add .
git commit -m "Organiza entrega da fase 3 com dados do Oracle"
git push
```

Esses comandos permitiram atualizar o repositório com o relatório, os prints, os arquivos CSV, os códigos e as consultas SQL.

---

## 14. Conclusão

Com esta atividade, foi possível demonstrar o fluxo completo dos dados dentro do projeto FarmTech Solutions.

Primeiro, os dados foram gerados por uma simulação no Wokwi, utilizando ESP32 e sensores simulados. Em seguida, o código foi ajustado para transformar as leituras em uma saída organizada em formato de tabela. Depois, os dados foram copiados para um arquivo CSV e importados no banco Oracle por meio do Oracle SQL Developer.

Após a importação, os comandos SQL foram executados para validar a gravação dos dados e realizar consultas básicas, como visualização geral dos registros, contagem por status da bomba e análise da umidade do solo.

Dessa forma, o grupo conseguiu transformar dados simulados de sensores em registros estruturados dentro de um banco de dados relacional, criando uma base para futuras análises, dashboards e aplicações de inteligência artificial no agronegócio.
