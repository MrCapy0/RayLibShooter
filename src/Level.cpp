#include "Level.h"
#include "Game.h"
#include "Player.h"

#include <iostream>
#include <memory>

std::unique_ptr<G::Player> player;

G::Level::Level()
{
}

void G::Level::Setup()
{
    player = Game::AddActor<Player>();
}

void G::Level::Update(float delta)
{
}
