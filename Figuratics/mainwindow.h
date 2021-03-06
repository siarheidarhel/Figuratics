#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <figuretype.h>

#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QImage>
#include <QListWidget>
#include <QMainWindow>
#include <QPicture>
#include <QPointF>
#include <QString>
//#include <mytextclass.h>

namespace Ui {
class MainWindow;
}
class MyScene;
class MyTextClass;
class MainWindow : public QMainWindow {
  Q_OBJECT
  QGraphicsTextItem *myTextItem =  nullptr;
  QString windowTitle = {"Figuratics"};
  QString inputText;
  QString myHelpMove = {
      "USE \n <UP> AND <DOWN> \n KEYS TO NAVIGATE SELECTIONS"};
  // QBrush myBack=( Qt::red);
  QPalette myPalleteFill;
  QPalette myPalleteBorders;

  // QListWidget myListWiget;
  // QWidget myTempWidget;

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui = nullptr;
  MyScene *scene = nullptr;
  MyTextClass *myText = nullptr;

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
  void on_openButton_clicked();
  void on_textButton_clicked();
  void on_spinBox_2_valueChanged(int rotate);
  void on_doubleSpinBox_valueChanged(double figureOpacity);
  void on_moveItemButton_clicked();
  void on_selectButton_clicked();

  // void SelectItemThruList();

  void onList();

  void on_listWiItemsShow_itemClicked(QListWidgetItem *item);

  void on_bringToFront_clicked();

  void on_bringToBack_clicked();

 public slots:
  // void resetRotation ();
};

#endif  // MAINWINDOW_H
