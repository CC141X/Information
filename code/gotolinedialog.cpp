#include "gotolinedialog.h"
#include "ui_gotolinedialog.h"
#include <QPushButton>

GotoLineDialog::GotoLineDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GotoLineDialog)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

    ui->gotoLineEdit->setValidator(new QIntValidator(1, 2147483647, this));

    connect(ui->gotoLineEdit, SIGNAL(textChanged(const QString&)), this,
            SLOT(onLineEditTextChanged()));
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

GotoLineDialog::~GotoLineDialog()
{
    delete ui;
}

void GotoLineDialog::onLineEditTextChanged()
{
  ui->buttonBox->button(QDialogButtonBox::Ok)->
      setEnabled(ui->gotoLineEdit->hasAcceptableInput());
}

QString GotoLineDialog::getLineEditText()
{
    return ui->gotoLineEdit->text();
}
