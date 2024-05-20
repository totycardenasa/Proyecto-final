#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "firstscn.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Batalla_Naval = new firstScn(this);
    ui->escenario->setScene(Batalla_Naval);

    // Inicializar la etiqueta para mostrar la posición del mouse
    mousePositionLabel = new QLabel(this);
    ui->statusbar->addPermanentWidget(mousePositionLabel); // Añadir la etiqueta a la barra de estado
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateMousePosition(const QPointF &pos)
{
    mousePositionLabel->setText(QString("Mouse position: (%1, %2)").arg(pos.x()).arg(pos.y()));
}
