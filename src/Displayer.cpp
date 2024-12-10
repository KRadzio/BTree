#include "Displayer.hpp"

Displayer::Displayer() {}
Displayer::~Displayer() {}

Displayer &Displayer::GetInstance()
{
    static Displayer *instance = new Displayer;
    return *instance;
}

void Displayer::DiplayTree() {}
void Displayer::DiplayData() {}