#ifndef BASEENTITY_H
#define BASEENTITY_H

#include <headers.h>
#include <memory>

class Position;

class BaseEntity {
 private:
  std::shared_ptr<Position> pos;

 public:
  BaseEntity();
  ~BaseEntity();
  void setPosition(std::shared_ptr<Position> position);
  std::shared_ptr<Position> getPosition();
};

#endif  // BASEENTITY_H
