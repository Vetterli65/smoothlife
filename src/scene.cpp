#include "scene.h"

Scene::Scene(int screenWidth, int screenHeight) : screenWidth(screenWidth), screenHeight(screenHeight){
    InitWindow(screenWidth, screenHeight, "Smoothlife");
    SetTargetFPS(60);

    Image image = GenImagePerlinNoise(screenWidth, screenHeight, 0, 0, 5.0f);

    state[0] = LoadRenderTexture(screenWidth, screenHeight);
    SetTextureWrap(state[0].texture, TEXTURE_WRAP_REPEAT);
    SetTextureFilter(state[0].texture, TEXTURE_FILTER_ANISOTROPIC_8X);
    UpdateTexture(state[0].texture, image.data);

    state[1] = LoadRenderTexture(screenWidth, screenHeight);
    SetTextureWrap(state[1].texture, TEXTURE_WRAP_REPEAT);
    SetTextureFilter(state[1].texture, TEXTURE_FILTER_ANISOTROPIC_8X);

    shader = LoadShader(nullptr, "./shader.fs");

    Vector2 resolution = {(float) screenWidth, (float) screenHeight};
    int resolution_loc = GetShaderLocation(shader, "resolution");
    SetShaderValue(shader, resolution_loc, &resolution, SHADER_UNIFORM_VEC2);

    configLoc.b = GetShaderLocation(shader, "b");
    configLoc.d = GetShaderLocation(shader, "d");
    configLoc.alpha = GetShaderLocation(shader, "alphaVec");
    configLoc.dt = GetShaderLocation(shader, "dt");
}

Scene::~Scene(){
    CloseWindow();
}

void Scene::drawControlBox(){
    GuiGroupBox(windowBox, "Smoothlife configuration");
    GuiSlider((Rectangle){windowBox.x + 59, windowBox.y + 148, 120, 16}, "dt", TextFormat("%.3f", config.dt), &config.dt, 0, 5);
    GuiSlider((Rectangle){windowBox.x + 59, windowBox.y + 79, 120, 16}, "d2", TextFormat("%.3f", config.d.y), &config.d.y, 0, 1);
    GuiSlider((Rectangle){windowBox.x + 59, windowBox.y + 57, 120, 16}, "d1", TextFormat("%.3f", config.d.x), &config.d.x, 0, 1);
    GuiSlider((Rectangle){windowBox.x + 59, windowBox.y + 124, 120, 16}, "b2", TextFormat("%.3f", config.b.y), &config.b.y, 0, 1);
    GuiSlider((Rectangle){windowBox.x + 59, windowBox.y + 102, 120, 16}, "b1", TextFormat("%.3f", config.b.x), &config.b.x, 0, 1);
    GuiSlider((Rectangle){windowBox.x + 59, windowBox.y + 12, 120, 16}, "alpha_n", TextFormat("%.3f", config.alphaVec.x), &config.alphaVec.x, 0, 0.1);
    GuiSlider((Rectangle){windowBox.x + 59, windowBox.y + 35, 120, 16}, "alpha_m", TextFormat("%.3f", config.alphaVec.y), &config.alphaVec.y, 0, 0.2);
    GuiCheckBox((Rectangle){ windowBox.x + 10, windowBox.y + 172, 20, 20 }, "Brush Mode", &brushMode);
    if(brushMode) GuiToggleGroup((Rectangle){ windowBox.x + 100, windowBox.y + 172, 50, 20 }, "Birth;Death", &colorMode);
}

void Scene::updateControlBoxLocation(){
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (CheckCollisionPointRec(GetMousePosition(), dragArea)) {
            isDragging = true;
            dragOffset.x = GetMousePosition().x - windowBox.x;
            dragOffset.y = GetMousePosition().y - windowBox.y;
        }
    }

    if (isDragging) {
        windowBox.x = GetMouseX() - dragOffset.x;
        windowBox.y = GetMouseY() - dragOffset.y;

        dragArea.x = windowBox.x;
        dragArea.y = windowBox.y;

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            isDragging = false;
        }
    }
}

void Scene::updateGPUConfig(){
    SetShaderValue(shader, configLoc.b, &config.b, SHADER_UNIFORM_VEC2);
    SetShaderValue(shader, configLoc.d, &config.d, SHADER_UNIFORM_VEC2);
    SetShaderValue(shader, configLoc.alpha, &config.alphaVec, SHADER_UNIFORM_VEC2);
    SetShaderValue(shader, configLoc.dt, &config.dt, SHADER_UNIFORM_FLOAT);
}

void Scene::drawPixels(int i){
    if(brushMode && !CheckCollisionPointRec(GetMousePosition(), windowBox)){
        Vector2 mousePosition = GetMousePosition();
        mousePosition = (Vector2){ mousePosition.x, screenHeight - mousePosition.y};
        BeginTextureMode(state[i]);
            DrawCircleLinesV(mousePosition , 41, RED);
        EndTextureMode();
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
            BeginTextureMode(state[i]);
                DrawCircleV(mousePosition , 40, colors[colorMode]);
            EndTextureMode();
        }   
    }
}

void Scene::run(){
    int i = 0;
    while (!WindowShouldClose()) {
        updateControlBoxLocation();
        updateGPUConfig();

        BeginTextureMode(state[1 - i]);
            ClearBackground(BLACK);
            BeginShaderMode(shader);
                DrawTexture(state[i].texture, 0, 0, WHITE);
            EndShaderMode();
        EndTextureMode();

        drawPixels(1 - i);
        BeginDrawing();
            ClearBackground(BLACK);
            DrawTexture(state[1 - i].texture, 0, 0, WHITE);
            DrawFPS(screenWidth - 80, 10);
            drawControlBox();
        EndDrawing();

        i = 1 - i;
    }
};