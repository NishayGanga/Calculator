#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

namespace Ui {
class Calculator;
}

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    explicit Calculator(QWidget *parent = 0);
    ~Calculator();

private:
    Ui::Calculator *ui;

private slots:
    //These slots will be executed when a signal is submitted
    //Whenever a number, math, changesign, equal button is pressed these functions will be executed.
    void NumPressed();
    void MathButtonPressed();
    void EqualButton();
    void ChangeNumberSign();
    void Clear();
    void AddMemory();
    void ClearMemory();
    void GetMemory();

};

#endif // CALCULATOR_H
