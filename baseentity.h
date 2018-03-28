#ifndef BASEENTITY_H
#define BASEENTITY_H

#include <headers.h>
#include <QBrush>
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
  std::shared_ptr<Position> getPosition();
  void setPosition(std::shared_ptr<Position> position);
  QBrush* getBrush();
  void setBrush(QBrush* pBrush);
  bool isCitizen();
  void setCitizen(bool cit);
};  // TODO interface statt base class

#endif  // BASEENTITY_H
