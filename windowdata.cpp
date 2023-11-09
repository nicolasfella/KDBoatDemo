#include "windowdata.h"

#include <QDesktopWidget>
#include <QApplication>

WindowData::WindowData(bool portrait)
    : QObject()
    , m_portrait(portrait)
{
    QSize screenSize = QApplication::desktop()->size();
    m_lowResn = screenSize.width() < 1280 || screenSize.height() < 720;
}

int WindowData::width() const
{
    if (m_lowResn) {
        return m_portrait ? 480 : 800;
    } else {
        return m_portrait ? 720 : 1280;
    }
}

int WindowData::height() const
{
    if (m_lowResn) {
        return m_portrait ? 800 : 400;
    } else {
        return m_portrait ? 1280 : 720;
    }
}

bool WindowData::isLowRes() const
{
    return m_lowResn;
}
