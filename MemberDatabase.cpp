// MemberDatabase.cpp
// Member-function definitions for class MemberDatabase
#include <iostream>
#include <fstream>
#include "MemberDatabase.h" // MemberDatabase class definition

// MemberDatabase default constructor loads members from the file Members.dat
MemberDatabase::MemberDatabase()
{
   loadMembers();
}

// MemberDatabase destructor saves members into the file Members.dat
MemberDatabase::~MemberDatabase()
{
   saveMembers();
}

vector< Member >::iterator MemberDatabase::end()
{
   return members.end();
}

// retrieve Member object containing specified id
bool MemberDatabase::existingId( string id )
{
	for (int i = 0; i < members.size(); i++){
		if (members.operator[](i).getIdNumber() == id){
			return true;
		}
	}
	return false;
} // end function existingId

// retrieve Member object containing specified email
bool MemberDatabase::existingEmail( string email )
{
	for (int i = 0; i < members.size(); i++){
		if (members.operator[](i).getEmail() == email){
			return true;
		}
	}
	return false;
} // end function existingEmail

void MemberDatabase::addMember( Member newMember )
{
   members.push_back( newMember );
   saveMembers();
   loadMembers();
}

vector< Member >::iterator MemberDatabase::getMember(string email, string password){
	vector< Member >::iterator it = members.begin();
	for (; it != members.end(); ++it){
		if (it->getEmail() == email && it->getPassword() == password){
			return it;
		}
	}
	cout << "\nSorry, unrecognized email or password.\n\n";
	return members.end();
}

void MemberDatabase::loadMembers()
{
	ifstream inMemberFile;
	inMemberFile.open("Members.dat", ios::in | ios::binary);
	if (!inMemberFile){
		cout << "Members.dat could not be opend." << endl;
		system("pause");
	}
	while (!inMemberFile.eof()){
		if (inMemberFile.eof()){
			break;
		}

		Member buffer;
		inMemberFile.read((char*)&buffer, sizeof(Member));
		if (!inMemberFile.eof()){
			members.push_back(buffer);
		}
	}
	inMemberFile.close();
}

void MemberDatabase::saveMembers()
{
	ofstream outMemberFile("Members.dat", ios::out | ios::binary);
	if (!outMemberFile){
		cout << "Members could not be opend." << endl;
		system("pause");
	}
	for (int i = 0; i < members.size(); i++){
		outMemberFile.write((char*)&members[i], sizeof(Member));
	}
	outMemberFile.close();
}