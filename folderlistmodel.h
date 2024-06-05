#ifndef FOLDERLISTMODEL_H
#define FOLDERLISTMODEL_H

#include <QAbstractListModel>
#include <QSettings>

class FolderListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit FolderListModel(QObject *parent = nullptr);

    enum { PathRole = Qt::UserRole };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

signals:
    void postItemAppended();

private:
    QSettings *settings;
};

#endif // FOLDERLISTMODEL_H
