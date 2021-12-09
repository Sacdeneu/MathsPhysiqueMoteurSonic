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

private:
	vector<Contact> contacts;
	int maxContacts;
};
