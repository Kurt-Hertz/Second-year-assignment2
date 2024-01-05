/********* definitions.c ********
   Student Name 	= Kurt Hertz
   Student Number	= 101261740
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "a2_nodes.h"
#include "a2_functions.h"

// Your solution goes here

/*
   Function that creates a new user and adds it to a sorted (ascending order) linked list at
   the proper sorted location. Return the head of the list.
*/
user_t *add_user(user_t *users, const char *username, const char *password)
{
   //Make new user
   user_t *new = malloc(sizeof(user_t));
   assert(new != NULL);

   strcat(new->username, username);
   strcat(new->password, password);
   new->friends = NULL;
   new->posts = NULL;
   new->next = NULL;

   // Insert in ascending order
   if(users == NULL || stricmp(users->username, username) > 0){
      users = new;
      return users;
   }

   user_t *temp = users;

   while(temp != NULL && strcmp(temp->username, username) > 0){
      temp = temp->next;
   }
   new->next = temp;
   temp = new;
   return users;
   
}
/*
   Function that searches if the user is available in the database
   Return a pointer to the user if found and NULL if not found.
*/
user_t *find_user(user_t *users, const char *username)
{
   user_t *temp = users;

   while(temp != NULL && strcmp(temp->username, username) != 0){
      temp = temp->next;
   }

   if(temp == NULL){
      printf("NOT FOUND");
      return NULL;
   }

   return temp;
   
}
/*
   Function that creates a new friend's node.
   Return the newly created node.
*/
friend_t *create_friend(const char *username)
{
   friend_t *new = malloc(sizeof(friend_t));
   assert(new != NULL);

   strcat(new->username, username);
   new->next = NULL;

   return new;
}

/*
   Function that links a friend to a user. The friend's name should be added into
   a sorted (ascending order) linked list.
*/
void add_friend(user_t *user, const char *friend)
{
   friend_t *new = create_friend(friend);

   if(user->friends == NULL || stricmp(user->friends->username, friend) > 0){
      new->next = user->friends;
      user->friends = new;
      return;
   }

   friend_t *temp = user;

   while(temp != NULL && strcmp(temp->username, friend) > 0){
      temp = temp->next;
   }
   new->next = temp;
   temp = new;
}

/*
   Function that removes a friend from a user's friend list.
   Return true of the friend was deleted and false otherwise.
*/
_Bool delete_friend(user_t *user, char *friend_name)
{
   // Check if the user's friend list is empty
   if (user->friends == NULL) {
      return 0; 
   }

    // Check if the first friend in the list is the one to be deleted
   if (stricmp(user->friends->username, friend_name) == 0) {
      friend_t *temp = user->friends;
      user->friends = user->friends->next;
      free(temp->username); // Free the memory for the username
      return 1; 
   }

   friend_t *temp = user;
   friend_t *keep = malloc(sizeof(friend_t));

   while(temp != NULL && strcmp(temp->username, friend_name) != 0){
      keep = temp;
      temp = temp->next;
   }
   keep->next = temp->next;
   free(temp->username);
   return 1;
}

/*
   Function that creates a new user's post.
   Return the newly created post.
*/
post_t *create_post(const char *text)
{
   
}

/*
   Function that adds a post to a user's timeline. New posts should be added following
   the stack convention (LIFO) (i.e., to the beginning of the Posts linked list).
*/
void add_post(user_t *user, const char *text)
{
   
}

/*
   Function that removes a post from a user's list of posts.
   Return true if the post was deleted and false otherwise.
*/
_Bool delete_post(user_t *user, int number)
{
   
}

/*
   Function that  displays a specific user's posts

-----------------------------------------------
Dumbledore's posts
1- Dumbledore: He's a genius! Best wizard in the
world! But he is a bit mad, yes. Potatoes, Harry?
2- Dumbledore: What happened down in the dungeons
between you and Professor Quirrell is a complete
secret... so, naturally the whole school knows
------------------------------------------------
*/
void display_user_posts(user_t *user)
{
   printf("\n----------------------------------\n");
   printf("          %s's posts\n",user->username );

   post_t *temp = user->posts;
   int count = 1;

   if(user->posts == NULL){
      printf("No posts available for %s.\n", user->username);
      
   } else{
      while (temp != NULL){
         printf("%d - %s: %s\n",count, user->username, temp->content);
         temp = temp->next;
         count++;
      }
   }
   printf("----------------------------------\n\n");

   printf("1. Add a new user post\n");
   printf("2. Remove a users post\n");
   printf("3. Return to main menu\n\n");
}

/*
   Function that displays a specific user's friends

List of Dumbledore's friends:
1- FawkexPhoenix
2- HarryPotter
3- Mcgonagall
*/
void display_user_friends(user_t *user)
{
   friend_t *temp = user->friends;
   int count = 1;

   printf("\nList of %s's friends:\n",user->username);

   if(user->friends == NULL){
      printf("No friends available for Dumbledore.\n");

   } else { 
      while (temp != NULL){
         printf("%d - %s\n",count, temp->username);
         temp = temp->next;
         count++;
      }
   }
   
}
/*
   Function that displays all the posts of 2 users at a time from the database.
   After displaying 2 users' posts, it prompts if you want to display
   posts of the next 2 users.
   If there are no more post or the user types “n” or “N”, the function returns.
1- ArthurHermione: Ron Weasley: Accidentally turned my
pet rat into a cup. Oops! #MagicalMishaps
#TransfigurationTroubles
2- ArthurHermione: Fred and George Weasley - Opening a
new joke shop in Diagon Alley! Weasley's Wizard
Wheezes - pranks for all occasions! #MischiefManaged
3- ArthurHermione: Pansy Parkinson: Started a fashion
line inspired by Death Eater masks. It's all the rage
in Slytherin. #DarkMarkCouture
1- BartyPetunia: Rita Skeeter - Latest scoop: Harry
Potter seen in Hogsmeade with a mysterious creature.
Exclusive details in the Daily Prophet! #GossipQueen
*/
void display_all_posts(user_t *users)
{
     if(users->posts == NULL){
      printf("No posts available for %s.\n", users->username);
      
   } else { 
      for (int i = 0; i < 2; i++){ 

         post_t *temp = users->posts;
         int count = 1;
         while (temp != NULL){
            printf("%d - %s: %s\n",count, users->username, temp->content);
            temp = temp->next;
            count++;
         }
         users = users->next;
      }
   }

}

/*
   Fucntion that free all users from the database before quitting the application.
*/
void teardown(user_t *users)
{
   printf("***********************************************\nThank you for using Text-Based Facebook\nGoodBye!\n***********************************************\n");
   
}

/*
   Function that prints the main menu with a list of options for the user to choose from
*/
void print_menu()
{
printf("\n***********************************************\n");
printf("                MAIN MENU:\n");
printf("***********************************************\n\n");
printf("1. Register a new User\n");
printf("2. Manage a user's profile (change password)\n");
printf("3. Manage a user's posts (display/add/remove)\n");
printf("4. Manage a user's friends (display/add/remove)\n");
printf("5. Display All Posts\n");
printf("6. Exit\n\n");

printf("Enter your choice: ");
}



/*
   ******** DONT MODIFY THIS FUNCTION ********
   Function that reads users from the text file.
   IMPORTANT: This function shouldn't be modified and used as is
   ******** DONT MODIFY THIS FUNCTION ********
*/
user_t *read_CSV_and_create_users(FILE *file, int num_users)
{
    user_t *users = NULL;
    char buffer[500];
    fgets(buffer, sizeof(buffer), file); // Read and discard the header line
    int count = 0;
    for (int i = 0; i < num_users; i++)
    {
        fgets(buffer, sizeof(buffer), file);
        buffer[strcspn(buffer, "\r\n")] = 0; // Remove newline characters

        char *token = strtok(buffer, ",");
        char *token2 = strtok(NULL, ",");
        users = add_user(users, token, token2);
        char *username = token;

        token = strtok(NULL, ",");

        user_t *current_user = users;
        for (; current_user != NULL && stricmp(current_user->username, username) != 0; current_user = current_user->next)
            ;

        while (token != NULL && stricmp(token, ",") != 0 && count < 3)
        {
            if (stricmp(token, " ") != 0)
            {
                add_friend(current_user, token);
            }
            token = strtok(NULL, ",");
            count++;
        }
        count = 0;

        // token = strtok(NULL, ",");
        while (token != NULL && stricmp(token, ",") != 0)
        {
            add_post(current_user, token);
            token = strtok(NULL, ",");
        }
    }
    return users;
}
