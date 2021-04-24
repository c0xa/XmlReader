#include "mainwindow.h"
#include "cake.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _model = new Cake(this);
    _model->addCakeAndCandy(1, "medovic");
    _model->addCakeAndCandy(1, "chizkek");
    ui->tableView->setModel(_model);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAddCake_triggered()
{
    _model->addCakeAndCandy(ui->lineEdit->text().toInt(),
                            ui->lineEdit_2->text());
}

void MainWindow::on_actionDeleteCake_triggered()
{
    _model->deleteCakeAndCandy(ui->tableView->currentIndex().row());
}

void MainWindow::on_actionEditCake_triggered()
{
    _model->editCakeAndCandy(ui->tableView->currentIndex().row(), ui->lineEdit->text().toInt(),
                             ui->lineEdit_2->text());
}

void MainWindow::on_actionreadFromXml_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "select file");
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
        return;
    QByteArray data = file.readAll();
    _model->deserializeXML(QString(data));
    file.close();
}

void MainWindow::on_actionsaveToXml_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "select file");
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly))
        return;
    QByteArray data;
    data = _model->serializeXML().toUtf8();
    file.write(data);
    file.close();

}













