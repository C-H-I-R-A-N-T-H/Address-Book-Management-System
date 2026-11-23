#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include <ctype.h>

int validate_name(char *str);
int validate_phone(AddressBook *addressBook, char *phone);
int validate_email(AddressBook *addressBook, char *email);
int Search_name(AddressBook *addressBook, char *name);
int Search_phone(AddressBook *addressBook, char *phone);
int Search_email(AddressBook *addressBook, char *email);

void listContacts(AddressBook *addressBook)
{
     for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("Name: %s\n", addressBook->contacts[i].name);
        printf("Phone: %s\n", addressBook->contacts[i].phone);
        printf("Email: %s\n", addressBook->contacts[i].email);
    }
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook);
    exit(EXIT_SUCCESS);
}

void createContact(AddressBook *addressBook)
{
    int flag = 0;
    do
    {
        printf("Enter the Name : ");
        scanf(" %[^\n]", addressBook->contacts[addressBook->contactCount].name);
        flag = validate_name(addressBook->contacts[addressBook->contactCount].name);
        if ( flag == 0 ) printf("The entered name is not valid, Please enter the correct name : ");
    } while(flag == 0);

    do
    {
        printf("Enter the phone number : ");
        scanf(" %[^\n]", addressBook->contacts[addressBook->contactCount].phone);
        flag = validate_phone(addressBook, addressBook->contacts[addressBook->contactCount].phone);
        if ( flag == 1 ) printf("The entered phone number is not having 10 digits, please enter the 10 digits number : ");
        if ( flag == 2 ) printf("The entered number containing non digit chars, please enter the proper 10 digit number : ");
        if ( flag == 3 ) printf("The entered number is already present, please enter the unique number : ");
    } while(flag!= 0);

    do
    {
        printf("Enter the Email : ");
        scanf(" %[^\n]", addressBook->contacts[addressBook->contactCount].email);
        flag = validate_email(addressBook, addressBook->contacts[addressBook->contactCount].email);
        if(flag!=0) printf("Invalid Email, try again : ");
    } while(flag!=0);

    addressBook->contactCount++;
    printf("The Contact has added Sucessfully\n");
}

void searchContact(AddressBook *addressBook)
{
    printf("1) Name\n2) Phone no\n3) Email\n");
    printf("Enter the Option to search : ");
    int option; char str[50]; int res=0; // FIXED: added res
    scanf("%d", &option);
    switch(option)
    {
        case 1:
            printf("Enter Name: ");
            scanf(" %[^\n]", str);
            res = Search_name(addressBook, str);
            if ( res == 0 ) printf("Please enter the correct name\n");
            else printf("The contact has found successfully\n");
            break;
        case 2:
            printf("Enter Phone: ");
            scanf(" %[^\n]", str);
            res = Search_phone(addressBook, str);
            if ( res == 0 ) printf("Please enter the correct number\n");
            else printf("The contact has found successfully\n");
            break;
        case 3:
            printf("Enter Email: ");
            scanf(" %[^\n]", str);
            res = Search_email(addressBook, str);
            if ( res == 0 ) printf("Please enter the correct email\n");
            else printf("The contact has found successfully\n");
            break;
        default: printf("Invalid option\n");
    }
}

void editContact(AddressBook *addressBook)
{
    int option, ret, editOption;
    char str[50], newData[50];
    printf("1. Name\n2. Phone no\n3. Email\nEnter option: ");
    scanf("%d", &option);
    if(option == 1){ printf("Enter Name: "); 
	    scanf(" %[^\n]", str); ret = Search_name(addressBook, str); }
    else if(option == 2){ printf("Enter Phone: ");
	    scanf(" %[^\n]", str); ret = Search_phone(addressBook, str); }
    else if(option == 3){ printf("Enter Email: ");
	    scanf(" %[^\n]", str); ret = Search_email(addressBook, str); }
    else 
    {
	    printf("Invalid option\n"); return; 
    }

    if(ret > 0){
        int index = -1;
        for(int i=0; i<addressBook->contactCount; i++){
            if(option==1 && strcmp(addressBook->contacts[i].name, str)==0) index=i;
            if(option==2 && strcmp(addressBook->contacts[i].phone, str)==0) index=i;
            if(option==3 && strcmp(addressBook->contacts[i].email, str)==0) index=i;
        }
        printf("Please select the option which you want to edit:\n1. Name\n2. Phone num\n3. Email\nEnter the option: ");
        scanf("%d", &editOption);


        printf("Enter new data: "); scanf(" %[^\n]", newData);
        if(editOption == 1) strcpy(addressBook->contacts[index].name, newData);
        else if(editOption == 2) strcpy(addressBook->contacts[index].phone, newData);
        else if(editOption == 3) strcpy(addressBook->contacts[index].email, newData);
        printf("Edited Successfully\n");
    }
    else
   
    {
	    printf("Contact not found\n");
    }
}

void deleteContact(AddressBook *addressBook)
{
    int option, index = -1; char str[50], ch;
    printf("1) Name\n2) Phone no\n3) Email\nEnter the option to search the contact: ");
    scanf("%d", &option);

    if(option == 1)
    { printf("Enter the Name: ");
	    scanf(" %[^\n]", str); 
	    for(int i=0; i<addressBook->contactCount; i++)
		    if(strcmp(addressBook->contacts[i].name, str)==0)
		    { 
			    index=i; break;
		    }
    }
    else
	    if(option == 2)
    { 
	    printf("Enter the Phone no: "); 
	    scanf(" %[^\n]", str); 
	    for(int i=0; i<addressBook->contactCount ;i++) 
	if(strcmp(addressBook->contacts[i].phone, str)==0)
	    { 
		    index=i; break;
	    }
    }
    else if(option == 3)
    { printf("Enter the Email: ");
	    scanf(" %[^\n]", str); 
	    for(int i=0; i<addressBook->contactCount; i++)
		    if(strcmp(addressBook->contacts[i].email, str)==0)
		    {
			    index=i; break;
		    
		    }
    }
    if(index == -1)
    {
	    printf("Contact Not found\n"); 
	    return;
    }
    printf("Name: %s\nPhone num: %s\nEmail: %s\n", addressBook->contacts[index].name, addressBook->contacts[index].phone, addressBook->contacts[index].email);
    printf("Confirm here do you want to delete the contact (Y/y): "); scanf(" %c", &ch);
    if(ch == 'Y' || ch == 'y'){
        for(int i=index; i < addressBook->contactCount - 1; i++) addressBook->contacts[i] = addressBook->contacts[i+1];
        addressBook->contactCount--;
        printf("The contact has deleted successfully\n");
    }
}

int validate_name(char *str)
{
    if (str == NULL || strlen(str) == 0) return 0;
    for (int i = 0; str[i]!= '\0'; i++)
        if (!isalpha((unsigned char)str[i]) && str[i]!=' ') return 0;
    return 1;
}

int Search_name(AddressBook *addressBook, char *name)
{
    int count = 0; int arr[100];
    for (int i=0; i<addressBook->contactCount; i++)
        if(strcmp(addressBook->contacts[i].name, name) == 0){ arr[count] = i; count++; }
    if ( count == 0 ){ printf("Contact Not found\n"); return 0; }
    for ( int i = 0; i < count ; i++)
        printf("%s\n%s\n%s\n",addressBook->contacts[arr[i]].name, addressBook->contacts[arr[i]].phone, addressBook->contacts[arr[i]].email);
    return count;
}

int validate_phone(AddressBook *addressBook, char *phone)
{
    if (strlen(phone)!= 10) return 1;
    for (int i = 0; i < 10; i++) if (!isdigit((unsigned char)phone[i])) return 2;
    for (int i = 0; i < addressBook->contactCount; i++) if (strcmp(addressBook->contacts[i].phone, phone) == 0) return 3;
    return 0;
}

int Search_phone(AddressBook *addressBook, char *phone)
{
    int count = 0; int arr[100];
    for(int i=0; i<addressBook->contactCount; i++)
        if(strcmp(addressBook->contacts[i].phone, phone)==0){ arr[count]=i; count++; }
    if(count==0){ printf("Contact Not found\n"); return 0; }
    for(int i=0; i<count; i++) printf("%s\n%s\n%s\n", addressBook->contacts[arr[i]].name, addressBook->contacts[arr[i]].phone, addressBook->contacts[arr[i]].email);
    return count;
}

int validate_email(AddressBook *addressBook, char *email)
{
    char *at = strchr(email, '@'); char *dot = strrchr(email, '.');
    if (at == NULL || dot == NULL) return 1;
    if (dot < at || (dot - at) <= 1) return 2;
    if (strlen(dot) <= 1) return 3;
    for (int i = 0; i < addressBook->contactCount; i++) if (strcmp(addressBook->contacts[i].email, email) == 0) return 4;
    return 0;
}

int Search_email(AddressBook *addressBook, char *email)
{
    int count = 0; int arr[100];
    for(int i=0; i<addressBook->contactCount; i++)
        if(strcmp(addressBook->contacts[i].email, email)==0){ arr[count]=i; count++; }
    if(count==0){ printf("Contact Not found\n"); return 0; }
    for(int i=0; i<count; i++) printf("%s\n%s\n%s\n", addressBook->contacts[arr[i]].name, addressBook->contacts[arr[i]].phone, addressBook->contacts[arr[i]].email);
    return count;
}
