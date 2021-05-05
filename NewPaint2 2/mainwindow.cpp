#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QColor>
#include <QPicture>
#include<QImage>
#include <QPainterPath>
#include <QGraphicsSceneMouseEvent>
#include<myscene.h>

#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
        scene = new MyScene();
      ui->graphicsView->setScene(scene);


      //ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
     // ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

MainWindow::~MainWindow()
{
    delete scene;
    delete ui;
}










void MainWindow::on_lineButton_clicked()
{
    ui->lineButton->setDown(true);
   ui-> triangleButton->setDown(false);
   ui-> rectButton->setDown(false);
   ui-> circleButton->setDown(false);
   ui-> pointsButton->setDown(false);
   ui-> PencilButton->setDown(false);

scene->setFigureType(Line);
}


void MainWindow::on_triangleButton_clicked()
{
    ui->lineButton->setDown(false);
   ui-> triangleButton->setDown(true);
   ui-> rectButton->setDown(false);
   ui-> circleButton->setDown(false);
   ui-> pointsButton->setDown(false);
   ui-> PencilButton->setDown(false);
    scene->setFigureType(Triangle);
}






void MainWindow::on_rectButton_clicked()
{
    ui->lineButton->setDown(false);
   ui-> triangleButton->setDown(false);
   ui-> rectButton->setDown(true);
   ui-> circleButton->setDown(false);
   ui-> pointsButton->setDown(false);
   ui-> PencilButton->setDown(false);
    scene->setFigureType(Rectangle);
}

void MainWindow::on_clearButton_5_clicked()
{
scene->clearScene();
}


void MainWindow::on_PencilButton_clicked()
{
    ui->lineButton->setDown(false);
   ui-> triangleButton->setDown(false);
   ui-> rectButton->setDown(false);
   ui-> circleButton->setDown(false);
   ui-> pointsButton->setDown(false);
   ui-> PencilButton->setDown(true);
    scene->setFigureType(Pencil);
}

void MainWindow::on_circleButton_clicked()
{
    ui->lineButton->setDown(false);
   ui-> triangleButton->setDown(false);
   ui-> rectButton->setDown(false);
   ui-> circleButton->setDown(true);
   ui-> pointsButton->setDown(false);
   ui-> PencilButton->setDown(false);
    scene->setFigureType(Circle);
}

void MainWindow::on_pointsButton_clicked()
{
    ui->lineButton->setDown(false);
   ui-> triangleButton->setDown(false);
   ui-> rectButton->setDown(false);
   ui-> circleButton->setDown(false);
   ui-> pointsButton->setDown(true);
   ui-> PencilButton->setDown(false);
    scene->setFigureType(Points);
}

void MainWindow::on_undoButton_clicked()
{
    scene->undoMethod();
}

void MainWindow::on_colourButton_clicked()
{
   QColor colour= QColorDialog::getColor(Qt::yellow,this);
   scene->colourDial(colour);
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    QPen myPenW;
    myPenW.setWidth(arg1);
    scene->setLineWidth(arg1);
}





void MainWindow::on_fillColourButton_clicked()
{
    QColor colourFill =QColorDialog::getColor(Qt::yellow,this);
    scene->setFillColour(colourFill);
}






void MainWindow::on_saveButton_clicked()
{
    QString newPath = QFileDialog::getSaveFileName(this,"Save file As");

   QPixmap pixmap(800,800);
   QPainter painter(&pixmap);

    pixmap.fill(Qt::white);
    painter.setRenderHint(QPainter::Antialiasing);
    scene->render(&painter);

     painter.end();

    pixmap.save(newPath);



}






void MainWindow::on_openButton_clicked()
{

    QPixmap pixmapNewFile;
    pixmapNewFile.load(QFileDialog::getOpenFileName(this));
    scene->addPixmap(pixmapNewFile);

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    event->ignore();
}
