#include <unistd.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    istream(stdin, QIODevice::ReadOnly)
{
    ui->setupUi(this);
    pNot = new QSocketNotifier(STDIN_FILENO, QSocketNotifier::Read, this);
    bool status = connect(pNot, SIGNAL(activated(int)), this, SLOT(onData()));
}

MainWindow::~MainWindow()
{
    calc.close();
    calc.waitForFinished();
    delete ui;
}

void MainWindow::setInitialEq(const QString& init)
{
    ui->lineEdit->setText(init);
}

void MainWindow::on_pushButton_calc_clicked()
{
    std::cerr << "Got a button push!" << std::endl;
    QString input = ui->lineEdit->text();
    input.append("\n");
    std::cerr << "Writing " << input.toStdString() << " to process stdin. I think." << std::endl;
    std::cout << input.toStdString() << std::endl;
    line = input.trimmed().append("=");
}

void MainWindow::onData()
{
  std::cerr << "Got a SocketNotifier signal!" << std::endl;
  line.append(istream.readLine());
  ui->textBrowser->append(line.toLocal8Bit());
  line = "";
}
