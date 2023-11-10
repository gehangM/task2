#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    char username[30];
    char password[30];
    union {
        int intValue;
        bool boolValue;
    } flag;
} User;

#define MAX_USERS 100

User users[MAX_USERS];
int userCount = 0;
char flagInput[30];
void registerUser() {
    if (userCount == MAX_USERS) {
        printf("Maximum user limit exceeded. Cannot register more users.\n");
        return;
    }

    User newUser;
    printf("Enter username: ");
    scanf("%s", newUser.username);

    printf("Enter password: ");
    scanf("%s", newUser.password);

    printf("Enter flag (0 or 1 for integer, 'true' , 'yes' or 'false' , 'no' for boolean): ");
    scanf("%s", flagInput);

    if (strcmp(flagInput, "0") == 0 || strcmp(flagInput, "1") == 0) {
        newUser.flag.intValue = atoi(flagInput);
    }
    else if (strcmp(flagInput, "true") == 0 || strcmp(flagInput, "yes") == 0) {
        newUser.flag.boolValue = true;
    }
    else if (strcmp(flagInput, "false") == 0 || strcmp(flagInput, "no") == 0) {
        newUser.flag.boolValue = false;
    }
    else {
        printf("Invalid flag input. Defaulting to 0 (integer).\n");
        newUser.flag.intValue = 0;
    }

    users[userCount++] = newUser;
    printf("User registered successfully!\n");
}

void loginUser() {
    // Check flag first
    bool active = false;

    if (strcmp(flagInput, "1") == 0 || strcmp(flagInput, "true") == 0 || strcmp(flagInput, "yes") == 0) {
        active = true;
    }
    else if (strcmp(flagInput, "0") != 0 && strcmp(flagInput, "false") != 0 && strcmp(flagInput, "no") != 0) {
        printf("Invalid flag input. Login failed.\n");
        return;
    }

    if (!active) {
        printf("You are not active. Login failed.\n");
        return;
    }

    // Get username and password for login
    char username[30], password[30];
    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            printf("User logged in successfully!\n");
            return;
        }
    }

    printf("Invalid username or password. Please try again.\n");
}

int main() {
    int option;

    while (1) {
        printf("Press '1' to Register \nPress '2' to Login \nPress '3' to Exit\n\n");
        scanf("%d", &option);

        if (option == 1) {
            registerUser();
        } else if (option == 2) {
            loginUser();
        } else if (option == 3) {
            printf("Program terminated.\n");
            break;
        } else {
            printf("Invalid option. Please try again.\n");
        }

        printf("\n");
    }

    return 0;
}
