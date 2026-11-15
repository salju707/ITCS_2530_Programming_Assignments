#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <windows.h> //for console colors
using namespace std;

//global constants
const double FAST_SHUTTER = 250;   // 1/250 or faster
const double SLOW_SHUTTER = 30;    // 1/30 or slower
const double WIDE_APERTURE = 4.0;   // f/4 or smaller number = wide opening
const int HIGH_ISO = 1600;

// color codes!
const int COLOR_DEFAULT = 7; //white
const int COLOR_BANNER = 13; //light pink
const int COLOR_MENUS = 11; // light aqua
const int COLOR_RESULT = 10; // light  mint green
const int COLOR_REPORT = 9; //light periwinkle blue 
const int COLOR_ERROR = 12; //light coral red

// function prototypes
void setColor(int colorCode);
void displayBanner();
string getName();
double getAperture();
double getShutterDenom();
int getISO();
double calcShutterMs(double shutterDenom);
double calcBrightness(int iso, double shutterDenom, double aperture);
double calcFasterShutter(double shutterDenom);
void displayMenu();
int getMenuChoice();
void showRecipe(string name, double aperture, double shutterDenom, int iso);
void showDetails(double shutterMs, double brightness, int iso, double shutterDenom);
void showIsoTip(double fasterShutter, int iso, double shutterDenom);
void displayReport(string name, double aperture, double shutterDenom, int iso,
	double shutterMs, double brightness, double fasterShutter);
bool saveReport(string name, double aperture, double shutterDenom, int iso,
	double shutterMs, double brightness, double fasterShutter);

int main()
{
	//Variables
	string name;
	double aperture;
	double shutterDenom;  // denominator of shutter speed
	int iso;
	int menuChoice;
	char again;

	displayBanner();
	// Collect and validate three exposure setting (plus name)
	name = getName();
	aperture = getAperture();
	shutterDenom = getShutterDenom();
	iso = getISO();

	//derived values
	double shutterMs = calcShutterMs(shutterDenom);
	double brightness = calcBrightness(iso, shutterDenom, aperture);
	double fasterShutter = calcFasterShutter(shutterDenom);

	// do while loop: repeats until user says no
	do
	{
		displayMenu();
		menuChoice = getMenuChoice();

		//show decimals with 3 digits of precision
		cout << fixed << setprecision(3);

		//switch
		switch (menuChoice)
		{
		case 1:
			showRecipe(name, aperture, shutterDenom, iso);
			break;
		case 2:
			showDetails(shutterMs, brightness, iso, shutterDenom);
			break;
		case 3:
			showIsoTip(fasterShutter, iso, shutterDenom);
			break;
		default:
			setColor(COLOR_ERROR);
			cout << "\nThat's not on the menu. Please choose 1, 2, or 3.\n";
			setColor(COLOR_DEFAULT);
			break;
		}
		// prompt the user if they want to go again
		cout << "\nView another option? (y/n): ";
		cin >> again;
	} while (again == 'y' || again == 'Y');

	//show summary table, then save to a file
	displayReport(name, aperture, shutterDenom, iso, shutterMs, brightness, fasterShutter);

	if (saveReport(name, aperture, shutterDenom, iso, shutterMs, brightness, fasterShutter))
	{
		setColor(COLOR_RESULT);
		cout << "\nYour report was saved to report.txt\n";
	}
	else
	{
		setColor(COLOR_ERROR);
		cout << "\nCould not create report.txt\n";
	}

	setColor(COLOR_DEFAULT);
	return 0;
}

void setColor(int colorCode)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, colorCode);
}
	// Print Welcome Banner
void displayBanner()
{
	setColor(COLOR_BANNER);
	cout << "======================================\n";
	cout << "  Welcome to the Exposure Triangle\n";
	cout << "          Photo Calculator!\n";
	cout << "======================================\n";
	setColor(COLOR_DEFAULT);
}

//asks for name (spaces allowed) and re-asks if empty
string getName()
{
	string name;

	cout << "What's your name? ";
	getline(cin, name);

	while (name.empty())
	{
		setColor(COLOR_ERROR);
		cout << "Name can't be empty.";
		setColor(COLOR_DEFAULT);
		cout << "What's your name? ";
		getline(cin, name);
	}
	return name;
}

//Asks for aperture
double getAperture()
{
	double aperture;
	cout << "What aperture are you shooting at?: f/";
	cin >> aperture;

	while (cin.fail() || aperture <= 0)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		setColor(COLOR_ERROR);
		cout << "Invalid aperture. Enter a positive number: f/";
		setColor(COLOR_DEFAULT);
		cin >> aperture;
	}
	return aperture;
}

//Ask for shutter speed denominator
double getShutterDenom()
{
	double shutterDenom;

	cout << "What shutter speed? 1/";
	cin >> shutterDenom;

	while (cin.fail() || shutterDenom <= 0)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		setColor(COLOR_ERROR);
		cout << "Invalid shutter speed. Enter a positive number. 1/";
		setColor(COLOR_DEFAULT);
		cin >> shutterDenom;
	}
	return shutterDenom;
}
//Ask for ISO
int getISO()
{
	int iso;
	cout << "What ISO are you using? ";
	cin >> iso;

	while (cin.fail() || iso <= 0)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		setColor(COLOR_ERROR);
		cout << "Invalid ISO. Enter a positive number: ";
		setColor(COLOR_DEFAULT);
		cin >> iso;
	}
	return iso;
}

		// CALCULATIONS
		
		
// How long the shutter stays open
double calcShutterMs(double shutterDenom)
{
	double shutterSeconds = 1.0 / shutterDenom;
	return shutterSeconds * 1000;
}

//Brightness score using ewuation: (ISO * time / aperture^2)
double calcBrightness(int iso, double shutterDenom, double aperture)
{
	double shutterSeconds = 1.0 / shutterDenom;
	return (iso * shutterSeconds) / (aperture * aperture);
}

// shutter speed denominator you could use if ISO doubles
double calcFasterShutter(double shutterDenom)
{
	return shutterDenom * 2;
}

//Print menu options
void displayMenu()
{
	setColor(COLOR_MENUS);
	cout << "\n--- What would you like to see? ---\n";
	cout << "1 = Your photo recipe\n";
	cout << "2 = Shutter and brightness details\n";
	cout << "3 = ISO doubling tip\n";
	cout << "Choose an option (1-3): ";
	setColor(COLOR_DEFAULT);
}

// returns 0 if input wasn't a number
int getMenuChoice()
{
	int menuChoice;

	cin >> menuChoice;
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(1000, '\n');
		menuChoice = 0;
	}
	return menuChoice;
}

// Menu option 1
void showRecipe(string name, double aperture, double shutterDenom, int iso)
{
	setColor(COLOR_RESULT);
	cout << "\n---Your Photo Recipe---\n";
	cout << name << ", you're shooting at f/" << aperture
		<< ", 1/" << shutterDenom << " sec, and ISO " << iso << ".\n";

	// IF/ELSE with compound condition
	if (shutterDenom >= FAST_SHUTTER && aperture <= WIDE_APERTURE)
	{
		cout << "Fast shutter + wide aperture: great for freezing action with blurry background!\n";
	}
	else
	{
		cout << "Not a freeze-the-action setup, but it could work for other shots.\n";
	}
	setColor(COLOR_DEFAULT);
}

// Menu option 2
void showDetails(double shutterMs, double brightness, int iso, double shutterDenom)
{
	setColor(COLOR_RESULT);
	cout << "\n---Shutter and Brightness---\n";
	cout << "Your shutter stays open for " << shutterMs << " milliseconds!\n";
	cout << "Your brightness score is " << brightness << " (higher = brighter).\n";

	// IF/ELSE with compound condition (||): either one being true is enough
	if (iso >= HIGH_ISO || shutterDenom <= SLOW_SHUTTER)
	{
		cout << "Note: high ISO can add grain, and a slow shutter can cause blur.\n";
	}
	else
	{
		cout << "Your ISO and shutter speed are in a safe range for a clean, sharp shot.\n";
	}
	setColor(COLOR_DEFAULT);
}

// Menu option 3
void showIsoTip(double fasterShutter, int iso, double shutterDenom)
{
	setColor(COLOR_RESULT);
	cout << "\n---ISO Doubling Tip---\n";
	cout << "If you doubled ISO, you could increase your shutter speed to 1/"
		<< fasterShutter << " and get the same brightness!\n";

	cout << "\n--- ISO Stop Ladder ---\n";
	int ladderISO = iso;
	double ladderShutter = shutterDenom;

	// FOR LOOP: runs exactly 4 times (one per stop)
	for (int stop = 1; stop <= 4; stop++)
	{
		ladderISO = ladderISO * 2;
		ladderShutter = ladderShutter * 2;
		cout << "+" << stop << " stop: ISO " << ladderISO
			<< " allows 1/" << ladderShutter << " sec\n";
	}
	setColor(COLOR_DEFAULT);
}

// Prints the summary table to the console
void displayReport(string name, double aperture, double shutterDenom, int iso,
	double shutterMs, double brightness, double fasterShutter)
{
	cout << fixed << setprecision(3);
	setColor(COLOR_REPORT);
	cout << "\n====== Photo Settings Report ======\n";
	cout << left << setw(30) << "Photographer:" << right << setw(16) << name << "\n";
	cout << left << setw(30) << "Aperture (f/):" << right << setw(16) << aperture << "\n";
	cout << left << setw(30) << "Shutter speed (1/):" << right << setw(16) << shutterDenom << "\n";
	cout << left << setw(30) << "ISO:" << right << setw(16) << iso << "\n";
	cout << left << setw(30) << "Shutter time (ms):" << right << setw(16) << shutterMs << "\n";
	cout << left << setw(30) << "Brightness score:" << right << setw(16) << brightness << "\n";
	cout << left << setw(30) << "Shutter if ISO doubles (1/):" << right << setw(16) << fasterShutter << "\n";
	cout << "===================================\n";
	setColor(COLOR_DEFAULT);
}

// writes summary table to report.txt
bool saveReport(string name, double aperture, double shutterDenom, int iso,
	double shutterMs, double brightness, double fasterShutter)
{
	ofstream reportFile("report.txt");
	if (reportFile.fail())
	{
		return false;
	}

	reportFile << fixed << setprecision(3);
	reportFile << "====== Photo Settings Report ======\n";
	reportFile << left << setw(30) << "Photographer:" << right << setw(16) << name << "\n";
	reportFile << left << setw(30) << "Aperture (f/):" << right << setw(16) << aperture << "\n";
	reportFile << left << setw(30) << "Shutter speed (1/):" << right << setw(16) << shutterDenom << "\n";
	reportFile << left << setw(30) << "ISO:" << right << setw(16) << iso << "\n";
	reportFile << left << setw(30) << "Shutter time (ms):" << right << setw(16) << shutterMs << "\n";
	reportFile << left << setw(30) << "Brightness score:" << right << setw(16) << brightness << "\n";
	reportFile << left << setw(30) << "Shutter if ISO doubles (1/):" << right << setw(16) << fasterShutter << "\n";
	reportFile << "===================================\n";

	reportFile.close();
	return true;
}
