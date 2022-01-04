//
// Created by ilias on 4/1/22.
//

#ifndef CHESS_UPDATEABLE_H
#define CHESS_UPDATEABLE_H

class Updateable {
public:
  virtual void update(float ms) = 0;
  virtual ~Updateable() = default;
};

#endif//CHESS_UPDATEABLE_H
