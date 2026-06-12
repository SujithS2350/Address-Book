#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook)       // function definition for saving contacts into a file 
{
    FILE* fptr = fopen("contacts.txt", "w");            // opening the file in write mode

    fprintf(fptr, "#%d\n", addressBook->contactCount);  // storing the contactCount value   

    for(int i = 0; i < addressBook->contactCount; i++)  // starting a loop to store the contacts
    {
        // storing in the format name,phone_number,email_id\n

        fprintf(fptr, "%s,%s,%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
    fclose(fptr);       // closing the file
}

void loadContactsFromFile(AddressBook *addressBook)     // function definition for loading the contacts back from the file
{
    
    FILE* fptr = fopen("contacts.txt", "r");                // opening the file in read mode
    fscanf(fptr, "#%d\n", &(addressBook->contactCount));    // scaning the saved contactCount from the file
    for(int i = 0; i < addressBook->contactCount; i++)      // starting loop load contacts
    {
        fscanf(fptr, "%[^,]", addressBook->contacts[i].name);   // read the name till ',' is found

        getc(fptr);     // remove the ',' from stdin                                              

        fscanf(fptr, "%[^,]", addressBook->contacts[i].phone);  // read the phone number till ',' is found
        
        getc(fptr);     // remove the ',' from the stdin

        fscanf(fptr, "%s\n", addressBook->contacts[i].email);    // read the email till '\n' 
    }
    fclose(fptr);       // closing the file
}

  