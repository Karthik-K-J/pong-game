#include <iostream>
#include <raylib.h>

using namespace std;

int player_score = 0;
int cpu_score = 0;

class Ball
{
    public:
    float x,y;
    int speed_x, speed_y;
    int radius;

    void Draw()
    {
         DrawCircle(x, y, radius, WHITE);
    }

    void Update()
    {
        x += speed_x;
        y += speed_y;
        if(y + radius >= GetScreenHeight() || y - radius <= 0){
            speed_y *= -1;
        }
        if(x + radius >= GetScreenWidth() || x - radius <= 0){
            speed_x *= -1;
        }
    }
};

class Paddle
{
    protected:
    void LimitMovement()
    {
        if(y <= 0)
        {
            y = 0;
        }
        if(y + height >= GetScreenHeight())
        {
            y = GetScreenHeight() - height;
        }
    }

    public:
    int speed;
    float x, y;
    float height, width;

    void Draw(){
         DrawRectangle(x, y, width, height, WHITE);
    }

    void Update(){
        if(IsKeyDown(KEY_UP))
        {
            y = y - speed;
        }
        if(IsKeyDown(KEY_DOWN))
        {
            y = y + speed;
        }

        LimitMovement();
    }
};

class CpuPaddle: public Paddle
{
    public:

    void Update(int ball_y)
    {
        if(y + height/2 > ball_y )
        {
            y = y - speed;
        }
        if(y + height/2 <= ball_y )
        {
            y = y + speed;
        }
        LimitMovement();
    }

};

Ball ball;
Paddle player;
CpuPaddle cpu;

int main () {

    const int screenWidth = 1280;
    const int screenHeight = 800;

    cout << "Hello World" << endl;

    InitWindow(screenWidth, screenHeight, "My first RAYLIB program!");
    SetTargetFPS(60);

    ball.radius=20;
    ball.x=screenWidth/2;
    ball.y=screenHeight/2;
    ball.speed_x=7;
    ball.speed_y=7;

    player.width = 25;
    player.height = 120;
    player.x = screenWidth - player.width -10;
    player.y = screenHeight/2 - player.height/2;
    player.speed = 6;

    cpu.height = 120;
    cpu.width = 25;
    cpu.x = 10;
    cpu.y = screenHeight/2 - cpu.height/2;
    cpu.speed = 6;

    while (WindowShouldClose() == false){
        BeginDrawing();

        ClearBackground(BLACK);
        ball.Update();
        player.Update();
        cpu.Update(ball.y);

        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.height}))
        {
            ball.speed_x *= -1;
        }
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{cpu.x, cpu.y, cpu.width, cpu.height}))
        {
            ball.speed_x *= -1;
        }
        
        DrawLine(screenWidth/2, 0, screenWidth/2, screenHeight, WHITE);
        ball.Draw();
        cpu.Draw();
        player.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}