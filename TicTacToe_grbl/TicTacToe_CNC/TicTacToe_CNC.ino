// --- Includes
#include "_config.h"
#include <IRremote.h>
#include <SoftwareSerial.h>

// --- Serial to debug (using USB<>Serial converter)
SoftwareSerial debug(9, 10);
#define LOGln debug.println
#define LOG debug.print

// --- IRremote variables
IRrecv irRemote(IR_PIN);
decode_results irResults;

// --- Game variables
int currentGame[9] = {EMPTY};
int numberOfPlays = 0;
int winnerLocation;
int currentPlayer;
bool gameOver = false;

// --- CNC state
bool CNCidle = false;

void setup(){
	// --- Set Serial communication
	Serial.begin(115200);
	Serial.setTimeout(10000);
	debug.begin(9600);

	// --- Wait initial message of the GRBL
	while(!Serial.available());
	delay(1000);
	while(Serial.available()){
		LOG((char)Serial.read());
	}
	LOGln("--- Ready!");

	// --- Set pin to choose the first player
	pinMode(FIRST_PLAYER_PIN, INPUT_PULLUP);
	currentPlayer = digitalRead(FIRST_PLAYER_PIN)*-2 + 1;

	// --- Led of sinalization
	pinMode(LED_PIN, OUTPUT);

	// --- Set InfraRed sensor
	irRemote.enableIRIn();

	CNC_initialize();
	CNC_drawBoard();

	// --- If the machine is the first player, play without needing the algorithm
	if(currentPlayer == MACHINE){
		CNC_drawPlayer(MACHINE, 0);
		currentGame[0] = MACHINE;
		draw();
		numberOfPlays++;
		currentPlayer = HUMAN;
	}
}

void loop(){

	if(gameOver){
		LOGln("--- GAME OVER");
		CNC_reset();
		while(1);
	}

	if(currentPlayer == MACHINE){
		machineMovement();
		currentPlayer = HUMAN;
		LOGln("--- HUMAN MOVEMENT");
	}else if(currentPlayer == HUMAN){
		if(GRBL_isIdle()){
			digitalWrite(LED_PIN, HIGH);
			int playerCommand = readIRRemote();

			if(playerCommand != NOTHING && currentGame[playerCommand] == EMPTY){
				CNCidle = false;
				humanMovement(playerCommand);
				currentPlayer = MACHINE;
				LOGln("--- MACHINE MOVEMENT");
				digitalWrite(LED_PIN, LOW);
			}
		}
	}
}

