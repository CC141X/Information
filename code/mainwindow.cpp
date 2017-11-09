#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createActions();
    //createMenus();
    createContextActions();
    createToolBar();

    setWindowIcon(QIcon(":/resources/images/logo_lefttop.png"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
/**
 * @brief MainWindow::createActions
 * @date 2017/11/9
 */
void MainWindow::createActions()
{
    //文件菜单
    ui->action_New->setIcon(QIcon(":/resources/images/new.png"));
    ui->action_New->setStatusTip(tr("Create a new file."));
    connect(ui->action_New, SIGNAL(triggered(bool)), this, SLOT(newFile()));
    ui->action_Open->setIcon(QIcon(":/resources/images/open.png"));
    ui->action_Open->setStatusTip(tr("Open a file."));
    connect(ui->action_Open, SIGNAL(triggered(bool)), this, SLOT(open()));
    ui->action_Save->setIcon(QIcon(":/resources/images/save.png"));
    ui->action_Save->setStatusTip(tr("Save a file."));
    connect(ui->action_Save, SIGNAL(triggered(bool)), this, SLOT(save()));

    for(int i = 0; i < emMaxRecentFile; ++i)
    {
        recentFileActions[i] = new QAction(this);
        recentFileActions[i]->setVisible(false);
        ui->menu_File->addAction(recentFileActions[i]);
        connect(recentFileActions[i], SIGNAL(triggered()), this, SLOT(openRecentFile()));
    }

    ui->action_Exit->setStatusTip(tr("Exit the application."));
    connect(ui->action_Exit, SIGNAL(triggered(bool)), this, SLOT(close()));
    //编辑菜单
    ui->action_Cut->setIcon(QIcon(":/resources/images/cut.png"));
    ui->action_Cut->setStatusTip(tr("Cut."));
    connect(ui->action_Cut, SIGNAL(triggered(bool)), this, SLOT(cut()));
    ui->action_Copy->setIcon(QIcon(":/resources/images/copy.png"));
    ui->action_Copy->setStatusTip(tr("Copy."));
    connect(ui->action_Copy, SIGNAL(triggered(bool)), this, SLOT(copy()));
    ui->action_Paste->setIcon(QIcon(":/resources/images/paste.png"));
    ui->action_Paste->setStatusTip(tr("Paste."));
    connect(ui->action_Paste, SIGNAL(triggered(bool)), this, SLOT(paste()));

    ui->action_All->setStatusTip(tr("Select all the cells int the spreadsheet."));
    connect(ui->action_All, SIGNAL(triggered(bool)), ui->mainTableWidget, SLOT(selectAll()));

    ui->action_ShowGrid->setChecked(ui->mainTableWidget->showGrid());
    ui->action_ShowGrid->setStatusTip(tr("Show or hide the table grid."));
    connect(ui->action_ShowGrid, SIGNAL(toggled(bool)), ui->mainTableWidget, SLOT(setShowGrid(bool)));
    //帮助菜单
    ui->action_About->setStatusTip(tr("Show the Information Library's About box."));
    connect(ui->action_About, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt()));
}
/**
 * @brief MainWindow::createContextActions
 * @date 2017/11/9
 */
void MainWindow::createContextActions()
{
    ui->mainTableWidget->addAction(ui->action_Cut);
    ui->mainTableWidget->addAction(ui->action_Copy);
    ui->mainTableWidget->addAction(ui->action_Paste);
    ui->mainTableWidget->setContextMenuPolicy(Qt::ActionsContextMenu);//显示这些动作
}

/**
 * @brief MainWindow::createToolBar
 * @date 2017/11/9
 */
void MainWindow::createToolBar()
{
    ui->mainToolBar->addAction(ui->action_New);
    ui->mainToolBar->addAction(ui->action_Open);
    ui->mainToolBar->addAction(ui->action_Save);
    ui->mainToolBar->addSeparator();//分隔符
    ui->mainToolBar->addAction(ui->action_Cut);
    ui->mainToolBar->addAction(ui->action_Copy);
    ui->mainToolBar->addAction(ui->action_Paste);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(ui->action_Find);
}

void MainWindow::newFile()
{
    qDebug("[%s, %s]", __DATE__, __FUNCTION__);
}

void MainWindow::open()
{
    qDebug("[%s, %s]", __DATE__, __FUNCTION__);
}

bool MainWindow::save()
{
    qDebug("[%s, %s]", __DATE__, __FUNCTION__);
    return true;
}
