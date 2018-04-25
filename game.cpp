#include "game.h"

Game::Game(bool typeA, QObject *parent) : QObject(parent)
{
    style = typeA;
    eggs = new QVector<Egg*>;
}

void Game::tapEvent(bool left_wolf, bool top_basket)
{
    this->player_wolf = left_wolf;
    this->player_basket = top_basket;
}

int Game::getScore()
{
    return this->score;
}

int Game::getLife()
{
    return this->life;
}

bool Game::takeIt(int layer)
{
    int t;
    if(player_wolf && !player_basket)
        t = 1;
    else if(player_wolf && player_basket)
        t = 2;
    else if(!player_wolf && player_basket)
        t = 3;
    else
        t = 4;

    return layer == t;
}

void Game::Play()
{
    bool new_egg = rand()%chance + 1 == 2;
    if(eggs->length() < 5 && new_egg){
        int r_layer = style ? 4 : 3;
        eggs->push_back(new Egg(rand()%r_layer + 1, 1));
    }

    for(int i = 0; i < eggs->length(); i++){
        eggs->value(i)->pos += eggs->value(i)->speed;

        if(eggs->value(i)->pos > 5){
            if(takeIt(eggs->value(i)->layer)){
                score++;
                emit collectEgg();
            }else{
                life--;
                if(life <= 0)
                    emit GameOver();
                else
                    emit lostEgg(eggs->value(i)->layer == 1 || eggs->value(i)->layer == 2);

            }

            eggs->remove(i);
        }
    }
}

Egg::Egg(int layer, int speed)
{
    this->layer = layer;
    this->pos = 1;
    this->speed = speed;
}
