#include "game.h"

Game::Game(bool typeA)
{
    style = typeA;
    eggs = new QVector<Egg*>;
}

void Game::tapEvent(bool left_wolf, bool top_basket)
{
    this->player_wolf = left_wolf;
    this->player_basket = top_basket;
}

void Game::Play()
{

}

Egg::Egg(int layer, int speed)
{
    this->layer = layer;
    this->speed = speed;
}

void Game::newEgg()
{
    eggs->push_back(new Egg(rand()%4, 1));
}
