#include "worker.h"

Worker::Worker(Board* pBoard, int pIterations) {
  board = pBoard;
  iterations = pIterations;
  remainingIterations = iterations;

  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(process()));
}

Worker::~Worker() {}

void Worker::start() {
  timer->start(100);
}

void Worker::stop() {
  timer->stop();
}

void Worker::setBoard(Board* pBoard) {
  board = pBoard;
  remainingIterations = iterations;
}

void Worker::process() {
  std::vector<std::shared_ptr<BaseEntity>>* entities = board->getBaseEntities();
  for (std::shared_ptr<BaseEntity> entity : *entities) {
    if (entity->isCitizen()) {
      switch (rand() % 4) {
        case 0:
          left(entity);
          break;
        case 1:
          right(entity);
          break;
        case 2:
          up(entity);
          break;
        case 3:
          down(entity);
          break;
      }
    }
  }
  board->resetTalkingStatus();
  emit repaint();
  if (QThread::currentThread()->isInterruptionRequested()) {
    return;
  }
  if (board->isDictatorship()) {
    emit finished();
  }
}

void Worker::left(std::shared_ptr<BaseEntity> cit) {
  board->moveWest(cit);
}

void Worker::right(std::shared_ptr<BaseEntity> cit) {
  board->moveEast(cit);
}

void Worker::up(std::shared_ptr<BaseEntity> cit) {
  board->moveNorth(cit);
}

void Worker::down(std::shared_ptr<BaseEntity> cit) {
  board->moveSouth(cit);
}
