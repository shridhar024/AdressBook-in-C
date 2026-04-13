#ifndef CONTACTS_H
#define CONTACTS_H

#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[15];
    char email[50];
} Contact;

// Add a new contact at given index, returns 1 on success, 0 on failure
int add_contact(Contact contacts[], int index);

// Check if a contact with same name or phone already exists
int is_already_exists(Contact contacts[], int count, char name[], char phone[]);

// Display all saved contacts
void show_contact(Contact contacts[], int count);

// Search a contact by name or phone
void search_contact(Contact contacts[], int count);

// Edit an existing contact
void edit_contact(Contact contacts[], int count);

// Delete a contact
void delete_contact(Contact contacts[], int *count);

// Save contacts to file
void save_contacts(Contact contacts[], int count);

// Load contacts from file
void load_contacts(Contact contacts[], int *count);

#endif
