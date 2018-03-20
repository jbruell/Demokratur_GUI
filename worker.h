#ifndef WORKER_H
#define WORKER_H

#include <board.h>
#include <QObject>
#include <QThread>

class Worker : public QObject {
  Q_OBJECT

 private:
  Board* board;
  int iterations;
  int remainingIterations;

 public:
  Worker(Board* board, int pIterations);
  ~Worker();

 public slots:
  void process();
  void setBoard(Board* pBoard);

 signals:
  void finished();
  void repaint();
};

#endif  // WORKER_H
