#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"ListaLigada.h"
#include<QFileDialog>
#include <QMessageBox>
#include<QGraphicsScene>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    LSLSE<Neurona> admin;
    QFileDialog *fileDialog;
    QGraphicsScene scene;


private slots:
    void on_lineEdit_editingFinished();

    void on_lineEdit_2_editingFinished();

    void on_lineEdit_3_editingFinished();

    void on_lineEdit_4_editingFinished();

    void on_lineEdit_5_editingFinished();

    void on_lineEdit_7_editingFinished();

    void on_lineEdit_6_editingFinished();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_actionSave_triggered();

    void on_actionOpen_triggered();

    void on_lineEdit_8_editingFinished();

    void on_pushButton_5_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
