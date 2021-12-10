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

	return contacts.at(index);
}

void CollisionData::AddContact(Contact* newContact)
{
	if (contacts.size() < maxContacts)
		contacts.push_back(newContact);
}

Contact* CollisionData::GetDeepestContact()
{
	int deepestIndex = 0;
	float deepestPenetration = GetContact(0)->GetInterpenetration();
	for (int i = 1; i < GetContactCount(); i++)
	{
		float p = GetContact(i)->GetInterpenetration();
		if (p > deepestPenetration)
		{
			deepestPenetration = p;
			deepestIndex = i;
		}
	}
	return GetContact(deepestIndex);
}