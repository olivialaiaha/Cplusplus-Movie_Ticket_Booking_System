// MemberDetails.cpp
// Member-function definitions for class MemberDetails
#include <iostream>
using namespace std;
#include "MemberDetails.h" // MemberDetails class definition

int inputAnInteger( int begin, int end );

MemberDetails::MemberDetails( MemberDatabase &theMemberDatabase )
   : memberDatabase( theMemberDatabase )
{
}

void MemberDetails::execute( vector< Member >::iterator it )
{
	it->display();
	cout << "\n\nWhich one do you want to modify (0 - not modify)? ";
	while (true){
		char tmp[40];
		switch (inputAnInteger(0, 5)){
		case 0:
			return;//0 - not modify

		case 1:
			cout << "Enter correct data: ";
			cin >> tmp;
			it->setName(tmp);
			cout << "\nSuccessful!\n\n";
			return;

		case 2:
			cout << "Enter correct data: ";
			cin >> tmp;
			if (memberDatabase.existingEmail(tmp)){//確認email是否存在
				cout << "\nAn account already exists with the email!\n\n";
				return;
			}
			it->setEmail(tmp);
			cout << "\nSuccessful!\n\n";
			return;

		case 3:
			cout << "Enter correct data: ";
			cin >> tmp;
			it->setPhone(tmp);
			cout << "\nSuccessful!\n\n";
			return;

		case 4:
			cout << "Enter correct data: ";
			cin >> tmp;
			if (memberDatabase.existingId(tmp))//確認ID是否存在
			{
				cout << "\nAn account already exists with the ID Number!\n\n";
				return;
			}
			it->setIdNumber(tmp);
			cout << "\nSuccessful!\n\n";
			return;

		case 5:
			cout << "Enter correct data: ";
			cin >> tmp;
			it->setPassword(tmp);
			cout << "\nSuccessful!\n\n";
			return;

		default:
			cout << "\nInput Error! Please try again: ";
			break;
		}
	}
}