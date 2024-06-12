#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}

class firstScn; // Declaramos la clase para poder usarla en este archivo
class Game;     // Declaramos la clase para poder usarla en este archivo

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void updateMousePosition(const QPointF &pos); // Método para actualizar la posición del mouse
public slots:
    void cambiolvl();
    void handleGameWon(); // Definir el slot

private:
    Ui::MainWindow *ui;
    firstScn *Batalla_Naval;
    Game *game;
    QLabel *mousePositionLabel; // Etiqueta para mostrar la posición del mouse
};

#endif // MAINWINDOW_H
