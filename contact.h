#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100    // defining max contacts to be 100

typedef struct {        // creating the Contact structure
    char name[50];          // array of character called name to store name of contact
    char phone[20];         // array of character called phone to store phone number of contact
    char email[50];         // array of character called email to store emaill id of contact
} Contact;

typedef struct {        // creating another structure which will act as a database for the porject called AddressBook
    Contact contacts[100];      // creating an array of Contact datatype as defined earlier of size 100
    int contactCount;           // a contactCount variable to store the number of contacts present currently in the address book
} AddressBook;

// defination of all the user defined functions

void createContact(AddressBook *addressBook);
int searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);
void loadContactsFromFile(AddressBook *addressBook);
#endif
