#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// �w�q�y���ƩM�C��
#define ROWS 9
#define COLS 9
#define MAX_TRIES 3
#define PASSWORD "2024"

// �M���ù����禡�A�ϥΥ��x�L�����覡
void clearScreen() {
    printf("\033[H\033[J");
}

// ����w��e��
void printWelcomeScreen() {
    printf("**************************\n");
    printf("*    Welcome to Booking   *\n");
    printf("*       System 2024       *\n");
    printf("**************************\n");
}

// ���ұK�X�禡
int verifyPassword() {
    char input[5]; // �ΨӦs���J���K�X
    int attempts = 0; // ���զ��ƭp��

    while (attempts < MAX_TRIES) {
        printf("Enter the 4-digit password: ");
        scanf("%4s", input); // Ū��4��ƱK�X
        if (strcmp(input, PASSWORD) == 0) {
            printf("Password correct. Welcome!\n");
            return 1; // �K�X���T�A��^1
        } else {
            printf("Incorrect password. Try again.\n");
            attempts++; // ���զ��ƥ[1
        }
    }
    printf("Too many incorrect attempts. Exiting program.\n");
    return 0; // �W�L�̤j���զ��ơA��^0
}

// ��ܥD���
void printMainMenu() {
    printf("+-+-+-+-+-+-+-BookingSystem-+-+-+-+-+-+-+\n");
    printf("|                                       |\n");
    printf("|                                       |\n");
    printf("|                                       |\n");
    printf("|                                       |\n");
    printf("|                                       |\n");
    printf("|        a. Available seats             |\n");
    printf("|                                       |\n");
    printf("|                                       |\n");
    printf("|        b. Arrange for you             |\n");
    printf("|                                       |\n");
    printf("|                                       |\n");
    printf("|        c. Choose by yourself          |\n");
    printf("|                                       |\n");
    printf("|                                       |\n");
    printf("|        d. Exit                        |\n");
    printf("|                                       |\n");
    printf("|                                       |\n");
    printf("|                                       |\n");
    printf("|                 E1B22                 |\n");
    printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n");//�ӤH����D��� 
}

// ��l�Ʈy���A���H���ͦ�10�Ӥw�Q�w�q���y��
void generateInitialSeats(char seats[ROWS][COLS]) {
    int i, j, k;
    // ��l�ƩҦ��y�쬰'-'
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            seats[i][j] = '-';
        }
    }

    // �H���w�q10�Ӯy��
    srand(time(0));
    for (k = 0; k < 10; k++) {
        int row = rand() % ROWS;
        int col = rand() % COLS;
        if (seats[row][col] == '-') {
            seats[row][col] = '*'; // �аO���w�w�q
        } else {
            k--; // �p�G�y��w�Q�w�q�A����
        }
    }
}

// ��ܮy���
void printSeats(char seats[ROWS][COLS]) {
    clearScreen();
    printf("  123456789\n"); // ��ܦC�s��
    int i, j;
    for (i = 0; i < ROWS; i++) {
        printf("%d ", 9 - i); // ��ܦ�s��
        for (j = 0; j < COLS; j++) {
            printf("%c", seats[i][j]); // ��ܮy�쪬�A
        }
        printf("\n");
    }
}

// �B�z��ܥi�ήy�쪺�ﶵ
void handleViewAvailableSeats(char seats[ROWS][COLS]) {
    printSeats(seats);
    printf("Press any key to return to main menu...");
    getchar();
    getchar(); // ���ݫ���A�M���^�D���
    clearScreen();
}

// �B�z�t�Φ۰ʦw�Ʈy�쪺�ﶵ
void handleArrangeSeats(char seats[ROWS][COLS]) {
    int numSeats;
    printf("How many seats do you need (1-4)? ");
    scanf("%d", &numSeats);

    // �ھڻݭn���y��ƶi���H���w��
    srand(time(0));
    int found = 0;
    if (numSeats <= 3) {
        // �H����ܳs��y��
        int i, j, k;
        for (i = 0; i < ROWS && !found; i++) {
            for (j = 0; j <= COLS - numSeats && !found; j++) {
                int canPlace = 1;
                for (k = 0; k < numSeats; k++) {
                    if (seats[i][j + k] != '-') {
                        canPlace = 0;
                        break;
                    }
                }
                if (canPlace) {
                    for (k = 0; k < numSeats; k++) {
                        seats[i][j + k] = '@'; // �аO����ĳ�y��
                    }
                    found = 1;
                }
            }
        }
    } else if (numSeats == 4) {
        // �H����ܳs��4�Ӯy��ά۾F��C�U��Ӯy��
        int i, j;
        for (i = 0; i < ROWS - 1 && !found; i++) {
            for (j = 0; j < COLS && !found; j++) {
                if (seats[i][j] == '-' && seats[i][j + 1] == '-' && seats[i + 1][j] == '-' && seats[i + 1][j + 1] == '-') {
                    seats[i][j] = seats[i][j + 1] = seats[i + 1][j] = seats[i + 1][j + 1] = '@';
                    found = 1;
                }
            }
        }
    }

    if (!found) {
        printf("No suitable arrangement found. Returning to main menu.\n");
    } else {
        printSeats(seats);
        char response;
        printf("Are you satisfied with the arrangement? (y/n): ");
        getchar();
        scanf("%c", &response);
        if (response == 'y' || response == 'Y') {
            // �N��ĳ�y��аO���w�w�q
            int i, j;
            for (i = 0; i < ROWS; i++) {
                for (j = 0; j < COLS; j++) {
                    if (seats[i][j] == '@') {
                        seats[i][j] = '*';
                    }
                }
            }
        } else {
            // ������ĳ�y�쪺�аO
            int i, j;
            for (i = 0; i < ROWS; i++) {
                for (j = 0; j < COLS; j++) {
                    if (seats[i][j] == '@') {
                        seats[i][j] = '-';
                    }
                }
            }
        }
    }
    clearScreen();
}

// �B�z�ϥΪ̦ۦ��ܮy�쪺�ﶵ
void handleChooseSeats(char seats[ROWS][COLS]) {
    int row, col;
    char choice[4];
    while (1) {
        printf("Enter seat (row-col) or 'q' to quit: ");
        scanf("%s", choice);
        if (choice[0] == 'q') {
            break;
        }
        if (sscanf(choice, "%d-%d", &row, &col) == 2 && row >= 1 && row <= 9 && col >= 1 && col <= 9) {
            row = 9 - row; // �վ�����
            col = col - 1; // �վ�C����
            if (seats[row][col] == '-') {
                seats[row][col] = '@'; // �аO���ϥΪ̿�ܮy��
            } else {
                printf("Seat already taken or invalid input. Try again.\n");
            }
        } else {
            printf("Invalid format. Try again.\n");
        }
    }
    printSeats(seats);
    printf("Press any key to confirm and return to main menu...");
    getchar();
    getchar();
    int i, j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (seats[i][j] == '@') {
                seats[i][j] = '*'; // �N��ܮy��аO���w�w�q
            }
        }
    }
    clearScreen();
}

// �B�z�h�X�{�����ﶵ
void handleExit() {
    char response;
    printf("Continue? (y/n): ");
    getchar(); // �M���w�İ�
    scanf("%c", &response);
    if (response == 'y' || response == 'Y') {
        clearScreen(); // �~��A�M���ù�
    } else if (response == 'n' || response == 'N') {
        exit(0); // �����{��
    } else {
        printf("Invalid input. Try again.\n");
    }
}

// �D�禡
int main() {
    char seats[ROWS][COLS]; // �y���}�C
    generateInitialSeats(seats); // ��l�Ʈy���

    printWelcomeScreen(); // ����w��e��
    if (!verifyPassword()) {
        return 0; // ���ұK�X���ѡA�����{��
    }

    char choice;
    while (1) {
        printMainMenu(); // ��ܥD���
        printf("Enter your choice: ");
        getchar(); // �M���w�İ�
        scanf("%c", &choice);

        switch (choice) {
            case 'a':
                handleViewAvailableSeats(seats); // ��ܥi�ήy��
                break;
            case 'b':
                handleArrangeSeats(seats); // �t�Φ۰ʦw�Ʈy��
                break;
            case 'c':
                handleChooseSeats(seats); // �ϥΪ̦ۦ��ܮy��
                break;
            case 'd':
                handleExit(); // �B�z�h�X�{��
                break;
            default:
                printf("Invalid choice. Try again.\n");
                break;
        }
    }

    return 0;
}

//�߱o�G�������@�~�M�W������_�Ӧh�F��h�������ʡA���M�W�@���ڦ]���L�k�ήɳ]�w�nGIT�ӵL�kú�榨�\�A�o�@���ڧ�F�P�Ǩ�������t�ק֤F�ܦh�A�Ʊ�@��@�����@�~�]�බ�Q�����C 
