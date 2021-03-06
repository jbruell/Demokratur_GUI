#include "worker.h"

Worker::Worker(Board* pBoard, int pIterations) {
  board = pBoard;
  iterations = pIterations;
  remainingIterations = iterations;
  connect(board, SIGNAL(isDictatorship()), this, SLOT(isDictatorship()));
}

Worker::~Worker() {}

void Worker::setBoard(Board* pBoard) {
  board = pBoard;
  remainingIterations = iterations;
}

void Worker::process() {
  std::srand((unsigned)time(NULL));
  for (int i = 0; i < remainingIterations; i++) {
    board->prepareEncounter(0);
    if (i % 1000 == 0) {
      emit repaint();
      if (board->isDictatorship()) {
        remainingIterations = iterations;
        emit finished();
        return;
      }
    }
    if (QThread::currentThread()->isInterruptionRequested()) {
      remainingIterations = iterations - i;
      return;
    }
  }
  emit finished();
}
