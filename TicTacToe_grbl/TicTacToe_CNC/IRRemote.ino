int readIRRemote(){
	int result = NOTHING;
	if (irRemote.decode(&irResults)) {
		// DEBUGln(irResults.value, HEX);
	    result = decodeIR(irResults.value);
	    irRemote.resume();
	}

	return result;
}

int decodeIR(long value){
  long buttons[9] = {IR_CODE_1, IR_CODE_2, IR_CODE_3, IR_CODE_4, IR_CODE_5, IR_CODE_6, IR_CODE_7, IR_CODE_8, IR_CODE_9};

  for(int i = 0; i < 9; i++){
    if(value == buttons[i])  return i;  // compara o valor recebido com a posição do array
  }

  return NOTHING;
}