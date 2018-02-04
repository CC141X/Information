#include <QLabel>
#include <QMessageBox>
#include <QFileDialog>
#include <QSettings>

#include "mainwindow.h"
#include "maintablewidget.h"
#include "gotolinedialog.h"
#include "finddialog.h"
#include "ui_mainwindow.h"
#include "common/commondefine.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_mainTableWidget(0),
    m_findDlg(0)
{
    ui->setupUi(this);
    m_mainTableWidget = new MainTableWidget(this);
    setCentralWidget(m_mainTableWidget);

    readSettings();

    createActions();
    //createMenus();
    createContextActions();
    createToolBar();
    createStatusBar();

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
    connect(ui->action_All, SIGNAL(triggered(bool)), m_mainTableWidget, SLOT(selectAll()));

    ui->action_Find->setStatusTip(tr("Find the specified content"));
    connect(ui->action_Find, SIGNAL(triggered(bool)), this, SLOT(find()));
    ui->action_GotoLine->setStatusTip(tr("Go to line"));
    connect(ui->action_GotoLine, SIGNAL(triggered(bool)), this, SLOT(gotoLine()));

    ui->action_ShowGrid->setChecked(m_mainTableWidget->showGrid());
    ui->action_ShowGrid->setStatusTip(tr("Show or hide the table grid."));
    connect(ui->action_ShowGrid, SIGNAL(toggled(bool)), m_mainTableWidget, SLOT(setShowGrid(bool)));
    //帮助菜单
    ui->action_About->setStatusTip(tr("Show the Information Library's About box."));
    connect(ui->action_About, SIGNAL(triggered(bool)), this, SLOT(about()));
}
/**
 * @brief MainWindow::createContextActions
 * @date 2017/11/9
 */
void MainWindow::createContextActions()
{
    m_mainTableWidget->addAction(ui->action_Cut);
    m_mainTableWidget->addAction(ui->action_Copy);
    m_mainTableWidget->addAction(ui->action_Paste);
    m_mainTableWidget->setContextMenuPolicy(Qt::ActionsContextMenu);//显示这些动作
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

/**
 * @brief MainWindow::createStatusBar
 * @date 2017/11/11
 */
void MainWindow::createStatusBar()
{
    m_labelStatusBarLocation = new QLabel("W999");//设置大小
    m_labelStatusBarLocation->setAlignment(Qt::AlignCenter);
    m_labelStatusBarLocation->setMinimumSize(m_labelStatusBarLocation->sizeHint());

    m_labelStatusBarContent = new QLabel;
    m_labelStatusBarContent->setIndent(3);//设置偏移量

    statusBar()->addWidget(m_labelStatusBarLocation);
    statusBar()->addWidget(m_labelStatusBarContent, 1);//伸展因子为1

    connect(m_mainTableWidget, SIGNAL(currentCellChanged(int,int,int,int)),
           this, SLOT(updateStatusBar()));
    connect(m_mainTableWidget, SIGNAL(modified()), this, SLOT(mainTableWidgetModified()));

    updateStatusBar();
}

/**
 * @brief MainWindow::updateStatusBar
 * @date 2017/11/11
 */
void MainWindow::updateStatusBar()
{
    m_labelStatusBarLocation->setText("loation"/*ui->mainTableWidget->currentItemLocation()*/);
    m_labelStatusBarContent->setText("content"/*ui->mainTableWidget->currentItemContent()*/);
}

/**
 * @brief MainWindow::mainTableWidgetModified
 * @date 2017/11/11
 */
void MainWindow::mainTableWidgetModified()
{
    setWindowModified(true);
    updateStatusBar();
}

/**
 * @brief MainWindow::newFile
 * @date 2017/11/11
 */
void MainWindow::newFile()
{
    if(okToContinue())
    {
        m_mainTableWidget->clear();
        setCurrentFile("");
    }
}

/**
 * @brief MainWindow::open
 * @date 2017/11/11
 */
void MainWindow::open()
{
    if(okToContinue())
    {
        //第三个参数指定从哪一级目录开始打开
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), tr("."),
                                                        tr("Infomation table file (*.info)\n"
                                                           "Comma-separated values files (*.csv)"));
        if(!fileName.isEmpty())
            loadFile(fileName);
    }
}

bool MainWindow::save()
{
    qDebug("[%s, %s]", __DATE__, __FUNCTION__);
    m_mainTableWidget->writeFile("test");
    return true;
}

/**
 * @brief MainWindow::okToContinue
 * @date 2017/11/11
 */
bool MainWindow::okToContinue()
{
    if(isWindowModified())
    {
        int r = QMessageBox::warning(this, tr("MainTableSheet"),
                tr("The document has been modified.\nDo you want to save your changes?"),
                QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if(QMessageBox::Yes == r){
            return save();
        }else if(QMessageBox::Cancel){
            return false;
        }
    }
    return true;
}

/**
 * @brief MainWindow::setCurrentFile
 * @date 2017/11/11
 * @param file
 */
void MainWindow::setCurrentFile(const QString &file)
{
    qDebug("[%s, %s]", __DATE__, __FUNCTION__);
}

/**
 * @brief MainWindow::loadFile
 * @date 2017/11/11
 * @param file
 */
bool MainWindow::loadFile(const QString &file)
{
    qCritical("[%s, %s]", __DATE__, __FUNCTION__);
    if(true/*!ui->mainTableWidget->readFile(file)*/)
    {
        statusBar()->showMessage(tr("Loading cancel"), 2000);//显示2秒
        return false;
    }

    setCurrentFile(file);
    statusBar()->showMessage(tr("File load"), 2000);
    return true;
}

/**
 * @brief MainWindow::find
 * @date 2017/11/11
 */
void MainWindow::find()
{
    qDebug("[%s, %s] - begin", __DATE__, __FUNCTION__);
    if(!m_findDlg)
    {
        m_findDlg = new FindDialog(this);

//        connect(m_findDlg, SIGNAL(findNext(QString,Qt::CaseSensitivity)),
//                ui->mainTableWidget, SLOT(findNext(QString,Qt::CaseSensitivity)));
//        connect(m_findDlg, SIGNAL(findPrevious(QString,Qt::CaseSensitivity)),
//                ui->mainTableWidget, SLOT(findPrevious(QString,Qt::CaseSensitivity)));
    }
    m_findDlg->show();
    m_findDlg->raise();//顶层
    m_findDlg->activateWindow();//活动
    qDebug("[%s, %s] - end", __DATE__, __FUNCTION__);
}

/**
 * @brief MainWindow::gotoLine
 * @date 2017/11/11
 */
void MainWindow::gotoLine()
{
    qDebug("[%s, %s] - begin", __DATE__, __FUNCTION__);
    GotoLineDialog gotoDlg(this);
    if(gotoDlg.exec())
    {
        QString str = gotoDlg.getLineEditText().toUpper();
    }
    qDebug("[%s, %s] - end", __DATE__, __FUNCTION__);
}

/**
 * @brief MainWindow::sort
 * @date 2017/11/11
 */
void MainWindow::sort()
{
    qDebug("[%s, %s] - begin", __DATE__, __FUNCTION__);
    //SortDialog sortDlg(this);
    QList<QTableWidgetSelectionRange> range = m_mainTableWidget->selectedRanges();
    //sortDlg.setColumnRange('A' + range.leftColumn(), 'A' + range.rightColumn());
    //if(sortDlg.exec()){
    //    ui->mainTableWidget->performSort(sortDlg.comparisonObject());
    //}
    qDebug("[%s, %s] - end", __DATE__, __FUNCTION__);
}

/**
 * @brief MainWindow::about
 * @date 2017/11/11
 */
void MainWindow::about()
{
    QMessageBox::about(this, tr("About Information"),
                       tr("<h2>Information 1.1</h2>"
                          "<p>Copyright &copy; 2017 Software Inc."
                          "<p>Information is a learning application that "
                          "demonstrates all kinds of knowledges."));
}

/**
 * @brief MainWindow::closeEvent
 * @date 2017/11/11
 * @param event
 */
void MainWindow::closeEvent(QCloseEvent *event)
{
    writeSettings();
}

/**
 * @brief MainWindow::writeSettings
 * @date 2017/11/11
 */
void MainWindow::writeSettings()
{
    QSettings settings(tr(chstrSettings[emComimutyName], chstrSettings[emApplicationName]));//组织名称和应用名称
    settings.setValue(chstrSettings[emMainWindowGeometry], saveGeometry());//几何尺寸
    settings.setValue("recentFiles", recentFiles);
    settings.setValue(chstrSettings[emShowGrid], ui->action_ShowGrid->isChecked());
}

/**
 * @brief MainWindow::readSettings
 * @date 2017/11/11
 */
void MainWindow::readSettings()
{
    QSettings settings(tr(chstrSettings[emComimutyName], chstrSettings[emApplicationName]));//组织名称和应用名称

    restoreGeometry(settings.value(chstrSettings[emMainWindowGeometry]).toByteArray());
    recentFiles = settings.value(chstrSettings[emRecentOpenedFiles]).toStringList();
    updateRecentFileActions();
    ui->action_ShowGrid->setChecked(settings.value(chstrSettings[emShowGrid], true).toBool());//设置默认值true
}

/**
 * @brief MainWindow::updateRecentFileActions
 * @date 2017/11/11
 */
void MainWindow::updateRecentFileActions()
{
qDebug("[%s, %s] - begin", __DATE__, __FUNCTION__);
}
