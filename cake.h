#ifndef CAKE_H
#define CAKE_H
#include <QAbstractTableModel>
#include <QColor>
#include <QFile>
#include <QFileDialog>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QMainWindow>
#include <QDomDocument>
#include <QDomNode>
#include <QDomElement>

struct CakeAndCandy{
    int id;
    QString name;
};

class Cake: public QAbstractTableModel
{
    Q_OBJECT
public:

    enum Column {
        Cid,
        Cname,
        Ccount
    };
    Cake(QObject * parent = nullptr);


    int columnCount(const QModelIndex &parent) const;
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
//    virtual QModelIndex Index(int row, int column, const QModelIndex &parent = QModelIndex()) const = 0;
    void addCakeAndCandy(int id, const QString &name);
    void deleteCakeAndCandy(int row);
    void editCakeAndCandy(int row, int id, const QString &name);
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;
    QString serializeXML();
    void deserializeXML(const QString &xml);
private:
    QVector<CakeAndCandy> _CakeAndCandy;
};

#endif // CAKE_H
