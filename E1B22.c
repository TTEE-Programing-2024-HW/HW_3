#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// 定義座位行數和列數
#define ROWS 9
#define COLS 9
#define MAX_TRIES 3
#define PASSWORD "2024"

// 清除螢幕的函式，使用平台無關的方式
void clearScreen() {
    printf("\033[H\033[J");
}

// 顯示歡迎畫面
void printWelcomeScreen() {
    printf("**************************\n");
    printf("*    Welcome to Booking   *\n");
    printf("*       System 2024       *\n");
    printf("**************************\n");
}

// 驗證密碼函式
int verifyPassword() {
    char input[5]; // 用來存放輸入的密碼
    int attempts = 0; // 嘗試次數計數

    while (attempts < MAX_TRIES) {
        printf("Enter the 4-digit password: ");
        scanf("%4s", input); // 讀取4位數密碼
        if (strcmp(input, PASSWORD) == 0) {
            printf("Password correct. Welcome!\n");
            return 1; // 密碼正確，返回1
        } else {
            printf("Incorrect password. Try again.\n");
            attempts++; // 嘗試次數加1
        }
    }
    printf("Too many incorrect attempts. Exiting program.\n");
    return 0; // 超過最大嘗試次數，返回0
}

// 顯示主選單
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
    printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n");//個人風格主選單 
}

// 初始化座位表，並隨機生成10個已被預訂的座位
void generateInitialSeats(char seats[ROWS][COLS]) {
    int i, j, k;
    // 初始化所有座位為'-'
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            seats[i][j] = '-';
        }
    }

    // 隨機預訂10個座位
    srand(time(0));
    for (k = 0; k < 10; k++) {
        int row = rand() % ROWS;
        int col = rand() % COLS;
        if (seats[row][col] == '-') {
            seats[row][col] = '*'; // 標記為已預訂
        } else {
            k--; // 如果座位已被預訂，重試
        }
    }
}

// 顯示座位表
void printSeats(char seats[ROWS][COLS]) {
    clearScreen();
    printf("  123456789\n"); // 顯示列編號
    int i, j;
    for (i = 0; i < ROWS; i++) {
        printf("%d ", 9 - i); // 顯示行編號
        for (j = 0; j < COLS; j++) {
            printf("%c", seats[i][j]); // 顯示座位狀態
        }
        printf("\n");
    }
}

// 處理顯示可用座位的選項
void handleViewAvailableSeats(char seats[ROWS][COLS]) {
    printSeats(seats);
    printf("Press any key to return to main menu...");
    getchar();
    getchar(); // 等待按鍵，然後返回主選單
    clearScreen();
}

// 處理系統自動安排座位的選項
void handleArrangeSeats(char seats[ROWS][COLS]) {
    int numSeats;
    printf("How many seats do you need (1-4)? ");
    scanf("%d", &numSeats);

    // 根據需要的座位數進行隨機安排
    srand(time(0));
    int found = 0;
    if (numSeats <= 3) {
        // 隨機選擇連續座位
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
                        seats[i][j + k] = '@'; // 標記為建議座位
                    }
                    found = 1;
                }
            }
        }
    } else if (numSeats == 4) {
        // 隨機選擇連續4個座位或相鄰兩列各兩個座位
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
            // 將建議座位標記為已預訂
            int i, j;
            for (i = 0; i < ROWS; i++) {
                for (j = 0; j < COLS; j++) {
                    if (seats[i][j] == '@') {
                        seats[i][j] = '*';
                    }
                }
            }
        } else {
            // 取消建議座位的標記
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

// 處理使用者自行選擇座位的選項
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
            row = 9 - row; // 調整行索引
            col = col - 1; // 調整列索引
            if (seats[row][col] == '-') {
                seats[row][col] = '@'; // 標記為使用者選擇座位
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
                seats[i][j] = '*'; // 將選擇座位標記為已預訂
            }
        }
    }
    clearScreen();
}

// 處理退出程式的選項
void handleExit() {
    char response;
    printf("Continue? (y/n): ");
    getchar(); // 清除緩衝區
    scanf("%c", &response);
    if (response == 'y' || response == 'Y') {
        clearScreen(); // 繼續，清除螢幕
    } else if (response == 'n' || response == 'N') {
        exit(0); // 結束程式
    } else {
        printf("Invalid input. Try again.\n");
    }
}

// 主函式
int main() {
    char seats[ROWS][COLS]; // 座位表陣列
    generateInitialSeats(seats); // 初始化座位表

    printWelcomeScreen(); // 顯示歡迎畫面
    if (!verifyPassword()) {
        return 0; // 驗證密碼失敗，結束程式
    }

    char choice;
    while (1) {
        printMainMenu(); // 顯示主選單
        printf("Enter your choice: ");
        getchar(); // 清除緩衝區
        scanf("%c", &choice);

        switch (choice) {
            case 'a':
                handleViewAvailableSeats(seats); // 顯示可用座位
                break;
            case 'b':
                handleArrangeSeats(seats); // 系統自動安排座位
                break;
            case 'c':
                handleChooseSeats(seats); // 使用者自行選擇座位
                break;
            case 'd':
                handleExit(); // 處理退出程式
                break;
            default:
                printf("Invalid choice. Try again.\n");
                break;
        }
    }

    return 0;
}

//心得：本次的作業和上次的比起來多了更多的複雜性，雖然上一次我因為無法及時設定好GIT而無法繳交成功，這一次我找了同學來幫忙後速度快了很多，希望作後一次的作業也能順利完成。 
