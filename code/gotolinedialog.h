#ifndef GOTOLINEDIALOG_H
#define GOTOLINEDIALOG_H

#include <QDialog>

namespace Ui {
class GotoLineDialog;
}

class GotoLineDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GotoLineDialog(QWidget *parent = 0);
    virtual ~GotoLineDialog();
    QString getLineEditText();

private slots:
    void onLineEditTextChanged();

private:
    Ui::GotoLineDialog *ui;
};

#endif // GOTOLINEDIALOG_H
