#include "finddialog.h"
#include "ui_finddialog.h"

FindDialog::FindDialog(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::FindDialog)
{
    ui->setupUi(this);

    connect(ui->findLineEdit, SIGNAL(textChanged(const QString&)), this,
            SLOT(enableFindButton(const QString&)));
    connect(ui->findPushButton, SIGNAL(clicked()), this, SLOT(findClicked()));
    connect(ui->closePushButton, SIGNAL(clicked()), this, SLOT(close()));

    setFixedHeight(sizeHint().height());//设置固定高度
}

FindDialog::~FindDialog()
{
    delete ui;
}

void FindDialog::findClicked()
{
    QString text = ui->findLineEdit->text();
    Qt::CaseSensitivity cs = ui->caseCheckBox->isCheckable() ? Qt::CaseSensitive :
                                                           Qt::CaseInsensitive;
    if(ui->backwardCheckbox->isChecked())
        emit findPrevious(text, cs);
    else
        emit findNext(text, cs);
}

void FindDialog::enableFindButton(const QString &text)
{
    ui->findPushButton->setEnabled(!text.isEmpty());
}
