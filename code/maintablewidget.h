#ifndef MAINTABLEWIDGET_H
#define MAINTABLEWIDGET_H

#include <QTableWidget>

class Cell;
class TablesheetCompare;

namespace Ui {
class MainTableWidget;
}

class MainTableWidget : public QTableWidget
{
    Q_OBJECT

public:
    explicit MainTableWidget(QWidget *parent = 0);
    ~MainTableWidget();

//    bool autoRecalculate() const { const autoRecalc; }
    QString currentLocation() const;
//    QString currentFormula() const;
    QTableWidgetSelectionRange selectedRange() const;
    void clear();
    bool readFile(const QString& fileName);
    bool writeFile(const QString& fileName);
//    void sort(const TablesheetCompare& compare);

public slots:
    void cut();
    void copy();
    void paste();
    void del();
//    void selectCurrentRow();
//    void selectCurrentColumn();
//    void recalculate();
//    void setAutoRecalculculate(bool recalc);
//    void findNext(const QString& str, Qt::CaseSensitivity cs);

signals:
    void modified();

private slots:
//    void somethingChanged();

private:
    Ui::MainTableWidget *ui;

    enum { emMagicNumber = 0x7F51C883, emRowCount = 999, emColumnCount = 26 };

//    Cell* cell(int row, int column) const;
//    QString text(int row, int column) const;
//    QString formula(int row, int column) const;
//    void setFormula(int row, int column, const QString& formula);
//    bool autoRecalc;
};

class TablesheetCompare
{
public:
    bool operator()(const QStringList& row1, const QStringList& row2) const;
    enum { emKeyCount = 3 };
    int m_iKeys[emKeyCount];
    bool m_bAscending[emKeyCount];
};

#endif // MAINTABLEWIDGET_H
