// Core Programming: Coursework 3
// Marcus Daniel McFarlane

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <algorithm>
#include <numeric>


using namespace std;


// Function Definitions

void total_rain(const vector<double> v, vector<double>& vt){
    //accumulate for each year
    vector<double>::const_iterator i;
    for (i = v.begin(); i != v.end(); i+=12) {
        double totalEachYear = accumulate(i, i+12, 0.0);
        vt.push_back(totalEachYear);
    }
}



void maxFrost (vector <double> container, vector <int> itsMonth, vector <int> itsYear)
	{
		vector <double>::iterator maxFrostValue;
		double maxFrostPosition;
	
		maxFrostValue = max_element (container.begin(), container.end());
		maxFrostPosition = distance (container.begin(), maxFrostValue);
		cout << "The highest record of airfrost occurred within " << *maxFrostValue << " days"<< endl;

		// Switch loop changing the month integer to the actual name format for the relevant month.	
		cout << "This was in ";
		
		switch(itsMonth[maxFrostPosition])
			{
				case 1:
					cout<<"January";
					break;
					
				case 2:
					cout<<"February";
					break;
					
				case 3:
					cout<<"March";
					break;
					
				case 4:
					cout<<"April";
					break;
					
				case 5:
					cout<<"May";
					break;
					
				case 6:
					cout<<"June";
					break;
					
				case 7:
					cout<<"July";
					break;
					
				case 8:
					cout<<"August";
					break;
					
				case 9:
					cout<<"September";
					break;
					
				case 10:
					cout<<"October";
					break;
					
				case 11:
					cout<<"November";
					break;
					
				case 12:
					cout<<"December";
					break;

			default: 
				cout<<"invalid month conversion!"<<endl;
		}
		cout << " " << itsYear[maxFrostPosition] << "\n"<<endl;
	}

// Main Function

int main(int argc, char *argv[])
{

	cout << "Core Programming: Coursework 3\n" << endl;

	// Command line argument
	if (argc != 2){
		cerr << "\n" << "Usage: " << argv[0] << " <filename>" << "\n" << endl;
		return 1;
	}

	string filename = argv[1];

	// Prompt user to enter a filename

	cout << "Enter filename: ";
	cin >> filename;
	cout << " " << endl;

	// Error if the file cannot be opened

	ifstream infile(filename.c_str());

	if (not infile.is_open()) {
		cerr << "Error: cannot open " << filename << endl;
		return 1;
	}

	// Reading the first 4 lines (Skipping the header lines).
	string line;

    for(int i = 0; i < 3; ++i)
	{
        getline(infile, line);
	}

	// Vector creation
	vector <double> vecRain;
	vector <double> vecAirFrost;
	vector <int> vecYear, vecMonth, vecDay;

	// ifstream the token(column)
	double colMaxTemp, colMinTemp, colAirFrost, colRain, colSun;
	int colYear, colMonth, colDays;	

	// While loop reading the remaining lines of the file.
	int cl = 0;
	while (getline(infile, line))
	{
		if (infile >> colYear >> colMonth >>  colMaxTemp >> colMinTemp >> colAirFrost >> colRain >> colSun)
		{
			// Store values in vectors.
			vecRain.push_back(colRain);
			vecAirFrost.push_back(colAirFrost);
			vecYear.push_back(colYear);
			vecMonth.push_back(colMonth);			
		}
		cl++;
	}

	// Closing the file.
	infile.close();	
	
	cout << "Rainfall measurements line count: " << vecRain.size() <<endl;
	
	vector<double> totalRain;

	// Get each years total. Calling the function total_rain using 2 arguments.
	total_rain(vecRain, totalRain);

	//Find max (Wettest Year).

	vector<double>::const_iterator i;
	double max = 0;
	int maxYear;
	int yearCounter = 1930;

	// Find min (Dryest Year).

	double min = 1000;
	int minYear = 1930;


	for (i = totalRain.begin(); i != totalRain.end(); i++) {
		if (*i > max){
		    max = *i;
		    maxYear = yearCounter;
		}
		if (*i < min){
		    min = *i;
		    minYear = yearCounter;
		}
		yearCounter++;
	}

	// Wettest Year & Total Rainfall
	cout << "Wettest year: " << maxYear << endl;	
	cout << "Total rainfall for " << maxYear << " was: " << max << "mm" << endl;	

	// Dryest Year & Total Rainfall
	cout << "Dryest year: " << minYear << endl;
	cout << "Total rainfall for " << minYear << " was: " << min << "mm" << endl;	

	// Calculating airfrost data
	maxFrost( vecAirFrost, vecMonth, vecYear);

	return 0;
}
