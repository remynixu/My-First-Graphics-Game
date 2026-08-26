
/*
#include "core/engine.h"

static struct engine_ctx ctx_data;
struct engine_ctx *const ctx = &ctx_data;

int main(void){
    int errcode = 0;
    {
        struct engine_hint hint;
        {
            hint.target_fps = 60;
        }
        errcode = engine_init(ctx, &hint);
    }
    if(errcode){
        engine_perror(ctx);
        return -1;
    }
    while((*ctx).state == ENGINE_STATE_RUNNING){
        engine_update(ctx);
        engine_render(ctx);
    }
    engine_close(ctx);
    return 0;
}
*/

#include <raylib.h>

/*
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
*/
#include "core/platform/image.h"

#include <stdlib.h>
#include <string.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Manual Rendering");
    SetTargetFPS(60);

    int imgWidth, imgHeight, imgChannels;
    unsigned char *imgPixels = stbi_load("assets/textures/entity/arundel.png", &imgWidth, &imgHeight, &imgChannels, 4); // Force 4 channels (RGBA)

    Color *screenBuffer = (Color *)malloc(SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Color));

    Image canvasImage;
    Texture2D canvasTexture;
    canvasImage.data = screenBuffer;
    canvasImage.width = SCREEN_WIDTH;
    canvasImage.height = SCREEN_HEIGHT;
    canvasImage.mipmaps = 1;
    canvasImage.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;
    canvasTexture = LoadTextureFromImage(canvasImage);

    while (!WindowShouldClose()) {
        int i;
        for (i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
            /*
            screenBuffer[i] = (Color){ 30, 30, 30, 255 };
            */
           screenBuffer[i].r = 30;
           screenBuffer[i].g = 30;
           screenBuffer[i].b = 30;
           screenBuffer[i].a = 255;
        }

        if (imgPixels) {
            int y;
            for (y = 0; y < imgHeight; y++) {
                int x;
                for (x = 0; x < imgWidth; x++) {
                    if (x < SCREEN_WIDTH && y < SCREEN_HEIGHT) {
                        int srcIndex = (y * imgWidth + x) * 4;
                        int destIndex = y * SCREEN_WIDTH + x;

                        /*
                        screenBuffer[destIndex] = (Color){
                            imgPixels[srcIndex],     // R
                            imgPixels[srcIndex+1],   // G
                            imgPixels[srcIndex+2],   // B
                            imgPixels[srcIndex+3]    // A
                        };
                        */
                       screenBuffer[destIndex].r = imgPixels[srcIndex];
                       screenBuffer[destIndex].g = imgPixels[srcIndex + 1];
                       screenBuffer[destIndex].b = imgPixels[srcIndex + 2];
                       screenBuffer[destIndex].a = imgPixels[srcIndex + 3];
                    }
                }
            }
        }

        UpdateTexture(canvasTexture, screenBuffer);

        BeginDrawing();
            DrawTexture(canvasTexture, 0, 0, WHITE);
        EndDrawing();
    }

    if (imgPixels) stbi_image_free(imgPixels);
    free(screenBuffer);
    UnloadTexture(canvasTexture);
    CloseWindow();

    return 0;
}