#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    calc.start("bc", QStringList() << "-q");
    calc.waitForStarted();
    calc.write("scale=4\n");
    bool status = connect(&calc, SIGNAL(readyReadStandardOutput()), this, SLOT(on_calc_readyRead()));
}

MainWindow::~MainWindow()
{
    calc.close();
    calc.waitForFinished();
    delete ui;
}

void MainWindow::on_pushButton_calc_clicked()
{
    std::cerr << "Got a button push!" << std::endl;
    QString input = ui->lineEdit->text();
    input.append("\n");
    std::cerr << "Writing " << input.toStdString() << " to process stdin. I think." << std::endl;
    calc.write(input.toLocal8Bit());
    line = input.trimmed().append("=");
}

void MainWindow::on_calc_readyRead()
{
    std::cerr << "Got a readyReadStandardOutput signal!" << std::endl;
    ui->textBrowser->append(line.append(calc.readAllStandardOutput()).trimmed());
}
