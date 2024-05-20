#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}

class firstScn; //Llamamos a la clase para poder usarla en este archivo

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void updateMousePosition(const QPointF &pos); // Método para actualizar la posición del mouse

private:
    Ui::MainWindow *ui;
    firstScn *Batalla_Naval;
    QLabel *mousePositionLabel; // Etiqueta para mostrar la posición del mouse
};

#endif // MAINWINDOW_H
