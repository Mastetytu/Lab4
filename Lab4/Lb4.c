// библиотеки
#include <math.h>
#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

// управляющие консолью библиотеки
#include <windows.h>
#include <conio.h>

// с помощью дефайнов объявляются размеры всех меню
#define MAIN_MENU_SIZE 3
#define SETTINGS_MENU_SIZE 4
#define LANG_MENU_SIZE 2
#define THEMES_MENU_SIZE 3
#define DIFFICULT_MENU_SIZE 3
#define GAMES_MENU_SIZE 2
#define GUESSNUM_GAME_MODE_SIZE 2
#define GUESSNUM_GAME_CHOISE_SIZE 3

// основные ключи клавиш, которые могут пригодиться
#define NOT_KEY 67
#define KEY_EXIT 27
#define KEY_ENTER 13
#define ARROW_KEY 224
#define KEY_SPACE 0
#define KEY_BACKSPACE 8
#define KEY_ARROW_RIGHT 77
#define KEY_ARROW_LEFT 75
#define KEY_ARROW_UP 72
#define KEY_ARROW_DOWN 80

int createMenu(char* menu[], HANDLE console, int size) {

    int choose_pos = 0;
    int iKey = 0;
    COORD cursorPos = (COORD){ 0, 0 };

    while (iKey != KEY_EXIT && iKey != KEY_ENTER) {
        switch (iKey) {
        case KEY_ARROW_UP:
            choose_pos--;
            break;
        case KEY_ARROW_DOWN:
            choose_pos++;
            break;
        default:
            break;
        }

        // зацикливание перелистывания меню
        if (choose_pos < 0) { choose_pos = size - 1; }
        if (choose_pos > size - 1) { choose_pos = 0; }

        // перед перерисовкой меню очистка
        system("cls");

        // перерисовка меню
        for (int i = 0; i < size; i++) {
            cursorPos = (COORD){ 3, i };
            SetConsoleCursorPosition(console, cursorPos);
            printf("%s \n", menu[i]);
        }

        // обозначение выбранной позиции
        cursorPos = (COORD){ 0, choose_pos };
        SetConsoleCursorPosition(console, cursorPos);
        printf("<<");
        cursorPos = (COORD){ strlen(menu[choose_pos]) + 3 + 1, choose_pos };
        SetConsoleCursorPosition(console, cursorPos);
        printf(">>");

        // ожидание нового нажатия клавиши
        iKey = _getch();
    }
    return choose_pos;
}

int main() {
    srand(time(NULL));

    system("title Arcade Game");

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(console, &structCursorInfo);
    structCursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(console, &structCursorInfo);

    SetConsoleTextAttribute(console, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
    system("cls");

    //УГАДАЙКА
    int enter;
    int trys;
    int num;
    int min;
    int max;
    int game_over;

    //ОБЩЕЕ
    int choose_pos = 0;
    int exit_flag = 0;
    int difficulty = 1;
    int lang = 1;
    int status = 1;
    int iKey = 0;
    COORD cursorPos;

    // вложенные меню и настройка языка
    char* lang_menu[LANG_MENU_SIZE] = { "Русский", "English" };

    char* main_menu_eng[MAIN_MENU_SIZE] = { "Game", "Settings", "Exit" };
    char* settings_menu_eng[SETTINGS_MENU_SIZE] = { "Difficulty Settings", "Color Settings", "Language", "Back" };
    char* themes_menu_eng[THEMES_MENU_SIZE] = { "Dark", "White", "Yellow" };
    char* difficult_menu_eng[DIFFICULT_MENU_SIZE] = { "Easy", "Normal", "Hard" };
    char* game_menu_eng[GAMES_MENU_SIZE] = { "GuessNum", "Back" };
    char* guessgame_mode_eng[GUESSNUM_GAME_MODE_SIZE] = { "Bot guessing", "Player guessing" };
    char* guessgame_choise_eng[GUESSNUM_GAME_CHOISE_SIZE] = { "Smaller", "Bigger", "Correct" };

    char* settings_menu_ru[SETTINGS_MENU_SIZE] = { "Сложность", "Тема", "Язык", "Назад" };
    char* themes_menu_ru[THEMES_MENU_SIZE] = { "Темная", "Белая", "Желтая" };
    char* difficult_menu_ru[DIFFICULT_MENU_SIZE] = { "Легко", "Нормально", "Сложно" };
    char* main_menu_ru[MAIN_MENU_SIZE] = { "Играть", "Настройки", "Выход" };
    char* game_menu_ru[GAMES_MENU_SIZE] = { "Угадайка", "Назад" };
    char* guessgame_mode_ru[GUESSNUM_GAME_MODE_SIZE] = { "Бот угадывает", "Игрок угадывает" };
    char* guessgame_choise_ru[GUESSNUM_GAME_CHOISE_SIZE] = { "Меньше", "Больше", "Правильно" };

    char* main_menu[MAIN_MENU_SIZE];
    char* game_menu[GAMES_MENU_SIZE];
    char* settings_menu[SETTINGS_MENU_SIZE];
    char* themes_menu[THEMES_MENU_SIZE];
    char* difficult_menu[DIFFICULT_MENU_SIZE];
    char* guessgame_mode[GUESSNUM_GAME_MODE_SIZE];
    char* guessgame_choise[GUESSNUM_GAME_CHOISE_SIZE];

    for (int i = 0; i < MAIN_MENU_SIZE; i++) main_menu[i] = main_menu_eng[i];
    for (int i = 0; i < GAMES_MENU_SIZE; i++) game_menu[i] = game_menu_eng[i];
    for (int i = 0; i < SETTINGS_MENU_SIZE; i++) settings_menu[i] = settings_menu_eng[i];
    for (int i = 0; i < THEMES_MENU_SIZE; i++) themes_menu[i] = themes_menu_eng[i];
    for (int i = 0; i < DIFFICULT_MENU_SIZE; i++) difficult_menu[i] = difficult_menu_eng[i];
    for (int i = 0; i < GUESSNUM_GAME_MODE_SIZE; i++) guessgame_mode[i] = guessgame_mode_eng[i];
    for (int i = 0; i < GUESSNUM_GAME_CHOISE_SIZE; i++) guessgame_choise[i] = guessgame_choise_eng[i];

    while (!exit_flag) {

        system("cls");
        cursorPos = (COORD){ 0, 0 };
        SetConsoleCursorPosition(console, cursorPos);

        if (status == 1) // ГЛАВНОЕ МЕНЮ
        {
            choose_pos = createMenu(main_menu, console, MAIN_MENU_SIZE);
        }
        else if (status == 11) { // НАСТРОЙКИ
            choose_pos = createMenu(settings_menu, console, SETTINGS_MENU_SIZE);
            choose_pos += 3;
        }
        else if (status == 111) { // НАСТРОЙКИ | СЛОЖНОСТЬ
            choose_pos = createMenu(difficult_menu, console, DIFFICULT_MENU_SIZE);
            choose_pos += 7;
        }
        else if (status == 112) { // НАСТРОЙКИ | ТЕМА
            choose_pos = createMenu(themes_menu, console, THEMES_MENU_SIZE);
            choose_pos += 10;
        }
        else if (status == 113) { //НАСТРОЙКИ | ЯЗЫК 
            choose_pos = createMenu(lang_menu, console, LANG_MENU_SIZE);
            choose_pos += 13;
        }

        switch (choose_pos) {

        case 0: // ИГРЫ | ГЛАВНОЕ МЕНЮ       // ТУТ МНЕ ПРИШЛОСЬ ЧУТЬ ЧУТЬ ПОПОТЕТЬ, ЧТОБЫ В БУДУЩЕМ МНЕ БЫЛО ХОРОШО ДОБАВЛЯТЬ НОВЫЕ ИГРЫ
            choose_pos = createMenu(game_menu, console, GAMES_MENU_SIZE);
            switch (choose_pos) {
                {
            case 0: // УГАДАЙКА | ИГРЫ | ГЛАВНОЕ МЕНЮ
                choose_pos = createMenu(guessgame_mode, console, GUESSNUM_GAME_MODE_SIZE);
                switch (choose_pos) {
                case 0: // BOT | УГАДАЙКА | ИГРЫ | ГЛАВНОЕ МЕНЮ
                    system("cls");
                    trys = 1, num = rand() % 101; // УГАДАЙКА
                    if (lang == 2) printf("Я выбрал число от 0 до 100. Попробуй его отгадать за 10 попыток!\n");
                    else if (lang == 1) printf("I have chosen a number from 0 to 100. try to guess the number in 10 attemps!\n");

                    while (1) {
                        if (trys == 11) {
                            if (lang == 2) printf("\n\nТы проиграл! Я загадал число %d!\n\n", num);
                            else if (lang == 1) printf("\n\nYou lose, i had guessed the number %d!", num);
                            system("pause");
                            break;
                        }
                        if (lang == 2) printf("Попытка номер %d: ", trys);
                        else if (lang == 1) printf("Try number %d: ", trys);
                        scanf_s("%d", &enter);
                        if (enter == num) {
                            if (lang == 2) printf("\n\nМолодец ты выиграл! Я загадал число %d!\n\n", num);
                            else if (lang == 1) printf("\n\nAmazing, you won!!! i guessed the number %d!\n\n", num);
                            system("pause");
                            break;

                        }
                        else if (enter > num) {
                            if (lang == 2) printf("Я загадал число меньше!\n");
                            else if (lang == 1) printf("I'm thinking of a smaller number!\n");
                        }
                        else if (enter < num) {
                            if (lang == 2) printf("Я загадал число больше!\n");
                            else if (lang == 1) printf("I'm thinking of a bigger number!\n");
                        }
                        trys++;
                    }
                    break;
                case 1: // PLAYER | УГАДАЙКА | ИГРЫ | ГЛАВНОЕ МЕНЮ
                    system("cls");
                    enter, trys = 1, min = 0, max = 100, game_over = 0;

                    while (1) {
                        if (game_over == 1) break;
                        if (trys == 11) {
                            if (lang == 2) printf("\n\nЯ проиграл!");
                            else if (lang == 1) printf("\n\nI lose!");
                            system("pause");
                            break;
                        }
                        if (trys == 1) {
                            enter = rand() % (max - min + 1) + min;
                        }
                        else {
                            enter = max - ((max - min) / 2);
                        }


                        choose_pos = 0;
                        iKey = 0;
                        cursorPos = (COORD){ 0, 0 };

                        while (iKey != KEY_EXIT && iKey != KEY_ENTER) { // ТУТ НЕ ПОЛУЧИЛОСЬ ИСПОЛЬЗОВАТЬ ФУНКЦИЮ 
                            switch (iKey) {
                            case KEY_ARROW_UP:
                                choose_pos--;
                                break;
                            case KEY_ARROW_DOWN:
                                choose_pos++;
                                break;
                            default:
                                break;
                            }

                            // зацикливание перелистывания меню
                            if (choose_pos < 0) { choose_pos = GUESSNUM_GAME_CHOISE_SIZE - 1; }
                            if (choose_pos > GUESSNUM_GAME_CHOISE_SIZE - 1) { choose_pos = 0; }

                            // перед перерисовкой меню очистка
                            system("cls");

                            if (lang == 2) printf("\nПопытка номер %d: %d", trys, enter);
                            else if (lang == 1) printf("\nTry number %d: %d", trys, enter);

                            // перерисовка меню
                            for (int i = 3; i < GUESSNUM_GAME_CHOISE_SIZE + 3; i++) {
                                cursorPos = (COORD){ 3, i };
                                SetConsoleCursorPosition(console, cursorPos);
                                printf("%s \n", guessgame_choise[i - 3]);
                            }

                            // обозначение выбранной позиции
                            cursorPos = (COORD){ 0, choose_pos + 3 };
                            SetConsoleCursorPosition(console, cursorPos);
                            printf("<<");
                            cursorPos = (COORD){ strlen(guessgame_choise[choose_pos]) + 3 + 1, choose_pos + 3 };
                            SetConsoleCursorPosition(console, cursorPos);
                            printf(">>");

                            // ожидание нового нажатия клавиши
                            iKey = _getch();
                        }

                        switch (choose_pos) {
                        case 0:
                            max = enter - 1;
                            break;
                        case 1:
                            min = enter;
                            break;
                        case 2:
                            system("cls");
                            if (lang == 2) printf("\n\nЯ выиграл!\n");
                            else if (lang == 1) printf("\n\nI win\n!");
                            game_over = 1;
                            system("pause");
                            break;
                        }

                        if (max == min) {
                            system("cls");
                            if (lang == 2) printf("\n\nТы меня обманул! Игра закончена!\n\n");
                            else if (lang == 1) printf("\n\nYou cheater! Game Over!\n\n");
                            game_over = 1;
                            system("pause");
                            break;
                        }
                        trys++;
                    }
                    break;
                }
                break;
                }
            }
            break;

        case 1: // ГЛАВНОЕ МЕНЮ | НАСТРОЙКИ
            status = 11;
            break;
        case 2: // ГЛАВНОЕ МЕНЮ | ВЫХОД 
            exit_flag = 1;
            break;
        case 3: // НАСТРОЙКИ | СЛОЖНОСТЬ 
            status = 111;
            break;
        case 4: // НАСТРОЙКИ | ТЕМА 
            status = 112;
            break;
        case 5: // НАСТРОЙКИ | ЯЗЫК 
            status = 113;
            break;
        case 6: // НАСТРОЙКИ | НАЗАД 
            status = 1;
            break;
        case 7: // НАСТРОЙКИ | СЛОЖНОСТЬ | СЛОЖНО
            difficulty = 3;
            status = 11;
            break;
        case 8: // НАСТРОЙКИ | СЛОЖНОСТЬ | СРЕДНЕ
            difficulty = 2;
            status = 11;
            break;
        case 9: // НАСТРОЙКИ | СЛОЖНОСТЬ | ЛЕГКО
            difficulty = 1;
            status = 11;
            break;
        case 10: // НАСТРОЙКИ | ТЕМА | DARK
            SetConsoleTextAttribute(console, BACKGROUND_INTENSITY);
            status = 11;
            break;
        case 11: // НАСТРОЙКИ | ТЕМА | WHITE
            SetConsoleTextAttribute(console, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
            status = 11;
            break;
        case 12: // НАСТРОЙКИ | ТЕМА | YELLOW
            SetConsoleTextAttribute(console, BACKGROUND_RED | BACKGROUND_GREEN);
            status = 11;
            break;
        case 13: // НАСТРОЙКИ | ЯЗЫК | РУССКИЙ
            for (int i = 0; i < MAIN_MENU_SIZE; i++) main_menu[i] = main_menu_ru[i];
            for (int i = 0; i < GAMES_MENU_SIZE; i++) game_menu[i] = game_menu_ru[i];
            for (int i = 0; i < SETTINGS_MENU_SIZE; i++) settings_menu[i] = settings_menu_ru[i];
            for (int i = 0; i < THEMES_MENU_SIZE; i++) themes_menu[i] = themes_menu_ru[i];
            for (int i = 0; i < DIFFICULT_MENU_SIZE; i++) difficult_menu[i] = difficult_menu_ru[i];
            for (int i = 0; i < GUESSNUM_GAME_MODE_SIZE; i++) guessgame_mode[i] = guessgame_mode_ru[i];
            for (int i = 0; i < GUESSNUM_GAME_CHOISE_SIZE; i++) guessgame_choise[i] = guessgame_choise_ru[i];
            lang = 2;
            status = 11;
            break;
        case 14: // НАСТРОЙКИ | ЯЗЫК | ENGLISH
            for (int i = 0; i < MAIN_MENU_SIZE; i++) main_menu[i] = main_menu_eng[i];
            for (int i = 0; i < GAMES_MENU_SIZE; i++) game_menu[i] = game_menu_eng[i];
            for (int i = 0; i < SETTINGS_MENU_SIZE; i++) settings_menu[i] = settings_menu_eng[i];
            for (int i = 0; i < THEMES_MENU_SIZE; i++) themes_menu[i] = themes_menu_eng[i];
            for (int i = 0; i < DIFFICULT_MENU_SIZE; i++) difficult_menu[i] = difficult_menu_eng[i];
            for (int i = 0; i < GUESSNUM_GAME_MODE_SIZE; i++) guessgame_mode[i] = guessgame_mode_eng[i];
            for (int i = 0; i < GUESSNUM_GAME_CHOISE_SIZE; i++) guessgame_choise[i] = guessgame_choise_eng[i];
            lang = 1;
            status = 11;
            break;
        }

    }

    system("cls");
    printf("Goodbay!\n");

    system("pause");
    return 0;
}