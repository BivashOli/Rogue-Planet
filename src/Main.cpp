#include "raylib.h"
#include <vector>
#include <string>
#include <iostream>

class Sprite
{
public:
    double x, y, width, height;
    Rectangle spriteRectangle;
    Texture2D spriteSheet;

    Sprite(double x, double y, double width, double height, Rectangle spriteRectangle, Texture2D spriteSheet)
    {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
        this->spriteRectangle = spriteRectangle;
        this->spriteSheet = spriteSheet;
    }

    void render()
    {
        DrawTextureRec(spriteSheet, spriteRectangle, (Vector2){(float)x, (float)y}, BLUE);
    }

    virtual void update()
    {
        // std::cout << "Hello World!";
    }
};

class Scene
{
public:
    std::string name;
    std::vector<Sprite *> sprites;
    Scene(std::string name, std::vector<Sprite *> sprites)
        : name(name), sprites(sprites)
    {
    }
};

Scene currentScene;

Scene LoadScene(std::string )
{
}

class Player : public Sprite
{
public:
    double velocity = 200;
    Player(double x, double y, double width, double height, Rectangle spriteRectangle, Texture2D spriteSheet)
        : Sprite(x, y, width, height, spriteRectangle, spriteSheet)
    {
    }
    void update() override
    {
        move();
    }
    void move()
    {

        if (IsKeyDown(KEY_D))
        {
            x += velocity * GetFrameTime();
        }
        else if (IsKeyDown(KEY_A))
        {
            x -= velocity * GetFrameTime();
        }
    }
};

void Setup()
{
    InitWindow(800, 450, "Monster Collector");
    SetWindowSize(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()));
    ToggleFullscreen();
}

int main(void)
{

    Setup();
    // SetConfigFlags(FLAG_VSYNC_HINT);

    std::vector<Texture2D> spriteSheets;
    std::vector<Scene *> scenes;
    std::vector<Sprite *> sprites;

    Texture2D tileset = LoadTexture("master-tileset.png");
    spriteSheets.push_back(tileset);
    sprites.push_back(new Player(20, 20, 64, 64, Rectangle{64, 0, 64, 64}, spriteSheets.at(0)));
    sprites.push_back(new Sprite(100, 200, 64, 64, Rectangle{64, 64, 64, 64}, spriteSheets.at(0)));

    scenes.push_back(new Scene("Level1", sprites));
    currentScene = scenes

        // SetWindowPosition((int)(GetMonitorWidth(display) / 2) - (int)(GetMonitorHeight(display) / 2), (int)(GetMonitorWidth(display) / 2) - (int)(GetMonitorHeight(display) / 2));
        while (!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(RAYWHITE);
        for (Sprite *s : sprites)
        {
            s->render();
            s->update();
        }
        EndDrawing();
    }

    for (Sprite *sprite : sprites)
    {
        delete sprite;
    }
    sprites.clear();

    CloseWindow();

    return 0;
}