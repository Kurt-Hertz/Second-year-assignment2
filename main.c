/********* main.c ********
    Student Name 	= Kurt Hertz
    Student Number	= 101261740
*/

// Includes go here
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>

//#include "a2_nodes.h"
//#include "a2_functions.h"
#include "a2_functions.c"

void flushInputBuffer()
{
    int c;
    while (c = getchar() != '\n' && c != EOF) {};
}

int main()
{
    /******** DONT MODIFY THIS PART OF THE CODE ********/
    /* THIS CODE WILL LOAD THE DATABASE OF USERS FROM THE FILE 
       AND GENERATE THE STARTING LINKED LIST.
    */
    FILE *csv_file = fopen("user_details.csv", "r");
    if (csv_file == NULL)
    {
        perror("Error opening the CSV file");
        return 1;
    }
    // Parse CSV data and create users
    user_t *users = read_CSV_and_create_users(csv_file, 50);

    fclose(csv_file);
    /******** DONT MODIFY THIS PART OF THE CODE ********/
    
    /* IMPORTANT: You must use the users linked list created in the code above. 
                  Any new users should be added to that linked list.
    */

    // Your solution goes here

    printf("***********************************************\n");
    printf("        Welcome to Text-Based Facebook\n");
    printf("***********************************************\n");
    
    int in;

    while(true){
        
        in = 0;

        while(in < 1 || in > 6){
            print_menu();
            scanf("%d", &in);
            if (in > 0 && in < 7){
                break;
            } else{
                printf("\nInvalid choice. Please try again.\n");
            }
        }

        if (in == 1){

            char username[30];
            char password[15];

            printf("\nEnter a username: ");
            scanf("%30s", &username);

            printf("\nEnter an upto 15 characters password: ");
            scanf("%15s", &password);

            add_user(users, username, password);

            printf("**** User Added! ****\n");

        } else if (in == 2){

            char username[30];
            char password[15];
            user_t *user;

            printf("\nEnter username to update their password: ");
            scanf("%30s", &username);
            
            user = find_user(users, username);
            if(user == NULL){

                printf("\n\n-----------------------------------------------\n");
                printf("            User not found.\n");
                printf("-----------------------------------------------\n");

            } else {

                printf("\nEnter a new password that is upto 15 characters: ");
                scanf("%15s", &password);

                strcpy(user->password, password);  

                printf("**** Password changed! ****\n");
            }

            

        }else if (in == 3){
            
            char username[30];
            user_t *user = malloc(sizeof(user_t));
            assert(user != NULL);

            printf("\nEnter username to manage their posts: ");
            scanf("%30s", &username);

            user = find_user(users, username);

            if(user == NULL){

                printf("\n\n-----------------------------------------------\n");
                printf("            User not found.\n");
                printf("-----------------------------------------------\n");

            } else {

            int choice;

                while(true){

                    choice = 0;

                    display_user_posts(user);

                    printf("\nYour choice: ");
                    if (scanf("%d", &choice) != 1 || choice < 1 || choice > 3) {
                        printf("\nInvalid choice. Please try again.\n");

                        while (getchar() != '\n');
                        continue;  
                    }

                    if (choice == 1){
                   
                        char text[250];

                        if (text != NULL) {
                            flushInputBuffer();
                            printf("\nEnter your post content: ");
                            fgets(text, 250, stdin);

                            
                            int n = strlen(text);
                            if (n > 0 && text[n-1] == '\n') {
                                text[n-1] = '\0';
                            }
                            printf("Input: %s\n", text);
                            add_post(user, text);

                            printf("\nPost added to your profile.\n");
                
                        } 

                    } else if (choice == 2){

                        _Bool re = 0;
                        int number = 0; 

                        printf("\nWhich post you want to delete? ");
                        scanf("%d", &number);

                        re = delete_post(user, number);

                        if(re == 0){
                            printf("\nInvalid post's number\n");
                        } else {
                            printf("\nPost %d was deleted successfully!\n", number);
                        }

                    } else if (choice == 3){
                        break;
                    }
                }
            }
            
        }else if (in == 4){
            
            char username[30];
            user_t *user = malloc(sizeof(user_t));
            assert(user != NULL);

            printf("\nEnter username to manage their friends: ");
            scanf("%30s", &username);

            user = find_user(users, username);
            if(user == NULL){

                printf("\n\n-----------------------------------------------\n");
                printf("            User not found.\n");
                printf("-----------------------------------------------\n");

            } else {

                int choice;

                while(true){
                    
                    choice = 0;

                    printf("\n----------------------------------\n");
                    printf("        %s's friends\n", user->username);
                    printf("----------------------------------\n\n");
                    printf("1. Display all user's friends\n");
                    printf("2. Add a new friend\n");
                    printf("3. Delete a friend\n");
                    printf("4. Return to main menu\n\n");

                    printf("\nYour choice: ");
                    if (scanf("%d", &choice) != 1 || choice < 1 || choice > 4) {
                        printf("\nInvalid choice. Please try again.\n");

                        while (getchar() != '\n');
                        continue;  
                    }

                    if (choice == 1){
                        
                        display_user_friends(user);

                    } else if (choice == 2){

                        char friend[30];
                        printf("\nEnter a new friends' name: ");
                        scanf("%30s", &friend);

                        add_friend(user, friend);

                        printf("\nFriend added to the list.\n");

                    } else if (choice == 3){

                        char friend[30];
                        _Bool re = 0;

                        display_user_friends(user); 

                        printf("\nEnter a friend's name to delete: ");
                        scanf("%30s", &friend);

                        re = delete_friend(user, friend);

                        if(re == 0){
                            printf("\nInvalid friend's name\n");
                            break;
                        }

                        display_user_friends(user);
                    }else if (choice == 4){
                        break;
                    }
                }
            }

        }else if (in == 5){

            char ans;

            while(true){
                display_all_posts(users);

                printf("\nDo you want to display next 2 users posts? (Y/N): ");
                if (scanf(" %c", &ans) != 1 || (ans != 'y' && ans != 'n')) {
                    printf("\nInvalid choice. Please try again.\n");

                    while (getchar() != '\n');
                    continue;  
                }

                if (ans == 'n') {
                    break;
                } else if (ans == 'y') {

                    if (users != NULL && users->next != NULL) {
                        users = users->next->next;
                    } else {
                        printf("\nNo more users to display.\n");
                        break;
                    }
                }
            }
           
            
        }else if (in == 6){
            teardown(users);
            break;
        }
    }

    return 0;
}