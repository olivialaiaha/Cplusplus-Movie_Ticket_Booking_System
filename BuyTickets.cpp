// BuyTickets.cpp
// Member-function definitions for class BuyTickets
#include <iostream>
#include <iomanip>
using namespace::std;
#include "BuyTickets.h" // BuyTickets class definition

extern char hours[ 17 ][ 8 ];
extern char movieNames[ 30 ][ 60 ];
extern char availableDates[ 10 ][ 12 ];
extern int numDates;
int inputAnInteger( int begin, int end );

// BuyTickets default constructor
BuyTickets::BuyTickets( MovieDatabase &theMovieDatabase, BookingDatabase &theBookingDatabase, string theEmail )
   : movieDatabase( theMovieDatabase ),
     bookingDatabase( theBookingDatabase )
{
   int length = theEmail.size();
   for( int i = 0; i < length; i++ )
      email[ i ] = theEmail[ i ];
   email[ length ] = '\0';
}

void BuyTickets::execute()
{
	cout << endl;
	movieDatabase.displaySessionTimes(movieNames, availableDates);
	int choice;

	Booking newBooking;
	while (true){
		cout << "Enter movie code(0 - 10): ";
		choice = inputAnInteger(0, 10);
		if (choice >= 0 && choice <= 10){
			newBooking.setMovieCode(choice);
			break;
		}
	}
	cout << endl;
	while (true){
		cout << "Enter date code(0 - 3): ";
		choice = inputAnInteger(0, 3);
		if (choice >= 0 && choice <= 3 && movieDatabase.getMovie(newBooking.getMovieCode()).getDate(choice) == 1){
			newBooking.setDateCode(choice);
			break;
		}
	}
	cout << endl;
	while (true){
		cout << "Enter session time code(0 - 16): ";
		choice = inputAnInteger(0, 16);
		if (choice >= 0 && choice <= 16 && movieDatabase.getMovie(newBooking.getMovieCode()).getSessionTime(choice) == 1){
			newBooking.setSessionTimeCode(choice);
			break;
		}
	}
	cout << endl;

	newBooking.setEmail(email);
	cout << "Movie: " << movieNames[newBooking.getMovieCode()] << endl;
	cout << "Date: " << availableDates[newBooking.getDateCode()] << endl;
	cout << "Show Time: " << hours[newBooking.getSessionTimeCode()] << endl;
	cout << "Price: Adult-" << movieDatabase.getMovie(newBooking.getMovieCode()).getPrice(0)
		<< ", Concession-" << movieDatabase.getMovie(newBooking.getMovieCode()).getPrice(1)
		<< ", Disability-" << movieDatabase.getMovie(newBooking.getMovieCode()).getPrice(2)
		<< ", Elderly-" << movieDatabase.getMovie(newBooking.getMovieCode()).getPrice(3) << endl << endl;

	int numTickets[4];
	while (true){
		while (true){
			cout << "Enter the number of adult tickets (0 - 6): ";
			choice = inputAnInteger(0, 6);
			if (choice >= 0 && choice <= 6){
				numTickets[0] = choice;
				break;
			}
		}
		while (true){
			cout << "Enter the number of concession tickets (0 - 6): ";
			choice = inputAnInteger(0, 6);
			if (choice >= 0 && choice <= 6){
				numTickets[1] = choice;
				break;
			}
		}
		while (true){
			cout << "Enter the number of disability tickets (0 - 6): ";
			choice = inputAnInteger(0, 6);
			if (choice >= 0 && choice <= 6){
				numTickets[2] = choice;
				break;
			}
		}
		while (true){
			cout << "Enter the number of elderly tickets (0 - 6): ";
			choice = inputAnInteger(0, 6);
			if (choice >= 0 && choice <= 6){
				numTickets[3] = choice;
				break;
			}
		}
		cout << endl;
		if (numTickets[0] + numTickets[1] + numTickets[2] + numTickets[3] != 0){
			break;
		}
	}
	newBooking.setNumTickets(numTickets);

	newBooking.displayBooking(movieDatabase);
	selectSeats(newBooking);
	cin.ignore();
}

void BuyTickets::selectSeats( Booking &newBooking )
{
	/*
	char alphabet = 'A', seatArray[3];
	int info[3] = {newBooking.getMovieCode(),
		newBooking.getDateCode(),
		newBooking.getSessionTimeCode()};
	int numTotal = 0;

	cout << "\n ";
	for (int i = 0; i < 12; i++){
		cout << " " << alphabet;
		alphabet++;
	}
	cout << endl;

	for (int i = 0; i < 8; i++){
		cout << i;
		for (int j = 0; j < 12; j++){
			cout << " " << movieDatabase.getMovie(info[0]).getOccupiedSeat(info[1], info[2], i, j);
		}
		cout << endl;
	}

	for (int i = 0; i < 4; i++){
		numTotal += newBooking.getNumTickets(i);
	}
	string seats[24][2];
	int seatsNumber = 1;
	cout << "Select " << numTotal << " seats (e.g. 0A):\n";
	for (int i = 0; i < numTotal;){
		cout << "? ";
		cin >> seatArray;
		int buffer[2] = {seatArray[0] - '0', seatArray[1] - 'A'};
		if (buffer[0] > 7 || seatArray[1] > 'L'){
			cout << "This seat is not available. Please select another seat.\n";
		}else if (movieDatabase.getMovie(info[0]).getOccupiedSeat(info[1], info[2], buffer[0], buffer[1]) == 1){
			cout << "This seat bas been occupied. Please select another seat.\n";
		} else{
			for (int j = 0; j < 2; j++){
				seats[i][j] = seatArray[j];
			}
			movieDatabase.setMovieSeat(info[0], info[1], info[2], buffer[0], buffer[1]);
			seatsNumber++;
			i++;
		}
	}
	newBooking.setSeletedSeats(*seats, seatsNumber);
	*/
	char cul = 'A';
	int info[3] = {
		newBooking.getMovieCode(),
		newBooking.getDateCode(),
		newBooking.getSessionTimeCode()},
		numTotal = 0;
	Movie chMovie = movieDatabase.getMovie(info[0]);
	cout << "\n ";
	for (int i = 0; i < 12; i++, cul++)
		cout << " " << cul;
	cout << endl;

	for (int i = 0; i < 8; i++){
		cout << i;
		for (int j = 0; j < 12; j++)
			if (chMovie.getOccupiedSeat(info[1], info[2], i, j))
				cout << " 1";
			else
				cout << " 0";
		cout << endl;
	}

	for (int i = 0; i < 4; i++)
		numTotal += newBooking.getNumTickets(i);
	cout << "Select " << numTotal << " seats (e.g. 0A):\n";
	string *seat = new string[numTotal]();
	for (int i = 0; i < numTotal;){
		cout << "? ";
		cin >> seat[i];
		int buffer[2] = {seat[i][0] - '0', seat[i][1] - 'A'};
		if (buffer[0] < 0 || buffer[0] > 7 || buffer[1] < 0 || buffer[1] > 11){
			cout << "\nThis seat is not available. Please select another seat.\n";
		} else if (chMovie.getOccupiedSeat(info[1], info[2], buffer[0], buffer[1])){
			cout << "\nThis seat bas been occupied. Please select another seat.\n";
		} else{
			movieDatabase.setMovieSeat(info[0], info[1], info[2], buffer[0], buffer[1]);//=true
			i++;
		}
	}
	newBooking.setSeletedSeats(seat, numTotal);
	
	cout << endl << "Successful!" << endl;
	bookingDatabase.addBooking(newBooking);
}