#include "collisionData.h"

CollisionData::CollisionData()
{
	maxContacts = 8;
}

int CollisionData::GetContactCount()
{
	return contacts.size();
}

Contact* CollisionData::GetContact(int index)
{
	if (index >= contacts.size())
		return NULL;

	return &(contacts[index]);
}