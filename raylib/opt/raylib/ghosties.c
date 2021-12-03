#include <math.h>
#include "raylib.h"
#include <stdio.h>
#include "string.h"

#define MAX_TOUCH_POINTS 10

const int ghostCount = 100;
const int width = 800;
const int height = 480;

typedef struct Ghosty
{
    Texture2D *tex;
    Vector2 loc;
    Vector2 vel;
} Ghosty;

void updateGhosts(Ghosty *ghosts, float delta)
{
    for (int i = 0; i < ghostCount; i++)
    {
        ghosts[i].loc.x += ghosts[i].vel.x * delta;
        ghosts[i].loc.y += ghosts[i].vel.y * delta;

        if (ghosts[i].loc.x < -65)
            ghosts[i].loc.x = GetScreenWidth() + 64;
        else if (ghosts[i].loc.x > GetScreenWidth() + 65)
            ghosts[i].loc.x = -64;

        if (ghosts[i].loc.y < -65)
            ghosts[i].loc.y = GetScreenHeight() + 39;
        else if (ghosts[i].loc.y > GetScreenHeight() + 65)
            ghosts[i].loc.y = -64;
    }
}

int main(void)
{
    Font font = GetFontDefault();
    Ghosty ghosts[ghostCount];

    InitWindow(width, height, "Ghosties");
    SetTargetFPS(60);

    bool gameShouldEnd = false;
    Texture2D boo1 = LoadTexture("boo1.png");
    Texture2D boo2 = LoadTexture("boo2.png");
    Texture2D boo3 = LoadTexture("boo3.png");

    int zoom = 3;

    for (int i = 0; i < ghostCount; i++)
    {
        switch (GetRandomValue(0, 2))
        {
        case 0:
            ghosts[i].tex = &boo1;
            ghosts[i].vel = (Vector2){
                GetRandomValue(1, 100) - 50,
                GetRandomValue(1, 40) - 20};

            break;
        case 1:
            ghosts[i].tex = &boo2;
            ghosts[i].vel = (Vector2){
                GetRandomValue(1, 299) - 100,
                GetRandomValue(1, 60) - 30};

            break;
        case 2:
            ghosts[i].tex = &boo3;
            ghosts[i].vel = (Vector2){
                GetRandomValue(1, 20) - 10,
                GetRandomValue(1, 10) - 5};

            break;
        }

        ghosts[i].loc = (Vector2){
            GetRandomValue(0, width),
            GetRandomValue(0, height)};
    };

    Vector2 boo1Loc = {
        GetRandomValue(0, GetScreenWidth()),
        GetRandomValue(0, GetScreenHeight())};

    Vector2 boo2Loc = {
        GetRandomValue(0, GetScreenWidth()),
        GetRandomValue(0, GetScreenHeight())};

    int distance = height / 2.0f - 32;
    if (width < height)
        distance = width / 2.0f - 32;

    while (!WindowShouldClose() && !gameShouldEnd)
    {
        float delta = GetFrameTime();
        int currentGesture = GetGestureDetected();
        Vector2 mousePosition = GetMousePosition();
        Vector2 touchPosition = GetTouchPosition(0);

        /* 0 = MOUSE_BUTTON_DOWN which isn't defined on rpi for some reason */
        if (IsMouseButtonPressed(0))
        {
            Vector2 position = mousePosition;
        }

        updateGhosts(ghosts, delta);

        BeginDrawing();
        {
            ClearBackground(BLACK);
            for (int i = 0; i < ghostCount; i++)
            {
                float alpha = 1.0f;

                float xDif = width / 2.0f - ghosts[i].loc.x;
                float yDif = height / 2.0f - ghosts[i].loc.y;
                float distance = sqrtf(xDif * xDif + yDif * yDif);

                if (IsMouseButtonDown(0))
                {
                    gameShouldEnd = true;
                }

                alpha = distance * 4 / height / 2;
                if (alpha < 0)
                    alpha = 0.0f;
                if (alpha > 1.0f)
                    alpha = 1.0f;
                alpha = 1 - alpha;

                Color myColor = Fade(WHITE, alpha);

                if (ghosts[i].vel.x < 0)
                {
                    // flying left
                    DrawTexturePro(*ghosts[i].tex, (Rectangle){0, 0, -boo1.width, boo1.height}, (Rectangle){ghosts[i].loc.x, ghosts[i].loc.y, boo1.width * zoom, boo1.height * zoom}, (Vector2){boo1.width / 2 * zoom, boo1.height / 2 * zoom}, 0.0f, myColor);
                }
                else
                {
                    // flying right
                    DrawTexturePro(*ghosts[i].tex, (Rectangle){0, 0, boo1.width, boo1.height}, (Rectangle){ghosts[i].loc.x, ghosts[i].loc.y, boo1.width * zoom, boo1.height * zoom}, (Vector2){boo1.width / 2 * zoom, boo1.height / 2 * zoom}, 0.0f, myColor);
                }
            }
        }
        EndDrawing();
    }

    CloseWindow();
}
