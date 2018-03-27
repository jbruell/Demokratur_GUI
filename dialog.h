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
  void handleStartButton();
  void handleStopButton();
  void handlePauseButton();

  Board* board;

  QGroupBox* horizontalGroupBox;
  QGroupBox* villageGroupBox;

  QLabel* labels;
  QPushButton* buttons[3];
  QLineEdit* lineEdits[3];

  QThread* thread;
  Worker* worker;

  bool reset;

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
