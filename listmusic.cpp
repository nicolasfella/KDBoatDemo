#include "musicmodel.h"

#include <QTest>

int main()
{
    MusicModel model;
    model.load(QFINDTESTDATA("resources/music.txt"));
    model.printAlbums();
}
