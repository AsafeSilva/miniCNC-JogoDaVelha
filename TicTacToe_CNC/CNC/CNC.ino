/*=================  TIC TAC TOE - CNC =================*/

/*
 * EIXO Y         --> 8,9,10,11
 * EIXO X         --> 2,3,4,5
 * EIXO Z         --> 14,15,16,17 (A0,A1,A2,A3)
 * FIM DE CURSO Y --> 12  
 * FIM DE CURSO X --> 6
 * FIM DE CURSO Z --> 19 (A5)
 * LED            --> 13
 * INFRA VERMELHO --> 7
 * 1º JOGADOR     --> 18 (A4)
 */

#define HALF_STEP
//#define FULL_STEP       // Necessário mudar a variável stepsTotal

#define pinPlayer   18
#define pinLed      13
#define pinFimX     6
#define pinFimY     12
#define pinFimZ     19
#define pinIR       7
#define HALF        6
#define FULL        4
#define X           1
#define Y           2
#define Z           3
#define stepsTotal  380

byte stepsX [HALF] = {B100000, B101000, B001000, B010000, B010100, B000100};  // ordem de acionamento das bobinas
byte stepsY [HALF] = {B1000, B1010, B0010, B0100, B0101, B0001};              // ordem de acionamento das bobinas
byte stepsZ [HALF] = {B1000, B1010, B0010, B0100, B0101, B0001};              // ordem de acionamento das bobinas
//byte stepsX [FULL] = {B100000, B001000, B010000, B000100};                  // ordem de acionamento das bobinas
//byte stepsY [FULL] = {B1000, B0010, B0100, B0001};                          // ordem de acionamento das bobinas

int i;                                                                        // retorna a linha do ganhador
#define speed 5

byte pinsOut[13] = {2, 3, 4, 5, 8, 9, 10, 11, pinLed, 14, 15, 16, 17};        // portas de saída

int  sentido;                                                                 // sentido de giro do motor [-1 ou 1]
int8_t indexX = 0, indexY = 0, indexZ = 0;
int contStepX = 0, contStepY = 0, contStepZ;                                  // contagem de passos
unsigned long lastTimeX, lastTimeY, lastTimeZ;

int game[9] = {0};                                                            // armazena jogo atual
int jogador;                                                                  //-1 --> "O"  e  1 --> "X"
int jogadas;                                                                  // quantidade de jogadas
boolean finish = false;                                                       // testar se o jogo acabou

boolean firstPlayer;                                                          // 0 --> MÁQUINA; 1 --> JOGADOR 

void setup(){
  // Inicializa Serial
  Serial.begin(9600);
  while(!Serial);

  // ========== SETA PORTAS DE SAÍDA E ENTRADA ==========
  for(int i = 0; i < 13; i++)  pinMode(pinsOut[i], OUTPUT);
  pinMode(pinPlayer, INPUT);
  pinMode(pinFimX,   INPUT);
  pinMode(pinFimY,   INPUT);
  pinMode(pinFimZ,   INPUT);
  delay(100);
  // ****************************************************
 
  config_(digitalRead(pinPlayer));                                            // configura 1° jogador

  if(fimCurso(pinFimZ)){  contStepZ = 0;  eixoZ(100, speed);  }               // inicia eixo Z
  
  init(speed);                                                                // zera eixos
  drawTable(speed);                                                           // desenha tabuleiro

  ///*  se a máquina começar, faz ela jogar sem precisar processar algoritimo
  if(firstPlayer == 0){
    drawPlayer(1,0,speed);
      game[0] = 1;              // atualiza matriz(tabuleiro) do jogo
      jogadas++;                // incrementa nº de jogadas 
      firstPlayer = true;       // desabilita jogada da máquina
  }
  //*/
}

String inString = "";
int number;

void loop(){
  process_(); 
/*  
  while (Serial.available() > 0) {
    char inChar = Serial.read();

    if (inChar != '\n') { 
      inString += inChar;
    }
    else {
      number = inString.toInt();
      Serial.println(number);
      
      while(contStepY != number) eixoY(5, number);

      inString = "";
    }
  }
*/
}




