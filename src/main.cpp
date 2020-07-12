#define STB_IMAGE_IMPLEMENTATION

#include "Constants.h"
#include "Engine.h"

#include "stb_image.h"

int main(int argc, const char * argv[]) {
    Engine *engine = new Engine();
    engine->Initialize(WINDOW_WIDTH, WINDOW_HEIGHT);

    while(engine->IsRunning()) {
        engine->ProcessInput();
        engine->Update();
        engine->Render();
    }

    engine->Destroy();

    return 0;
}