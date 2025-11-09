
#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <math.h>
#include <time.h>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define AMOUNT 2500
#define VELOCITYFACTOR 0.5f
#define FRICTION 0.98f
#define MAXSPEED 8.0f
#define MINDISTANCE 10.0f
#define FORCEDISTANCE 150.0f
#define MAXSIZE 1

typedef struct {
    float x;
    float y;
    float xv;
    float yv;
    float mass;
    Color colour;
} Particle;

float sign(float x) { return (x > 0) - (x < 0); }

float randRange(float min, float max) {
    return min + ((float)rand() / RAND_MAX) * (max - min);
}

Particle InitParticle(Color colour) {
    Particle p = {
        (float)((rand() % (SCREEN_WIDTH / 2)) + SCREEN_WIDTH / 4),
        (float)((rand() % (SCREEN_HEIGHT / 2)) + SCREEN_HEIGHT / 4),
        0, 0,
        (rand() % MAXSIZE) + 1,
        colour
    };
    return p;
}

int createGroup(int number, Color colour, Particle *Particles, int index) {
    for (int i = 0; i < number; i++) Particles[index++] = InitParticle(colour);
    return index;
}

void DrawParticles(Particle *Particles, int index) {
    for (int i = 0; i < index; i++)
        DrawCircle(Particles[i].x, Particles[i].y, Particles[i].mass * 3, Particles[i].colour);
}

void rule(Particle *p1, int n1, Particle *p2, int n2, float g) {
    for (int i = 0; i < n1; i++) {
        Particle particle1 = p1[i];
        float fx = 0, fy = 0;

        for (int j = 0; j < n2; j++) {
            Particle particle2 = p2[j];
            float dx = particle2.x - particle1.x;
            float dy = particle2.y - particle1.y;
            float dist = sqrtf(dx * dx + dy * dy);
            if (dist > 0 && dist < FORCEDISTANCE) {
                float force = g * particle2.mass / dist;
                if (dist < MINDISTANCE) force *= -1.5f;
                fx += force * (dx / dist);
                fy += force * (dy / dist);
            }
        }

        particle1.xv += fx * VELOCITYFACTOR;
        particle1.yv += fy * VELOCITYFACTOR;

        particle1.xv *= FRICTION;
        particle1.yv *= FRICTION;

        if (fabsf(particle1.xv) > MAXSPEED) particle1.xv = sign(particle1.xv) * MAXSPEED;
        if (fabsf(particle1.yv) > MAXSPEED) particle1.yv = sign(particle1.yv) * MAXSPEED;

        Particle updated = {
            particle1.x + particle1.xv,
            particle1.y + particle1.yv,
            particle1.xv,
            particle1.yv,
            particle1.mass,
            particle1.colour
        };

        if (updated.x < 0) updated.x += SCREEN_WIDTH;
        if (updated.x >= SCREEN_WIDTH) updated.x -= SCREEN_WIDTH;
        if (updated.y < 0) updated.y += SCREEN_HEIGHT;
        if (updated.y >= SCREEN_HEIGHT) updated.y -= SCREEN_HEIGHT;

        p1[i] = updated;
    }
}

int main() {
    srand(time(NULL));
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Smooth Particle Copy Update");
    SetTargetFPS(120);

    Particle red[AMOUNT], white[AMOUNT], blue[AMOUNT], green[AMOUNT], yellow[AMOUNT];
    int nR = createGroup(AMOUNT / 5, RED, red, 0);
    int nW = createGroup(AMOUNT / 5, WHITE, white, 0);
    int nB = createGroup(AMOUNT / 5, BLUE, blue, 0);
    int nG = createGroup(AMOUNT / 5, GREEN, green, 0);
    int nY = createGroup(AMOUNT / 5, YELLOW, yellow, 0);

    float rules[5][5];
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            rules[i][j] = randRange(-1.0f, 1.0f);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        float g = 0.5f;

        rule(red, nR, red, nR, g * rules[0][0]);
        rule(red, nR, white, nW, g * rules[0][1]);
        rule(red, nR, blue, nB, g * rules[0][2]);
        rule(red, nR, green, nG, g * rules[0][3]);
        rule(red, nR, yellow, nY, g * rules[0][4]);

        rule(white, nW, red, nR, g * rules[1][0]);
        rule(white, nW, white, nW, g * rules[1][1]);
        rule(white, nW, blue, nB, g * rules[1][2]);
        rule(white, nW, green, nG, g * rules[1][3]);
        rule(white, nW, yellow, nY, g * rules[1][4]);

        rule(blue, nB, red, nR, g * rules[2][0]);
        rule(blue, nB, white, nW, g * rules[2][1]);
        rule(blue, nB, blue, nB, g * rules[2][2]);
        rule(blue, nB, green, nG, g * rules[2][3]);
        rule(blue, nB, yellow, nY, g * rules[2][4]);

        rule(green, nG, red, nR, g * rules[3][0]);
        rule(green, nG, white, nW, g * rules[3][1]);
        rule(green, nG, blue, nB, g * rules[3][2]);
        rule(green, nG, green, nG, g * rules[3][3]);
        rule(green, nG, yellow, nY, g * rules[3][4]);

        rule(yellow, nY, red, nR, g * rules[4][0]);
        rule(yellow, nY, white, nW, g * rules[4][1]);
        rule(yellow, nY, blue, nB, g * rules[4][2]);
        rule(yellow, nY, green, nG, g * rules[4][3]);
        rule(yellow, nY, yellow, nY, g * rules[4][4]);

        DrawParticles(red, nR);
        DrawParticles(white, nW);
        DrawParticles(blue, nB);
        DrawParticles(green, nG);
        DrawParticles(yellow, nY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

