#include "stdafx.h"
#include "SerialInterface.h"
#include <iostream>
#include <vector>


using std::cout;
using std::vector;
using std::exception;
using std::stoi;
using std::string;


SerialInterface::SerialInterface()
{
	vector <serial::PortInfo> devicesFound = serial::list_ports();

	vector <serial::PortInfo>::iterator iter = devicesFound.begin();


	while (iter != devicesFound.end())
	{
		serial::PortInfo device = *iter++;
		string port = device.port.c_str();

		try
		{
			mySerial = new serial::Serial(port, 115200, serial::Timeout::simpleTimeout(250));

			if (mySerial->isOpen())
			{
				cout << "Connection successful: " << port << "\n";
				connected = true;

				break;
			}
		}
		catch (exception &e)
		{

		}
	}
}


SerialInterface::~SerialInterface()
{
}

void SerialInterface::send(string msg)
{
	if (connected)
	{
		mySerial->write(msg);
	}
}

void SerialInterface::getPositions()
{
	if (connected)
	{
		mySerial->write("P");

		string result = mySerial->readline();

		if (result.length() >= 9)
		{
			string sub1 = result.substr(0, 4);
			if (sub1 != "")
			{
				pot1 = stoi(sub1);
			}


			string sub2 = result.substr(5, 9);
			if (sub2 != "")
			{
				pot2 = stoi(sub2);
			}
		}



	}
}

//function to take the arduino code
void SerialInterface::LEDGoal(string input)
{
	if (connected)
	{
		//Get the arduino code
		mySerial->write(input);
	}

}

void SerialInterface::close()
{
	mySerial->flush();
	mySerial->close();
}
