// BookingDatabase.cpp
// Member-function definitions for class BookingDatabase
#include <iostream>
#include <fstream>
#include "BookingDatabase.h" // BookingDatabase class definition

extern char hours[17][8];
extern char movieNames[30][60];
extern char availableDates[10][12];

// BookingDatabase default constructor loads bookings from the file Bookings.dat
BookingDatabase::BookingDatabase(){
	loadBookings();
}

// BookingDatabase destructor saves bookings into the file Bookings.dat
BookingDatabase::~BookingDatabase(){
	saveBookings();
}

void BookingDatabase::addBooking(Booking newBooking){
	bookings.push_back(newBooking);
	saveBookings();
}

// retrieve Booking object containing specified email
bool BookingDatabase::existingBooking(string email){
	for (int i = 0; i < bookings.size(); i++){
		if (bookings[i].getEmail() == email){
			return true;
		}
	}
	return false;
} // end function existingBooking

void BookingDatabase::displayBookings( string email, MovieDatabase &movieDatabase )
{
	if (existingBooking(email) == false){
		cout << "No bookings!" << endl;
	} else{
		int noBookings[100], counter = 0;
		for (int i = 0; i < bookings.size(); i++){
			if (bookings[i].getEmail() == email){
				noBookings[counter] = i;
				counter++;
			}
		}
		
		cout << "\nBooking History:" << endl;
		for (int i = 0; i < counter; i++){
			cout << "\n" << i+1 << '.' << endl;
			cout << "Movie: " << movieNames[bookings[noBookings[i]].getMovieCode()] << endl;
			cout << "Date: " << availableDates[bookings[noBookings[i]].getDateCode()] << endl;
			cout << "Show Time: " << hours[bookings[noBookings[i]].getSessionTimeCode()] << endl;
			cout << "Seats:";
			for (int j = 0; j < (bookings[noBookings[i]].getNumTickets(0)+ bookings[noBookings[i]].getNumTickets(1)+ bookings[noBookings[i]].getNumTickets(2)+ bookings[noBookings[i]].getNumTickets(3)); j++){
				cout << " " << bookings[noBookings[i]].getSeletedSeat(j);
			}
			cout << endl << endl;

			bookings[noBookings[i]].displayBooking(movieDatabase);
			cout << endl;
			cout << "----------------------------------------------" << endl;
		}
	}
	/*if (existingBooking(email)){
		cout << "\nBooking History:\n";
		for (int i = 0; i < bookings.size(); i++)
			if (email == bookings[i].getEmail()){
				Movie buffer = movieDatabase.getMovie(bookings[i].getMovieCode());
				cout << "\nMovie: " << movieNames[bookings[i].getMovieCode()]
					<< "\nDate: " << availableDates[bookings[i].getDateCode()]
					<< "\nShow Time: " << hours[bookings[i].getSessionTimeCode()]
					<< "\nSeats: ";
				int numSeat = 0;
				for (int j = 0; j < 4; j++)
					numSeat += bookings[i].getNumTickets(j);
				for (int j = 0; j < numSeat; j++)
					cout << bookings[i].getSeletedSeat(j) << "  ";
				cout << "\n\n";
				bookings[i].displayBooking(movieDatabase);
				cout << endl;
				for (int j = 0; j < 60; j++)
					cout << "-";
				cout << endl;
			}//end if
	} else cout << "No bookings!\n";*/
}

void BookingDatabase::loadBookings()
{
	ifstream inBookingFile("Bookings.dat", ios::in | ios::binary);
	if (!inBookingFile){
		cout << "Bookings.dat could not be opend." << endl;
		system("pause");
		exit(1);
	}
	while (!inBookingFile.eof()){
		if (inBookingFile.eof())
			break;
		Booking buffer;
		inBookingFile.clear();
		inBookingFile.read((char*)&buffer, sizeof(Booking));
		if (!inBookingFile.eof()){
			/*for (int i = 0; i < 40; i++){
				bookingHistories[numBookings].email[i] = buffer.email[i];
			}
			bookingHistories[numBookings].movieCode = buffer.movieCode;
			bookingHistories[numBookings].dateCode = buffer.dateCode;
			bookingHistories[numBookings].sessionTimeCode = buffer.sessionTimeCode;
			for (int i = 0; i < 4; i++){
				bookingHistories[numBookings].numTickets[i] = buffer.numTickets[i];
			}
			for (int i = 0; i < 24; i++){
				for (int j = 0; j < 4; j++){
					bookingHistories[numBookings].seletedSeats[i][j] = buffer.seletedSeats[i][j];
				}
			}
			numBookings++;*/
			addBooking(buffer);
		}
	}
	inBookingFile.close();
}

void BookingDatabase::saveBookings()
{
	ofstream outMemberFile("Bookings.dat", ios::out | ios::binary);
	if (!outMemberFile){
		cout << "Bookings.dat could not be opend." << endl;
		system("pause");
		exit(1);
	}
	for (int i = 0; i < bookings.size();i++){
		outMemberFile.write((char*)&bookings[i], sizeof(Booking));
	}
	outMemberFile.close();
}