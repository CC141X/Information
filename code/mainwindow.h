#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QAction;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
//    void closeEvent(QCloseEvent *event);

protected slots:
    void newFile();
    void open();
    bool save();
//    bool saveAs();
//    void find();
//    void gotoLine();
//    void sort();
//    void about();
//    void openRecentFile();
//    void updateStatusBar();
//    void spreadsheetModified();

private:
    Ui::MainWindow *ui;
    enum { emMaxRecentFile = 5 };
    QAction* recentFileActions[emMaxRecentFile];

    void createActions();
    void createContextActions();
    void createToolBar();
};

#endif // MAINWINDOW_H
