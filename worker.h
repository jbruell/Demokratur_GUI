#ifndef WORKER_H
#define WORKER_H

#include <board.h>
#include <QObject>
#include <QThread>
#include <QTimer>

class Worker : public QObject {
  Q_OBJECT

 private:
  Board* board;
  QTimer* timer;
  int iterations;
  int remainingIterations;

 public:
  Worker(Board* board, int pIterations);
  ~Worker();

 public slots:
  void process();
  void setBoard(Board* pBoard);

  void left(std::shared_ptr<BaseEntity> cit);
  void right(std::shared_ptr<BaseEntity> cit);
  void up(std::shared_ptr<BaseEntity> cit);
  void down(std::shared_ptr<BaseEntity> cit);

 signals:
  void finished();
  void repaint();
};

#endif  // WORKER_H
