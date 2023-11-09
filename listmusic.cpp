#include "musicmodel.h"

int main()
{
    MusicModel model;
    model.load(":/resources/music.txt");
    model.printAlbums();
}
