#include "worker.h"

Worker::Worker(Board* pBoard, int pIterations) {
  // you could copy data from constructor arguments to internal variables here.
  board = pBoard;
  iterations = pIterations;
}

// --- DECONSTRUCTOR ---
Worker::~Worker() {
  // free resources
}

// --- PROCESS ---
// Start processing data.
void Worker::process() {
  // allocate resources using new here
  std::srand((unsigned)time(NULL));
  for (int i = 0; i < iterations; i++) {
    board->prepareEncounter(0);
    if (i % 1000 == 0) {
      emit repaint();
    }
  }
  emit finished();
}
