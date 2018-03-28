#ifndef DIALOG_H
#define DIALOG_H

#include <board.h>
#include <worker.h>
#include <QBrush>
#include <QFrame>
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

class Dialog : public QFrame {
  Q_OBJECT

 private:
  void createHorizontalGroupBox();
  void createVillageArea();
  void handleStartButton();
  void handleStopButton();
  void handlePauseButton();

  Board* board;
  QThread* thread;
  Worker* worker;

  QGroupBox* horizontalGroupBox;
  QGroupBox* villageGroupBox;

  QPushButton* buttons[3];
  QLineEdit* lineEdits[3];

  bool reset;

 public:
  Dialog();
  ~Dialog();

 protected:
  void paintEvent(QPaintEvent*);
  virtual void closeEvent(QCloseEvent* e);

 public slots:
  void finished();
  void repaint();

 signals:
  void setBoard(Board* pBoard);
  void start();
  void stop();
};

#endif  // DIALOG_H
