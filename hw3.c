#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define ROWS 9
#define COLS 9

// �ͦ��w�w�q���y��
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

// ��ܮy���
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

// �M���ù�
void clear_screen() {
    system("cls");
}

// �w�Ʈy��
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
        // �u����P�C���s��|�Ӯy��
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
    // �ӤH����
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

    // ��J�K�X
    int password, i;
    for (i=3;i>0;i--) { // �ϥΪ̿�J�K�X�A�̦h�T��
        printf("�п�J�K�X: ");  // ��J�K�X
        scanf("%d",&password);

        if (password == 2024) {
            printf("�K�X���T�C\n");
            system("pause");
            clear_screen();

            // ��l�Ʈy���
            char seats[ROWS][COLS];
            for (int i=0;i<ROWS;i++) {
                for (int j=0;j<COLS;j++) {
                    seats[i][j]='-';
                }
            }

            // �]�m�H���ơA�B�ͦ��y���
            srand(time(0));
            generate_seats(seats);

            char option;
            while (1) {
                puts("!!!�w��!!!");
                puts("--------------------------");
                puts("|  a. Available seats    |");
                puts("|  b. Arrange for you    |");
                puts("|  c. Choose by yourself |");
                puts("|  d. Exit               |");
                puts("--------------------------");

                printf("�п�J�@�ӿﶵ: ");
                option = getch();   // Ū���Τ��ܪ��ﶵ
                clear_screen();

                if (option == 'a') {
                    display_seats(seats);
                    printf("�����N���^�D���...\n");
                    getch();
                    system("cls");
                } else if (option=='b') {
                    int num_seats;
                    printf("�п�J�ݭn���y��ƶq�]1~4�^: ");
                    scanf("%d", &num_seats);
                    if (num_seats < 1 || num_seats > 4) {
                        printf("�L�Ī��y��ƶq�C\n");
                        system("pause");
                        clear_screen();
                        continue;
                    }

                    if (arrange_seats(seats, num_seats)) {
                        display_seats(seats);
                        printf("�O�_���N�y��w�ơH(y/n): ");
                        char confirm = getch();
                        if (confirm == 'y' || confirm == 'Y') {
                            for (int i=0;i<ROWS;i++){
                                for (int j=0;j<COLS;j++) {
                                    if (seats[i][j]=='@') {
                                        seats[i][j]='*';
                                    }
                                }
                            }
                            printf("\n�y��w�T�{�C\n");
                            system("pause");
                            return 0;
                        } else {
                            // �M����ĳ�y��аO
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
                        printf("�L�k�w�Ƴs��y��C\n");
                        system("pause");
                        return 0;
                    }
                } 
                else if (option=='c') {
                printf("�гv�@��J�y���ܡA�p1-2�B2-9�]��Enter��T�{��ܡ^�G\n");
                int chosen_seats[4][2]; // �Ω��x�s�ϥΪ̪����
                int num_chosen_seats = 0; // �ϥΪ̤w��ܪ��y��ƶq

                while (num_chosen_seats < 4) {
                char input[5]; // �Ω󱵦��ϥΪ̪���J
                scanf("%4s",&input);

                // �ˬd��J�O�_����
                int row, col;
                if (sscanf(input, "%d-%d", &row, &col) != 2) {
                    printf("��J�榡���~�A�Э��s��J�G");
                    while (getchar() != '\n'); // �M����J�w�İ�
                    continue;
                }

                // �ˬd�y��O�_�w�Q��ܩήy�츹�W�X�d��
                if (row < 1 ||row>ROWS ||col<1 ||col>COLS||seats[row-1][col-1] != '-') {
                    printf("�L�Ī��y���ܡA�Э��s��J�G");
                    continue;
                }

                // �x�s�ϥΪ̪����
                chosen_seats[num_chosen_seats][0]=row-1; // �ץ����ޱq0�}�l
                chosen_seats[num_chosen_seats][1]=col-1;
                num_chosen_seats++;

                // �аO�y�쬰�ϥΪ̿�ܪ��y��
                seats[row - 1][col - 1] = '@';

                // �ˬd�O�_�٦��Ѿl�y��i���
                if (num_chosen_seats < 4) {
                    printf("�w��ܮy�� %d-%d�A���~���ܡG", row, col);
                } else {
                    printf("�y���ܧ����C\n");
                    break;
                }
            }

            // ��ܮy���
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
                        printf("�{�������C\n");
                        break;
                    } else {
                        printf("�L�Ī���ܡC\n");
                        system("pause");
                        system("cls");
                    }
                } else {
                    printf("�L�Ī��ﶵ�C\n");
                    system("pause");
                   system("cls"); 
            }
        }
			break;
		
        } else {
            printf("�Ѿl%d�����|\n", i - 1);
            if (i-1==0) {  // ��J�̫�@���B���~�ɡA�o�Xĵ�i��
                printf("%c", '\a');
                printf("�s��T����J���~�A�{�������C\n");
                return 0;
            }
        }
    }
    return 0;
}
/*�߱o:�o�����@�~��ڨӻ��D�ԫD�`�j�A���ȭn�x���H�e�ҾǪ��y�k�C
�٭n�F���B�Ψ�ơB�`���B����y�y�ӧ����S�w���\��C�b���檺�ɭԡA�J��F���ְ��D�C
�Ҧp�A�]�p�y��۰ʦw���޿�ɡA�ݭn�T�O�s��y�쪺���T�ʡA�S�O�O��Τ��ܥ|�Ӯy�쪺�ɭԡA��k����{�ܱo�D�`�x���C
���~�A�Τ��ʿ��ɡA�ˬd��J�榡���קK���ƿ�ܤ]��O�j�q���ɶ��C
�o�����@�~�u�����I�W�X�ڪ���O�d��F�A���b�P�Ǫ����U�U�٬O�j�j�����F�o�����@�~�A�q�L���_�����թM���աA�ھǨ�ܦh��Ϊ��s��ޥ��A�]��|��F����������D���ɭԡA�ݭn�������@�߸�ӽo�����n�ʡC*/ 
