#include <stdio.h>      // including standard input/output functions
#include <stdlib.h>     // including standard library funtions
#include <string.h>     // including string related functions
// including user defined functions and datatypes
#include "contact.h"    
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook)         // function defination for lisiting contacts
{
    char temp[20];  // a temporary variable used in sorting logic

    printf("%-7s%-25s%-15s%-25s\n","Sl.No", "Name", "Mobile", "Email ID");  // printing the first line of the list

    for(int i = 0; i < addressBook->contactCount - 1; i++)
    {                                                                    // using bubble sort logic to sort the list in alphabetical order
        for(int j = 0 ; j < addressBook->contactCount -1 - i; j++)
        {
            int res = strcasecmp(addressBook->contacts[j].name,addressBook->contacts[j + 1].name);
            {
                if(res > 0)
                {
                    // swap logic

                    strcpy(temp, addressBook->contacts[j].name);
                    strcpy(addressBook->contacts[j].name,addressBook->contacts[j + 1].name);
                    strcpy(addressBook->contacts[j + 1].name, temp);
                    strcpy(temp, addressBook->contacts[j].phone);
                    strcpy(addressBook->contacts[j].phone,addressBook->contacts[j + 1].phone);  
                    strcpy(addressBook->contacts[j + 1].phone, temp);
                    strcpy(temp, addressBook->contacts[j].email);
                    strcpy(addressBook->contacts[j].email,addressBook->contacts[j + 1].email);
                    strcpy(addressBook->contacts[j + 1].email, temp);
                    
                }
            }
        }
    }
    // printing the contacts in a formatted way

    for(int i = 0; i < addressBook->contactCount; i++)
    {
        printf("%-7d%-25s%-15s%-25s\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    //loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

int validate_name(char *name)       // function to perform validation of a name entered
{
    while(*name)
    {
        // entered name must contain only alphabets, dots and spaces

        if(*name >= 'a' && *name <= 'z' || *name >= 'A' && *name <= 'Z' || *name ==' ' || *name == '.')
        {
            name++;
        }
        else
            return 0;
    }
    return 1;
}

int validate_mobile(char *mobile, AddressBook *addressBook)     // function to perform validation of a phone number entered
{
    // entered number must not be already present in the address book

    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].phone, mobile) == 0)
        {
            printf("Mobile number already present\n");
            return 0;
        }
    }

    // entered phone number must contain only digits and there must be 10 digits
    if(strlen(mobile) != 10)
        return 0;
    while(*mobile)
    {
        if(*mobile >= '0' && *mobile <= '9')
        {
            mobile++;
        }
        else
            return 0;
    }
    return 1;
}
int validate_mail(char *mail, AddressBook *addressBook)         // // function to perform validation of an email id entered
{
    // entered email id must not be already present in the address book

    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].email, mail) == 0)
        {
            printf("Email id already present\n");
            return 0;
        }
    }
    int i = 0;
    if(*mail >= 'a' && *mail <= 'z')    // 1st character must be a letter
    {
        int count = 0;
        while(mail[i])
        {
            if(mail[i] == '@')              // checking number of @ used and if there are character after @ or not
            {
                count++;
                if(mail[i + 1] == '.' || mail[i +1] == '\0')
                    return 0;
            }
            i++;    
        }
        i = 0;
        if(count != 1)
            return 0;
        if(strstr(mail, ".com") == NULL)       // checking if ".com is present or not"
            return 0;
        while(mail[i])
        {
            if(mail[i] >= 'A' && mail[i] <= 'Z')        // checking that all the alphabets must be lowercase
                return 0;
            i++;
        }
        i = 0;
        while(mail[i])
        {
            if(mail[i] == ' ')          // checking that there must be no spaces
                return 0;
            i++;
        }
        return 1;
    }
    else
        return 0;
}
void createContact(AddressBook *addressBook)    // function defination for creating a new cantact
{

    char name[20];  // name variable to store the name
    int valid;      // valid variable to store validation

    while(1)        
    {
        printf("Enter the name : ");
        scanf(" %[^\n]", name);         // scanning the name
        valid = validate_name(name);    // passing name to the function to check validation
        if(valid == 1)                  // if valid          
            break;
        printf("An invalid name was entered make sure to use only letters, spaces and dots.\n");
    }

    char mobile[20];    // mobile variable to store phone number

    while(1)
    {
        printf("Enter the mobile number : ");
        scanf(" %[^\n]", mobile);                       // scanning phone number
        valid = validate_mobile(mobile, addressBook);   // passing it to the function for validation
        if(valid == 1)                                  // if valid
            break;
        printf("An invalid mobile number was entered make sure to use only digits and there must be 10 digits.\n");
    }

    char mail[30];  // mail variable to store the email id

    while(1)
    {
        printf("Enter the email id : ");
        scanf(" %[^\n]", mail);                     // scanning the email id
        valid = validate_mail(mail, addressBook);   // passing it to the function for validation
        if(valid == 1)                              // if valid
            break;
        printf("An invalid email id was entered make sure to use proper email id.\n");
    }  

    // storing all the 3 data in the database

    strcpy(addressBook->contacts[addressBook->contactCount].name, name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, mobile);
    strcpy(addressBook->contacts[addressBook->contactCount].email, mail);
    printf("\nNew contact created successfully\n");
    addressBook->contactCount++;    // incrementing the number of contacts by 1

}

int search_by_name(AddressBook *addressBook)        // function defination to search a contact by name
{
    char name[30];                          // name varable to store a name to search
    printf("Enter the name to search: ");
    scanf(" %[^\n]", name);                 // taking name as input to search
    int i, count = 0;                       // count varable to see total number of match found
    for(i = 0; i < addressBook->contactCount; i++)
    {
        if(strcasestr(addressBook->contacts[i].name, name) != NULL)     // searching for matching name (fuull / partial)
        {
            count++;        // incrementing count when match is found and printing the contact details
            printf("%d\t%s\t%s\t%s\n", count, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
        }
    }
    if(count == 0)      // if no match found return
    {
        printf("No matching name found\n");
        return -1;
    }
    if(count == 1)      // if only 1 match found return the index of that contact
    {
        for(i = 0; i < addressBook->contactCount; i++)
        {
            if(strcasestr(addressBook->contacts[i].name, name) != NULL)
            {
                return i;
            }
        }   
    }
    // in case of multiple display of contacts, asking the user to enter sl-no of the contact
    int sl_no;      
    count = 0;
    printf("Enter the Sl No of the contact you want details about: ");
    scanf("%d", &sl_no);
    for(i = 0; i < addressBook->contactCount; i++)
    {
        if(strcasestr(addressBook->contacts[i].name, name) != NULL)
        {
            count++;
            if(count == sl_no)      // finding that contact and printing it
            {
                printf("1\t%s\t%s\t%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                return i;           // returning the index of that contact
            }
        }
    }
    
}

int search_by_mobile(AddressBook *addressBook)      // function defination to search a contact by phone number
{
    char mobile[11];        // mobile variable to store the phone number
    printf("Enter the mobile number to search: ");  
    scanf(" %[^\n]", mobile);       // taking the input of phone number
    int i;
    for(i = 0; i < addressBook->contactCount; i++)      // searching 
    {
        if(strcasestr(addressBook->contacts[i].phone, mobile) != NULL)  // if found printing the contact
        {
          printf("1\t%s\t%s\t%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
          return i;     // returning the index of contact
        }
    }
    printf("No matching phone number found\n");
    return -1;
}
int search_by_email(AddressBook *addressBook)   // function defination to search a contact by email id
{   
    char email[30];         // email variable to store the email id
    printf("Enter the email id to search: ");
    scanf(" %[^\n]", email);    // taking input of email id
    int i;
    for(i = 0; i < addressBook->contactCount; i++)      // searching
    {
        if(strcasestr(addressBook->contacts[i].email, email) != NULL)       // if found printing the contact


        
        {
          printf("1\t%s\t%s\t%s\n" ,addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
          return i;     // returning the index of contact
        }
    }
    printf("No matching email id found\n");
    return -1;
}

int searchContact(AddressBook *addressBook)         // function defination for searching contacts
{
    
    int i;      // variable i for storing index value
        int choise;     // variable to store the parameter by which user wants to search
        printf("By which parameter do you want to search by ?\n1. Name\n2. Mobile\n3. Email\n");
        scanf("%d", &choise);       // taking the input of user
        switch (choise)     // using switch case to select parameter
        {
            case 1:
                i = search_by_name(addressBook);        // function call to search by name if name as a parameter is selected
                break;
            case 2:
                i = search_by_mobile(addressBook);      // function call to search by mobile if Mobile  as a parameter is selected
                break;
            case 3:
                i = search_by_email(addressBook);       // function call to search by email if email as a parameter is selected
                break;
            default:
                printf("Invalid input\n");              // any other value entered is termed invalid

        }  
    return i;       // returning the index
}
void edit_name(int ind, AddressBook *addressBook)       // function defination for editing name
{
    char name[20];      // declaring variable to store new name
    while(1)
    {
        printf("Enter the new name: ");     // prompting user to enter the new name
        scanf(" %[^\n]", name);
        int valid = validate_name(name);    // validating name
        if(valid)                           // if valid then break out of the loop
            break;
        printf("Invalid name\n");           // else invalid input
    }   
    strcpy(addressBook->contacts[ind].name,name);       // updating the valid name
    printf("Updated successfully\n");

    return;
    
}
void edit_mobile(int ind, AddressBook *addressBook)     // function defination for editing phone number
{
    char phone[20];     // declaring variable to store new phone number
    while(1)
    {
        printf("Enter the new phone number: ");     // prompting user to enter the new phone number
        scanf(" %[^\n]", phone);
        int valid = validate_mobile(phone, addressBook);    // validating phone number
        if(valid)                                           // if valid then break out of the loop
            break;
        printf("Invalid phone number\n");                   // else invalid input
    }
    strcpy(addressBook->contacts[ind].phone,phone);         // updating the valid phone number
    printf("Updated successfully\n");

    return;
    
}
void edit_email(int ind, AddressBook *addressBook)      // function defination for editing email id
{
    char email[20];     // declaring variable to store new email id
    while(1)
    {
        printf("Enter the new email id: ");         // prompting user to enter the new email id
        scanf(" %[^\n]", email);
        int valid = validate_mail(email, addressBook);      // validating email id
        if(valid)                                           // if valid then break out of the loop
            break;                                              
        printf("Invalid email id\n");                       // else invalid input
    }
    strcpy(addressBook->contacts[ind].email,email);         // updating the valid email id
    printf("Updated successfully\n");

    return;
    
}
void editContact(AddressBook *addressBook)          // function defination for editing contacts
{
    // calling the search contact fnuction for finding the contact to edit

	int ind = searchContact(addressBook);           // storing the index of the contact the user wants to edit
    if(ind < 0)     // if contact not found return
        return;
    // asking the user for the parameter they wnat to edit
    printf("Which attribute would you like to edit??\n1. Name\n2. Mobile\n3. Email\n");

    int choise;
    scanf("%d", &choise);       // storing choice in choise

    switch(choise)              // using switch case to select parameter
    {
        case 1:
            edit_name(ind, addressBook);        // function call to edit name
            break;
        case 2:
            edit_mobile(ind, addressBook);      // function call to edit phone number
            break;
        case 3:
            edit_email(ind, addressBook);       // function call to edit email id
            break;
        default:
            printf("Invalid input\n");          // any other input is termed invalid
    }
    
}

void deleteContact(AddressBook *addressBook)     // function defination to delete a contact
{
    // calling the search contact fnuction for finding the contact to delete
    int ind = searchContact(addressBook);       // storing the index of the contact the user wants to edit
    if(ind < 0)     // if contact not found return
        return;
    for(int i = ind; i < addressBook->contactCount - 1; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];        // deleting the contact by shifting and overwriting
    }
    printf("Contact deleted\n");
    addressBook->contactCount--;        // decrementing the total contacts by 1
}
