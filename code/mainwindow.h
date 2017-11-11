#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QAction;
class QLabel;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QStringList recentFiles;

protected:
    void closeEvent(QCloseEvent *event);
    void writeSettings();
    void readSettings();

protected slots:
    void newFile();
    void open();
    bool save();
//    bool saveAs();
    void find();
    void gotoLine();
    void sort();
    void about();
//    void openRecentFile();
    void updateStatusBar();
//    void spreadsheetModified();

private:
    Ui::MainWindow *ui;

    enum { emMaxRecentFile = 5 };

    QAction* recentFileActions[emMaxRecentFile];
    QLabel* m_labelStatusBarLocation;
    QLabel* m_labelStatusBarContent;
    QDialog* m_findDlg;

    void createActions();
    void createContextActions();
    void createToolBar();
    void createStatusBar();

    void mainTableWidgetModified();
    bool okToContinue();
    void setCurrentFile(const QString& file);
    bool loadFile(const QString& file);
    void updateRecentFileActions();
};

#endif // MAINWINDOW_H
