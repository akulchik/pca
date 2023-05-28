#ifndef VENUS_ENGINE_ANIMATION_H
#define VENUS_ENGINE_ANIMATION_H

#include <emscripten/emscripten.h>


namespace venus {

class Animation {
public:
  Animation(double duration);
  virtual ~Animation();

  virtual void update(double progress) = 0;
  virtual void complete() = 0;

  double duration;
  double start_time;
  bool is_started;
};

} // namespace venus

#endif
