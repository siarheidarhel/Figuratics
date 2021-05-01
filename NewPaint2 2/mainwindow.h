#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPointF>
#include <QImage>
#include<QGraphicsView>
#include<QGraphicsScene>
#include<QPicture>
#include <QGraphicsLineItem>





namespace Ui {
class MainWindow;
}
class MyScene;
class MainWindow : public QMainWindow
{
    Q_OBJECT



public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui=nullptr;
    MyScene *scene=nullptr;


private slots:


    void on_lineButton_clicked();
    void on_rectButton_clicked();
    void on_clearButton_5_clicked();
    void on_triangleButton_clicked();
    void on_PencilButton_clicked();
    void on_circleButton_clicked();
    void on_pointsButton_clicked();
    void on_undoButton_clicked();
    void on_colourButton_clicked();
    void on_spinBox_valueChanged(int arg1);

    void on_fillColourButton_clicked();

    void on_saveButton_clicked();
};

#endif // MAINWINDOW_H









