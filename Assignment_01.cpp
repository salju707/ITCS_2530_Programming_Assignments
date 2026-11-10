#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

int main()
{
	//Variables
	string name;
	double aperture;
	double shutterdenom;  // denominator of shutter speed
	int iso;

	// Cutoffs used in the if/else checks
	const double FAST_SHUTTER = 250;   // 1/250 or faster
	const double SLOW_SHUTTER = 30;    // 1/30 or slower
	const double WIDE_APERTURE = 4.0;   // f/4 or smaller number = wide opening
	const int HIGH_ISO = 1600;
	// Welcome Banner
	cout << "======================================\n";
	cout << "  Welcome to the Exposure Triangle\n";
	cout << "          Photo Calculator!\n";
	cout << "======================================\n";

	// Collect exposure triangle settings
	cout << "What's your name? ";
	getline(cin, name);

	cout << "What aperture are you shooting at?: f/";
	cin >> aperture;
	//WHILE LOOP #1
	while (cin.fail() || aperture <= 0)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Invalid aperture. Enter a positive number: f/";
		cin >> aperture;
	}


	cout << "What shutter speed? 1/";
	cin >> shutterdenom;
	// WHILE LOOP #2
	while (cin.fail() || shutterdenom <= 0)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Invalid shutter speed. Enter a positive number: 1/";
		cin >> shutterdenom;
	}
	cout << "What ISO are you using? ";
	cin >> iso;
	//WHILE LOOP #3
	while (cin.fail() || iso <= 0)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Invalid ISO. Enter a positive number. ";
		cin >> iso;
	}

	//Calculations: Gives shutter time in milliseconds, brightness score
	// using the Exposure Equation, and the shutter speed if ISO doubles
	double shutterseconds = 1.0 / shutterdenom;
	double shutterMs = shutterseconds * 1000;
	double brightness = (iso * shutterseconds) / (aperture * aperture);
	double fastershutter = shutterdenom * 2;

	// Menu
	int menuChoice;
	char again;
	// DO-WHILE LOOP
	do
	{
		// Menu
		cout << "\n--- What would you like to see? ---\n";
		cout << "1 = Your photo recipe\n";
		cout << "2 = Shutter and brightness details\n";
		cout << "3 = ISO doubling tip\n";
		cout << "Choose an option (1-3): ";
		cin >> menuChoice;

		//Bad menu input
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			menuChoice = 0;
		}

		// Show decimals with 3 digits of precision
		cout << fixed << setprecision(3);

		// Display result depending on the menu choice
		switch (menuChoice)
		{
		case 1:
			cout << "\n---Your Photo Recipe---\n";
			cout << name << ", you're shooting at f/" << aperture
				<< ", 1/" << shutterdenom << " sec, and ISO " << iso << ". \n";

			// Compound condition with &&
			if (shutterdenom >= FAST_SHUTTER && aperture <= WIDE_APERTURE)
			{
				cout << "Fast shutter + wide aperture: great for freezing action with blurry background! \n";
			}
			else
			{
				cout << "Not a freeze-the-action setup, but it could work for other shots.\n";
			}
			break;
		case 2:
			cout << "\n---Shutter and Brightness---\n";
			cout << "Your shutter stays open for " << shutterMs << " milliseconds!\n";
			cout << "Your brightness score is " << brightness << " (higher = brighter). \n";

			// Compound condition ||:
			if (iso >= HIGH_ISO || shutterdenom <= SLOW_SHUTTER)
			{
				cout << "Note: high ISO can add grain, and a slow shutter can cause blur. \n";
			}
			else
			{
				cout << "Your ISO and shutter speed are in a safe range for a clean, sharp shot. \n";
			}
			break;
		case 3:
		{
			cout << "\n---ISO Doubling Tip---\n";
			cout << "If you doubled ISO, you could increase your shutter speed to 1/"
				<< fastershutter << " and get the same brightness!\n";
			// FOR LOOP
			cout << "\n--- ISO Stop Ladder ---\n";
			int ladderISO = iso;
			double ladderShutter = shutterdenom;
			for (int stop = 1; stop <= 4; stop++)
			{
				ladderISO = ladderISO * 2;
				ladderShutter = ladderShutter * 2;
				cout << "+" << stop << " stop: ISO " << ladderISO
					<< " allows 1/" << ladderShutter << " sec\n";
			}
			break;
		}
		default:
		{
			cout << "\nThat's not on the menu. Please choose 1, 2, or 3.\n";
			break;
		}
		}

		// Ask if they want to go again 
		cout << "\nView another option? (y/n): ";
		cin >> again;
	} while (again == 'y' || again == 'Y');

	// Open report.txt for writing
	ofstream reportFile("report.txt");
	if (reportFile.fail())
	{
		cout << "Could not create report.txt.\n";
		return 1;
	}


	reportFile << fixed << setprecision(3);

	// Summary table
	cout << "\n====== Photo Settings Report ======\n";
	cout << left << setw(30) << "Photographer:" << right << setw(16) << name << "\n";
	cout << left << setw(30) << "Aperture (f/):" << right << setw(16) << aperture << "\n";
	cout << left << setw(30) << "Shutter speed (1/):" << right << setw(16) << shutterdenom << "\n";
	cout << left << setw(30) << "ISO:" << right << setw(16) << iso << "\n";
	cout << left << setw(30) << "Shutter time (ms):" << right << setw(16) << shutterMs << "\n";
	cout << left << setw(30) << "Brightness score:" << right << setw(16) << brightness << "\n";
	cout << left << setw(30) << "Shutter if ISO doubles (1/):" << right << setw(16) << fastershutter << "\n";
	cout << "===================================\n";

	// Table written to report.txt
	reportFile << "====== Photo Settings Report ======\n";
	reportFile << left << setw(30) << "Photographer:" << right << setw(16) << name << "\n";
	reportFile << left << setw(30) << "Aperture (f/):" << right << setw(16) << aperture << "\n";
	reportFile << left << setw(30) << "Shutter speed (1/):" << right << setw(16) << shutterdenom << "\n";
	reportFile << left << setw(30) << "ISO:" << right << setw(16) << iso << "\n";
	reportFile << left << setw(30) << "Shutter time (ms):" << right << setw(16) << shutterMs << "\n";
	reportFile << left << setw(30) << "Brightness score:" << right << setw(16) << brightness << "\n";
	reportFile << left << setw(30) << "Shutter if ISO doubles (1/):" << right << setw(16) << fastershutter << "\n";
	reportFile << "===================================\n";

	reportFile.close();
	cout << "\nYour report was saved to report.txt\n";

	return 0;
}