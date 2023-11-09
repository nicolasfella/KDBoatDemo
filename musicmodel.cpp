#include "musicmodel.h"

#include <QTextStream>
#include <QDebug>
#include <QFile>
#include <QTextCodec>

MusicModel::MusicModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int MusicModel::rowCount(const QModelIndex &parent) const
{
    return m_data.count();
}

QVariant MusicModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if (row < 0 || row > rowCount()) {
        return {};
    }

    if (role == NameRole) {
        return m_data[row].name;
    } else if (role == FormattedDurationRole) {

        int minutes = m_data[row].minutes;
        int seconds = m_data[row].seconds;

        QString result;
        if (minutes < 10) {
            result += "0" + QString::number(minutes);
        } else {
            result += QString::number(minutes);
        }

        result += ":";

        if (seconds < 10) {
            result += "0" + QString::number(seconds);
        } else {
            result += QString::number(seconds);
        }

        return result;
    } else if (role == AlbumRole) {
        return m_data[row].album;
    } else if (role == CoverRole) {
        return m_data[row].cover;
    }

    return {};
}

QHash<int, QByteArray> MusicModel::roleNames() const
{
    return {
        { NameRole, "name" },
        { FormattedDurationRole, "duration" },
        { AlbumRole, "album" },
        { CoverRole, "cover" },
    };
}

QUrl MusicModel::sourceFile() const
{
    return m_sourceFile;
}

void MusicModel::setSourceFile(const QUrl &path)
{
    m_sourceFile = path;

    load(path.toString().remove(QRegExp("^qrc")));
}

void MusicModel::load(const QString &path)
{
    QFile file(path);
    bool open = file.open(QIODevice::ReadOnly);

    if (!open) {
        qWarning() << "Could not open file" << path;
    }

    QTextStream input(&file);
    input.setCodec(QTextCodec::codecForName("UTF-8"));

    while (!input.atEnd()) {
        QString line = input.readLine();

        Data data;
        data.name = line.left(line.indexOf(":"));

        QStringRef propsString = line.midRef(line.indexOf(":") + 1);
        QVector<QStringRef> props = propsString.split(";");

        for (const QStringRef prop : props) {
            if (prop.left(prop.indexOf("=")) == "cover") {
                data.cover = prop.mid(prop.indexOf("=") + 1).toString();
            } else if (prop.left(prop.indexOf("=")) == "duration") {
                QString duration = prop.mid(prop.indexOf("=") + 1).toString();

                QRegExp numbers("(\\d+):(\\d+)");
                numbers.indexIn(duration);

                data.minutes = numbers.cap(1).toInt();
                data.seconds = numbers.cap(2).toInt();
            } else if (prop.left(prop.indexOf("=")) == "album") {
                data.album = prop.mid(prop.indexOf("=") + 1).toString();
            }
        }

        m_data << data;
    }

    Q_EMIT sourceFileChanged();
}

void MusicModel::printAlbums() const
{
    QMap<QString, QString> albumMap;

    for (const Data &data : qAsConst(m_data)) {
        albumMap.insertMulti(data.album, data.name);
    }

    for (const QString &key : albumMap.uniqueKeys()) {
        qWarning() << "Album" << key << " has songs" << albumMap.values(key);
    }
}
