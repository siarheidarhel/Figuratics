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
#include <figuretype.h>
#include<mytextclass.h>
#include <QStyleOptionGraphicsItem>

#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

      ui->setupUi(this);
      scene = new MyScene(this);
      ui->graphicsView->setFixedSize (700,740);
      ui->graphicsView->setScene(scene);
      ui->spinBox_2->setValue(0);
      setWindowTitle(windowTitle);
      ui->helpWindow->setHidden(true);
      ui->helpLabel->setHidden(true);

connect(scene, SIGNAL(myReset()), this, SLOT(resetRotation()));qDebug()<<"slot";


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
   ui->moveItemButton->setDown(false);

   ui->helpLabel->setHidden(true);
   ui->helpWindow->setHidden(true);
   ui->helpWindow->clear();

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
   ui->moveItemButton->setDown(false);

   ui->helpLabel->setHidden(true);
   ui->helpWindow->setHidden(true);
   ui->helpWindow->clear();

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
    ui->moveItemButton->setDown(false);

    ui->helpLabel->setHidden(true);
    ui->helpWindow->setHidden(true);
    ui->helpWindow->clear();

    scene->setFigureType(Rectangle);

}

void MainWindow::on_clearButton_5_clicked()
{
    this->setCursor(QCursor(Qt::ArrowCursor));
    scene->clearScene();
    scene->clear();
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
    ui->moveItemButton->setDown(false);

    ui->helpLabel->setHidden(true);
    ui->helpWindow->setHidden(true);
    ui->helpWindow->clear();

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
   ui->moveItemButton->setDown(false);


   ui->helpLabel->setHidden(true);
   ui->helpWindow->setHidden(true);
   ui->helpWindow->clear();

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
   ui->moveItemButton->setDown(false);

   ui->helpLabel->setHidden(true);
   ui->helpWindow->setHidden(true);
   ui->helpWindow->clear();

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
   ui->moveItemButton->setDown(false);


   ui->helpLabel->setHidden(true);
   ui->helpWindow->setHidden(true);
   ui->helpWindow->clear();

  scene->setFigureType(Text);

}



void MainWindow::on_spinBox_2_valueChanged(int rotate)
{
    this->setCursor(QCursor(Qt::ArrowCursor));
    scene->rotationFigure(rotate);
    //connect(scene, SIGNAL(&MyScene::rotationFigure), this,SLOT(MainWindow::resetRotation()));qDebug()<<"slot";

}

void MainWindow::resetRotation()
{
    ui->spinBox_2->setValue(0);
}




//void MainWindow::on_editText_clicked()
//{
//    this->setCursor(QCursor(Qt::IBeamCursor));
//    ui-> lineButton->setDown(false);
//    ui-> triangleButton->setDown(false);
//    ui-> rectButton->setDown(false);
//    ui-> circleButton->setDown(false);
//    ui-> pointsButton->setDown(false);
//    ui-> PencilButton->setDown(false);
//    ui-> textButton->setDown(false);
//    ui->editText->setDown(true);
   // scene->setFigureType(Text);

//}

void MainWindow::on_doubleSpinBox_valueChanged(double figureOpacity)
{
    scene->myOpacityFunc(figureOpacity);

}

void MainWindow::on_moveItemButton_clicked()
{

        ui-> lineButton->setDown(false);
        ui-> triangleButton->setDown(false);
        ui-> rectButton->setDown(false);
        ui-> circleButton->setDown(false);
        ui-> pointsButton->setDown(false);
        ui-> PencilButton->setDown(false);
        ui-> textButton->setDown(false);
        ui->moveItemButton->setDown(true);

          ui->helpLabel->setHidden(false);
         ui->helpWindow->setHidden(false);
         ui->helpWindow->setEnabled(true);
         ui->helpWindow->setText(myHelpMove);

      scene->setFigureType(MoveItem);


}
