#ifndef MOVABLE_H
#define MOVABLE_H

class Movable {

public:
  Movable() = default;
  virtual void move(float ms) = 0;
  virtual ~Movable() = default;
};

#endif // MOVABLE_H
