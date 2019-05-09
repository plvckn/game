#include "Klases.h"
namespace game{

bool gameON = true;
std::ofstream r("rez.txt");

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_FONT_INFOEX cfi;
//STATINIAI KINTAMIEJI
char FieldClass::field[ROWS][COLUMNS]{0};
bool FieldClass::nodes[ROWS][COLUMNS]{false};
int ScoreWindowClass::ScoreCounter=0;
//LANGELIAI:
char spc = '0'; // space/empty tile
char pts = '1'; // point tile
char hwall = '2'; // horizontal wall
char vwall = '3'; // vertical wall
char cwall = '4'; // corner wall*/
char pass = 'P'; // passthrough - perejimo langelis



ScoreWindowClass::ScoreWindowClass()
{
    window.X = 40;
    window.Y = 0;
}

void ScoreWindowClass::drawScore()
{
    short x, y; getCoord(x, y); SetCursor(x, y);
    std::string name = "SCORE:";
    std::cout << name << ScoreCounter;
    setCoord(x + name.length(), y);
}


void ScoreWindowClass::updateCounter()
{
    short x, y; getCoord(x, y);
    SetCursor(x, y);
    std::cout << ScoreCounter;
    if(ScoreCounter >= goalPoints) VictoryScreen(getWinCondition());
}

int getCounter()
{
    return ScoreWindowClass::ScoreCounter;
}

void addScore()
{
    ScoreWindowClass::ScoreCounter += 100;
}

void ScoreWindowClass::setWinCondition(int points)
{
    goalPoints = points;
}

int ScoreWindowClass::getWinCondition()
{
    return goalPoints;
}
void CoordClass::setCoord(short x, short y)
{
    coordinates = {x, y};
}

void CoordClass::getCoord(short &x, short &y)
{
    x = this->coordinates.X;
    y = this->coordinates.Y;
}


void FieldClass::setGameCoord(short x, short y)
{
    setCoord(x, y);
    SetCursor(x, y);
}

void FieldClass::load_map()
{
    std::ifstream df("map_.txt");
    char symbol;
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLUMNS; j++)
        {
            df >> symbol;
            field[i][j] = symbol;
        }
    }
}

void FieldClass::addNodes()
{
    nodes[1][6]   = true;
    nodes[1][18]  = true;
    nodes[5][1]   = true;
    nodes[5][6]   = true;
    nodes[5][18]  = true;
    nodes[5][23]  = true;
    nodes[7][6]   = true;
    nodes[7][18]  = true;
    nodes[15][6]  = true;
    nodes[15][18] = true;
    nodes[17][6]  = true;
    nodes[17][18] = true;
    nodes[19][11] = true;
    nodes[19][13] = true;
}

bool FieldClass::checkNode(int i, int j)
{
    if(nodes[j][i]==true) return true;
    else return false;
}

char FieldClass::getTile(int i, int j)
{
    return field[i][j];
}

bool FieldClass::passableTile(int i, int j)
{
    if(getTile(j, i) == spc || getTile(j, i) == pts) return true;
    else return false;
}


PlayerClass::PlayerClass()
{
    pcounter = 0;
    Player = 'C';
}

void PlayerClass::rotateSymbol()
{
    pcounter++;
    if(pcounter%2==1) Player = 'c';
    else Player = 'C';
}

void FieldClass::clearTile(int i, int j)
{
    SetCursor(i, j);
    std::cout << ' ';
}


void FieldClass::drawMap()
{
    char spcS = char(32); // space symbol
    char ptsS = char(46); // points symbol
    char hwallS = char(45); // horizontal wall symbol
    char vwallS = char(124); // vertical wall symbol
    char cwallS = char(43); // corner wall symbol
    char passS = char(32); // space symbol
    short x, y; getCoord(x, y);

    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLUMNS; j++)
        {
            if(getTile(i, j) == spc || getTile(i, j) == pass) std::cout << spcS;
            else if(getTile(i, j) == pts) std::cout << ptsS;
            else if(getTile(i, j) == hwall) std::cout << hwallS;
            else if(getTile(i, j) == vwall) std::cout << vwallS;
            else if(getTile(i, j) == cwall) std::cout << cwallS;
        }
        SetCursor(x, y+i+1);
    }
}

void PlayerClass::load_player()
{
    std::cout<<Player;
}

void PlayerClass::setPCoord(short x, short y)
{
    pcoord.X = x;
    pcoord.Y = y;
    SetCursor(pcoord.X, pcoord.Y);
}

void PlayerClass::getPCoord(short &x, short &y)
{
    x = pcoord.X;
    y = pcoord.Y;
}


bool PlayerClass::command_move(int Keystate) //Judejimo nustatymas pagal klaviso aptikima
{
        short tempX, tempY; getPCoord(tempX, tempY);
        while(true)
        {

            if(Keystate == VK_UP)    { tempY--; if(!move(tempX, tempY)) {Keystate == NULL; tempY++;} else clearTile(tempX, tempY+1); return true;}
            if(Keystate == VK_DOWN)  { tempY++; if(!move(tempX, tempY)) {Keystate == NULL; tempY--;} else clearTile(tempX, tempY-1); return true;}
            if(Keystate == VK_LEFT)  { tempX--; if(!move(tempX, tempY)) {Keystate == NULL; tempX++;} else clearTile(tempX+1, tempY); return true;}
            if(Keystate == VK_RIGHT) { tempX++; if(!move(tempX, tempY)) {Keystate == NULL; tempX--;} else clearTile(tempX-1, tempY); return true;}
            else return true;}
}

bool PlayerClass::move(short x, short y) // Zaidejas pajuda (jei laisvas langelis)
{
    if(getTile(y, x)== spc || getTile(y, x) == pts)
    {
        if(getTile(y, x) == pts) addScore();
        setPCoord(x,  y);
        load_player();
        return true;
    }
    else return false;
}

EnemyClass::EnemyClass() //KONSTRUKTORIUS
{
    enemyS = 'A';
    enemyCount = 4;
    enemies.reserve(enemyCount);
    enemies.push_back({0,0}); dir[0].UP = true;
    enemies.push_back({0,0}); dir[1].DOWN = true;
    enemies.push_back({0,0}); dir[2].UP = true;
    enemies.push_back({0,0}); dir[3].DOWN = true;

}

void EnemyClass::setECoord(short x, short y, int it)
{
    enemies[it].X = x;
    enemies[it].Y = y;

}

void EnemyClass::getECoord(short &x, short &y, int it)
{
    x = this->enemies[it].X;
    y = this->enemies[it].Y;
}

void EnemyClass::loadEnemy(int it)
{
    short x, y;
    getECoord(x, y, it);
    SetCursor(x, y);
    std::cout << enemyS;
}

void EnemyClass::loadEnemies(COORD a, COORD b, COORD c, COORD d)
{
    setECoord(a.X, a.Y, 0);
    setECoord(b.X, b.Y, 1);
    setECoord(c.X, c.Y, 2);
    setECoord(d.X, d.Y, 3);
    for(int i = 0; i < enemies.size(); i++)
    {
        loadEnemy(i);
    }
}

void EnemyClass::launchEnemies()
{
    for(int i=0; i<enemies.size(); i++) // if getnexttile (-<get dir) != passable tile
    {
        short x, y; getECoord(x, y, i);
        if(checkNode(x, y))
        {
            decisionMove(i);
        }

        getNextTile(x, y, i);
        if(!passableTile(x, y))
        {
            changeDir(i);
        }
        else move(i);
    }
}

void EnemyClass::getNextTile(short &x, short &y, int it)
{
    getECoord(x, y, it);
    getDir(x, y, it);
}

void EnemyClass::getDir(short &x, short &y, int it)
{
    if(dir[it].UP == true)   { y--; return;}
    if(dir[it].RIGHT == true){ x++; return;}
    if(dir[it].DOWN == true) { y++; return;}
    if(dir[it].LEFT == true) { x--; return;}
}

void EnemyClass::move(int it)
{
    short x, y; getECoord(x, y, it);
    clearTile(x, y);
    getDir(x, y, it);
    setECoord(x, y, it);
    loadEnemy(it);
}

void EnemyClass::clearTile(int i, int j)
{
    SetCursor(i, j);
    std::cout << '.';
}

void EnemyClass::changeDir(int it)
{
    short x, y; getECoord(x, y, it);
    bool vertical = false;   nextAxis(vertical, it);

    if(vertical)
    {
        if(dir[it].UP == false)    { if(passableTile(x, y-1)) {dir[it].UP = true; dir[it].RIGHT = false; dir[it].DOWN = false; dir[it].LEFT = false; move(it); return;} }
        if(dir[it].DOWN == false)  { if(passableTile(x, y+1)) {dir[it].UP = false; dir[it].RIGHT = false; dir[it].DOWN = true; dir[it].LEFT = false; move(it); return;} }
    }
    else //HORIZONTAL MOVEMENT
    {
        if(dir[it].RIGHT == false) { if(passableTile(x+1, y)) {dir[it].UP = false; dir[it].RIGHT = true; dir[it].DOWN = false; dir[it].LEFT = false; move(it); return;} }
        if(dir[it].LEFT == false)  { if(passableTile(x-1, y)) {dir[it].UP = false; dir[it].RIGHT = false; dir[it].DOWN = false; dir[it].LEFT = true; move(it); return;} }
    }
}

void EnemyClass::nextAxis(bool &axis, int it)
{
    if( dir[it].UP == true || dir[it].DOWN == true ) axis = false;
    else axis = true;
}

void EnemyClass::decisionMove(int it)
{
    inverseDir(it);
    pickDir(it);
    move(it);
}

void EnemyClass::inverseDir(int it)
{
    short x, y; getECoord(x, y, it);
    if(dir[it].UP == true)    { dir[it].DOWN = false;  dir[it].UP = passableTile(x, y-1); dir[it].RIGHT = passableTile(x+1, y); dir[it].LEFT = passableTile(x-1, y); return; }
    if(dir[it].RIGHT == true) { dir[it].LEFT = false;  dir[it].UP = passableTile(x, y-1); dir[it].RIGHT = passableTile(x+1, y); dir[it].DOWN = passableTile(x, y+1); return; }
    if(dir[it].DOWN == true)  { dir[it].UP = false;  dir[it].RIGHT = passableTile(x+1, y); dir[it].DOWN = passableTile(x, y+1); dir[it].LEFT = passableTile(x-1, y); return; }
    if(dir[it].LEFT == true)  { dir[it].RIGHT = false;  dir[it].UP = passableTile(x, y-1); dir[it].DOWN = passableTile(x, y+1); dir[it].LEFT = passableTile(x-1, y); return; }
}

void EnemyClass::pickDir(int it)
{
    while(true)
    {
        int choice = rand()%4;
        switch(choice)
        {
        case 0:
            if(dir[it].UP == true)
            {
                dir[it].UP = true; dir[it].RIGHT = false; dir[it].DOWN = false; dir[it].LEFT = false; return;
            } else break;
        case 1:
            if(dir[it].RIGHT == true)
            {
                dir[it].UP = false; dir[it].RIGHT = true; dir[it].DOWN = false; dir[it].LEFT = false; return;
            } else break;
        case 2:
            if(dir[it].DOWN == true)
            {
                dir[it].UP = false; dir[it].RIGHT = false; dir[it].DOWN = true; dir[it].LEFT = false; return;
            } else break;
        case 3:
            if(dir[it].LEFT == true)
            {
                dir[it].UP = false; dir[it].RIGHT = false; dir[it].DOWN = false; dir[it].LEFT = true; return;
            } else break;
        }
    }
}


bool PlayerKilled(PlayerClass a, EnemyClass b)
{
    short x1, y1, x2, y2;
    for(int i=0; i<4; i++)
    {
        a.getPCoord(x1, y1);
        b.getECoord(x2, y2, i);
        if( (x1 == x2) && (y1 == y2) ) return true;
    }
    return false;
}

void UpdateFile()
{

    r << getCounter();
}

void VictoryScreen(int score)
{
    UpdateFile();
    gameON = false;
    system("cls");
    SetFontSize(18, 32);
    SetCursor(25,15);
    std::cout << "YOU WON!";
    SetCursor(25, 16);
    std::cout << "Victory condition met!";
    SetCursor(25, 17);
    std::cout << score;
    SetCursor(25, 19);
    system("pause");
    exit_program();
}

void LoseScreen()
{
    UpdateFile();
    gameON = false;
    system("cls");
    SetFontSize(18, 32);
    SetCursor(25,15);
    std::cout << "THE END!";
    SetCursor(25, 17);
    std::cout << getCounter();
    SetCursor(25, 19);
    system("pause");
    exit_program();

}

int GetKeystate()
{
    if(GetAsyncKeyState(VK_UP))      return  VK_UP;
    if(GetAsyncKeyState(VK_DOWN))    return  VK_DOWN;
    if(GetAsyncKeyState(VK_LEFT))    return  VK_LEFT;
    if(GetAsyncKeyState(VK_RIGHT))   return  VK_RIGHT;
}

void exit_program()
{
    exit(0);
}

void Delay(int seconds)
{
    clock_t delay = seconds * CLOCKS_PER_SEC;
    clock_t start = clock();
    while((clock() - start) < delay);
}

void GameSpeed(DWORD a)
{
    Sleep(a);
}

void Fullscreen()
{
    SetConsoleDisplayMode(console, CONSOLE_FULLSCREEN_MODE, NULL);
}

void TextColor(short col)
{
    SetConsoleTextAttribute(console, col);
}

void SetCursor(short x, short y)
{
    SetConsoleCursorPosition(console, {x, y});
}

void SetFontSize(short x, short y)
{
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = x;
    cfi.dwFontSize.Y = y;
    SetCurrentConsoleFontEx(console, false, &cfi);

}

void RemoveScrollbar()
{
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(console, &info);
    COORD new_size = {
        info.srWindow.Right - info.srWindow.Left + 1,
        info.srWindow.Bottom - info.srWindow.Top + 1
    };
    SetConsoleScreenBufferSize(console, new_size);
}

void show_cursor(bool show_cursor_FLAG){

    CONSOLE_CURSOR_INFO cursor;
    GetConsoleCursorInfo(console, &cursor);
    cursor.bVisible = show_cursor_FLAG;
    SetConsoleCursorInfo(console, &cursor);
}

}
