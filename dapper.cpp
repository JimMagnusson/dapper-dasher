// From following C++ tutorial from GamedevTV
#include "raylib.h"

struct AnimData 
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};
int main()
{
    int windowDimensions[2];
    windowDimensions[0] = 512;
    windowDimensions[1] = 380;

    InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Game");

    // pixels/s/s
    const int gravity{1'000};

    // pixels / s
    const int jumpVel{-600};
    
    // Nebula variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    AnimData nebData{
        {0.0, 0.0, nebula.width/8, nebula.height/8}, // Rectangle rec
        {windowDimensions[0], windowDimensions[1] - nebula.height/8}, // Vector2 pos
        0, // int frame
        1.0/12.0, // float updateTime
        0 // float runningTime
    };
    // nebula X velocity (pixels/second)
    int nebVel{-200};

    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width/6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = windowDimensions[0]/2 - scarfyData.rec.width/2;
    scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0/12.0;
    scarfyData.runningTime = 0.0;

    int velocity{0};

    bool isInAir{};

    SetTargetFPS(60);
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);

        // delta time
        float dT {GetFrameTime()};

        // ground check
        if(scarfyData.pos.y >= windowDimensions[1] - scarfyData.rec.height) {
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
        nebData.pos.x += nebVel * dT;

        // update scarfy position
        scarfyData.pos.y += velocity * dT;

        // update scarfy's animation frame
        if(!isInAir) {
            scarfyData.runningTime += dT;
            if(scarfyData.runningTime >= scarfyData.updateTime) {
                scarfyData.runningTime = 0.0;
                
                // update the animation frame
                scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
                scarfyData.frame++; 
                if(scarfyData.frame > 5) {
                    scarfyData.frame = 0;
                } 
            }
        }

        // update neb running time
        nebData.runningTime += dT;
        if(nebData.runningTime >= nebData.updateTime) {
            nebData.runningTime = 0.0;
            
            // update the animation frame
            nebData.rec.x = nebData.frame * nebData.rec.width;
            nebData.frame++;
            if(nebData.frame > 7) {
                nebData.frame = 0;
            } 
        }

        // draw nebula
        DrawTextureRec(nebula, nebData.rec, nebData.pos, WHITE);

        // draw scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);
        //DrawText("Game over!", 400, 200, 20, RED);
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}
