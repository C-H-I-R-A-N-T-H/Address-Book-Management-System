#include "contact.h"
// Dummy contact data
static Contact dummyContacts[] = {
    {"Chiru", "5646859575", "chiru@91@gmail.com"},
    {"Shantosh", "4563524189", "shantu@gmail.com"},
    {"Sui", "1112223333", "suiii@gmail.com"},
    {"rahul", "4445556666", "rahulaa@gmail.com"},
    {"roshni", "7778889999", "roshi@gmail.com"},
    {"Mohanaa", "6665554444", "mohana@gmail.com"}
};

void populateAddressBook(AddressBook* addressBook)
{
    int numDummyContacts = sizeof(dummyContacts) / sizeof(dummyContacts[0]);
    for (int i = 0; i < numDummyContacts && addressBook->contactCount < MAX_CONTACTS; ++i) {
        addressBook->contacts[addressBook->contactCount++] = dummyContacts[i];
    }
}
