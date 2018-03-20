#ifndef DIALOG_H
#define DIALOG_H

#include <board.h>
#include <worker.h>
#include <QDialog>
#include <QObject>
#include <QThread>
#include <QtWidgets>
#include <iostream>

class QAction;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QMenu;
class QMenuBar;
class QPushButton;
class QTextEdit;

class Dialog : public QDialog {
  Q_OBJECT

 public:
  Dialog();
  ~Dialog();
  QLabel* getLabels();
  void setLabels(QLabel* pLabels);

 private:
  void createHorizontalGroupBox();
  void createVillageArea();

  Board* board;

  QGroupBox* horizontalGroupBox;
  QGroupBox* villageGroupBox;

  QLabel* labels;
  QPushButton* buttons[2];
  QLineEdit* lineEdits[2];

  QAction* exitAction;

  QThread* thread;
  Worker* worker;

 protected:
  void paintEvent(QPaintEvent*);

 public slots:
  void handleStartButton();
  void handleStopButton();
  void finished();
  void repaint();

 signals:
  void setBoard(Board* pBoard);
};

#endif  // DIALOG_H
