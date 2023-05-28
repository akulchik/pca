#ifndef VENUS_ENGINE_ANIMATION_ENGINE_H
#define VENUS_ENGINE_ANIMATION_ENGINE_H

#include <vector>

#include <emscripten/emscripten.h>

#include "animation.h"

namespace venus {

class AnimationEngine {
public:
  AnimationEngine();

  void add_animation(Animation* animation);
  void start();
  void stop();

private:
  std::vector<Animation*> animations;
  bool is_animating;

  static void animateWrapper(void* user_data);

  void animate();

};

} // namespace venus

#endif