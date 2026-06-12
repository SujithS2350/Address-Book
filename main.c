/*
Name : Sujith.S
Project Name : Address Book
Project Start Date : 27/03/2026
Project End Date : 02/04/2026
Project Description : This project is a digital adaptation of the physical address book that allows the user to 
save new contacts, edit, delete and search and list already saved contacts. The digital adaptations allows for much easier 
and efficient access to all the contact details as it provides flexibility of searching contacts using various parameters.
The list is automatically sorted in alphabetical order avoiding manual updation. The program also saves the contacts in a 
file at the end of the program which can be loaded back when the program is run again.
*/
#include <stdio.h>          // including standard input/output functions
#include "contact.h"        // including declarations of user defined functions


int main()                  // main function
{
    
    int choice;                 // choice variable declared to take input from user's choice
    AddressBook addressBook;    // declaring an addressBook variable which is the database of this project

    loadContactsFromFile(&addressBook);     // function call to load all the contacts back

    // initialize(&addressBook); // Initialize the address book
    // addressBook.contactCount = 0;


    // starting a do-while loop
    do                                     
    {
        // printing Address Book Menu
        printf("|---------------------------------|\n");
        printf("|          Address Book           |\n");
        printf("|---------------------------------|\n");       
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
    	printf("6. Save and Exit\n");		
        // printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);               // scanning users input into choice variable
        
        switch (choice)                     // using switch to select operation
        {
            case 1:                         
                createContact(&addressBook);    // function call to create a new contact
                break;
            case 2:
                searchContact(&addressBook);    // function call search a contact
                break;
            case 3:
                editContact(&addressBook);      // function call to edit a contact
                break;
            case 4:
                deleteContact(&addressBook);    // function call to delete contact
                break;
            case 5:          
                listContacts(&addressBook);     // function call to list all contacts
                break;
            case 6:
                printf("Saving and Exiting....\n");
                saveContactsToFile(&addressBook);   // function call to save the contacts into a file
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);      // if choice 6 i,e. save and exit is selected looping is exited
    
    return 0;       // termination of program
}
