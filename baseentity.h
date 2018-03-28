#ifndef BASEENTITY_H
#define BASEENTITY_H

#include <headers.h>
#include <QBrush>
#include <QColor>
#include <memory>

class Position;

class BaseEntity {
 private:
  std::shared_ptr<Position> pos;
  QBrush* brush;
  bool citizen;

 public:
  BaseEntity();
  ~BaseEntity();
  void setPosition(std::shared_ptr<Position> position);
  std::shared_ptr<Position> getPosition();
  void setBrush(QBrush* pBrush);
  QBrush* getBrush();
  bool isCitizen();
  void setCitizen(bool cit);
};  // TODO interface statt base class

#endif  // BASEENTITY_H
