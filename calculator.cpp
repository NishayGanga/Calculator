#include "calculator.h"
#include "ui_calculator.h"

double Value = 0.0; //tracks value or current value in the calculation. Which initialized to 0.0
double *ValueP;
double memory;
//These variables are to track down which button was used last.
bool divTracker = false;
bool multiplyTracker = false;
bool AddTracker = false;
bool SubtractTracker = false;

Calculator::Calculator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Calculator)
{
    ui->setupUi(this);

    //the ui LineEdit or also named the Display shows the current value.
    ui->Display->setText(QString::number(Value));

    //making an array to reference all the QPushButtons i.e 0-9
    QPushButton *NumButtons[10];
    //To add all the buttons to the array we have to use a loop
    //The loop will start from 0 and ends till 9
    for(int i = 0 ; i < 10 ; i++){
        //We first have to make a variable and store the button + the iterator
        //Which gives us button0, button2 and so on...
        QString ButtonName = "Button" + QString::number(i);
        //appending the buttons into the array
        //which finds the find the child of QPushButton referencing Button Name
        NumButtons[i] = Calculator::findChild<QPushButton *>(ButtonName);
        connect(NumButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }
    //connecting the signals to slots
    connect(ui->Add, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Subtract, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Multiply, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Divide, SIGNAL(released()), this, SLOT(MathButtonPressed()));

    connect(ui->ChangeSign, SIGNAL(released()), this, SLOT(ChangeNumberSign()));

    connect(ui->Equal, SIGNAL(released()), this, SLOT(EqualButton()));
    connect(ui->Clear, SIGNAL(released()), this, SLOT(Clear()));
    connect(ui->MemAdd, SIGNAL(released()), this, SLOT(AddMemory()));
    connect(ui->MemClear, SIGNAL(released()), this, SLOT(ClearMemory()));
    connect(ui->MemGet, SIGNAL(released()), this, SLOT(GetMemory()));
}

Calculator::~Calculator()
{
    delete ui;
}


void Calculator::NumPressed(){
    //The sender will return a pointer when the button is pressed.
    QPushButton *button = (QPushButton *)sender();

    //We have to store the number that was pressed.
    QString buttonPressed = button->text();

    //Get the display when the button is clicked
    QString DisplayValue = ui->Display->text();

    //if the display meets these conditions the display the that button was pressed
    //else displays the new value
    if((DisplayValue.toDouble() == 0) || (DisplayValue.toDouble() == 0.0)){
        ui->Display->setText(buttonPressed);
    }
    else
    {
        //This adds the display value with the button pressed value and stores it in a varible called
        //newValue, like adding 2 strings;
        QString newValue = DisplayValue + buttonPressed;
        double  doubleNewValue = newValue.toDouble();
        //displays exponential form after entering 16 digits
        ui->Display->setText(QString::number(doubleNewValue, 'g', 16));
    }

}


void Calculator::MathButtonPressed(){
    //Track which math button was clicked on last
    //initialize all trackers to false;
    divTracker = false;
    multiplyTracker = false;
    AddTracker = false;
    SubtractTracker = false;
    //get the value that is displayed
    QString displayValue = ui->Display->text();
    //convert  the value to a double
    Value = displayValue.toDouble();
    //storing the button value that was pressed into the variable button
    QPushButton *button = (QPushButton *)sender();
    //storing the text value into the variable button value
    QString buttonValue = button->text();
    //determining which math buttons are pressed abd changing the corresponding variables to true;
    if(QString::compare(buttonValue, "/", Qt::CaseInsensitive) == 0){
        divTracker = true;
    }

    else if (QString::compare(buttonValue, "X", Qt::CaseInsensitive) == 0){
        multiplyTracker = true;
    }

   else  if(QString::compare(buttonValue, "-", Qt::CaseInsensitive) == 0){
        SubtractTracker = true;
    }

    else {
        AddTracker = true;
    }

    ui->Display->setText("");
}

void Calculator::EqualButton(){
    //setting the solution to the equal to sign to a double
    double solution = 0.0;
    //extracting the value from the display
    QString display = ui->Display->text();
    double dbdisplay = display.toDouble();

    //whenever add the = is clicked than the corresponding tracker will have an affect on the calculation
    if(AddTracker || SubtractTracker || multiplyTracker || divTracker){
        if(AddTracker){
            solution = Value + dbdisplay;
        }
        else if(SubtractTracker){
            solution = Value - dbdisplay;
        }
        else if(multiplyTracker){
            solution = Value * dbdisplay;
        }
        else {
            solution = Value / dbdisplay;
        }
    }

    ui->Display->setText(QString::number(solution));
}


void Calculator::ChangeNumberSign(){
    QString display = ui->Display->text();
    QRegExp reg("[-]?[0-9.]*");
    if(reg.exactMatch(display)){
        double dbdisplay = display.toDouble();
        double dbdisplaySign = -1 * dbdisplay;
        ui->Display->setText(QString::number(dbdisplaySign));
    }else{
        double dbdisplay = display.toDouble();
        double dbdisplaySign = 1 * dbdisplay;
        ui->Display->setText(QString::number(dbdisplaySign));
    }

}

void Calculator::Clear(){
    ui->Display->setText("0.0");
    delete ValueP;
}


void Calculator::ClearMemory(){
    memory = 0.0;
}

void Calculator::GetMemory(){
    ui->Display->setText(QString::number(memory));
}

void Calculator::AddMemory(){
   //  EqualButton();
    memory += ui->Display->text().toDouble();
}
