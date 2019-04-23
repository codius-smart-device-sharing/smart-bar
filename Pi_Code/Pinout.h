// direcion and step pins from Pi to A4988
int DIR_X = 6;
int STEP_X = 5;
int DIR_Y = 4;
int STEP_Y = 1;


// These choose the correct pump through the GAL shift register
// Connects to GAL IN1 pin to send step signal through to A4988
                    //         _____
int GAL_CLK = 2;    // CLK/IN |     | VCC
int STEP_IN = 0;    // IN1    |     | I/O10 to MIX3/mot5
int SEL2 = 7;       // IN2    |     | I/O9  to MIX2/mot4
                    // IN/PD  |     | I/O8  to MIX1/mot3
int SEL1 = 9;       // IN3    |     | I/O7  to SPIRIT3/mot2
int SEL0 = 8;       // IN4    |     | I/O6  to SPIRIT2/mot1
                    // IN5    |     | I/O5  to SPIRIT1/mot0
                    // IN6    |     | I/O4
                    // IN7    |     | I/O3
                    // IN8    |     | I/O2
                    // IN9    |     | I/O1
                    // GND    |_____| IN10

// Endstop Pins to Pi (Active LOW)
int X_STOP = 22;
int Y_STOP = 23;
int ROT_STOP = 24;
int CLAMP_STOP = 25;

// 5V Cup Ejector Pins from Pi to Motor
int EJECT_1 = 28;
int EJECT_2 = 29;
int EJECT_3 = 21;
int EJECT_4 = 14;

// 5V Clamp Pins from Pi to Motor
int CLAMP_1 = 10;
int CLAMP_2 = 11;
int CLAMP_3 = 26;
int CLAMP_4 = 27;

// 5V Rotation Pins from Pi to Motor
int ROT_1 = 15;
int ROT_2 = 16;
int ROT_3 = 3;
int ROT_4 = 13;
