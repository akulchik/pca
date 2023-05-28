#include <vector>

#include <emscripten/emscripten.h>

#include "animation_engine.h"


namespace venus {

AnimationEngine::AnimationEngine() : is_animating(false) {}

void AnimationEngine::add_animation(Animation* animation) {
    animations.push_back(animation);
}

void AnimationEngine::start() {
    if (is_animating) return;
    is_animating = true;
    emscripten_set_main_loop_arg(reinterpret_cast<em_arg_callback_func>(animateWrapper), this, 0, true);
}

void AnimationEngine::stop() {
    if (!is_animating) return;
    is_animating = false;
    emscripten_cancel_main_loop();
}

void AnimationEngine::animateWrapper(void* user_data) {
    AnimationEngine* engine = static_cast<AnimationEngine*>(user_data);
    engine->animate();
}

void AnimationEngine::animate() {
double current_time = emscripten_get_now();
    for (auto it = animations.begin(); it != animations.end();) {
      Animation* animation = *it;

      if (!animation->is_started) {
        animation->start_time = current_time;
        animation->is_started = true;
      }

      double elapsed = current_time - animation->start_time;
      double progress = std::min(elapsed / animation->duration, 1.0);

      animation->update(progress);

      if (elapsed >= animation->duration) {
        animation->complete();
        delete animation;
        it = animations.erase(it);
      } else {
        ++it;
      }
    }

    if (animations.size() == 0) {
      is_animating = false;
    }
  }

} // namespace venus
