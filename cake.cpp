#include "cake.h"

Cake::Cake(QObject *parent) : QAbstractTableModel(parent) {}

int Cake::columnCount(const QModelIndex &parent) const
{
	(void)parent;
	return 2;
}

int Cake::rowCount(const QModelIndex &parent) const
{
	(void)parent;
	return _CakeAndCandy.size();
}

QVariant Cake::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();
	if (role == Qt::DisplayRole) {
		switch (index.column()) {
		case 0:
			return _CakeAndCandy[index.row()].id;
		case 1:
			return _CakeAndCandy[index.row()].name;
		}
	}

	if (role == Qt::DecorationRole) {
		if (index.row() % 2 == 0)
		{
			return QColor("#999999");
		}
		else
		{
			return QColor("#000099");
		}

	}

	if (role == Qt::ToolTipRole) {
		switch (index.column()) {
		case 0:
			return QString("Cake: " + _CakeAndCandy[index.row()].name);
		}
	}
	return QVariant();
}

QVariant Cake::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation == Qt::Horizontal)
	{
		if (role == Qt::DisplayRole) {
			switch (section) {
			case Cid:
				return "id";
			case Cname:
				return "name";
			}
		}
	}
	return QAbstractItemModel::headerData(section, orientation, role);
}

void Cake::addCakeAndCandy(int id, const QString &name)
{
	beginInsertRows(QModelIndex(), _CakeAndCandy.size(), _CakeAndCandy.size());
	CakeAndCandy s;
	s.id = id;
	s.name = name;
	_CakeAndCandy.append(s);
	endInsertRows();
}

void Cake::deleteCakeAndCandy(int row)
{
	if (row < 0)
		return;
	if (!_CakeAndCandy.size())
		return;
	beginRemoveRows(QModelIndex(), row, row);
	_CakeAndCandy.removeAt(row);
	endRemoveRows();

}

void Cake::editCakeAndCandy(int row, int id, const QString &name)
{
	if (row < 0)
		return;
	CakeAndCandy s;
	s.id = id;
	s.name = name;
	_CakeAndCandy[row] = s;
	emit dataChanged(index(row, Cid), index(row, Cname));
	}

bool Cake::setData(const QModelIndex &index, const QVariant &value, int role)
{
	(void)role;
	switch (index.column()) {
		case Cid:
			_CakeAndCandy[index.row()].id = value.toInt();
		case Cname:
			_CakeAndCandy[index.row()].name = value.toString();
	}
	emit dataChanged(index, index);
	return true;
}

Qt::ItemFlags Cake::flags(const QModelIndex &index) const
{
	return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

QString Cake::serializeXML()
{
	QDomDocument document;
	QDomElement root = document.createElement("CakeDataBase");
	document.appendChild(root);
	for (CakeAndCandy s: _CakeAndCandy)
	{
		QDomElement cakeElement = document.createElement("Cake");
		QDomElement id = document.createElement("id");
		id.appendChild(document.createTextNode(QString::number(s.id)));
		cakeElement.appendChild(id);
		QDomElement name = document.createElement("Name");
		name.appendChild(document.createTextNode(s.name));
		cakeElement.appendChild(name);
		root.appendChild(cakeElement);
		}
	return document.toString();
}

void Cake::deserializeXML(const QString &xml)
{
	beginResetModel();
	_CakeAndCandy.clear();
	QDomDocument document;
	if (!document.setContent(xml))
		return;
	QDomElement root = document.firstChildElement("CakeDataBase");
	QDomElement cakeElement = root.firstChildElement("Cake");

	while (!cakeElement.isNull())
	{
		CakeAndCandy s;
		QDomElement id = cakeElement.firstChildElement("id");
		s.id= id.firstChild().nodeValue().toInt();
		QDomElement name = cakeElement.firstChildElement("Name");
		s.name= name.firstChild().nodeValue();
		_CakeAndCandy.append(s);
		cakeElement = cakeElement.nextSiblingElement("Cake");
	}
	endResetModel();
}










