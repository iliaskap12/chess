#ifndef PROMOTABLE_H
#define PROMOTABLE_H

class Promotable {

public:
  Promotable() = default;
  virtual void promote() = 0;
  virtual ~Promotable() = default;
};

#endif // PROMOTABLE_H
