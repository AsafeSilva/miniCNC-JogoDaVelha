const float level[7][7] = {
	{Z0, Z1, Z2, Z3, Z4, Z5, Z6},
	{Z7, Z8, Z9, Z10, Z11, Z12, Z13},
	{Z14, Z15, Z16, Z17, Z18, Z19, Z20},
	{Z21, Z22, Z23, Z24, Z25, Z26, Z27},
	{Z28, Z29, Z30, Z31, Z32, Z33, Z34},
	{Z35, Z36, Z37, Z38, Z39, Z40, Z41},
	{Z42, Z43, Z44, Z45, Z46, Z47, Z48}
};

void CNC_initialize(){
	LOGln("--- Initializing");

	LOGln("$X");
	Serial.println("$X");
	while(!Serial.available());
	Serial.readStringUntil('\n');
	waitGRBLResponse();

	GRBL_SendCommand("$21=1");
	GRBL_SendCommand("$H");
	
	LOGln("--- Disabling hard limits");
	GRBL_SendCommand("$21=0");
}

void CNC_reset(){
	LOGln("--- Enabling hard limits");
	GRBL_SendCommand("$21=1");
}

void CNC_2home(){
	char toHome[15];

	sprintf(toHome, "G0 X0 Y%d", Y_MAX);

	LOGln("--- To home");
	GRBL_SendCommand(UP_Z);
	GRBL_SendCommand(toHome);
}

void CNC_drawBoard(){
	char command[25];
	char zValue[8];

	LOGln("--- Drawing board");

	sprintf(command, "F%d", TOOL_VEL);
	GRBL_SendCommand(command);

	// LINE 1
	dtostrf(Z44, 6, 3, zValue);
	sprintf(command, "G1 X%d Y%d Z%s", X_MAX/3, Y_MAX, zValue);
	GRBL_SendCommand(command);

	dtostrf(Z30, 6, 3, zValue);
	sprintf(command, "G1 X%d Y%d Z%s", X_MAX/3, Y_MAX*2/3, zValue);
	GRBL_SendCommand(command);

	dtostrf(Z16, 6, 3, zValue);
	sprintf(command, "G1 X%d Y%d Z%s", X_MAX/3, Y_MAX/3, zValue);
	GRBL_SendCommand(command);

	dtostrf(Z2, 6, 3, zValue);
	sprintf(command, "G1 X%d Y%d Z%s", X_MAX/3, 0, zValue);
	GRBL_SendCommand(command);

	GRBL_SendCommand(UP_Z);

	// LINE 2
	dtostrf(Z4, 6, 3, zValue);
	sprintf(command, "G1 X%d Y%d Z%s", X_MAX*2/3, 0,zValue);
	GRBL_SendCommand(command);

	dtostrf(Z18, 6, 3, zValue);
	sprintf(command, "G1 X%d Y%d Z%s", X_MAX*2/3, Y_MAX/3, zValue);
	GRBL_SendCommand(command);

	dtostrf(Z32, 6, 3, zValue);
	sprintf(command, "G1 X%d Y%d Z%s", X_MAX*2/3, Y_MAX*2/3, zValue);
	GRBL_SendCommand(command);

	dtostrf(Z46, 6, 3, zValue);
	sprintf(command, "G1 X%d Y%d Z%s", X_MAX*2/3, Y_MAX, zValue);
	GRBL_SendCommand(command);

	GRBL_SendCommand(UP_Z);

	// LINE 3
	dtostrf(Z34, 6, 3, zValue);
	sprintf(command, "G1 X%d Y%d Z%s", X_MAX, Y_MAX*2/3, zValue);
	GRBL_SendCommand(command);

	dtostrf(Z32, 6, 3, zValue);
	sprintf(command, "G1 X%d Y%d Z%s", X_MAX*2/3, Y_MAX*2/3, zValue);
	GRBL_SendCommand(command);

	dtostrf(Z30, 6, 3, zValue);
	sprintf(command, "G1 X%d Y%d Z%s", X_MAX/3, Y_MAX*2/3, zValue);
	GRBL_SendCommand(command);

	dtostrf(Z28, 6, 3, zValue);
	sprintf(command, "G1 X%d Y%d Z%s", 0, Y_MAX*2/3, zValue);
	GRBL_SendCommand(command);

	GRBL_SendCommand(UP_Z);

	// LINE 4
	dtostrf(Z14, 6, 3, zValue);
	sprintf(command, "G1 X%d Y%d Z%s", 0, Y_MAX/3, zValue);
	GRBL_SendCommand(command);

	dtostrf(Z16, 6, 3, zValue);
	sprintf(command, "G1 X%d Y%d Z%s", X_MAX/3, Y_MAX/3, zValue);
	GRBL_SendCommand(command);

	dtostrf(Z18, 6, 3, zValue);
	sprintf(command, "G1 X%d Y%d Z%s", X_MAX*2/3, Y_MAX/3, zValue);
	GRBL_SendCommand(command);

	dtostrf(Z20, 6, 3, zValue);
	sprintf(command, "G1 X%d Y%d Z%s", X_MAX, Y_MAX/3, zValue);
	GRBL_SendCommand(command);

	// sprintf(command, "G1 X%d Y%d Z0 F%d", X_MAX/3, Y_MAX, TOOL_VEL);
	// GRBL_SendCommand(command);

	// sprintf(command, "G1 Y%d", 0);
	// GRBL_SendCommand(command);

	// GRBL_SendCommand(UP_Z);

	// sprintf(command, "G1 X%d Z0", X_MAX*2/3);
	// GRBL_SendCommand(command);

	// sprintf(command, "G1 Y%d", Y_MAX);
	// GRBL_SendCommand(command);

	// GRBL_SendCommand(UP_Z);

	// sprintf(command, "G1 X%d Y%d Z0", X_MAX, Y_MAX*2/3);
	// GRBL_SendCommand(command);

	// sprintf(command, "G1 X%d", 0);
	// GRBL_SendCommand(command);

	// GRBL_SendCommand(UP_Z);

	// sprintf(command, "G1 Y%d Z0", Y_MAX/3);
	// GRBL_SendCommand(command);

	// sprintf(command, "G1 X%d", X_MAX);
	// GRBL_SendCommand(command);

	CNC_2home();
}

void CNC_drawWinner(int winner, int location){
	char command[25];
	char zValue[8];

	if(winner == EMPTY){
		LOGln("--- DRAW");

		dtostrf(Z42, 6, 3, zValue);
		sprintf(command, "G1 X%d Y%d Z%s", 0, Y_MAX, zValue);
		GRBL_SendCommand(command);

		// LEFT LINE
		dtostrf(Z28, 6, 3, zValue);
		sprintf(command, "G1 X%d Y%d Z%s", 0, Y_MAX*2/3, zValue);
		GRBL_SendCommand(command);

		dtostrf(Z14, 6, 3, zValue);
		sprintf(command, "G1 X%d Y%d Z%s", 0, Y_MAX/3, zValue);
		GRBL_SendCommand(command);

		dtostrf(Z0, 6, 3, zValue);
		sprintf(command, "G1 X%d Y%d Z%s", 0, 0, zValue);
		GRBL_SendCommand(command);

		// DOWN LINE
		dtostrf(Z2, 6, 3, zValue);
		sprintf(command, "G1 X%d Y%d Z%s", X_MAX/3, 0, zValue);
		GRBL_SendCommand(command);

		dtostrf(Z4, 6, 3, zValue);
		sprintf(command, "G1 X%d Y%d Z%s", X_MAX*2/3, 0, zValue);
		GRBL_SendCommand(command);

		dtostrf(Z6, 6, 3, zValue);
		sprintf(command, "G1 X%d Y%d Z%s", X_MAX, 0, zValue);
		GRBL_SendCommand(command);

		// RIGHT LINE
		dtostrf(Z20, 6, 3, zValue);
		sprintf(command, "G1 X%d Y%d Z%s", X_MAX, Y_MAX/3, zValue);
		GRBL_SendCommand(command);

		dtostrf(Z34, 6, 3, zValue);
		sprintf(command, "G1 X%d Y%d Z%s", X_MAX, Y_MAX*2/3, zValue);
		GRBL_SendCommand(command);

		dtostrf(Z48, 6, 3, zValue);
		sprintf(command, "G1 X%d Y%d Z%s", X_MAX, Y_MAX, zValue);
		GRBL_SendCommand(command);

		// UP LINE
		dtostrf(Z46, 6, 3, zValue);
		sprintf(command, "G1 X%d Y%d Z%s", X_MAX*2/3, Y_MAX, zValue);
		GRBL_SendCommand(command);

		dtostrf(Z44, 6, 3, zValue);
		sprintf(command, "G1 X%d Y%d Z%s", X_MAX/3, Y_MAX, zValue);
		GRBL_SendCommand(command);

		dtostrf(Z42, 6, 3, zValue);
		sprintf(command, "G1 X%d Y%d Z%s", 0, Y_MAX, zValue);
		GRBL_SendCommand(command);

		// sprintf(command, "G1 X%d Y%d Z0", 0, Y_MAX);
		// GRBL_SendCommand(command);

		// sprintf(command, "G1 X%d Y%d Z0", 0, 0);
		// GRBL_SendCommand(command);

		// sprintf(command, "G1 X%d Y%d Z0", X_MAX, 0);
		// GRBL_SendCommand(command);

		// sprintf(command, "G1 X%d Y%d Z0", X_MAX, Y_MAX);
		// GRBL_SendCommand(command);

		// sprintf(command, "G1 X%d Y%d Z0", 0, Y_MAX);
		// GRBL_SendCommand(command);
	}else{
		LOG("--- VICTORY OF ");
		LOG(winner == PLAYER_X ? "'X'" : "'O'");
		LOG(" IN ");
		LOGln(location);

		switch (location){
			case 0:
				dtostrf(Z35, 6, 3, zValue);
				sprintf(command, "G1 X%d Y%d Z%s", 0, Y_MAX*5/6, zValue);
				GRBL_SendCommand(command);

				dtostrf(Z37, 6, 3, zValue);
				sprintf(command, "G1 X%d Y%d Z%s", X_MAX/3, Y_MAX*5/6, zValue);
				GRBL_SendCommand(command);

				dtostrf(Z39, 6, 3, zValue);
				sprintf(command, "G1 X%d Y%d Z%s", X_MAX*2/3, Y_MAX*5/6, zValue);
				GRBL_SendCommand(command);

				dtostrf(Z41, 6, 3, zValue);
				sprintf(command, "G1 X%d Y%d Z%s", X_MAX, Y_MAX*5/6, zValue);
				GRBL_SendCommand(command);

				// sprintf(command, "G1 X%d Y%d Z0", 0, Y_MAX*5/6);
				// GRBL_SendCommand(command);
				
				// sprintf(command, "G1 X%d Y%d Z0", X_MAX, Y_MAX*5/6);
				// GRBL_SendCommand(command);
			break;
			case 1:
				dtostrf(Z21, 6, 3, zValue);
				sprintf(command, "G1 X%d Y%d Z%s", 0, Y_MAX*3/6, zValue);
				GRBL_SendCommand(command);

				dtostrf(Z23, 6, 3, zValue);
				sprintf(command, "G1 X%d Y%d Z%s", X_MAX/3, Y_MAX*3/6, zValue);
				GRBL_SendCommand(command);

				dtostrf(Z25, 6, 3, zValue);
				sprintf(command, "G1 X%d Y%d Z%s", X_MAX*2/3, Y_MAX*3/6, zValue);
				GRBL_SendCommand(command);

				dtostrf(Z27, 6, 3, zValue);
				sprintf(command, "G1 X%d Y%d Z%s", X_MAX, Y_MAX*3/6, zValue);
				GRBL_SendCommand(command);

				// sprintf(command, "G1 X%d Y%d Z0", 0, Y_MAX*3/6);
				// GRBL_SendCommand(command);
				
				// sprintf(command, "G1 X%d Y%d Z0", X_MAX, Y_MAX*3/6);
				// GRBL_SendCommand(command);
			break;
			case 2:
				dtostrf(Z7, 6, 3, zValue);
				sprintf(command, "G1 X%d Y%d Z%s", 0, Y_MAX/6, zValue);
				GRBL_SendCommand(command);

				dtostrf(Z9, 6, 3, zValue);
				sprintf(command, "G1 X%d Y%d Z%s", X_MAX/3, Y_MAX/6, zValue);
				GRBL_SendCommand(command);

				dtostrf(Z11, 6, 3, zValue);
				sprintf(command, "G1 X%d Y%d Z%s", X_MAX*2/3, Y_MAX/6, zValue);
				GRBL_SendCommand(command);

				dtostrf(Z13, 6, 3, zValue);
				sprintf(command, "G1 X%d Y%d Z%s", X_MAX, Y_MAX/6, zValue);
				GRBL_SendCommand(command);

				// sprintf(command, "G1 X%d Y%d Z0", 0, Y_MAX*1/6);
				// GRBL_SendCommand(command);
				
				// sprintf(command, "G1 X%d Y%d Z0", X_MAX, Y_MAX*1/6);
				// GRBL_SendCommand(command);
			break;
			case 3:
				dtostrf(Z43, 6, 3, zValue);
				sprintf(command, "G1 X%d Y%d Z%s", X_MAX/6, Y_MAX, zValue);
				GRBL_SendCommand(command);

				dtostrf(Z29, 6, 3, zValue);
				sprintf(command, "G1 X%d Y%d Z%s", X_MAX/6, Y_MAX*2/3, zValue);
				GRBL_SendCommand(command);

				dtostrf(Z15, 6, 3, zValue);
				sprintf(command, "G1 X%d Y%d Z%s", X_MAX/6, Y_MAX/3, zValue);
				GRBL_SendCommand(command);

				dtostrf(Z1, 6, 3, zValue);
				sprintf(command, "G1 X%d Y%d Z%s", X_MAX/6, 0, zValue);
				GRBL_SendCommand(command);

				// sprintf(command, "G1 X%d Y%d Z0", X_MAX*1/6, Y_MAX);
				// GRBL_SendCommand(command);
				
				// sprintf(command, "G1 X%d Y%d Z0", X_MAX*1/6, 0);
				// GRBL_SendCommand(command);
			break;
			case 4:
				dtostrf(Z45, 6, 3, zValue);
				sprintf(command, "G1 X%d Y%d Z%s", X_MAX*3/6, Y_MAX, zValue);
				GRBL_SendCommand(command);

				dtostrf(Z31, 6, 3, zValue);
				sprintf(command, "G1 X%d Y%d Z%s", X_MAX*3/6, Y_MAX*2/3, zValue);
				GRBL_SendCommand(command);

				dtostrf(Z17, 6, 3, zValue);
				sprintf(command, "G1 X%d Y%d Z%s", X_MAX*3/6, Y_MAX/3, zValue);
				GRBL_SendCommand(command);

				dtostrf(Z3, 6, 3, zValue);
				sprintf(command, "G1 X%d Y%d Z%s", X_MAX*3/6, 0, zValue);
				GRBL_SendCommand(command);

				// sprintf(command, "G1 X%d Y%d Z0", X_MAX*3/6, Y_MAX);
				// GRBL_SendCommand(command);
				
				// sprintf(command, "G1 X%d Y%d Z0", X_MAX*3/6, 0);
				// GRBL_SendCommand(command);
			break;
			case 5:
				dtostrf(Z47, 6, 3, zValue);
				sprintf(command, "G1 X%d Y%d Z%s", X_MAX*5/6, Y_MAX, zValue);
				GRBL_SendCommand(command);

				dtostrf(Z33, 6, 3, zValue);
				sprintf(command, "G1 X%d Y%d Z%s", X_MAX*5/6, Y_MAX*2/3, zValue);
				GRBL_SendCommand(command);

				dtostrf(Z19, 6, 3, zValue);
				sprintf(command, "G1 X%d Y%d Z%s", X_MAX*5/6, Y_MAX/3, zValue);
				GRBL_SendCommand(command);

				dtostrf(Z5, 6, 3, zValue);
				sprintf(command, "G1 X%d Y%d Z%s", X_MAX*5/6, 0, zValue);
				GRBL_SendCommand(command);

				// sprintf(command, "G1 X%d Y%d Z0", X_MAX*5/6, Y_MAX);
				// GRBL_SendCommand(command);
				
				// sprintf(command, "G1 X%d Y%d Z0", X_MAX*5/6, 0);
				// GRBL_SendCommand(command);
			break;
			case 6:
				dtostrf(Z42, 6, 3, zValue);
				sprintf(command, "G1 X%d Y%d Z%s", 0, Y_MAX, zValue);
				GRBL_SendCommand(command);

				dtostrf(Z30, 6, 3, zValue);
				sprintf(command, "G1 X%d Y%d Z%s", X_MAX/3, Y_MAX*2/3, zValue);
				GRBL_SendCommand(command);

				dtostrf(Z18, 6, 3, zValue);
				sprintf(command, "G1 X%d Y%d Z%s", X_MAX*2/3, Y_MAX/3, zValue);
				GRBL_SendCommand(command);

				dtostrf(Z6, 6, 3, zValue);
				sprintf(command, "G1 X%d Y%d Z%s", X_MAX, 0, zValue);
				GRBL_SendCommand(command);

				// sprintf(command, "G1 X%d Y%d Z0", 0, Y_MAX);
				// GRBL_SendCommand(command);
				
				// sprintf(command, "G1 X%d Y%d Z0", X_MAX, 0);
				// GRBL_SendCommand(command);
			break;
			case 7:
				dtostrf(Z48, 6, 3, zValue);
				sprintf(command, "G1 X%d Y%d Z%s", X_MAX, Y_MAX, zValue);
				GRBL_SendCommand(command);

				dtostrf(Z32, 6, 3, zValue);
				sprintf(command, "G1 X%d Y%d Z%s", X_MAX*2/3, Y_MAX*2/3, zValue);
				GRBL_SendCommand(command);

				dtostrf(Z16, 6, 3, zValue);
				sprintf(command, "G1 X%d Y%d Z%s", X_MAX/3, Y_MAX/3, zValue);
				GRBL_SendCommand(command);

				dtostrf(Z0, 6, 3, zValue);
				sprintf(command, "G1 X%d Y%d Z%s", 0, 0, zValue);
				GRBL_SendCommand(command);

				// sprintf(command, "G1 X%d Y%d Z0", X_MAX, Y_MAX);
				// GRBL_SendCommand(command);
				
				// sprintf(command, "G1 X%d Y%d Z0", 0, 0);
				// GRBL_SendCommand(command);
			break;
		}
	}

	CNC_2home();
}

void CNC_drawPlayer(int player, int position){

	LOG("--- Drawing ");
	LOG(player == PLAYER_X ? "'X'" : (player == PLAYER_O ? "'O'" : "'+'"));
	LOG(" in ");
	LOGln(position);

	switch (player){
		case PLAYER_X:
			if(position <= 2)       CNC_drawPlayerX(X_MAX*(1/3.0)*position, Y_MAX);  
			else if(position <= 5)  CNC_drawPlayerX(X_MAX*(1/3.0)*(position-3), Y_MAX*2/3.0); 
			else               		CNC_drawPlayerX(X_MAX*(1/3.0)*(position-6), Y_MAX*1/3.0);
		break;
		case PLAYER_O:
			if(position <= 2)       CNC_drawPlayerO(X_MAX*(1/3.0)*position, Y_MAX*5/6.0);  
			else if(position <= 5)  CNC_drawPlayerO(X_MAX*(1/3.0)*(position-3), Y_MAX*3/6.0); 
			else               		CNC_drawPlayerO(X_MAX*(1/3.0)*(position-6), Y_MAX*1/6.0);
		break;
	}

	CNC_2home();
}

void CNC_drawPlayerX(int startX, int startY){
	char command[20];
	char zValue[8];

	GRBL_SendCommand(UP_Z);

	sprintf(command, "G0 X%d Y%d",startX, startY);
	GRBL_SendCommand(command);

	dtostrf(level[startX/6][startY/6], 6, 3, zValue);
	sprintf(command, "G1 X%d Y%d Z%s",startX, startY, zValue);
	GRBL_SendCommand(command);

	dtostrf(level[(startX + X_MAX*1/3)/6][(startY - Y_MAX*1/3)/6], 6, 3, zValue);
	sprintf(command, "G1 X%d Y%d Z%s", startX + X_MAX*1/3, startY - Y_MAX*1/3, zValue);
	GRBL_SendCommand(command);
	
	GRBL_SendCommand(UP_Z);

	sprintf(command, "G0 X%d Y%d",startX, startY - Y_MAX*1/3);
	GRBL_SendCommand(command);
	
	dtostrf(level[startX/6][(startY - Y_MAX*1/3)/6], 6, 3, zValue);
	sprintf(command, "G1 X%d Y%d Z%s",startX, startY - Y_MAX*1/3, zValue);
	GRBL_SendCommand(command);
	
	dtostrf(level[(startX + X_MAX*1/3)/6][startY/6], 6, 3, zValue);
	sprintf(command, "G1 X%d Y%d Z%s", startX + X_MAX*1/3, startY, zValue);
	GRBL_SendCommand(command);	

	// sprintf(command, "G1 X%d Y%d Z0",startX, startY);
	// GRBL_SendCommand(command);

	// sprintf(command, "G1 X%d Y%d Z0", startX + X_MAX*1/3, startY - Y_MAX*1/3);
	// GRBL_SendCommand(command);
	
	// GRBL_SendCommand(UP_Z);
	
	// sprintf(command, "G1 X%d Y%d Z0",startX, startY - Y_MAX*1/3);
	// GRBL_SendCommand(command);
	
	// sprintf(command, "G1 X%d Y%d Z0", startX + X_MAX*1/3, startY);
	// GRBL_SendCommand(command);
}


void CNC_drawPlayerO(int startX, int startY){
	char command[20];
	char zValue[8];

	GRBL_SendCommand(UP_Z);

	sprintf(command, "G0 X%d Y%d",startX, startY);
	GRBL_SendCommand(command);

	dtostrf(level[(startX)/6][startY/6], 6, 3, zValue);
	sprintf(command, "G1 X%d Y%d Z%s", startX, startY, zValue);
	GRBL_SendCommand(command);

	dtostrf(level[(startX + X_MAX/6)/6][(startY + Y_MAX/6)/6], 6, 3, zValue);
	sprintf(command, "G2 X%d Y%d Z%s I%d", startX + X_MAX/6, startY + Y_MAX/6, zValue, X_MAX/6);
	GRBL_SendCommand(command);

	dtostrf(level[(startX + X_MAX/3)/6][(startY)/6], 6, 3, zValue);
	sprintf(command, "G2 X%d Y%d Z%s J%d", startX + X_MAX/3, startY, zValue, -Y_MAX/6);
	GRBL_SendCommand(command);

	dtostrf(level[(startX + X_MAX/6)/6][(startY - Y_MAX/6)/6], 6, 3, zValue);
	sprintf(command, "G2 X%d Y%d Z%s I%d", startX + X_MAX/6, startY - Y_MAX/6, zValue, -X_MAX/6);
	GRBL_SendCommand(command);

	dtostrf(level[(startX)/6][(startY)/6], 6, 3, zValue);
	sprintf(command, "G2 X%d Y%d Z%s J%d", startX, startY, zValue, Y_MAX/6);
	GRBL_SendCommand(command);

	// sprintf(command, "G1 X%d Y%d Z0", startX, startY);
	// GRBL_SendCommand(command);

	// sprintf(command, "G2 X%d Y%d Z0 I%d", startX, startY, X_MAX*1/6);
	// GRBL_SendCommand(command);
}