// Booking.cpp
// Member-function definitions for class Booking
#include <iostream>
#include <iomanip>
#include "Booking.h" // Booking class definition

Booking::Booking()
{
}

void Booking::setEmail( string theEmail )
{
   int length = theEmail.size();
   length = ( length < 40 ? length : 39 );
   for( int i = 0; i < length; i++ )
      email[ i ] = theEmail[ i ];
   email[ length ] = '\0';
}

string Booking::getEmail()
{
   return string( email );
}

void Booking::setMovieCode( int theMovieCode )
{
   movieCode = ( theMovieCode > 0 ? theMovieCode : 0 );
}

int Booking::getMovieCode()
{
   return movieCode;
}

void Booking::setDateCode( int theDateCode )
{
   dateCode = ( theDateCode > 0 ? theDateCode : 0 );
}

int Booking::getDateCode()
{
   return dateCode;
}

void Booking::setSessionTimeCode( int theSessionTimeCode )
{
   sessionTimeCode = ( theSessionTimeCode > 0 ? theSessionTimeCode : 0 );
}

int Booking::getSessionTimeCode()
{
   return sessionTimeCode;
}

void Booking::setNumTickets( int theNumTickets[] )
{
   for( int i = 0; i < 4; i++ )
      numTickets[ i ] = ( theNumTickets[ i ] > 0 ? theNumTickets[ i ] : 0 );
}

int Booking::getNumTickets( int ticketType )
{
   return numTickets[ ticketType ];
}

void Booking::setSeletedSeats( string theSeletedSeats[], int numSeats )
{
   for( int i = 0; i < numSeats; i++ )
   {
      seletedSeats[ i ][ 0 ] = theSeletedSeats[ i ][ 0 ];
      seletedSeats[ i ][ 1 ] = theSeletedSeats[ i ][ 1 ];
   }
}

string Booking::getSeletedSeat( int number )
{
	string output = {seletedSeats[number][0], seletedSeats[number][1]};
	return output;
}

void Booking::displayBooking( MovieDatabase &movieDatabase )
{
	int total = 0;
	for (int i = 0; i < 4; i++){
		total += numTickets[i] * movieDatabase.getMovie(movieCode).getPrice(i);
	}
	cout << setw(27) << right << "No. of Tickets" << setw(7) << right << "Price" << setw(10) << right << "Subtotal" << endl;
	if (numTickets[0] != 0){
		cout << setw(17) << left << "Adult ticket" << setw(10) << right << numTickets[0] << setw(7) << right << movieDatabase.getMovie(movieCode).getPrice(0) << setw(10) << right << numTickets[0] * movieDatabase.getMovie(movieCode).getPrice(0) << endl;
	}
	if (numTickets[1] != 0){
		cout << setw(17) << left << "Concession ticket" << setw(10) << right << numTickets[1] << setw(7) << right << movieDatabase.getMovie(movieCode).getPrice(1) << setw(10) << right << numTickets[1] * movieDatabase.getMovie(movieCode).getPrice(1) << endl;
	}
	if (numTickets[2] != 0){
		cout << setw(17) << left << "Disability ticket" << setw(10) << right << numTickets[2] << setw(7) << right << movieDatabase.getMovie(movieCode).getPrice(2) << setw(10) << right << numTickets[2] * movieDatabase.getMovie(movieCode).getPrice(2) << endl;
	}
	if (numTickets[3] != 0){
		cout << setw(17) << left << "Elderly ticket" << setw(10) << right << numTickets[3] << setw(7) << right << movieDatabase.getMovie(movieCode).getPrice(3) << setw(10) << right << numTickets[3] * movieDatabase.getMovie(movieCode).getPrice(3) << endl;
	}
	cout << endl;
	cout << "Total Amount For Tickets: " << total << endl;
}