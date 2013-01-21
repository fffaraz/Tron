#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QColor>

#include "tronserver.h"
#include "mapdrawer.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void tronGameOver(int Player);
    void tronMapUpdated();
    void on_btnCreate_clicked();
    void on_btnStart_clicked();
    void on_btnStop_clicked();
    void on_confUpload_clicked();

private:
    Ui::MainWindow *ui;
    TronServer *server;
    MapDrawer *drawer;
    void popUp(QString str);
};

#endif // MAINWINDOW_H
