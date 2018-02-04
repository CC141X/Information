#include <QMessageBox>
#include <QFileInfo>
#include "maintablewidget.h"
#include "ui_maintablewidget.h"
//#include "cell.h"

MainTableWidget::MainTableWidget(QWidget *parent) :
    QTableWidget(parent),
    ui(new Ui::MainTableWidget)
{
    ui->setupUi(this);

//    autoRecalc = true;

//    setItemPrototype(new Cell);//重新创建单元格
//    setSelectionMode(ContiguousSelection);//矩形选择框
//    connect(this, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(somethingChanged()));

    clear();
}

MainTableWidget::~MainTableWidget()
{
    delete ui;
}

/**
 * @brief MainTableWidget::clear
 * @date 2017/11/12
 */
void MainTableWidget::clear()
{
    //清空
    setRowCount(0);
    setColumnCount(0);
    //重新调整
    setRowCount(emRowCount);
    setColumnCount(emColumnCount);
    //设置表头
    for(int i = 0; i < emColumnCount; ++i)
    {
        QTableWidgetItem* item = new QTableWidgetItem;
        item->setText(QString(QChar('A' + i)));
        setHorizontalHeaderItem(i, item);
    }
    setCurrentCell(0,0);//移动光标
}

//Cell* MainTableWidget::cell(int row, int column) const
//{
//    return static_cast<Cell*>(item(row, column));
//}

//QString MainTableWidget::text(int row, int column) const
//{
//    Cell* c = cell(row, column);
//    if(c){
//        return c->text();
//    }else{
//        return "";
//    }
//}

//QString MainTableWidget::formula(int row, int column) const
//{
//    Cell* cell(row, column);
//    if(c){
//        return c->formula();
//    }else{
//        return "";
//    }
//}

//void MainTableWidget::setFormula(int row, int column, const QString& formula)
//{
//    Cell* c = cell(row, column);
//    if(!c){
//        c = new Cell;
//        setItem(row, column, c);
//    }
//    c->setFormula(formula);
//}

/**
 * @brief MainTableWidget::currentLocation
 * @date 2017/11/12
 * @return current location
 */
QString MainTableWidget::currentLocation() const
{
    return QChar('A' + currentColumn()) + QString::number(currentRow() + 1);
}

//QString MainTableWidget::currentFormula() const
//{
//    return formula(currentRow(), currentColumn());
//}

//void MainTableWidget::somethingChanged()
//{
//    if(autoRecalc){
//        recalculate();
//    }
//    emit modified();
//}

bool MainTableWidget::writeFile(const QString& fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(this, tr("Information"),
                             tr("Cannot write file %1:\n%2.").arg(file.fileName())
                             .arg(file.errorString()));
        return false;
    }
    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_4_3);//qt版本
    out << quint32(emMagicNumber);//文件标志,32位，保证通用
    QApplication::setOverrideCursor(Qt::WaitCursor);//设置鼠标指针等待状态
    for(int row = 0; row < emRowCount; ++row)
    {
        for(int column = 0; column < emColumnCount; ++column)
        {
            QString str = "test";//formula(row, column);
            if(!str.isEmpty()){
                out << quint16(row) << quint16(column) << str;
            }
        }
    }
    QApplication::restoreOverrideCursor();
    return true;
}

bool MainTableWidget::readFile(const QString& fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, tr("Information"),
                             tr("Cannot read file %1:\n%2.").arg(file.fileName())
                             .arg(file.errorString()));
        return false;
    }
    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_4_3);

    quint32 magic;
    in >> magic;
    if(emMagicNumber != magic)
    {
        QMessageBox::warning(this, tr("Information"), tr("The file is not a Information file."));
        return false;
    }
    clear();

    quint16 row, column;
    QString str;
    QApplication::setOverrideCursor(Qt::WaitCursor);
    while(!in.atEnd())
    {
        in >> row >> column >> str;
//        setFormula(row, column, str);
    }
    QApplication::restoreOverrideCursor();
    return true;
}

void MainTableWidget::cut()
{
    copy();
    del();
}

void MainTableWidget::copy()
{
//    QTableWidgetSelectionRange range = selectedRange();
//    QString str;
//    for(int i = 0; i < range.rowCount(); ++i)
//    {
//        if(i > 0)
//        {
//            str += "\n";
//        }
//        for(int j = 0; j < range.columnCount(); ++j)
//        {
//            if(j > 0){
//                str += "\t";
//            }
//            str += formula(range.topRow() + i, range.leftColumn() + j);
//        }
//    }
//    QApplication::clipboard()->setText(str);//剪贴板
}

QTableWidgetSelectionRange MainTableWidget::selectedRange() const
{
    QList<QTableWidgetSelectionRange> ranges = selectedRanges();
    if(ranges.isEmpty()){
        return QTableWidgetSelectionRange();
    }
    return ranges.first();
}

void MainTableWidget::paste()
{
//    QTableWidgetSelectionRange range = selectedRange();
}
