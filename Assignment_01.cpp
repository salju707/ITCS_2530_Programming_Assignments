#include <iostream>
#include <string>
using namespace std;

int main()
{
	//Variables
	string name;
	double aperture;
	double shutterdenom;  // denominator of shutter speed
	int iso;

	// Collect exposure triangle settings
	cout << "--- Exposure Triangle Calculator ---\n\n";

	cout << "What's your name? ";
	cin >> name;

	cout << "What aperture are you shooting at?: f/";
	cin >> aperture;

	cout << "What shutter speed? 1/";
	cin >> shutterdenom;

	cout << "What ISO are you using? ";
	cin >> iso;

	//Calculations: Gives shutter time in milliseconds, brightness score
	// using the Exposure Equation, and the shutter speed if ISO doubles
	double shutterseconds = 1.0 / shutterdenom;
	double shutterMs = shutterseconds * 1000;
	double brightness = (iso * shutterseconds) / (aperture * aperture);
	double fastershutter = shutterdenom * 2;

	//Display
	cout << "\n---Your Photo Recipe---\n";
	cout << name << ", you're shooting at f/" << aperture
		<< ", 1/" << shutterdenom << " sec, and ISO " << iso << ".\n";
	cout << "Your shutter stays open for " << shutterMs << " milliseconds! \n";
	cout << "Your brightness score is " << brightness << " (higher = brighter). \n";
	cout << "If you doubled your ISO, you could increase your shutter speed to 1/" << fastershutter
		<< " and get the same brightness! \n";

	return 0;
}