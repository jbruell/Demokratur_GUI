#ifndef WORKER_H
#define WORKER_H

#include <board.h>
#include <QObject>

class Worker : public QObject {
  Q_OBJECT

 private:
  Board* board;
  int iterations;

 public:
  Worker(Board* board, int pIterations);
  ~Worker();

 public slots:
  void process();

 signals:
  void finished();
  void repaint();
};

#endif  // WORKER_H
