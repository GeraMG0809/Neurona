#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include<iostream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

Neurona neu(0,0,0,0,0,0,0);
void MainWindow::on_lineEdit_editingFinished()
{
    QString qs_id = ui->lineEdit->text();
    int st_id = qs_id.toInt();

    neu.setId(st_id);
}


void MainWindow::on_lineEdit_2_editingFinished() //voltaje
{
    QString qs_voltaje = ui->lineEdit_2->text();
    float vol = qs_voltaje.toFloat();
    std::cout<<vol;
    neu.setVoltaje(vol);
}


void MainWindow::on_lineEdit_3_editingFinished() // posicion x
{
    QString qs_posx = ui->lineEdit_3->text();
    int posx = qs_posx.toInt();
    std::cout<<posx;
    neu.setPosicion_x(posx);
}


void MainWindow::on_lineEdit_4_editingFinished() // poscion y
{
    QString qs_posy = ui->lineEdit_4->text();
    int posy = qs_posy.toInt();
    std::cout<<posy;
    neu.setPosicion_y(posy);
}


void MainWindow::on_lineEdit_5_editingFinished()//red
{
    QString qs_red = ui->lineEdit_5->text();
    int red = qs_red.toInt();
    std::cout<<red;
    neu.setRed(red);

}


void MainWindow::on_lineEdit_7_editingFinished() //blue
{
    QString qs_blue = ui->lineEdit_7->text();
    int blue = qs_blue.toInt();
    std::cout<<blue;
    neu.setBlue(blue);
}


void MainWindow::on_lineEdit_6_editingFinished() //green
{
    QString qs_green = ui->lineEdit_6->text();
    int green = qs_green.toInt();
    std::cout<<green;
    neu.setGreen(green);
}


void MainWindow::on_pushButton_2_clicked()
{
    admin.insertarInicio(neu);
}
void MainWindow::on_pushButton_3_clicked()
{
    admin.insertarFinal(neu);
}



void MainWindow::on_pushButton_clicked()
{
    ui->plainTextEdit->clear();
    std::string lista = admin.toString();
    QString qs_lista = QString::fromStdString(lista);
    ui->plainTextEdit->insertPlainText(qs_lista);
    //admin.guardarDatos();
}


void MainWindow::on_actionSave_triggered()
{

    QString fileName = QFileDialog::getSaveFileName(this, tr("Guardar archivo"),
                                                    "/path/to/default/directory",
                                                    tr("Archivos de texto (*.txt);;Todos los archivos (*.)"));
    if (!fileName.isEmpty()) {
        std::ofstream archivoNeuronas;
        archivoNeuronas.open(fileName.toStdString(), std::ios::app);

        node<Neurona>* aux = admin.primero();
        while (aux != nullptr) {
            Neurona neu = aux->getData();
            archivoNeuronas << neu.getId() << " " << neu.getVoltaje() << " " << neu.getPosicion_x() << " " << neu.getPosicion_y() << " " << neu.getRed() << " " << neu.getBlue() << " " << neu.getGreen() << std::endl;
            aux = aux->getSiguiente();
        }

        archivoNeuronas.close();
    }
}


void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "/path/to/default/directory",
                                                    tr("Archivos de texto (*.txt);;Todos los archivos (*.)"));

    if (!fileName.isEmpty()) {
        std::string file = fileName.toStdString();

        admin.cargarDatos(file);
    }
}



void MainWindow::on_lineEdit_8_editingFinished()
{

    QString qs_search = ui->lineEdit_8->text();
    int search = qs_search.toInt();
    node<Neurona>* busqueda;
    busqueda = admin.Buscar(search);


    // Establecer el número de columnas
    ui->tableWidget->setColumnCount(7);

    // Establecer los nombres de las columnas
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Id" << "Voltaje" << "Posicion x" << "Posicion y" << "Red" << "Green" << "Blue");

    // Verificar si la búsqueda devuelve un resultado
    if (busqueda != nullptr) {
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(busqueda->getData().getId())));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(busqueda->getData().getVoltaje())));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(busqueda->getData().getPosicion_x())));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(busqueda->getData().getPosicion_y())));
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(busqueda->getData().getRed())));
        ui->tableWidget->setItem(row, 5, new QTableWidgetItem(QString::number(busqueda->getData().getGreen())));
        ui->tableWidget->setItem(row, 6, new QTableWidgetItem(QString::number(busqueda->getData().getBlue())));
    } else {
        // Mostrar un mensaje de error si no se encontró el elemento
        QMessageBox::warning(this, tr("Error"), tr("El elemento buscado no existe en la lista."));
    }

}



void MainWindow::on_pushButton_5_clicked()
{
    scene.clear();
    QPen pen;
    node<Neurona>* aux = admin.primero();
    while(aux !=  nullptr){
        Neurona n = aux->getData();
        QColor c(n.getRed(),n.getGreen(),n.getBlue());
        pen.setColor(c);
        QBrush bru(c,Qt::Dense1Pattern);
        scene.addEllipse(n.getPosicion_x(),n.getPosicion_y(),n.getVoltaje(),n.getVoltaje(),pen,bru);
        aux = aux->getSiguiente();

    }
    ui->graphicsView->setScene(&scene);
    ui->graphicsView->show();

}




void MainWindow::on_pushButton_6_clicked()
{
    admin.Ordenamiento_id();
}


void MainWindow::on_pushButton_7_clicked()
{
    admin.Ordenamiento_voltaje();
}


void MainWindow::on_pushButton_8_clicked()
{

    admin.calcularDistancias(scene);
    ui->graphicsView->setScene(&scene);
    ui->graphicsView->show();
}

