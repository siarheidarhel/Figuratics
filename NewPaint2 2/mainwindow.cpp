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
#include<QInputDialog>

#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
        scene = new MyScene(this);
      ui->graphicsView->setScene(scene);
      //scene->setItemIndexMethod(QGraphicsScene::NoIndex);
     // ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
     // ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);



      setWindowTitle(windowTitle);


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
   this->setCursor(QCursor(Qt::ArrowCursor));
   ui->lineButton->setDown(true);
   ui->triangleButton->setDown(false);
   ui->rectButton->setDown(false);
   ui->circleButton->setDown(false);
   ui->pointsButton->setDown(false);
   ui->PencilButton->setDown(false);
   ui->textButton->setDown(false);
   ui->editText->setDown(false);

   scene->setFigureType(Line);
}


void MainWindow::on_triangleButton_clicked()
{
   this->setCursor(QCursor(Qt::ArrowCursor));
   ui->lineButton->setDown(false);
   ui-> triangleButton->setDown(true);
   ui-> rectButton->setDown(false);
   ui-> circleButton->setDown(false);
   ui-> pointsButton->setDown(false);
   ui-> PencilButton->setDown(false);
   ui->textButton->setDown(false);
   ui->editText->setDown(false);

    scene->setFigureType(Triangle);
}






void MainWindow::on_rectButton_clicked()
{
   this->setCursor(QCursor(Qt::ArrowCursor));
   ui->lineButton->setDown(false);
   ui-> triangleButton->setDown(false);
   ui-> rectButton->setDown(true);
   ui-> circleButton->setDown(false);
   ui-> pointsButton->setDown(false);
   ui-> PencilButton->setDown(false);
   ui->textButton->setDown(false);
    ui->editText->setDown(false);

    scene->setFigureType(Rectangle);
}

void MainWindow::on_clearButton_5_clicked()
{
    this->setCursor(QCursor(Qt::ArrowCursor));
    scene->clearScene();
}


void MainWindow::on_PencilButton_clicked()
{
    this->setCursor(QCursor(Qt::ArrowCursor));
    ui->lineButton->setDown(false);
   ui-> triangleButton->setDown(false);
   ui-> rectButton->setDown(false);
   ui-> circleButton->setDown(false);
   ui-> pointsButton->setDown(false);
   ui-> PencilButton->setDown(true);
   ui->textButton->setDown(false);
    ui->editText->setDown(false);

    scene->setFigureType(Pencil);
}

void MainWindow::on_circleButton_clicked()
{
    this->setCursor(QCursor(Qt::ArrowCursor));
   ui->lineButton->setDown(false);
   ui-> triangleButton->setDown(false);
   ui-> rectButton->setDown(false);
   ui-> circleButton->setDown(true);
   ui-> pointsButton->setDown(false);
   ui-> PencilButton->setDown(false);
   ui->textButton->setDown(false);
    ui->editText->setDown(false);

   scene->setFigureType(Circle);
}

void MainWindow::on_pointsButton_clicked()
{
    this->setCursor(QCursor(Qt::ArrowCursor));
    ui->lineButton->setDown(false);
   ui-> triangleButton->setDown(false);
   ui-> rectButton->setDown(false);
   ui-> circleButton->setDown(false);
   ui-> pointsButton->setDown(true);
   ui-> PencilButton->setDown(false);
   ui->textButton->setDown(false);
   ui->editText->setDown(false);

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
    this->setCursor(QCursor(Qt::ArrowCursor));
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
    this->setCursor(QCursor(Qt::ArrowCursor));
    QPixmap pixmapNewFile;
    pixmapNewFile.load(QFileDialog::getOpenFileName(this));
    scene->addPixmap(pixmapNewFile);

}



void MainWindow::on_textButton_clicked()
{
   ui-> lineButton->setDown(false);
   ui-> triangleButton->setDown(false);
   ui-> rectButton->setDown(false);
   ui-> circleButton->setDown(false);
   ui-> pointsButton->setDown(false);
   ui-> PencilButton->setDown(false);
   ui-> textButton->setDown(false);
    ui->editText->setDown(false);

   //scene->setFigureType(Text);
   inputText = QInputDialog::getText(this, tr("Set Text"),tr("Text"));
   myTextItem= new QGraphicsTextItem(inputText);

   scene->drawText(myTextItem);
   scene->blockSignals(true);

}



void MainWindow::on_spinBox_2_valueChanged(int rotate)
{
    this->setCursor(QCursor(Qt::ArrowCursor));
    scene->rotationFigure(rotate);
}

void MainWindow::on_editText_clicked()
{
    this->setCursor(QCursor(Qt::IBeamCursor));
    ui-> lineButton->setDown(false);
    ui-> triangleButton->setDown(false);
    ui-> rectButton->setDown(false);
    ui-> circleButton->setDown(false);
    ui-> pointsButton->setDown(false);
    ui-> PencilButton->setDown(false);
    ui-> textButton->setDown(false);
    ui->editText->setDown(true);
    scene->editText();
}
