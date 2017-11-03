#include <jni.h>
#include <string>

// Link following functions C-style (required for plugins)
extern "C"
{
    // The functions we will call from Unity.

    const char* PrintHello() {
        return "Hello";
    }

    int PrintANumber() {
        return 5;
    }

    int AddTwoIntegers(int a, int b) {
        return a + b;
    }

    float AddTwoFloats(float a, float b) {
        return a + b;
    }

} // end of export C block