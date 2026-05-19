#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

// Botoes dos nutrientes
int botaoN = 18;
int botaoP = 19;
int botaoK = 21;

// Sensor que vai simular o pH
int ldrPin = 34;

// Rele que representa a bomba de irrigacao
int relePin = 23;

// Contador de leituras para organizar a planilha
int numeroLeitura = 0;

// Se estiver true, imprime em formato de planilha.
// Se trocar para false, imprime no modelo descritivo bonito.
bool modoPlanilha = true;

void setup() {
  Serial.begin(115200);

  pinMode(botaoN, INPUT_PULLUP);
  pinMode(botaoP, INPUT_PULLUP);
  pinMode(botaoK, INPUT_PULLUP);
  pinMode(relePin, OUTPUT);

  digitalWrite(relePin, LOW);

  dht.begin();

  Serial.println("==============================================================");
  Serial.println("        SISTEMA DE IRRIGACAO AUTOMATICA - CULTURA MILHO");
  Serial.println("==============================================================");
  Serial.println("Projeto desenvolvido para simulacao no ESP32 - Wokwi");
  Serial.println();
  Serial.println("Componentes monitorados:");
  Serial.println("- DHT22: umidade do solo simulada");
  Serial.println("- LDR: pH do solo simulado");
  Serial.println("- Botao 1: Nitrogenio (N)");
  Serial.println("- Botao 2: Fosforo (P)");
  Serial.println("- Botao 3: Potassio (K)");
  Serial.println("- Rele: bomba de irrigacao");
  Serial.println();
  Serial.println("Regra do sistema:");
  Serial.println("A bomba liga quando o solo esta seco, o pH esta adequado");
  Serial.println("e pelo menos 2 nutrientes estao em boas condicoes.");
  Serial.println("==============================================================");
  Serial.println();

  if (modoPlanilha) {
    Serial.println("COPIE A PARTIR DA LINHA ABAIXO PARA USAR NO EXCEL:");
    Serial.println();

    Serial.println("Leitura;Tempo de simulacao (s);Cultura monitorada;Umidade do solo (%);Situacao da umidade;Valor do LDR;pH simulado;Situacao do pH;Nitrogenio (N);Fosforo (P);Potassio (K);Total de nutrientes bons;Status da bomba;Decisao do sistema");
  }
}

void loop() {
  numeroLeitura++;

  // Leitura dos botoes
  int leituraN = digitalRead(botaoN);
  int leituraP = digitalRead(botaoP);
  int leituraK = digitalRead(botaoK);

  // Leitura do LDR e da umidade
  int valorLDR = analogRead(ldrPin);
  float umidade = dht.readHumidity();

  // Evita erro caso o DHT22 falhe
  if (isnan(umidade)) {
    Serial.println("Erro na leitura da umidade;Verifique o sensor DHT22");
    delay(2000);
    return;
  }

  // Verificando se os nutrientes estao adequados
  bool nitrogenioBom = (leituraN == LOW);
  bool fosforoBom = (leituraP == LOW);
  bool potassioBom = (leituraK == LOW);

  int totalNutrientesBons = 0;

  if (nitrogenioBom) {
    totalNutrientesBons++;
  }

  if (fosforoBom) {
    totalNutrientesBons++;
  }

  if (potassioBom) {
    totalNutrientesBons++;
  }

  // Regra para o pH simulado pelo LDR
  bool phAdequado = (valorLDR >= 1500 && valorLDR <= 3000);

  // Valor simbolico para deixar a planilha mais explicativa
  String phSimulado;

  if (valorLDR < 1500) {
    phSimulado = "Acido";
  } else if (valorLDR <= 3000) {
    phSimulado = "Adequado";
  } else {
    phSimulado = "Alcalino";
  }

  // Regra para solo seco
  bool soloSeco = (umidade < 40);

  // Decisao da irrigacao
  bool ligarBomba = false;

  if (soloSeco && phAdequado && totalNutrientesBons >= 2) {
    ligarBomba = true;
  }

  if (ligarBomba) {
    digitalWrite(relePin, HIGH);
  } else {
    digitalWrite(relePin, LOW);
  }

  // Textos organizados para aparecerem na planilha
  String cultura = "Milho";

  String situacaoUmidade;
  if (soloSeco) {
    situacaoUmidade = "Solo seco";
  } else {
    situacaoUmidade = "Solo umido";
  }

  String situacaoPH;
  if (phAdequado) {
    situacaoPH = "pH adequado";
  } else {
    situacaoPH = "pH fora da faixa ideal";
  }

  String statusN;
  if (nitrogenioBom) {
    statusN = "Bom";
  } else {
    statusN = "Baixo";
  }

  String statusP;
  if (fosforoBom) {
    statusP = "Bom";
  } else {
    statusP = "Baixo";
  }

  String statusK;
  if (potassioBom) {
    statusK = "Bom";
  } else {
    statusK = "Baixo";
  }

  String statusBomba;
  String decisaoSistema;

  if (ligarBomba) {
    statusBomba = "Irrigacao ativada";
    decisaoSistema = "Bomba ligada porque o solo esta seco, o pH esta adequado e ha nutrientes suficientes";
  } else {
    statusBomba = "Irrigacao desligada";

    if (!soloSeco) {
      decisaoSistema = "Bomba desligada porque o solo ainda esta umido";
    } else if (!phAdequado) {
      decisaoSistema = "Bomba desligada porque o pH esta fora da faixa ideal";
    } else if (totalNutrientesBons < 2) {
      decisaoSistema = "Bomba desligada porque ha menos de 2 nutrientes em boas condicoes";
    } else {
      decisaoSistema = "Bomba desligada porque alguma condicao nao foi atendida";
    }
  }

  if (modoPlanilha) {
    imprimirLinhaPlanilha(
      numeroLeitura,
      millis() / 1000,
      cultura,
      umidade,
      situacaoUmidade,
      valorLDR,
      phSimulado,
      situacaoPH,
      statusN,
      statusP,
      statusK,
      totalNutrientesBons,
      statusBomba,
      decisaoSistema
    );
  } else {
    imprimirPainelBonito(
      numeroLeitura,
      cultura,
      umidade,
      situacaoUmidade,
      valorLDR,
      phSimulado,
      situacaoPH,
      statusN,
      statusP,
      statusK,
      totalNutrientesBons,
      statusBomba,
      decisaoSistema
    );
  }

  delay(2000);
}

void imprimirLinhaPlanilha(
  int leitura,
  unsigned long tempo,
  String cultura,
  float umidade,
  String situacaoUmidade,
  int valorLDR,
  String phSimulado,
  String situacaoPH,
  String statusN,
  String statusP,
  String statusK,
  int totalNutrientesBons,
  String statusBomba,
  String decisaoSistema
) {
  Serial.print(leitura);
  Serial.print(";");

  Serial.print(tempo);
  Serial.print(";");

  Serial.print(cultura);
  Serial.print(";");

  Serial.print(umidade, 2);
  Serial.print(";");

  Serial.print(situacaoUmidade);
  Serial.print(";");

  Serial.print(valorLDR);
  Serial.print(";");

  Serial.print(phSimulado);
  Serial.print(";");

  Serial.print(situacaoPH);
  Serial.print(";");

  Serial.print(statusN);
  Serial.print(";");

  Serial.print(statusP);
  Serial.print(";");

  Serial.print(statusK);
  Serial.print(";");

  Serial.print(totalNutrientesBons);
  Serial.print(";");

  Serial.print(statusBomba);
  Serial.print(";");

  Serial.println(decisaoSistema);
}

void imprimirPainelBonito(
  int leitura,
  String cultura,
  float umidade,
  String situacaoUmidade,
  int valorLDR,
  String phSimulado,
  String situacaoPH,
  String statusN,
  String statusP,
  String statusK,
  int totalNutrientesBons,
  String statusBomba,
  String decisaoSistema
) {
  Serial.println("--------------------------------------------------------------");
  Serial.print("LEITURA ");
  Serial.println(leitura);
  Serial.println("Sistema inteligente de irrigacao - Cultura do milho");
  Serial.println("--------------------------------------------------------------");

  Serial.print("Cultura monitorada: ");
  Serial.println(cultura);

  Serial.print("Umidade do solo: ");
  Serial.print(umidade, 2);
  Serial.println("%");

  Serial.print("Situacao da umidade: ");
  Serial.println(situacaoUmidade);

  Serial.println();

  Serial.print("Valor do LDR: ");
  Serial.println(valorLDR);

  Serial.print("pH simulado: ");
  Serial.println(phSimulado);

  Serial.print("Situacao do pH: ");
  Serial.println(situacaoPH);

  Serial.println();

  Serial.print("Nitrogenio (N): ");
  Serial.println(statusN);

  Serial.print("Fosforo (P): ");
  Serial.println(statusP);

  Serial.print("Potassio (K): ");
  Serial.println(statusK);

  Serial.println();

  Serial.print("Total de nutrientes bons: ");
  Serial.println(totalNutrientesBons);

  Serial.print("Status da bomba: ");
  Serial.println(statusBomba);

  Serial.print("Decisao do sistema: ");
  Serial.println(decisaoSistema);

  Serial.println("--------------------------------------------------------------");
  Serial.println();
}