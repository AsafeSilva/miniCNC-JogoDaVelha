void GRBL_SendCommand(const char* command){
	LOGln(command);
	Serial.println(command);

	waitGRBLResponse();
}

void waitGRBLResponse(){
	// LOGln("wait response...");
	while(!Serial.available());
	// LOGln("reading response...");

	String response = Serial.readStringUntil('\n');
	LOGln(response);
}

bool GRBL_isIdle(){
	if(CNCidle)
		return true;

	LOGln("--- Running");

	// LOGln('?');
	Serial.print('?');

	while(!Serial.available());
	delay(100);
	String response = Serial.readStringUntil('\n');
	// LOGln(response);

	int i = response.indexOf('|');
	String state = response.substring(1, i);
	state.trim();

	if(state.equals("Idle")){
		LOGln("--- Idle");
		CNCidle = true;
		return true;
	}

	return false;

}