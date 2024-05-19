#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define ROWS 9
#define COLS 9

// 生成已預訂的座位
void generate_seats(char seats[ROWS][COLS]) {
    int reserved = 0;
    while (reserved < 10) {
        int row = rand() % ROWS;
        int col = rand() % COLS;
        if (seats[row][col] == '-') {
            seats[row][col] = '*';
            reserved++;
        }
    }
}

// 顯示座位表
void display_seats(char seats[ROWS][COLS]) {
    printf("  123456789\n");
    for (int i = ROWS; i > 0; i--) {
        printf("%d ", i);
        for (int j = 0; j < COLS; j++) {
            printf("%c", seats[i - 1][j]);
        }
        printf("\n");
    }
}

// 清除螢幕
void clear_screen() {
    system("cls");
}

// 安排座位
int arrange_seats(char seats[ROWS][COLS], int num_seats) {
    int found=0;
    if (num_seats>= 1 && num_seats <= 3) {
        for (int i=0;i<ROWS;i++) {
            for (int j=0;j<=COLS-num_seats;j++) {
                int space=1;
                for (int k=0;k<num_seats;k++) {
                    if (seats[i][j+k] != '-') {
                        space=0;
                        break;
                    }
                }
                if (space) {
                    for (int k = 0; k < num_seats; k++) {
                        seats[i][j + k] = '@';
                    }
                    found = 1;
                    break;
                }
            }
            if (found) break;
        }
    } else if (num_seats == 4) {
        // 優先找同列的連續四個座位
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j <= COLS - 4; j++) {
                if (seats[i][j] == '-' && seats[i][j + 1] == '-' && seats[i][j + 2] == '-' && seats[i][j + 3] == '-') {
                    seats[i][j] = seats[i][j + 1] = seats[i][j + 2] = seats[i][j + 3] = '@';
                    found = 1;
                    break;
                }
            }
            if (found) break;
        } 
    }
    return found;
}

int main(void) {
    // 個人風格
    puts("-----------------------------------------------------------------");
    puts("|      EEEEEEEEEEEEEEEE          111         BBBBBBBBBBBBB       |");
    puts("|      EE                       1111         BB           B      |");
    puts("|      EE                      11111         BB            B     |");
    puts("|      EE                     111111         BB             B    |");
    puts("|      EE                        111         BB              B   |");
    puts("|      EE                        111         BB               B  |");
    puts("|      EE                        111         BB              B   |");
    puts("|      EE                        111         BB             B    |");
    puts("|      EE                        111         BB            B     |");
    puts("|      EEEEEEEEEEEEEEEE          111         BBBBBBBBBBBBBB      |");
    puts("|      EE                        111         BB            B     |");
    puts("|      EE                        111         BB             B    |");
    puts("|      EE                        111         BB              B   |");
    puts("|      EE                        111         BB               B  |");
    puts("|      EE                        111         BB                B |");
    puts("|      EE                        111         BB               B  |");
    puts("|      EE                        111         BB              B   |");
    puts("|      EE                        111         BB             B    |");
    puts("|      EEEEEEEEEEEEEEEE      11111111111     BBBBBBBBBBBBBBB     |");
    puts("|                                                                |");
    puts("|            444                111                              |");
    puts("|           4444               1111                              |");
    puts("|          44 44              11111                              |");
    puts("|         44  44             111111                              |");
    puts("|        44   44                111                              |");
    puts("|       44    44                111                              |");
    puts("|      44444444444444           111                              |");
    puts("|             44                111                              |");
    puts("|             44                111                              |");
    puts("|             44                111                              |");
    puts("|             44                111                              |");
    puts("|             44                111                              |");
    puts("|             44                111                              |");
    puts("|             44                111                              |");
    puts("|             44                111                              |");
    puts("|          44444444          111111111                           |");
    puts("------------------------------------------------------------------");
    system("pause");
    clear_screen();

    // 輸入密碼
    int password, i;
    for (i=3;i>0;i--) { // 使用者輸入密碼，最多三次
        printf("請輸入密碼: ");  // 輸入密碼
        scanf("%d",&password);

        if (password == 2024) {
            printf("密碼正確。\n");
            system("pause");
            clear_screen();

            // 初始化座位表
            char seats[ROWS][COLS];
            for (int i=0;i<ROWS;i++) {
                for (int j=0;j<COLS;j++) {
                    seats[i][j]='-';
                }
            }

            // 設置隨機數，且生成座位表
            srand(time(0));
            generate_seats(seats);

            char option;
            while (1) {
                puts("!!!歡迎!!!");
                puts("--------------------------");
                puts("|  a. Available seats    |");
                puts("|  b. Arrange for you    |");
                puts("|  c. Choose by yourself |");
                puts("|  d. Exit               |");
                puts("--------------------------");

                printf("請輸入一個選項: ");
                option = getch();   // 讀取用戶選擇的選項
                clear_screen();

                if (option == 'a') {
                    display_seats(seats);
                    printf("按任意鍵返回主選單...\n");
                    getch();
                    system("cls");
                } else if (option=='b') {
                    int num_seats;
                    printf("請輸入需要的座位數量（1~4）: ");
                    scanf("%d", &num_seats);
                    if (num_seats < 1 || num_seats > 4) {
                        printf("無效的座位數量。\n");
                        system("pause");
                        clear_screen();
                        continue;
                    }

                    if (arrange_seats(seats, num_seats)) {
                        display_seats(seats);
                        printf("是否滿意座位安排？(y/n): ");
                        char confirm = getch();
                        if (confirm == 'y' || confirm == 'Y') {
                            for (int i=0;i<ROWS;i++){
                                for (int j=0;j<COLS;j++) {
                                    if (seats[i][j]=='@') {
                                        seats[i][j]='*';
                                    }
                                }
                            }
                            printf("\n座位已確認。\n");
                            system("pause");
                            return 0;
                        } else {
                            // 清除建議座位標記
                            for (int i=0;i<ROWS;i++) {
                                for (int j=0;j<COLS;j++) {
                                    if (seats[i][j]=='@') {
                                        seats[i][j]='-';
                                    }
                                }
                            }
                            system("cls");
                        }
                   
                        
                    } else {
                        printf("無法安排連續座位。\n");
                        system("pause");
                        return 0;
                    }
                } 
                else if (option=='c') {
                printf("請逐一輸入座位選擇，如1-2、2-9（按Enter鍵確認選擇）：\n");
                int chosen_seats[4][2]; // 用於儲存使用者的選擇
                int num_chosen_seats = 0; // 使用者已選擇的座位數量

                while (num_chosen_seats < 4) {
                char input[5]; // 用於接收使用者的輸入
                scanf("%4s",&input);

                // 檢查輸入是否有效
                int row, col;
                if (sscanf(input, "%d-%d", &row, &col) != 2) {
                    printf("輸入格式錯誤，請重新輸入：");
                    while (getchar() != '\n'); // 清除輸入緩衝區
                    continue;
                }

                // 檢查座位是否已被選擇或座位號超出範圍
                if (row < 1 ||row>ROWS ||col<1 ||col>COLS||seats[row-1][col-1] != '-') {
                    printf("無效的座位選擇，請重新輸入：");
                    continue;
                }

                // 儲存使用者的選擇
                chosen_seats[num_chosen_seats][0]=row-1; // 修正索引從0開始
                chosen_seats[num_chosen_seats][1]=col-1;
                num_chosen_seats++;

                // 標記座位為使用者選擇的座位
                seats[row - 1][col - 1] = '@';

                // 檢查是否還有剩餘座位可選擇
                if (num_chosen_seats < 4) {
                    printf("已選擇座位 %d-%d，請繼續選擇：", row, col);
                } else {
                    printf("座位選擇完成。\n");
                    break;
                }
            }

            // 顯示座位表
            display_seats(seats);
            system("pause");
            return 0;
        }
            
			else if(option=='d'){
                    printf("Continue? (y/n): ");
                    char exit_option=getch();
                    if (exit_option=='y') {
                        system("cls");
                        continue;
                    } else if (exit_option=='n') {
                        printf("程式結束。\n");
                        break;
                    } else {
                        printf("無效的選擇。\n");
                        system("pause");
                        system("cls");
                    }
                } else {
                    printf("無效的選項。\n");
                    system("pause");
                   system("cls"); 
            }
        }
			break;
		
        } else {
            printf("剩餘%d次機會\n", i - 1);
            if (i-1==0) {  // 輸入最後一次且錯誤時，發出警告音
                printf("%c", '\a');
                printf("連續三次輸入錯誤，程式結束。\n");
                return 0;
            }
        }
    }
    return 0;
}
/*心得:這次的作業對我來說挑戰非常大，不僅要掌握以前所學的語法。
還要靈活運用函數、循環、條件語句來完成特定的功能。在執行的時候，遇到了不少問題。
例如，設計座位自動安排邏輯時，需要確保連續座位的正確性，特別是當用戶選擇四個座位的時候，算法的實現變得非常困難。
此外，用戶手動選位時，檢查輸入格式跟避免重複選擇也花費大量的時間。
這次的作業真的有點超出我的能力範圍了，但在同學的幫助下還是勉強完成了這次的作業，通過不斷的測試和測試，我學到很多實用的編輯技巧，也體會到了面對複雜問題的時候，需要極高的耐心跟細緻的重要性。*/ 
