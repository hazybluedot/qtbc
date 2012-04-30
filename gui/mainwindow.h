#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QSocketNotifier>
#include <QTextStream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
    void setInitialEq(const QString&);

private slots:
    void on_pushButton_calc_clicked();
    void onData();

private:
    Ui::MainWindow *ui;
    QProcess calc;
    QString line;
    QSocketNotifier *pNot;
    QTextStream istream;
};

#endif // MAINWINDOW_H
