// MovieDatabase.cpp
// Member-function definitions for class MovieDatabase
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace::std;
#include "MovieDatabase.h" // MovieDatabase class definition

extern char hours[ 17 ][ 8 ];

// MovieDatabase default constructor loads movies from the file Movies.dat
MovieDatabase::MovieDatabase()
{
   loadMovies();
}

// MovieDatabase destructor saves movies into the file Movies.dat
MovieDatabase::~MovieDatabase()
{
   saveMovies();
}

int MovieDatabase::getNumMovies()
{
   return movies.size();
}

Movie MovieDatabase::getMovie( int movieCode )
{
   return movies[ movieCode ];
}

void MovieDatabase::setMovieSeat( int movieCode, int dateCode, int sessionTimeCode, int row, int col )
{
   movies[ movieCode ].setOccupiedSeat( dateCode, sessionTimeCode, row, col );
}

void MovieDatabase::displaySessionTimes( char movieNames[][ 60 ], char availableDates[][ 12 ] )
{
	for (int i = 0; i < movies.size(); i++){
		cout << i << ". Movie: " << movieNames[i] << endl;
		cout << "   Date:  ";
		for (int j = 0; j < 4; j++){
			if (movies[i].getDate(j) == 1){
				cout << j << ". " << availableDates[j] << ",  ";
			}
		}
		cout << endl;
		cout << "   Session Time:  ";
		for (int j = 0; j < 17; j++){
			if (movies[i].getSessionTime(j) == 1){
				cout << j << ". " << hours[j] << ",  ";
			}
		}
		cout << endl << endl;
	}
}

void MovieDatabase::loadMovies()
{
	Movie buffer;
	ifstream inFile("Movies.dat", ios::binary | ios::in);

	if (!inFile){
		cout << "Movies.dat could not be opend." << endl;
		system("pause");
	}
	while (!inFile.eof()){
		/*if (inFile.eof()){
			break;
		}
		inFile.read((char*)&buffer, sizeof(Movie));

		movies.push_back(buffer);*/
		inFile.read(reinterpret_cast<char*>(&buffer), sizeof(Movie));
		if (!inFile.eof())
			movies.push_back(buffer);
	}

	inFile.close();
}

void MovieDatabase::saveMovies()
{
	ofstream outMoviesFile("Movies.dat", ios::out | ios::binary);
	if (!outMoviesFile){
		cout << "Movies.dat could not be opend." << endl;
		system("pause");
		exit(1);
	}
	for (int i = 0; i < movies.size(); i++){
		outMoviesFile.write((char*)&movies[i], sizeof(Movie));
	}
	outMoviesFile.close();
}