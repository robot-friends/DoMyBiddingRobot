#include <ArduinoRobot.h>

const int ledPin= 13;

void setup(){
	Serial.begin(9600);
	Robot.begin();
	Robot.beginTFT();
	Robot.stroke(0, 0, 0);
	Robot.text("Robot is initialized", 5, 5);
}

void loop() {
	if(Serial.available()) {
		Robot.stroke(0, 0, 0);
		Robot.text("Serial is available.", 5, 5);
		command(Serial.read() - '0');	// convert the character '1'-'9' to decimal 1-9
		digitalWrite(ledPin, HIGH);
	} else {
		digitalWrite(ledPin, LOW);
	}
}

void command(int serial) {
	const static int INITPAUSE = 500;
	static int pause = INITPAUSE;
	Robot.stroke(0, 0, 0);
	switch(serial) {
		case 1:
			Robot.text("Left", 5, 5);
			Robot.turn(10);
			break;
		case 2:
			Robot.text("Right", 5, 5);
			Robot.turn(-10);
			break;
		case 3:
			Robot.text("Up", 5, 5);
			Robot.motorsWrite(255, 255);
			delay(pause);
			Robot.motorsWrite(0, 0);
			pause <<= 1;
			break;
		case 4:
			Robot.text("Down", 5, 5);
			Robot.motorsWrite(-255, -255);
			delay(pause);
			Robot.motorsWrite(0, 0);
			pause = INITPAUSE;
			break;
	}
}
