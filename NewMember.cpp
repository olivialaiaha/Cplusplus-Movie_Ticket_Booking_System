// NewMember.cpp
// Member-function definitions for class NewMember
#include <iostream>
#include <fstream>
#include "NewMember.h" // NewMember class definition

NewMember::NewMember( MemberDatabase &theMemberDatabase )
   : memberDatabase( theMemberDatabase )
{
}

void NewMember::execute()
{
	Member input;
	char tmp[40];
	cout << "Enter your ID number: ";
	cin >> tmp;
	while (memberDatabase.existingId(tmp))//確認ID是否存在
	{
		cout << "\nAn account already exists with the ID number!\n\n";
		return;
	}
	input.setIdNumber(tmp);
	cout << "Enter your name: ";
	cin >> tmp;
	input.setName(tmp);
	cout << "Enter an email address: ";
	cin >> tmp;
	while (memberDatabase.existingEmail(tmp))//確認email是否存在
	{
		cout << "\nAn account already exists with the email!\n\nEnter an email address: ";
		cin >> tmp;
	}
	input.setEmail(tmp);
	cout << "Enter a password: ";
	cin >> tmp;
	input.setPassword(tmp);
	cout << "Enter your phone number: ";
	cin >> tmp;
	input.setPhone(tmp);
	memberDatabase.addMember(input);
	cout << "\nSuccessful!\n\n";
	cin.ignore();
}