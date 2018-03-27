#ifndef BASEENTITY_H
#define BASEENTITY_H

#include <headers.h>
#include <QColor>
#include <memory>

class Position;

class BaseEntity {
 private:
  std::shared_ptr<Position> pos;
  QColor color;
  bool citizen;

 public:
  BaseEntity();
  ~BaseEntity();
  void setPosition(std::shared_ptr<Position> position);
  std::shared_ptr<Position> getPosition();
  void setColor(QColor col);
  QColor getColor();
  bool isCitizen();
  void setCitizen(bool cit);
};  // TODO interface statt base class

#endif  // BASEENTITY_H
