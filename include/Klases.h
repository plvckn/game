#define _WIN32_WINNT 0x0601
#ifndef KLASES_H
#define KLASES_H
#ifdef __cplusplus
#endif

#define ROWS (23)
#define COLUMNS (25)

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ESC 27

#include <vector>
#include <windows.h>
#include <fstream>
#include <iostream>
#include <conio.h>
#include <time.h>

namespace game{

extern bool gameON;
void Fullscreen();
void TextColor(short col);
void SetCursor(short x, short y);
void SetFontSize(short x, short y);
void RemoveScrollbar();
void show_cursor(bool show_cursor_FLAG);
void Delay(int seconds);
void GameSpeed(DWORD a);
int GetKeystate();
void LoseScreen();
void VictoryScreen(int score);
void UpdateFile();
void exit_program();
//bool PlayerKilled(PlayerClass a, EnemyClass b); apacioje

struct Dir
{
    bool UP = false;
    bool RIGHT = false;
    bool DOWN = false;
    bool LEFT = false;
};


class CoordClass
{
    private:
        COORD coordinates;

    public:
        void setCoord(short, short);
        void getCoord(short&, short&);
};

class ScoreWindowClass : public CoordClass
{
    private:
        COORD window;
        static int ScoreCounter;
        int goalPoints;

    public:
        ScoreWindowClass();
        void drawScore();
        void updateCounter();
        void setWinCondition(int);
        int getWinCondition();
        friend int getCounter();
        friend void addScore();
};

class FieldClass : public CoordClass
{
    protected:
        static char field[ROWS][COLUMNS];
        static bool nodes[ROWS][COLUMNS]; // node - tam tikra koordinate lauke jungianti kelis takus (taku sankirta)

    public:
        void load_map();
        void drawMap();
        void addNodes();
        void setGameCoord(short, short);
        char getTile(int, int);
        bool passableTile(int, int);
        bool checkNode(int, int);
        void clearTile(int, int);
};

class PlayerClass : public FieldClass
{
    private:
        COORD pcoord;
        int pcounter;
        char Player;

    public:
        PlayerClass();
        void rotateSymbol();
        void load_player();
        bool command_move(int);
        bool move(short, short);
        void getPCoord(short&, short&);
        void setPCoord(short, short);
};



class EnemyClass : public FieldClass
{
    private:
        int enemyCount;
        char enemyS; // enemy Symbol
        std::vector<COORD>enemies;
        Dir dir[4];  //kryptys (up, right, down, left)

    public:
        EnemyClass();
        void setECoord(short, short, int);
        void getECoord(short&, short&, int);
        void loadEnemy(int);
        void loadEnemies(COORD, COORD, COORD, COORD);
        void launchEnemies(); //priesai pradeda judeti
        void getNextTile(short&, short&, int); //pagal vaiduoklio judejimo krypti nustato kito langelio koordinates
        void getDir(short&, short &, int); //aptinka vaiduoklio judejimo krypti ir nustato kito langelio koordinates
        void move(int);
        void clearTile(int, int); //vaiduokliui pakeiciant langeli jis nutrinamas sename langelyje
        void changeDir(int); // kita kryptis
        void nextAxis(bool&, int); // kita asis
        void decisionMove(int); // jei vaiduoklis atsiduria ant Node (keliu sankirtos) jis pats pasirenka kur judeti toliau
        void inverseDir(int);
        void pickDir(int); // random tinkama kryptis
};



typedef struct _CONSOLE_FONT_INFOEX
{
    ULONG cbSize;
    DWORD nFont;
    COORD dwFontSize;
    UINT  FontFamily;
    UINT  FontWeight;
    WCHAR FaceName[LF_FACESIZE];
}CONSOLE_FONT_INFOEX, *PCONSOLE_FONT_INFOEX;
extern "C" {
BOOL WINAPI SetCurrentConsoleFontEx(HANDLE hConsoleOutput, BOOL bMaximumWindow, PCONSOLE_FONT_INFOEX
lpConsoleCurrentFontEx);
}

bool PlayerKilled(PlayerClass a, EnemyClass b);

}
#endif
