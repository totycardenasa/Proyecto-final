#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "firstscn.h"
#include "game.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Batalla_Naval = new firstScn(this);
    ui->escenario->setScene(Batalla_Naval);

    connect(Batalla_Naval, &firstScn::gameWon, this, &MainWindow::handleGameWon); // Conectar la señal al slot

    // Inicializar la etiqueta para mostrar la posición del mouse
    mousePositionLabel = new QLabel(this);
    ui->statusbar->addPermanentWidget(mousePositionLabel); // Añadir la etiqueta a la barra de estado
}

MainWindow::~MainWindow()
{
    delete ui;
    delete Batalla_Naval;
}

void MainWindow::updateMousePosition(const QPointF &pos)
{
    mousePositionLabel->setText(QString("Mouse position: (%1, %2)").arg(pos.x()).arg(pos.y()));
}

void MainWindow::cambiolvl()
{
    if (Batalla_Naval) {
        delete Batalla_Naval;
        Batalla_Naval = nullptr;
        ui->groupBox->hide();
    }
    game = new Game(this);
    ui->escenario->setScene(game);
}

void MainWindow::handleGameWon()
{
    cambiolvl();
}
