#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define PASSWORD "2024"
#define MAX_TRIES 3
#define SEAT_ROWS 9
#define SEAT_COLS 9

char seats[SEAT_ROWS][SEAT_COLS];

// ��l�Ʈy���A���H���ͦ��Q�Ӥw�w�q���y��
void initializeSeats() {
    memset(seats, '-', sizeof(seats));
    srand(time(NULL));
    int i;
    for (i = 0; i < 10; ++i) {
        int r, c;
        do {
            r = rand() % SEAT_ROWS;
            c = rand() % SEAT_COLS;
        } while (seats[r][c] == '*');
        seats[r][c] = '*';
    }
}

// ��ܮy���
void displaySeats() {
    printf("\\123456789\n");
    int i,j;
    for (i = 0; i < SEAT_ROWS; ++i) {
        printf("%d", SEAT_ROWS - i);
        for (j = 0; j < SEAT_COLS; ++j) {
            printf("%c", seats[i][j]);
        }
        printf("\n");
    }
}

// �M���̹�
void clearScreen() {
    system("clear || cls");
}

// �D���
void mainMenu() {
    printf("----------[�w���t��]----------\n");
    printf("->  a. �i��y��               \n");
    printf("->  b. �t�Φw��               \n");
    printf("->  c. �ۦ���               \n");
    printf("->  d. ����                   \n");
    printf("------------------------------\n");
}

// �ˬd�K�X
int checkPassword() {
    char input[10];
    int tries;
    for (tries = 0; tries < MAX_TRIES; ++tries) {
        printf("��J�K�X: ");
        scanf("%s", input);
        if (strcmp(input, PASSWORD) == 0) {
            printf("�w��!\n");
            return 1;
        } else {
            printf("�K�X���~!�٦�%d�����|!\n",MAX_TRIES-tries-1);
        }
    }
    printf("���ƥκ�,���b���}�{��...\n");
    return 0;
}

// �w�Ʈy��
int arrangeSeats(int neededSeats) {
    int found = 0;
    int startRow = -1, startCol = -1;
    int i,j,k;

    if (neededSeats == 1 || neededSeats == 2 || neededSeats == 3) {
        for (i = 0; i < SEAT_ROWS && !found; ++i) {
            for (j = 0; j <= SEAT_COLS - neededSeats; ++j) {
                int available = 1;
                for (k = 0; k < neededSeats; ++k) {
                    if (seats[i][j + k] != '-') {
                        available = 0;
                        break;
                    }
                }
                if (available) {
                    found = 1;
                    startRow = i;
                    startCol = j;
                    break;
                }
            }
        }
    } else if (neededSeats == 4) {
        for (i = 0; i < SEAT_ROWS && !found; ++i) {
            for (j = 0; j <= SEAT_COLS - 4; ++j) {
                int available = 1;
                for (k = 0; k < 4; ++k) {
                    if (seats[i][j + k] != '-') {
                        available = 0;
                        break;
                    }
                }
                if (available) {
                    found = 1;
                    startRow = i;
                    startCol = j;
                    break;
                }
            }
            if (!found && i < SEAT_ROWS - 1) {
                for (j = 0; j < SEAT_COLS; ++j) {
                    if (seats[i][j] == '-' && seats[i + 1][j] == '-') {
                        found = 1;
                        startRow = i;
                        startCol = j;
                        break;
                    }
                }
            }
        }
    }

    if (found) {
        for (i = 0; i < neededSeats; ++i) {
            if (neededSeats == 4 && startCol == -1) {
                seats[startRow][startCol + i] = '@';
                if (i == 1) startRow++;
            } else {
                seats[startRow][startCol + i] = '@';
            }
        }
        displaySeats();
        char response;
        printf("�z�T�w�n�o�Ӯy���? (y/n): ");
        scanf(" %c", &response);
        if (response == 'y' || response == 'Y') {
            for (i = 0; i < SEAT_ROWS; ++i) {
                for (j = 0; j < SEAT_COLS; ++j) {
                    if (seats[i][j] == '@') {
                        seats[i][j] = '*';
                    }
                }
            }
            return 1;
        } else{
        	for (i = 0; i < SEAT_ROWS; ++i) {
                for (j = 0; j < SEAT_COLS; ++j) {
                    if (seats[i][j] == '@') {
                        seats[i][j] = '-';
                        }
                }
            }
            return 0;
        }
    } else{
        printf("��p�A�S���i�w�ƪ��y��C\n");
        return 0;
    }
}

// �ϥΪ̦ۦ��ܮy��
int chooseSeats(int seatCount) {
    int row, col, i, j;
    for (i = 0; i < seatCount; ++i) {
        while (1) {
            printf("��J�Q�n�w�w���y��]��-�C�^ %d: ", i + 1);
            scanf("%d-%d", &row, &col);
            if (row >= 1 && row <= SEAT_ROWS && col >= 1 && col <= SEAT_COLS && seats[SEAT_ROWS - row][col - 1] == '-') {
                seats[SEAT_ROWS - row][col - 1] = '@';
                break;
            } else {
                printf("�S�����y��άO���y��w�Q�w�q,�ЦA��J�@��\n");
            }
        }
    }
    displaySeats();
    char response;
    printf("�p�G��ܧ����Ы����N��H�~��...\n");
    getchar();
    getchar();
    for (i = 0; i < SEAT_ROWS; ++i) {
        for (j = 0; j < SEAT_COLS; ++j) {
            if (seats[i][j] == '@') {
                seats[i][j] = '*';
            }
        }
    }
    return 1;
}

// �D�{��
int main() {
	
	printf("*                  \n");
    printf("**                 \n");
    printf("***                \n");
    printf("****               \n");
    printf("*****              \n");
    printf(" *****             \n");
    printf("  *****            \n");
    printf("   *****           \n");
    printf("    *****          \n");
    printf("     *****         \n");
    printf("      *****        \n");
    printf("       *****       \n");
    printf("        *****      \n");
    printf("         *****     \n");
    printf("          *****    \n");
    printf("           *****   \n");
    printf("            *****  \n");
    printf("             ***** \n");
    printf("              *****\n");
    printf("               ****\n");
    printf("                ***\n");
    printf("                 **\n");
    printf("                  *\n");
    if (!checkPassword()) return 0;

    initializeSeats();
    char choice;
    while (1) {
        clearScreen();
        mainMenu();
        scanf(" %c", &choice);
        clearScreen();

        switch (choice) {
            case 'a':
                displaySeats();
                printf("�����N��H�^��D���...\n");
                getchar();
                getchar();
                break;
            case 'b': {
                int neededSeats;
                printf("�z�ݭn�w�w�X�Ӯy��(1~4)? ");
                scanf("%d", &neededSeats);
                if (neededSeats < 1 || neededSeats > 4) {
                    printf("��J���~,���b��^�D���...\n");
                } else {
                    if (!arrangeSeats(neededSeats)) {
                        printf("���b��^�D���...\n");
                    }
                }
                break;
            }
            case 'c': {
                int seatCount;
                printf("�z�ݭn�w�w�X�Ӯy��(1~4)? ");
                scanf("%d", &seatCount);
                if (seatCount < 1 || seatCount > 4) {
                    printf("��J���~,���b��^�D���...\n");
                } else {
                    chooseSeats(seatCount);
                }
                break;
            }
            case 'd': {
                char response;
                printf("�T�w�n���}? (y/n): ");
                scanf(" %c", &response);
                if (response == 'n' || response == 'N') {
                    return 0;
                } else if (response != 'y' && response != 'Y') {
                    printf("��J���~,���b��^�D���...\n");
                }
                break;
            }
            default:
                printf("��J���~,���b��^�D���...\n");
        }
    }

    return 0;
}


