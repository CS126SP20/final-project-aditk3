// Copyright (c) 2020 [Your Name]. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_EXAMPLE_H_
#define FINALPROJECT_MYLIBRARY_EXAMPLE_H_

#include <mylibrary/paddle.h>
#include <mylibrary/player.h>

namespace brickbreaker {
class Engine {
  Paddle paddle_;
  size_t width_{600}, height_{600}, score_{}, lives_{3};

 public:
  //    Engine() {}
  size_t Score() { return score_; }
  size_t Lives() { return lives_; }
};
}  // namespace brickbreaker

#endif  // FINALPROJECT_MYLIBRARY_EXAMPLE_H_
