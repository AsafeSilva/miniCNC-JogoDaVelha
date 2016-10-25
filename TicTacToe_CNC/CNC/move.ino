void drawPlayer(int player, int pos, int velocidade) {
  int valX, valY;
  int newStepX, newStepY;
  int sentY = -1, sentX = -1;
  
  if (player == -1) {
    
      if (pos <= 2) {
        valY = 5;
        valX = (2 * pos + 1);
      } else if (pos <= 5) {
        valY = 3;
        valX = (2 * pos - 5);
      } else {
        valY = 1;
        valX = (2 * pos - 11);
      }

    /*   SUBIR EIXO Z   */  eixoZ(100, velocidade);
    while (1) {  
      if (contStepX != stepsTotal * valX/6) moveMotor(X, -velocidade);
      if (contStepY != stepsTotal * valY/6) moveMotor(Y, -velocidade);
      if (contStepX == stepsTotal * valX/6 && contStepY == stepsTotal * valY/6) break;
    }
    contStepX = 0;
    contStepY = 0;

    while (contStepX != -63) moveMotor(X, velocidade);
    /*   BAIXAR EIXO Z   */ eixoZ(0, -velocidade);
    while (true) {

      newStepX = contStepX;
      if (newStepX == 63)sentX = sentX * -1;

      while (contStepX != newStepX + sentX * -1) moveMotor(X, sentX * velocidade);

      newStepY = sentX * sqrt( pow(63, 2) - pow(newStepX, 2));
      while (contStepY != newStepY)  moveMotor(Y, sentY * velocidade);

      if (newStepX == 0) sentY = sentY * -1;

      if (contStepX == -63)  break;
    }
/*****************************************************************************************/
  }else if(player == 1){

      if(pos <= 2){
        
        eixoZ(100, velocidade);
        while(1){
          if(contStepX != stepsTotal*pos/3) moveMotor(X, -velocidade);
          if(contStepY != stepsTotal*3/3)   moveMotor(Y, -velocidade);
          if(contStepX == stepsTotal*pos/3 && contStepY == stepsTotal*3/3) break;
        }

        eixoZ(0, -velocidade);
        while(1){
          if(contStepX != stepsTotal*(pos+1)/3) moveMotor(X, -velocidade); 
          if(contStepY != stepsTotal*2/3)       moveMotor(Y, -velocidade);
          if(contStepX == stepsTotal*(pos+1)/3 && contStepY == stepsTotal*2/3) break;
        }

        eixoZ(100, velocidade);
        while(contStepY != stepsTotal*3/3)  moveMotor(Y, velocidade);
        
        eixoZ(0, -velocidade);
        while(1){
          if(contStepX != stepsTotal*pos/3) moveMotor(X, velocidade);
          if(contStepY != stepsTotal*2/3)   moveMotor(Y, -velocidade);
          if(contStepX == stepsTotal*pos/3 && contStepY == stepsTotal*2/3) break;
        }

/***************************************************************************************/
      }else if(pos <= 5){

        eixoZ(100, velocidade);
        while(1){
          if(contStepX != stepsTotal*int(map(pos, 3, 5, 0, 2))/3) moveMotor(X, -velocidade);
          if(contStepY != stepsTotal*2/3)   moveMotor(Y, -velocidade);
          if(contStepX == stepsTotal*int(map(pos, 3, 5, 0, 2))/3 && contStepY == stepsTotal*2/3) break;
        }     

        eixoZ(0, -velocidade);
        while(1){
          if(contStepX != stepsTotal*(int(map(pos, 3, 5, 0, 2))+1)/3) moveMotor(X, -velocidade); 
          if(contStepY != stepsTotal*1/3)       moveMotor(Y, -velocidade);
          if(contStepX == stepsTotal*(int(map(pos, 3, 5, 0, 2))+1)/3 && contStepY == stepsTotal*1/3) break;
        }

        eixoZ(100, velocidade);
        while(contStepY != stepsTotal*2/3)  moveMotor(Y, velocidade);

        eixoZ(0, -velocidade);
        while(1){
          if(contStepX != stepsTotal*(int(map(pos, 3, 5, 0, 2)))/3) moveMotor(X, velocidade); 
          if(contStepY != stepsTotal*1/3)       moveMotor(Y, -velocidade);
          if(contStepX == stepsTotal*(int(map(pos, 3, 5, 0, 2)))/3 && contStepY == stepsTotal*1/3) break;
        }
/***************************************************************************************/                        
      }else{

        eixoZ(100, velocidade);
        while(1){
          if(contStepX != stepsTotal*int(map(pos, 6, 8, 0, 2))/3) moveMotor(X, -velocidade);
          if(contStepY != stepsTotal*1/3)   moveMotor(Y, -velocidade);
          if(contStepX == stepsTotal*int(map(pos, 6, 8, 0, 2))/3 && contStepY == stepsTotal*1/3) break;
        }  

        eixoZ(0, -velocidade);
        while(1){
          if(contStepX != stepsTotal*(int(map(pos, 6, 8, 0, 2))+1)/3) moveMotor(X, -velocidade); 
          if(contStepY != stepsTotal*0/3)       moveMotor(Y, -velocidade);
          if(contStepX == stepsTotal*(int(map(pos, 6, 8, 0, 2))+1)/3 && contStepY == stepsTotal*0/3) break;
        }

        eixoZ(100, velocidade);
        while(contStepY != stepsTotal*1/3)  moveMotor(Y, velocidade); 

        eixoZ(0, -velocidade);
        while(1){
          if(contStepX != stepsTotal*(int(map(pos, 6, 8, 0, 2)))/3) moveMotor(X, velocidade); 
          if(contStepY != stepsTotal*0/3)       moveMotor(Y, -velocidade);
          if(contStepX == stepsTotal*(int(map(pos, 6, 8, 0, 2)))/3 && contStepY == stepsTotal*0/3) break;
        }               
         
      }    
  }
    eixoZ(100, velocidade);
    init(velocidade);
    contStepY = stepsTotal;
    contStepX = 0;    
//    PORTB = 0;
//    PORTD = 0;
//    PORTC = 0;
}

void drawTable(int velocidade) {
  contStepX = 0;

  while (contStepX != stepsTotal / 3) moveMotor(X, -velocidade);
  /*   BAIXAR EIXO Z   */ 
  while(!fimCurso(pinFimZ)){
    moveMotor(Z, -velocidade);   //eixoZ(0, -velocidade);
    contStepZ = 0;
  }
  while (!fimCurso(pinFimY)) moveMotor(Y, -velocidade);
  /*   SUBIR EIXO Z   */  eixoZ(100, velocidade);
  while (contStepX != stepsTotal * 2 / 3) moveMotor(X, -velocidade);
  /*   BAIXAR EIXO Z   */ eixoZ(0, -velocidade);
  while (contStepY != stepsTotal) moveMotor(Y, velocidade);
  /*   SUBIR EIXO Z   */  eixoZ(100, velocidade);

  while (true) {
    if (contStepX != stepsTotal)      moveMotor(X, -velocidade);
    if (contStepY != stepsTotal * 2 / 3)  moveMotor(Y, -velocidade);
    if (contStepX == stepsTotal && contStepY == stepsTotal * 2 / 3)  break;
  }
  /*   BAIXAR EIXO Z   */ eixoZ(0, -velocidade);
  while (!fimCurso(pinFimX)) moveMotor(X, velocidade);
  /*   SUBIR EIXO Z   */  eixoZ(100, velocidade);
  while (contStepY != stepsTotal * 1 / 3)  moveMotor(Y, -velocidade);
  /*   BAIXAR EIXO Z   */ eixoZ(0, -velocidade);
  while (contStepX != stepsTotal) moveMotor(X, -velocidade);
  /*   SUBIR EIXO Z   */  eixoZ(100, velocidade);

  while (true) {
    if (!fimCurso(pinFimX))      moveMotor(X, velocidade);
    if (contStepY != stepsTotal) moveMotor(Y, velocidade);
    if (fimCurso(pinFimX) && contStepY == stepsTotal)  break;
  }

  PORTB = 0;
  PORTD = 0;
  PORTC = 0;

}

void drawWin(int winner, int velocidade){
//******************************************************************************
  if(winner <= 2){
    while(true){
      if(contStepX != 0)  moveMotor(X, velocidade);
      if(contStepY != stepsTotal*(-2*winner + 5)/6) moveMotor(Y, -velocidade);
      if(contStepX == 0 && contStepY == stepsTotal*(-2*winner + 5)/6) break;
    }
    eixoZ(0, -velocidade);
    while(contStepX != stepsTotal) moveMotor(X, -velocidade);
    eixoZ(100, velocidade);    
//******************************************************************************
  }else if(winner <= 5){
    while(true){
      if(contStepX != stepsTotal*(2*winner - 5)/6)  moveMotor(X, -velocidade);
//    if(contStepY != stepsTotal)                   moveMotor(Y, velocidade);
      if(contStepX == stepsTotal*(2*winner - 5)/6) break;
    }
    eixoZ(0, -velocidade);
    while(contStepY != 0) moveMotor(Y, -velocidade);
    eixoZ(100, velocidade);
//******************************************************************************
  }else{
    if(winner == 6){
      eixoZ(0, -velocidade);
      while(true){
        if(contStepX != stepsTotal) moveMotor(X, -velocidade);
        if(contStepY != 0)          moveMotor(Y, -velocidade);
        if(contStepX == stepsTotal && contStepY == 0) break;
      }
      eixoZ(100, velocidade);
    }
    if(winner == 7){
      while(contStepY != 0) moveMotor(Y, -velocidade);
      eixoZ(0, -velocidade);
      while(true){
        if(contStepX != stepsTotal) moveMotor(X, -velocidade);
        if(contStepY != stepsTotal) moveMotor(Y, velocidade);
        if(contStepX == stepsTotal && contStepY == stepsTotal) break;
      }
      eixoZ(100, velocidade);
    }
    if(winner == 8){
      eixoZ(0, -velocidade);
      while(contStepY != 0) moveMotor(Y, -velocidade);
      while(contStepX != stepsTotal) moveMotor(X, -velocidade);
      while(contStepY != stepsTotal) moveMotor(Y, velocidade);
      while(contStepX != 0) moveMotor(X, velocidade);
      eixoZ(100, velocidade);
    }
  }

  init(velocidade);
}


void init(int velocidade) {
  lastTimeX = lastTimeY = millis();
  indexX = indexY = 0;
  //  MOVIMENTA OS EIXOS X E Y PARA O FIM DE CURSO
  while (true) {
    if (!fimCurso(pinFimY)) moveMotor(Y, -velocidade);
    if (!fimCurso(pinFimX)) moveMotor(X, velocidade);
    if (fimCurso(pinFimY) && fimCurso(pinFimX)) break;
  }
  contStepY = 0;
  contStepX = 0;
  lastTimeX = lastTimeY = millis();
  indexX = indexY = 0;
  //  COLOCA O EIXO Y NA VISÃO DO JOGADOR
  while (contStepY != stepsTotal) moveMotor(Y, velocidade);

 PORTB = 0;
 PORTD = 0;
}

void moveMotor(int eixo, float velocidade) {
  if (velocidade != 0) {
    if (eixo == X) {
      if (millis() - lastTimeX >= abs(velocidade)) {  // true every X miliseconds
        PORTD = stepsX[indexX]; // set the PORTB with value of the array

        if (velocidade > 0) sentido = -1;
        else                sentido = 1;

        indexX += sentido;    // incrementa ou decrementa o contador
        contStepX += sentido;

#ifdef HALF_STEP
        switch (sentido) {
          case 1:
            if (indexX > HALF - 1) indexX = 0x00;
            break;
          case -1:
            if (indexX < 0x00) indexX = HALF - 1;
            break;
        }
#endif
#ifdef FULL_STEP
        switch (sentido) {
          case 1:
            if (indexX > FULL - 1) indexX = 0x00;
            break;
          case -1:
            if (indexX < 0x00) indexX = FULL - 1;
            break;
        }
#endif

        lastTimeX = millis();  // reinicia a contagem de tempo
      }
    }

    if (eixo == Y) {
      if (millis() - lastTimeY >= abs(velocidade)) {  // true every X miliseconds
        PORTB = stepsY[indexY]; // set the PORTB with value of the array

        if (velocidade > 0) sentido = 1;
        else                sentido = -1;

        indexY += sentido;    // incrementa ou decrementa o contador
        contStepY += sentido;

#ifdef HALF_STEP
        switch (sentido) {
          case 1:
            if (indexY > HALF - 1) indexY = 0x00;
            break;
          case -1:
            if (indexY < 0x00) indexY = HALF - 1;
            break;
        }
#endif
#ifdef FULL_STEP
        switch (sentido) {
          case 1:
            if (indexY > FULL - 1) indexY = 0x00;
            break;
          case -1:
            if (indexY < 0x00) indexY = FULL - 1;
            break;
        }
#endif

        lastTimeY = millis();  // reinicia a contagem de tempo
      }
    }

    if (eixo == Z) {
      if (millis() - lastTimeZ >= abs(velocidade)) {  // true every X miliseconds
        PORTC = stepsZ[indexZ]; // set the PORTB with value of the array

        if (velocidade > 0) sentido = 1;
        else                sentido = -1;

        indexZ += sentido;    // incrementa ou decrementa o contador
        contStepZ += sentido;

#ifdef HALF_STEP
        switch (sentido) {
          case 1:
            if (indexZ > HALF - 1) indexZ = 0x00;
            break;
          case -1:
            if (indexZ < 0x00) indexZ = HALF - 1;
            break;
        }
#endif
#ifdef FULL_STEP
        switch (sentido) {
          case 1:
            if (indexZ > FULL - 1) indexZ = 0x00;
            break;
          case -1:
            if (indexZ < 0x00) indexZ = FULL - 1;
            break;
        }
#endif

        lastTimeZ = millis();  // reinicia a contagem de tempo
      }
    }    
  }
}

/***
void eixoY(int velocidade, int targetSpeed){
      if (millis() - lastTimeY >= abs(velocidade)) {  // true every X miliseconds
        PORTB = stepsY[indexY]; // set the PORTB with value of the array

        if(targetSpeed > contStepY) sentido = 1;
        else                        sentido = -1;
        // if (velocidade > 0) sentido = 1;
        // else                sentido = -1;

        indexY += sentido;    // incrementa ou decrementa o contador
        contStepY += sentido;

        switch (sentido) {
          case 1:
            if (indexY > HALF - 1) indexY = 0x00;
            break;
          case -1:
            if (indexY < 0x00) indexY = HALF - 1;
            break;
        }

        lastTimeY = millis();  // reinicia a contagem de tempo
      }  
}
***/

bool fimCurso(int eixo) {
  return digitalRead(eixo);
}

void eixoZ(int steps, int velocidade){
  while(contStepZ != steps) moveMotor(Z, velocidade);
}

