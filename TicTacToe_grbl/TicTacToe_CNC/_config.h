#ifndef _CONFIG
#define _CONFIG

//
//	MISC STUFF
//
#define NOTHING -1


//
//	IR REMOTE
//
#define IR_PIN 		6

#define	IR_CODE_1 0xFF8A75
#define	IR_CODE_2 0xFF4AB5
#define	IR_CODE_3 0xFFCA35
#define	IR_CODE_4 0xFFB24D
#define	IR_CODE_5 0xFF728D
#define	IR_CODE_6 0xFFF20D
#define	IR_CODE_7 0xFF926D
#define	IR_CODE_8 0xFF52AD
#define	IR_CODE_9 0xFFD22D


// 
// GAME
// 
#define FIRST_PLAYER_PIN 	3

#define LED_PIN 13

#define PLAYER_X 	-1
#define EMPTY	 	0
#define PLAYER_O 	1

#define MACHINE PLAYER_X
#define HUMAN 	PLAYER_O


// 
// CNC PARAMETERS
//
// -- Provide dimensions in 'mm'
#define X_MAX	36
#define Y_MAX	36
#define UP_Z	"G0 Z2"
#define TOOL_VEL	1800


// 
// CNC Auto Leveler
// 
#define Z0	0
#define Z1	0.006
#define Z2	0.012
#define Z3	0.06
#define Z4	0.096
#define Z5	0.102
#define Z6	0.173

#define Z7	0.096
#define Z8	0.102
#define Z9	0.143
#define Z10	0.191
#define Z11	0.197
#define Z12	0.215
#define Z13	0.28

#define Z14	0.203
#define Z15	0.215
#define Z16	0.28
#define Z17	0.286
#define Z18	0.292
#define Z19	0.304
#define Z20	0.381

#define Z21	0.31
#define Z22	0.375
#define Z23	0.387
#define Z24	0.393
#define Z25	0.405
#define Z26	0.459
#define Z27	0.477

#define Z28	0.471
#define Z29	0.477
#define Z30	0.483
#define Z31	0.483
#define Z32	0.488
#define Z33	0.56
#define Z34	0.578

#define Z35	0.578
#define Z36	0.584
#define Z37	0.596
#define Z38	0.631
#define Z39	0.667
#define Z40	0.667
#define Z41	0.667

#define Z42	0.679
#define Z43	0.679
#define Z44	0.721
#define Z45	0.75
#define Z46	0.762
#define Z47	0.768
#define Z48	0.774

#endif