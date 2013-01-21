#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->cmbPlayer->addItem("1");
    ui->cmbPlayer->addItem("2");
    m_agent =0;
    m_client=0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnStart_clicked()
{
    if(m_client) m_client->deleteLater();
    if(m_agent) m_agent->deleteLater();

    m_agent = new Agent(ui->cmbPlayer->currentText().toInt());
    m_client = new TronClient(m_agent, this);
    drawer = new MapDrawer(m_client->GetMap());
    connect(m_client, SIGNAL(MapUpdated()), drawer, SLOT(repaint()));
    ui->grDrawer->addWidget(drawer);
    ui->btnStart->setText("reStart");
}
