#include "barrier.h"

// public methods

Barrier::Barrier() {
  QBrush* brush = new QBrush(Qt::gray, Qt::DiagCrossPattern);
  setBrush(brush);
  setCitizen(false);
}
