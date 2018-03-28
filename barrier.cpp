#include "barrier.h"

Barrier::Barrier() {
  QBrush* brush = new QBrush(Qt::gray, Qt::DiagCrossPattern);
  setBrush(brush);
  setCitizen(false);
}
