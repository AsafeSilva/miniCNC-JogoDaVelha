#include "IRremote.h"         // inclue biblioteca para Infra-Vermelho

// instancia obejto da biblioteca
IRrecv irrecv(pinIR);         
decode_results results;       


void config_(int player){
  firstPlayer = player; // inicializa 1° jogador
  irrecv.enableIRIn();  // Start the receiver
}

void process_(){
  digitalWrite(13,1);                           // liga led quando á máquina não está jogando
  if (irrecv.decode(&results)) {                // checa o sensor IR
    playerMove( decodeIR(results.value) );      // desenha na casa X [0-8]
    irrecv.resume();                            // Receive the next value
  }
  
  if(!firstPlayer)  computerMove(game);         // jogada da máquina
}

int decodeIR(long value){
  long buttons[9] = {0xFF807F, 0xFF40BF, 0xFFC03F, 0xFF20DF, 0xFFA05F, 0xFF609F, 0xFFE01F, 0xFF10EF, 0xFF906F};

  for(byte i = 0; i < 9; i++){
    if(value == buttons[i])  return i;  // compara o valor recebido com a posição do array
  }
  return -1;
}


int win(int board[]){
  int wins[8][3] = {{0,1,2},
                    {3,4,5},
                    {6,7,8},
                    {0,3,6},
                    {1,4,7},
                    {2,5,8},
                    {0,4,8},
                    {2,4,6}}; 

  for(i = 0; i < 8; i++){
    if(board[wins[i][0]] != 0 &&
       board[wins[i][0]] == board[wins[i][1]] &&
       board[wins[i][1]] == board[wins[i][2]])
       return board[wins[i][2]];                  // retorna vencedor (1 ou -1)
  }

  return 0;                     
}

void draw(int board[]){

  Serial.print(checkPlay(board[0]));
  Serial.print("  | ");
  Serial.print(checkPlay(board[1]));
  Serial.print(" | ");
  Serial.println(checkPlay(board[2]));
  Serial.println( "---+---+---");

  Serial.print(checkPlay(board[3]));
  Serial.print("  | ");
  Serial.print(checkPlay(board[4]));
  Serial.print(" | ");
  Serial.println(checkPlay(board[5]));
  Serial.println( "---+---+---");

  Serial.print(checkPlay(board[6]));
  Serial.print("  | ");
  Serial.print(checkPlay(board[7]));
  Serial.print(" | ");
  Serial.println(checkPlay(board[8]));
  Serial.println();
}

// conversão de número p/ caractere
char checkPlay(int i){
    switch(i) {
        case 1:
            return 'X';
        case -1:
            return 'O';
        case 0:
            return ' ';
    }
  return ' ';
}

int minmax(int board[], int player){
  
  int winner = win(board);
  if(winner != 0) return winner*player; // condição de parada
  
  int move = -1;
  int score = -2;
  
  for(int i = 0; i < 9; i++){
    if(board[i] == 0){                              // se casa não estiver preenchida
       board[i] = player;
       int thisScore = -minmax(board, player*-1);   // realiza cálculo recursivo
       if(thisScore > score){
          score = thisScore;
          move = i;
       }
       board[i] = 0;
    }
  }
  
  if(move == -1) return 0;
  return score;
}


void computerMove(int board[]){
  jogador = 1;                // atualiza jogador 
  int val = -1;
  int score = -2;
  digitalWrite(13,0);

  if (!finish) {              // jogo não acabou?

    for(int i = 0; i < 9; i++){
      if(board[i] == 0){           // testa se a casa não foi jogada
          board[i] = jogador;
          int tempScore = -minmax(board, -1);
          board[i] = 0;
          if(tempScore > score){
             score = tempScore;
             val = i;
          }
      }
    }

      drawPlayer(jogador, val, speed);  // desenha jogador no tabuleiro
      game[val] = jogador;              // atualiza matriz(tabuleiro) do jogo
      firstPlayer = true;               // desabilita jogada da máquina
      jogadas++;                        // incrementa nº de jogadas 
      draw(game);


      if(win(game) != 0){
        drawWin(i, speed);
        finish = true;
      }else if(jogadas == 9 && win(game) == 0){
        drawWin(8, speed);
        finish = true;
      }

/*
        if(win(game) != 0){                        // alguém ganhou?
          Serial.print("\n=========== ");           // escreve na tela
          Serial.print(checkPlay(win(game)));           // escreve na tela
          Serial.print(" WIN! ");           // escreve na tela
          Serial.println("===========");            // escreve na tela
          finish = true;                                          // finaliza jogo
        }else if(jogadas == 9 && win(game) == 0){  // empate? 
          Serial.println("\n=========== EMPATE ==========="); 
          finish = true;
        }  
*/         
    firstPlayer = true;  // desabilita jogada da máquina
  }
}

void playerMove(int val){
  if(val >= 0 && firstPlayer){
      jogador = -1;
      if(!finish){
        
        if(game[val] == 0){
          digitalWrite(13,0);  
          drawPlayer(jogador, val, speed);
          game[val] = jogador;
    
          jogadas++;
          draw(game);


        if(win(game) != 0){
          drawWin(i, speed);
          finish = true;
        }else if(jogadas == 9 && win(game) == 0){
          drawWin(8, speed);
          finish = true;
        }

/*    
            if(win(game) != 0){                        // alguém ganhou?
              Serial.print("=========== ");           // escreve na tela
              Serial.print(checkPlay(win(game)));           // escreve na tela
              Serial.print(" WIN! ");           // escreve na tela
              Serial.println("===========");            // escreve na tela
              finish = true;                                          // finaliza jogo
            }else if(jogadas == 9 && win(game) == 0){  // empate? 
              Serial.println("=========== EMPATE ==========="); 
              finish = false;
            }
*/            
          firstPlayer = false;         
        }
      }  
  }
}


