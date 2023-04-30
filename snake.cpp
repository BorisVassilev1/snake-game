#include <iostream>
#include <Windows.h>
#include <queue>
#include <random>
#include <time.h>

using namespace std;
//0 = Black  8 = Gray
//1 = Blue   9 = Light Blue
//2 = Green  a = Light Green
//3 = Aqua   b = Light Aqua
//4 = Red    c = Light Red
//5 = Purple d = Light Purple
//6 = Yellow e = Light Yellow
//7 = White  f = Bright White

HANDLE hConsole;

void moveCursor(int x, int y)
{
    SetConsoleCursorPosition(hConsole, {(short)(x * 2), (short)y});
}

void setColor(int color)
{
    SetConsoleTextAttribute(hConsole, color);
}

void printRainbow(string s)
{
    /*
        s[i];
        s.length()
    */
    int color = 0x0f;
    for(int i = 0; i < s.length(); i ++)
    {
        if(s[i] == ' ')
        {
            setColor(0x01);
            cout << s[i];
        }
        else
        {
            setColor(color);
            cout << s[i];
            color += 16;
            if(color > 0x7f) color = 0x0f;
        }

    }
    setColor(0x07);
}

bool isKeyPressed(int key) {
    return GetAsyncKeyState(key);
    //return GetKeyState(key) & 0x8000;
}

void drawPixel(int x, int y) {
    moveCursor(x, y);
    cout << (char) 219 << (char) 219;
}

int randomNumber(int range) {
    return rand() % (range - 2) + 1;
}

int main()
{
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    srand(time(0));

    int x = 1, y = 1;
    int posoka = 0;
    const int RAZMER_POLE = 20;
    int qbulkaX = randomNumber(RAZMER_POLE), qbulkaY = randomNumber(RAZMER_POLE);


    bool pole[RAZMER_POLE][RAZMER_POLE];
    for(int i = 0; i < RAZMER_POLE; i ++) {
        for(int j = 0; j < RAZMER_POLE; j ++) {
            if(i == 0 || j == 0 || i == RAZMER_POLE - 1 || j == RAZMER_POLE - 1) {
                pole[i][j] = true;
            } else {
                pole[i][j] = false;
            }
        }
    }

    deque<pair<int, int>> snake;
    for(int i = 0; i < 4; i ++) {
        snake.push_front({x, y});
    }   


    while(!isKeyPressed('Q')) {
        system("cls");

        if(isKeyPressed('A')) posoka = 3;
        if(isKeyPressed('D')) posoka = 0;
        if(isKeyPressed('W')) posoka = 1;
        if(isKeyPressed('S')) posoka = 2;

        switch(posoka) {
            case 0: 
                x ++;
                break;
            case 1:
                y --;
                break;
            case 2:
                y ++;
                break;
            case 3:
                x --;
                break;
        }

        pair<int, int> opashka = snake.back();
        snake.pop_back();
        pole[opashka.first][opashka.second] = false;

        if(pole[x][y] == true) {
            system("cls");
            moveCursor(10, 10);
            setColor(0x0c);
            cout << "YOU LOST";
            moveCursor(0, 20);
            break;
        }

        snake.push_front({x, y});
        pole[x][y] = true;

        
        if(x == qbulkaX && y == qbulkaY) {
            snake.push_back(opashka);
            qbulkaX = randomNumber(RAZMER_POLE);
            qbulkaY = randomNumber(RAZMER_POLE);
        }

        // steni
        setColor(0x0f);
        moveCursor(0,0);
        for(int i = 0; i < RAZMER_POLE; i ++) {
            cout << (char) 219 << (char) 219;
        }
        for(int i = 1; i < RAZMER_POLE - 1; i ++) {
            drawPixel(0, i);
            drawPixel(RAZMER_POLE - 1, i);
        }
        moveCursor(0,RAZMER_POLE - 1);
        for(int i = 0; i < RAZMER_POLE; i ++) {
            cout << (char) 219 << (char) 219;
        }

        // zmiq
        setColor(0x0a);
        for(int i = 0; i < snake.size(); i ++) {
            drawPixel(snake[i].first, snake[i].second);
        }

        // qbulka
        setColor(0x0c);
        drawPixel(qbulkaX, qbulkaY);
        
        // score
        setColor(0x0f);
        moveCursor(RAZMER_POLE, 0);
        cout << "Score: " << snake.size() * 2500;

        moveCursor(0,0);
        Sleep(1000 / 10);
    }
    setColor(0x07);

    return 0;
}
