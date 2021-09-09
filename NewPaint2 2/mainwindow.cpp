#include "mainwindow.h"

#include <figuretype.h>
#include <myscene.h>
#include <mytextclass.h>

#include <QBrush>
#include <QColor>
#include <QFileDialog>
#include <QGraphicsSceneMouseEvent>
#include <QImage>
#include <QInputDialog>
#include <QKeyEvent>
#include <QListWidget>
#include <QPainter>
#include <QPainterPath>
#include <QPen>
#include <QPicture>
#include <QStyleOptionGraphicsItem>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  scene = new MyScene(this);
  ui->graphicsView->setFixedSize(700, 740);
  ui->graphicsView->setScene(scene);

  ui->spinBox_2->setValue(0);
  setWindowTitle(windowTitle);

  ui->helpWindow->setHidden(true);
  ui->helpLabel->setHidden(true);

  ui->cubeColour->setAutoFillBackground(true);
  ui->cubeColour_2->setAutoFillBackground(true);

  myPalleteFill.setColor(QPalette::Window, QColor(Qt::white));
  ui->cubeColour->setPalette(myPalleteFill);

  myPalleteBorders.setColor(QPalette::Window, QColor(Qt::black));
  ui->cubeColour_2->setPalette(myPalleteBorders);


  connect(scene, SIGNAL(signalListWidget()), this, SLOT(onList()));
}

MainWindow::~MainWindow() {
  delete scene;
  delete ui;
}

void MainWindow::on_lineButton_clicked() {
  this->setCursor(QCursor(Qt::ArrowCursor));
  ui->lineButton->setDown(true);
  ui->triangleButton->setDown(false);
  ui->rectButton->setDown(false);
  ui->circleButton->setDown(false);
  ui->pointsButton->setDown(false);
  ui->PencilButton->setDown(false);
  ui->textButton->setDown(false);
  ui->moveItemButton->setDown(false);
  ui->selectButton->setDown(false);

  ui->helpLabel->setHidden(true);
  ui->helpWindow->setHidden(true);
  ui->helpWindow->clear();

  scene->setFigureType(Line);
}

void MainWindow::on_triangleButton_clicked() {
  this->setCursor(QCursor(Qt::ArrowCursor));
  ui->lineButton->setDown(false);
  ui->triangleButton->setDown(true);
  ui->rectButton->setDown(false);
  ui->circleButton->setDown(false);
  ui->pointsButton->setDown(false);
  ui->PencilButton->setDown(false);
  ui->textButton->setDown(false);
  ui->moveItemButton->setDown(false);
  ui->selectButton->setDown(false);

  ui->helpLabel->setHidden(true);
  ui->helpWindow->setHidden(true);
  ui->helpWindow->clear();

  scene->setFigureType(Triangle);
}

void MainWindow::on_rectButton_clicked() {
  this->setCursor(QCursor(Qt::ArrowCursor));
  ui->lineButton->setDown(false);
  ui->triangleButton->setDown(false);
  ui->rectButton->setDown(true);
  ui->circleButton->setDown(false);
  ui->pointsButton->setDown(false);
  ui->PencilButton->setDown(false);
  ui->textButton->setDown(false);
  ui->moveItemButton->setDown(false);
  ui->selectButton->setDown(false);

  ui->helpLabel->setHidden(true);
  ui->helpWindow->setHidden(true);
  ui->helpWindow->clear();

  scene->setFigureType(Rectangle);
}

void MainWindow::on_clearButton_5_clicked() {
  this->setCursor(QCursor(Qt::ArrowCursor));
  scene->clearScene();
  scene->clear();
}

void MainWindow::on_PencilButton_clicked() {
  this->setCursor(QCursor(Qt::ArrowCursor));
  ui->lineButton->setDown(false);
  ui->triangleButton->setDown(false);
  ui->rectButton->setDown(false);
  ui->circleButton->setDown(false);
  ui->pointsButton->setDown(false);
  ui->PencilButton->setDown(true);
  ui->textButton->setDown(false);
  ui->moveItemButton->setDown(false);
  ui->selectButton->setDown(false);

  ui->helpLabel->setHidden(true);
  ui->helpWindow->setHidden(true);
  ui->helpWindow->clear();

  scene->setFigureType(Pencil);
}

void MainWindow::on_circleButton_clicked() {
  this->setCursor(QCursor(Qt::ArrowCursor));
  ui->lineButton->setDown(false);
  ui->triangleButton->setDown(false);
  ui->rectButton->setDown(false);
  ui->circleButton->setDown(true);
  ui->pointsButton->setDown(false);
  ui->PencilButton->setDown(false);
  ui->textButton->setDown(false);
  ui->moveItemButton->setDown(false);
  ui->selectButton->setDown(false);

  ui->helpLabel->setHidden(true);
  ui->helpWindow->setHidden(true);
  ui->helpWindow->clear();

  scene->setFigureType(Circle);
}

void MainWindow::on_pointsButton_clicked() {
  this->setCursor(QCursor(Qt::ArrowCursor));
  ui->lineButton->setDown(false);
  ui->triangleButton->setDown(false);
  ui->rectButton->setDown(false);
  ui->circleButton->setDown(false);
  ui->pointsButton->setDown(true);
  ui->PencilButton->setDown(false);
  ui->textButton->setDown(false);
  ui->moveItemButton->setDown(false);
  ui->selectButton->setDown(false);

  ui->helpLabel->setHidden(true);
  ui->helpWindow->setHidden(true);
  ui->helpWindow->clear();

  scene->setFigureType(Points);
}

void MainWindow::on_undoButton_clicked() { scene->undoMethod(); }

void MainWindow::on_colourButton_clicked() {
  QColor colour = QColorDialog::getColor(Qt::black, this);

  myPalleteBorders.setColor(QPalette::Window, colour);
  ui->cubeColour_2->setPalette(myPalleteBorders);
  scene->colourDial(colour);
}

void MainWindow::on_spinBox_valueChanged(int arg1) {
  QPen myPenW;
  myPenW.setWidth(arg1);
  scene->setLineWidth(arg1);
}

void MainWindow::on_fillColourButton_clicked() {
  QColor colourFill = QColorDialog::getColor(Qt::white, this);

  myPalleteFill.setColor(QPalette::Window, colourFill);
  ui->cubeColour->setPalette(myPalleteFill);

  scene->setFillColour(colourFill);
}

void MainWindow::on_saveButton_clicked() {
  this->setCursor(QCursor(Qt::ArrowCursor));
  QString newPath = QFileDialog::getSaveFileName(this, "Save file As");

  QPixmap pixmap(800, 800);
  QPainter painter(&pixmap);

  pixmap.fill(Qt::white);
  painter.setRenderHint(QPainter::Antialiasing);
  scene->render(&painter);

  painter.end();

  pixmap.save(newPath);
}

void MainWindow::on_openButton_clicked() {
  this->setCursor(QCursor(Qt::ArrowCursor));
  QPixmap pixmapNewFile;
  pixmapNewFile.load(QFileDialog::getOpenFileName(this));
  scene->addPixmap(pixmapNewFile);
}

void MainWindow::on_textButton_clicked() {
  ui->lineButton->setDown(false);
  ui->triangleButton->setDown(false);
  ui->rectButton->setDown(false);
  ui->circleButton->setDown(false);
  ui->pointsButton->setDown(false);
  ui->PencilButton->setDown(false);
  ui->textButton->setDown(true);
  ui->moveItemButton->setDown(false);
  ui->selectButton->setDown(false);

  ui->helpLabel->setHidden(true);
  ui->helpWindow->setHidden(true);
  ui->helpWindow->clear();

  scene->setFigureType(Text);
}

void MainWindow::on_spinBox_2_valueChanged(int rotate) {
  this->setCursor(QCursor(Qt::ArrowCursor));

  scene->rotationFigure(rotate);


}

void MainWindow::on_doubleSpinBox_valueChanged(double figureOpacity) {
  scene->myOpacityFunc(figureOpacity);
}

void MainWindow::on_moveItemButton_clicked() {
  ui->lineButton->setDown(false);
  ui->triangleButton->setDown(false);
  ui->rectButton->setDown(false);
  ui->circleButton->setDown(false);
  ui->pointsButton->setDown(false);
  ui->PencilButton->setDown(false);
  ui->textButton->setDown(false);
  ui->moveItemButton->setDown(true);
  ui->selectButton->setDown(false);

  ui->helpLabel->setHidden(false);
  ui->helpWindow->setHidden(false);
  ui->helpWindow->setEnabled(true);
  ui->helpWindow->setText(myHelpMove);

  scene->setFigureType(MoveItem);
}

void MainWindow::on_selectButton_clicked() {
  ui->lineButton->setDown(false);
  ui->triangleButton->setDown(false);
  ui->rectButton->setDown(false);
  ui->circleButton->setDown(false);
  ui->pointsButton->setDown(false);
  ui->PencilButton->setDown(false);
  ui->textButton->setDown(false);
  ui->moveItemButton->setDown(false);
  ui->selectButton->setDown(true);

  scene->setFigureType(SelectItem);
}

void MainWindow::onList() {
  qDebug() << Q_FUNC_INFO;
  if (scene->items().isEmpty()) {
    ui->listWiItemsShow->clear();
    return;
  }

  QList<QString> nameItemsFigure[scene->items().count()];
  nameItemsFigure->clear();
  ui->listWiItemsShow->clear();
  for (int i = 0; i <= scene->items().count() - 1; ++i) {
    if (scene->items().at(i)->type() == 4) {
      nameItemsFigure[i] << "Circle";

      ui->listWiItemsShow->addItems(nameItemsFigure[i]);
    }

    if (scene->items().at(i)->type() == 3) {
      nameItemsFigure[i] << "Rectangle";

      ui->listWiItemsShow->addItems(nameItemsFigure[i]);
    }

    if (scene->items().at(i)->type() == 5) {
      nameItemsFigure[i] << "Triangle";

      ui->listWiItemsShow->addItems(nameItemsFigure[i]);
    }

    if (scene->items().at(i)->type() == 6) {
      nameItemsFigure[i] << "Line";

      ui->listWiItemsShow->addItems(nameItemsFigure[i]);
    }

    if (scene->items().at(i)->type() == 8) {
      QGraphicsTextItem *myTempItem =
          qgraphicsitem_cast<MyTextClass *>(scene->items().at(i));

      nameItemsFigure[i] << "TEXT: " + myTempItem->toPlainText();

      ui->listWiItemsShow->addItems(nameItemsFigure[i]);
    }

    // 3 Rect; 5 Triangle;  6 Line; 4 Dots; 8 Text;
  }
}

void MainWindow::on_listWiItemsShow_itemClicked(QListWidgetItem *item) {
  Q_UNUSED(item)
  if (!scene->items().isEmpty()) {
    scene->clearSelection();
    int index = ui->listWiItemsShow->currentRow();

    scene->items().at(index)->setSelected(true);
  }
}

void MainWindow::on_bringToFront_clicked() { scene->bringToFront(); }

void MainWindow::on_bringToBack_clicked() { scene->bringToBack(); }
