// From following C++ tutorial from GamedevTV
#include "raylib.h"
int main()
{
    const int windowWidth{512};
    const int windowHeight{380};
    InitWindow(windowWidth, windowHeight, "Dapper Game");

    // pixels/s/s
    const int gravity{1'000};

    // pixels / s
    const int jumpVel{-600};
    
    // Nebula variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    Rectangle nebRec{0.0, 0.0, nebula.width/8, nebula.height/8};
    Vector2 nebPos{windowWidth, windowHeight - nebRec.height};

    // nebula X velocity (pixels/second)
    int nebVel{-600};
    // nebula variabled
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRect;
    scarfyRect.width = scarfy.width/6;
    scarfyRect.height = scarfy.height;
    scarfyRect.x = 0;
    scarfyRect.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = windowWidth/2 - scarfyRect.width/2;
    scarfyPos.y = windowHeight/2 - scarfyRect.height/2;

    int velocity{0};

    bool isInAir{};

    // animation frame
    int frame{};
    const float updateTime{1.0 / 12.0};
    float runningTime{};


    SetTargetFPS(60);
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);

        // delta time
        float dT {GetFrameTime()};

        // ground check
        if(scarfyPos.y >= windowHeight - scarfy.height) {
            velocity = 0;
            isInAir = false;
        }
        else {
            velocity += gravity * dT;
            isInAir = true;
        }

        // Check for jumping
        if(IsKeyPressed(KEY_SPACE) && !isInAir) {
            velocity += jumpVel;
        }
        // update nebula position
        nebPos.x += nebVel * dT;

        // update nebula position
        scarfyPos.y += velocity * dT;

        // update the animation frame
        scarfyRect.x = frame * scarfyRect.width;

        runningTime += dT;

        if(runningTime >= updateTime) {
            runningTime = 0.0;
            frame++;  
        }

        if(frame > 5) {
            frame = 0;
        }
        // draw nebula
        DrawTextureRec(nebula, nebRec, nebPos, WHITE);

        // draw scarfy
        DrawTextureRec(scarfy, scarfyRect, scarfyPos, WHITE);
        //DrawText("Game over!", 400, 200, 20, RED);
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}
