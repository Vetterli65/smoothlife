#ifndef SCENE_H
#define SCENE_H

#include <raylib.h>
#include <raygui.h>

// Default configuration for simulation
struct Config{
    Vector2 alphaVec = {0.028f, 0.147f};
    Vector2 b = {0.278f, 0.365f};
    Vector2 d = {0.267f, 0.445f};
    float dt = 1.0f;
};

struct ConfigLoc{
    int alpha;
    int b;
    int d;
    int dt;
};

class Scene{
    public:
        Scene(int screenWidth, int screenHeight);
        ~Scene();
        void run();
    private:
        int screenWidth;
        int screenHeight;
        
        RenderTexture2D state[2];
        Shader shader;
        Config config;
        ConfigLoc configLoc;

        Vector2 dragOffset = {0.0f, 0.0f};
        Rectangle windowBox = {25, 81, 216, 200};
        Rectangle dragArea = {25, 81, 216, 20}; 

        bool isDragging = false;
        bool brushMode = false;
        Color colors[2] = {WHITE, BLACK};
        int colorMode = 0;
        void updateControlBoxLocation();
        void updateGPUConfig();
        void drawControlBox();
        void drawPixels(int i);
};

#endif // SCENE_H