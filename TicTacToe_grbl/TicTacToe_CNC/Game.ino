void humanMovement(int position){

	CNC_drawPlayer(HUMAN, position);
	currentGame[position] = HUMAN;

	numberOfPlays++;
	draw();

	int winner = checkWinner();
    if(winner != EMPTY || numberOfPlays == 9){
		CNC_drawWinner(winner, winnerLocation);
		gameOver = true;
	}
}

void machineMovement(){
	int minmaxScore = -2;
	int position = -1;

	for(int i = 0; i < 9; i++){
      if(currentGame[i] == EMPTY){

          currentGame[i] = MACHINE;
          int tempScore = -processMinmax(currentGame, HUMAN);
          currentGame[i] = EMPTY;

          if(tempScore > minmaxScore){
             minmaxScore = tempScore;
             position = i;
          }
      }
    }

    CNC_drawPlayer(MACHINE, position);
    currentGame[position] = MACHINE;

    numberOfPlays++;
    draw();

    int winner = checkWinner();
    if(winner != EMPTY || numberOfPlays == 9){
		CNC_drawWinner(winner, winnerLocation);
		gameOver = true;
	}
}

int processMinmax(int board[], int player){
  
	int winner = checkWinner();
	if(winner != EMPTY) return winner*player;

	int move = -1;
	int score = -2;
  
	for(int i = 0; i < 9; i++){
		if(board[i] == EMPTY){
		   
			board[i] = player;
			int thisScore = -processMinmax(board, player*-1);
			board[i] = EMPTY;
		   
			if(thisScore > score){
				score = thisScore;
				move = i;
			}
		}
	}
  
	if(move == -1) return 0;
	return score;
}

int checkWinner(){
	int positions[8][3] = {{0,1,2},
							{3,4,5},
							{6,7,8},
							{0,3,6},
							{1,4,7},
							{2,5,8},
							{0,4,8},
							{2,4,6}};

	for(winnerLocation = 0; winnerLocation < 8; winnerLocation++){
		if(currentGame[positions[winnerLocation][0]] != EMPTY &&
		   currentGame[positions[winnerLocation][0]] == currentGame[positions[winnerLocation][1]] &&
		   currentGame[positions[winnerLocation][1]] == currentGame[positions[winnerLocation][2]]){

			return currentGame[positions[winnerLocation][2]];
		}
	}

	return EMPTY;
}



void draw(){

  LOG(checkPlay(currentGame[0]));
  LOG("  | ");
  LOG(checkPlay(currentGame[1]));
  LOG(" | ");
  LOGln(checkPlay(currentGame[2]));
  LOGln( "---+---+---");

  LOG(checkPlay(currentGame[3]));
  LOG("  | ");
  LOG(checkPlay(currentGame[4]));
  LOG(" | ");
  LOGln(checkPlay(currentGame[5]));
  LOGln( "---+---+---");

  LOG(checkPlay(currentGame[6]));
  LOG("  | ");
  LOG(checkPlay(currentGame[7]));
  LOG(" | ");
  LOGln(checkPlay(currentGame[8]));
  LOGln("");
}

// conversão de número p/ caractere
char checkPlay(int i){
	switch(i) {
	    case PLAYER_X:
	        return 'X';
	    case PLAYER_O:
	        return 'O';
	    case EMPTY:
	        return ' ';
	}

	return ' ';
}