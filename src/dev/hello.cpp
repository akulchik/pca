#include <iostream>

#include <emscripten/emscripten.h>

#ifdef __cplusplus
#define EXTERN extern "C"
#else
#define EXTERN
#endif


[[nodiscard]]
auto main() -> int {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}

EXTERN EMSCRIPTEN_KEEPALIVE auto add_two_numbers(double a, double b) -> double {
    return a + b;
}
