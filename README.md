# Address-Book
An Address Book Management System in C is a menu-driven application used to store, search, edit, and delete contact details efficiently. The project uses structures, functions, and file handling concepts in C to manage contact information permanently. 
Technologies used - Advanced C – Structures, Functions, Arrays, File Handling, String Manipulation. 
Key challenges & Learnings  - Faced challenges in managing contact records, implementing search/edit/delete operations, and handling user inputs accurately in C. Learned file handling techniques, improved understanding of structures and functions, and gained experience in modular programming. 

# Address Book

A console-based Address Book application written in C that allows users to manage their contacts efficiently.

## Project Info

- **Author:** Sujith S
- **Start Date:** 27/03/2026
- **End Date:** 02/04/2026

## Description

This project is a digital adaptation of a physical address book. It allows users to save, edit, delete, search, and list contacts. Contacts are automatically sorted alphabetically and saved to a file so they persist across sessions.

## Features

- Add new contacts (name, phone number, email)
- Search contacts
- Edit existing contacts
- Delete contacts
- List all contacts in alphabetical order
- Save contacts to file and load them on next run

## File Structure

| File | Description |
|------|-------------|
| `main.c` | Entry point, menu loop |
| `contact.c / contact.h` | Core contact operations (create, search, edit, delete, list) |
| `file.c / file.h` | File I/O — save and load contacts from `contacts.txt` |
| `populate.c / populate.h` | Utility to populate address book with dummy data |
| `contacts.txt` | Persistent storage file for contacts |

## Data Structure

```c
typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[100];
    int contactCount;
} AddressBook;
```

## How to Compile and Run

```bash
gcc main.c contact.c file.c populate.c -o addressbook
./addressbook
```

Or using the Makefile (if provided):

```bash
make
./addressbook
```

## Usage

When you run the program, you'll see this menu:
Address Book

Create contact
Search contact
Edit contact
Delete contact
List all contacts
Save and Exit

Select an option by entering the corresponding number. Choose **6** to save all contacts and exit.

## Notes

- Maximum of **100 contacts** supported.
- Contacts are stored in `contacts.txt` in the format: `name,phone,email`
- The contact list is automatically sorted alphabetically.
