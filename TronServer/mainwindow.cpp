#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon("favicon.ico"));
    server = 0;
    drawer = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnCreate_clicked()
{
    if (server!=0) server->deleteLater();
    server = new TronServer(ui->txtIP1->text(), ui->txtIP2->text(),ui->mapWidth->value(),ui->mapHeight->value(), ui->blockNum->value(), this);
    connect(server,SIGNAL(GameOver(int)), this, SLOT(tronGameOver(int)));
    connect(server, SIGNAL(MapUpdated()), this, SLOT(tronMapUpdated()));
    ui->btnStart->setEnabled(true);
    if(drawer!=0)
    {
        ui->grDrawer->removeWidget(drawer);
        drawer->deleteLater();
    }
    drawer = new MapDrawer(server->GetMap(), this);
    ui->grDrawer->addWidget(drawer);
    drawer->repaint();
}

void MainWindow::on_btnStart_clicked()
{
    server->Start(ui->txtInterval->text().toInt());
    ui->btnStart->setEnabled(false);
    ui->btnStop->setEnabled(true);
}

void MainWindow::on_btnStop_clicked()
{
    server->Stop();
    ui->btnStart->setEnabled(true);
    ui->btnStop->setEnabled(false);
}

void MainWindow::tronGameOver(int Player)
{
    qDebug() << "Game Over" << Player;
    ui->btnStart->setEnabled(true);
    ui->btnStop->setEnabled(false);
    if(Player==3)
        popUp("Tie!");
    else if(Player==2)
        popUp("Player 1 Won!");
    else
        popUp("Player 2 Won!");
}

void MainWindow::tronMapUpdated()
{
    drawer->repaint();
}

void MainWindow::on_confUpload_clicked()
{
    QString str=QFileDialog::getOpenFileName(this,tr("Open Configuration File"), "", tr("Tron Configuration Files (*.txt)"));
    if(str!="" && server!=0)
    {
        server->LoadMap(str);
        ui->mapWidth->setValue(server->GetMap()->MapSize.X);
        ui->mapHeight->setValue(server->GetMap()->MapSize.Y);
    }
}

void MainWindow::popUp(QString str)
{
    QMessageBox *pop = new QMessageBox(this);
    pop->setText(str);
    pop->setIcon(QMessageBox::Information);
    pop->open();
}
