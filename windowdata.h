#pragma once

#include <QObject>

class WindowData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int width READ width CONSTANT)
    Q_PROPERTY(int height READ height CONSTANT)
    Q_PROPERTY(bool isLowRes READ isLowRes CONSTANT)

public:
    WindowData(bool portrait);

    int width() const;
    int height() const;
    bool isLowRes() const;

private:
    bool m_portrait;
    bool m_lowResn;
};
