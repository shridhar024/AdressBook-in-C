#include <stdio.h>
#include "contacts.h"
#include <ctype.h>
#include <string.h>
#include "coloured_text.h"

/* ─── ADD CONTACT ────────────────────────────────────────────────────────────
   Prompts user for name / phone / email with input validation.
   Saves to contacts[index] on success.
   Returns 1 on success, 0 on failure / cancel.
─────────────────────────────────────────────────────────────────────────── */
int add_contact(Contact contacts[], int index)
{
    char temp_name[50];
    char temp_phone[15];
    char temp_email[50];
    char retry;

    /* NAME — no digits allowed */
    retry_name:
    retry = '\0';
    printf(CYAN "Enter name: " RESET);
    scanf(" %[^\n]", temp_name);
    for (int i = 0; temp_name[i] != '\0'; i++) {
        if (isdigit(temp_name[i])) {
            printf(RED "Name cannot contain numbers!\n" RESET);
            printf("Retry? (Y/N): ");
            scanf(" %c", &retry);
            if (retry == 'y' || retry == 'Y') goto retry_name;
            else { printf("Cancelled.\n"); return 0; }
        }
    }

    /* PHONE — no letters allowed */
    retry_phone:
    retry = '\0';
    printf(CYAN "Enter phone number: " RESET);
    scanf(" %[^\n]", temp_phone);
    for (int i = 0; temp_phone[i] != '\0'; i++) {
        if (isalpha(temp_phone[i])) {
            printf(RED "Phone number cannot contain letters!\n" RESET);
            printf("Retry? (Y/N): ");
            scanf(" %c", &retry);
            if (retry == 'y' || retry == 'Y') goto retry_phone;
            else { printf("Cancelled.\n"); return 0; }
        }
    }

    /* EMAIL — must contain '@' and '.' */
    retry_email:
    retry = '\0';
    printf(CYAN "Enter email: " RESET);
    scanf(" %[^\n]", temp_email);
    if (strchr(temp_email, '@') == NULL || strchr(temp_email, '.') == NULL) {
        printf(RED "Invalid email! Must contain '@' and '.'\n" RESET);
        printf("Retry? (Y/N): ");
        scanf(" %c", &retry);
        if (retry == 'y' || retry == 'Y') goto retry_email;
        else { printf("Cancelled.\n"); return 0; }
    }

    /* DUPLICATE CHECK */
    if (is_already_exists(contacts, index, temp_name, temp_phone)) {
        printf(RED "A contact with the same name or phone already exists!\n" RESET);
        return 0;
    }

    /* SAVE to array */
    strcpy(contacts[index].name,  temp_name);
    strcpy(contacts[index].phone, temp_phone);
    strcpy(contacts[index].email, temp_email);

    printf(GREEN "Contact added successfully!\n" RESET);
    return 1;
}

/* ─── DUPLICATE CHECK ────────────────────────────────────────────────────────
   Returns 1 if name OR phone matches an existing contact.
─────────────────────────────────────────────────────────────────────────── */
int is_already_exists(Contact contacts[], int count, char name[], char phone[])
{
    for (int i = 0; i < count; i++) {
        if (strcmp(contacts[i].name,  name)  == 0 ||
            strcmp(contacts[i].phone, phone) == 0)
            return 1;
    }
    return 0;
}

/* ─── SHOW ALL CONTACTS ──────────────────────────────────────────────────────
   Prints a numbered table of every saved contact.
─────────────────────────────────────────────────────────────────────────── */
void show_contact(Contact contacts[], int count)
{
    printf(YELLOW "\n===== Contact List (%d) =====\n" RESET, count);
    for (int i = 0; i < count; i++) {
        printf(CYAN "--- Contact %d ---\n" RESET, i + 1);
        printf("  Name  : %s\n", contacts[i].name);
        printf("  Phone : %s\n", contacts[i].phone);
        printf("  Email : %s\n", contacts[i].email);
    }
    printf(YELLOW "=============================\n" RESET);
}

/* ─── SEARCH CONTACT ─────────────────────────────────────────────────────────
   Case-insensitive partial search by name; exact match by phone.
─────────────────────────────────────────────────────────────────────────── */
void search_contact(Contact contacts[], int count)
{
    char keyword[50];
    int  found = 0;

    printf(CYAN "Enter name or phone to search: " RESET);
    scanf(" %[^\n]", keyword);

    printf(YELLOW "\n===== Search Results =====\n" RESET);
    for (int i = 0; i < count; i++) {

        /* lowercase copies for case-insensitive name comparison */
        char lower_name[50], lower_key[50];
        strncpy(lower_name, contacts[i].name, 49); lower_name[49] = '\0';
        strncpy(lower_key,  keyword,           49); lower_key[49]  = '\0';
        for (int j = 0; lower_name[j]; j++) lower_name[j] = (char)tolower(lower_name[j]);
        for (int j = 0; lower_key[j];  j++) lower_key[j]  = (char)tolower(lower_key[j]);

        if (strstr(lower_name,         lower_key) != NULL ||
            strstr(contacts[i].phone,  keyword)   != NULL)
        {
            printf(CYAN "--- Contact %d ---\n" RESET, i + 1);
            printf("  Name  : %s\n", contacts[i].name);
            printf("  Phone : %s\n", contacts[i].phone);
            printf("  Email : %s\n", contacts[i].email);
            found++;
        }
    }

    if (found == 0)
        printf(RED "No contacts found matching '%s'\n" RESET, keyword);
    else
        printf(YELLOW "Found %d result(s).\n" RESET, found);
}

/* ─── EDIT CONTACT ───────────────────────────────────────────────────────────
   Lets the user pick a contact by number, then update each field.
   Pressing Enter on an empty field keeps the current value.
─────────────────────────────────────────────────────────────────────────── */
void edit_contact(Contact contacts[], int count)
{
    show_contact(contacts, count);

    int index;
    printf(CYAN "Enter contact number to edit (1-%d): " RESET, count);
    scanf("%d", &index);

    if (index < 1 || index > count) {
        printf(RED "Invalid contact number!\n" RESET);
        return;
    }
    index--; /* convert to 0-based */

    char input[50];

    /* EDIT NAME */
    printf("Current name  : " BOLD "%s" RESET "\nNew name  (Enter to keep): ", contacts[index].name);
    scanf(" %[^\n]", input);
    if (strlen(input) > 0) {
        int valid = 1;
        for (int i = 0; input[i]; i++) if (isdigit(input[i])) { valid = 0; break; }
        if (valid) strcpy(contacts[index].name, input);
        else printf(RED "Invalid name — keeping original.\n" RESET);
    }

    /* EDIT PHONE */
    printf("Current phone : " BOLD "%s" RESET "\nNew phone (Enter to keep): ", contacts[index].phone);
    scanf(" %[^\n]", input);
    if (strlen(input) > 0) {
        int valid = 1;
        for (int i = 0; input[i]; i++) if (isalpha(input[i])) { valid = 0; break; }
        if (valid) strcpy(contacts[index].phone, input);
        else printf(RED "Invalid phone — keeping original.\n" RESET);
    }

    /* EDIT EMAIL */
    printf("Current email : " BOLD "%s" RESET "\nNew email (Enter to keep): ", contacts[index].email);
    scanf(" %[^\n]", input);
    if (strlen(input) > 0) {
        if (strchr(input, '@') != NULL && strchr(input, '.') != NULL)
            strcpy(contacts[index].email, input);
        else
            printf(RED "Invalid email — keeping original.\n" RESET);
    }

    printf(GREEN "Contact updated successfully!\n" RESET);
    save_contacts(contacts, count);
}

/* ─── DELETE CONTACT ─────────────────────────────────────────────────────────
   User picks a contact by number, confirms, then the array is shifted left
   to fill the gap and count is decremented.
─────────────────────────────────────────────────────────────────────────── */
void delete_contact(Contact contacts[], int *count)
{
    show_contact(contacts, *count);

    int index;
    printf(CYAN "Enter contact number to delete (1-%d): " RESET, *count);
    scanf("%d", &index);

    if (index < 1 || index > *count) {
        printf(RED "Invalid contact number!\n" RESET);
        return;
    }
    index--; /* convert to 0-based */

    char confirm;
    printf(RED "Delete '%s'? (Y/N): " RESET, contacts[index].name);
    scanf(" %c", &confirm);
    if (confirm != 'y' && confirm != 'Y') {
        printf("Delete cancelled.\n");
        return;
    }

    /* Shift every contact after the deleted one one position to the left */
    for (int i = index; i < (*count) - 1; i++)
        contacts[i] = contacts[i + 1];

    (*count)--;
    printf(GREEN "Contact deleted successfully!\n" RESET);
    save_contacts(contacts, *count);
}

/* ─── SAVE CONTACTS ──────────────────────────────────────────────────────────
   Writes count (int) followed by all Contact structs to a binary file.
─────────────────────────────────────────────────────────────────────────── */
void save_contacts(Contact contacts[], int count)
{
    FILE *fp = fopen("contacts.dat", "wb");
    if (fp == NULL) {
        printf(RED "Error opening file for saving!\n" RESET);
        return;
    }
    fwrite(&count,   sizeof(int),     1,     fp);
    fwrite(contacts, sizeof(Contact), count, fp);
    fclose(fp);
}

/* ─── LOAD CONTACTS ──────────────────────────────────────────────────────────
   Reads count then Contact structs from the binary file.
   If the file doesn't exist (first run), sets count = 0 silently.
─────────────────────────────────────────────────────────────────────────── */
void load_contacts(Contact contacts[], int *count)
{
    FILE *fp = fopen("contacts.dat", "rb");
    if (fp == NULL) {
        *count = 0;
        return;
    }
    fread(count,    sizeof(int),     1,      fp);
    fread(contacts, sizeof(Contact), *count, fp);
    fclose(fp);
    printf(GREEN "Contacts loaded (%d found).\n" RESET, *count);
}
