#pragma once
#include "contact.h"
#include <vector>

class CollisionData
{
public:
	//CONSTRUCTEURS
	CollisionData();
	~CollisionData() = default;

	int GetContactCount();
	Contact* GetContact(int index);
	void AddContact(Contact* newContact);
	Contact* GetDeepestContact();

private:
	vector<Contact*> contacts;
	int maxContacts;
};
