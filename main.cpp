#include "Klases.h"
using namespace std;
int main()
{   //ekrano nustatymai
    srand(time(NULL));
    game::RemoveScrollbar();
    game::Fullscreen();
    game::TextColor(0b00000010);
    game::SetFontSize(14, 24);
    game::show_cursor(false);

    game::FieldClass laukas;
    laukas.setGameCoord(0, 0);
    laukas.load_map();
    laukas.drawMap();
    laukas.addNodes();

    game::ScoreWindowClass scoreWindow;
    scoreWindow.setCoord(30, 0);
    scoreWindow.drawScore();
    scoreWindow.setWinCondition(20000);

    game::PlayerClass player;
    player.setPCoord(12, 9);
    player.load_player();

    game::EnemyClass enemy;
    enemy.loadEnemies({6, 9}, {6, 13}, {18, 9}, {18, 13}); // 4 enemies at set coords

    int Keystate = getch();
    while(game::gameON){

        if(kbhit())
        {
            if(GetAsyncKeyState(VK_UP))      Keystate = VK_UP;
            if(GetAsyncKeyState(VK_DOWN))    Keystate = VK_DOWN;
            if(GetAsyncKeyState(VK_LEFT))    Keystate = VK_LEFT;
            if(GetAsyncKeyState(VK_RIGHT))   Keystate = VK_RIGHT;
            player.command_move(Keystate);
        }

        if(game::PlayerKilled(player, enemy)){game::LoseScreen();} //tikrinimas po zaidejo judesio
        player.rotateSymbol();
        scoreWindow.updateCounter();
        enemy.launchEnemies();
        if(game::PlayerKilled(player, enemy)){game::LoseScreen();} // tikrinimas po AI (prieso) judesio
        game::GameSpeed(225);
    }

    return 0;
}
