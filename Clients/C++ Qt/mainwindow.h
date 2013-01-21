#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "tronclient.h"
#include "mapdrawer.h"
#include "agent.h"

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
    void on_btnStart_clicked();

private:
    Ui::MainWindow *ui;
    Agent* m_agent;
    TronClient* m_client;
    MapDrawer* drawer;
};

#endif // MAINWINDOW_H
