#pragma once


#include <serial\serial.h>
#include <string>

using std::string;

class SerialInterface
{
public:
	SerialInterface();
	~SerialInterface();

	void send(string msg);
	void getPositions();

	int getPot1() { return pot1; };
	int getPot2() { return pot2; };

	void LEDGoal(string input);

	void close();

private:
	serial::Serial* mySerial;
	bool connected = false;

	int pot1 = 0;
	int pot2 = 0;
};

