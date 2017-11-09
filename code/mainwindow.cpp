#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createActions();
    setWindowIcon(QIcon(":/resources/images/logo_lefttop.png"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createActions()
{
    ui->action_New->setIcon(QIcon(":/resources/images/new.png"));
    ui->action_New->setStatusTip(tr("Create a new file."));
    connect(ui->action_New, SIGNAL(triggered(bool)), this, SLOT(newFile()));

    for(int i = 0; i < emMaxRecentFile; ++i)
    {
        recentFileActions[i] = new QAction(this);
        recentFileActions[i]->setVisible(false);
        connect(recentFileActions[i], SIGNAL(triggered()), this, SLOT(openRecentFile()));
    }
}

void MainWindow::newFile()
{

}
