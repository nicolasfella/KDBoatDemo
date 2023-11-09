#pragma once

#include <QAbstractListModel>
#include <QUrl>

class MusicModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QUrl sourceFile READ sourceFile WRITE setSourceFile NOTIFY sourceFileChanged)
public:
    enum Roles {
        NameRole = Qt::DisplayRole,
        FormattedDurationRole = Qt::UserRole + 1,
        AlbumRole,
        CoverRole,
    };
    Q_ENUM(Roles)

    MusicModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = {}) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    QUrl sourceFile() const;
    void setSourceFile(const QUrl &url);
    Q_SIGNAL void sourceFileChanged();

    void load(const QString &path);
    void printAlbums() const;

private:
    struct Data
    {
        QString name;
        int minutes;
        int seconds;
        QString album;
        QString cover;
    };

    QList<Data> m_data;
    QUrl m_sourceFile;
};
