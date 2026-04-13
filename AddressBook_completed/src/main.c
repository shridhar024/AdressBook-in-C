#include <stdio.h>
#include "coloured_text.h"
#include "contacts.h"
#include <ctype.h>
#include <string.h>

int count = 0;

int main()
{
    Contact contacts[MAX_CONTACTS];
    int choice, success;

    load_contacts(contacts, &count); // Load contacts from file at start

    do {
        printf(YELLOW "\n-----Address Book-----\n" RESET);
        printf(CYAN "1. Create Contact\n");
        printf("2. List Contacts\n");
        printf("3. Search for a contact\n");
        printf("4. Edit a contact\n");
        printf("5. Delete a contact\n");
        printf("6. Exit\n" RESET);
        printf(YELLOW "Enter your choice: " RESET);
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
            {
                if (count >= MAX_CONTACTS)
                {
                    printf(RED "Contact list is full!!\nDelete some contacts to add new...\n" RESET);
                    break;
                }

                success = add_contact(contacts, count);

                if (success)
                {
                    count++;
                    save_contacts(contacts, count);
                }
                else
                {
                    printf(RED "Failed to add contact!\n" RESET);
                }
                break;
            }

            case 2:
                if (count == 0)
                    printf(RED "There are no contacts saved!!\n" RESET);
                else
                    show_contact(contacts, count);
                break;

            case 3:
                if (count == 0)
                    printf(RED "There are no contacts saved!!\n" RESET);
                else
                    search_contact(contacts, count);
                break;

            case 4:
                if (count == 0)
                    printf(RED "There are no contacts saved!!\n" RESET);
                else
                    edit_contact(contacts, count);
                break;

            case 5:
                if (count == 0)
                    printf(RED "There are no contacts saved!!\n" RESET);
                else
                    delete_contact(contacts, &count);
                break;

            case 6:
                save_contacts(contacts, count);
                printf("Exiting...\n");
                break;

            default:
                printf(RED "Invalid choice! Please enter 1-6.\n" RESET);
        }

    } while (choice != 6);

    return 0;
}
