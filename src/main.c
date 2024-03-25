#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <math.h>
#include <time.h>
#include <strings.h>
#define SCREEN_WIDTH 1800
#define SCREEN_HEIGHT 1000
#define RADIUS 1
#define AMOUNT 10000
#define VELOCITYFACTOR 0.05
#define ACCERATIONFACTOR 1
#define MAXSIZE 1
#define MINDISTANCE 2
#define FORCEDISTANCE RADIUS*40

typedef struct {
    float x;
    float y;
    float xv;
    float yv;
    float mass;
    Color colour;
} Particle;

void ViewParticle(Particle p) {
    printf("x: %f, y: %f, xv: %f, yv: %f, mass: %f\n",p.x,p.y,p.xv,p.yv,p.mass);
}

void DrawParticle(Particle p) {
    DrawCircle(p.x, p.y, p.mass, p.colour);
}

Particle InitParticle(Color colour) {
    Particle p = {(float)(rand() % SCREEN_WIDTH),(float)(rand() % SCREEN_HEIGHT),0,0,(rand() % MAXSIZE) + 1,colour};
    return p;
}

int createGroup(int number,Color colour,Particle* Particles, int index) {
    for (int i = 0;i<number;i++) {
     Particle p = InitParticle(colour);
     Particles[index++] = p;
    }
    return index;

}

void DrawParticles(Particle* Particles, int index) {
    for (int i = 0; i<index;i++) {
        Particle p = Particles[i];
        DrawParticle(p);
    }
}



void rule(Particle* p1, int amountOfP1, Particle* p2, int amountOfP2, float g) {
    for (int i = 0; i<amountOfP1; i++) {
        Particle particle1 = p1[i];
        float fx = 0.0;
        float fy = 0.0;
        for (int j = 0; j<amountOfP2; j++) {
            Particle particle2 = p2[j];
            float dx = particle1.x - particle2.x;
            float dy = particle1.y - particle2.y;
            float distance = (float)sqrt(dx*dx + dy*dy);


            if (distance > MINDISTANCE && distance < FORCEDISTANCE) {
                //float F = g*1/pow(distance,2);
                float F = g*particle1.mass*particle2.mass/distance;
                if (distance <= MINDISTANCE) {
                    F = -1*particle1.mass*particle2.mass/distance;
                }

                fx += F * dx;
                fy += F * dy;
            }

        }

        Particle particleCopy = {particle1.x,particle1.y,particle1.xv,particle1.yv,particle1.mass,particle1.colour};

        particleCopy.xv += fx*ACCERATIONFACTOR;
        particleCopy.yv += fy*ACCERATIONFACTOR;
        particleCopy.x += particleCopy.xv*VELOCITYFACTOR;
        particleCopy.y += particleCopy.yv*VELOCITYFACTOR;

        if (particleCopy.x <= 0 || particleCopy.x >= SCREEN_WIDTH) {
            particleCopy.xv *=-1;
        }
        if (particleCopy.y <= 0 || particleCopy.x >= SCREEN_HEIGHT) {
            particleCopy.yv *=-1;
        }

        p1[i] = particleCopy;
    }

}





int main()
{
    srand(time(NULL));
    //    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    /* init state */
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Circles"); SetTargetFPS(130);
    SetTargetFPS(100);

    Particle ParticlesRED[AMOUNT];
    Particle ParticlesWHITE[AMOUNT];
    Particle ParticlesBLUE[AMOUNT];
    Particle ParticlesGREEN[AMOUNT];
    int indexRED = 0;
    int indexWHITE = 0;
    int indexBLUE = 0;
    int indexGREEN = 0;

    indexRED = createGroup(400,RED,ParticlesRED,indexRED);
    indexWHITE = createGroup(400,WHITE,ParticlesWHITE,indexWHITE);
    indexBLUE = createGroup(400,BLUE,ParticlesBLUE,indexBLUE);
    indexGREEN = createGroup(400,GREEN,ParticlesGREEN,indexGREEN);


    /* make rules */
    



    float FactorREDtoRED = (float)rand()/(float)(RAND_MAX/2) - 1;
    float FactorREDtoWHITE = (float)rand()/(float)(RAND_MAX/2) - 1;
    float FactorREDtoBLUE = (float)rand()/(float)(RAND_MAX/2) - 1;
    float FactorREDtoGREEN = (float)rand()/(float)(RAND_MAX/2) - 1;

    float FactorWHITEtoWHITE = (float)rand()/(float)(RAND_MAX/2) - 1;
    float FactorWHITEtoRED = (float)rand()/(float)(RAND_MAX/2) - 1;
    float FactorWHITEtoBLUE = (float)rand()/(float)(RAND_MAX/2) - 1;
    float FactorWHITEtoGREEN = (float)rand()/(float)(RAND_MAX/2) - 1;

    float FactorBLUEtoBLUE = (float)rand()/(float)(RAND_MAX/2) - 1;
    float FactorBLUEtoWHITE = (float)rand()/(float)(RAND_MAX/2) - 1;
    float FactorBLUEtoRED = (float)rand()/(float)(RAND_MAX/2) - 1;
    float FactorBLUEtoGREEN = (float)rand()/(float)(RAND_MAX/2) - 1;

    float FactorGREENtoGREEN = (float)rand()/(float)(RAND_MAX/2) - 1;
    float FactorGREENtoBLUE = (float)rand()/(float)(RAND_MAX/2) - 1;
    float FactorGREENtoWHITE = (float)rand()/(float)(RAND_MAX/2) - 1;
    float FactorGREENtoRED = (float)rand()/(float)(RAND_MAX/2) - 1;


    printf("Red to Red: %f\n",FactorREDtoRED);
    printf("Red to Blue: %f\n",FactorREDtoBLUE);
    printf("Red to WHITE: %f\n",FactorREDtoWHITE);
    printf("Red to GREEN: %f\n",FactorREDtoGREEN);


    printf("White to White: %f\n",FactorWHITEtoWHITE);
    printf("White to Red: %f\n",FactorWHITEtoRED);
    printf("White to Blue: %f\n",FactorWHITEtoBLUE);
    printf("White to Green: %f\n",FactorWHITEtoGREEN);

    printf("Blue to Blue: %f\n",FactorBLUEtoBLUE);
    printf("Blue to RED: %f\n",FactorBLUEtoRED);
    printf("Blue to WHITE: %f\n",FactorBLUEtoWHITE);
    printf("Blue to GREEN: %f\n",FactorBLUEtoGREEN);


    printf("Green to Green: %f\n",FactorGREENtoGREEN);
    printf("Green to White: %f\n",FactorGREENtoWHITE);
    printf("Green to Blue: %f\n",FactorGREENtoBLUE);
    printf("Green to Red: %f\n",FactorGREENtoRED);


    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        float g = -1.0;



        /* RED */
        rule(ParticlesRED,indexRED,ParticlesRED,indexRED,g*FactorREDtoRED);
        rule(ParticlesRED,indexRED,ParticlesWHITE,indexWHITE,g*FactorREDtoWHITE);
        rule(ParticlesRED,indexRED,ParticlesBLUE,indexBLUE,g*FactorREDtoBLUE);
        rule(ParticlesRED,indexRED,ParticlesGREEN,indexGREEN,g*FactorREDtoGREEN);

        /* WHITE */
        rule(ParticlesWHITE,indexWHITE,ParticlesWHITE,indexWHITE,g*FactorWHITEtoWHITE);
        rule(ParticlesWHITE,indexWHITE,ParticlesRED,indexRED,g*FactorWHITEtoRED);
        rule(ParticlesWHITE,indexWHITE,ParticlesGREEN,indexGREEN,g*FactorWHITEtoGREEN);
        rule(ParticlesWHITE,indexWHITE,ParticlesBLUE,indexBLUE,g*FactorWHITEtoBLUE);
        
        /* BLUE */
        rule(ParticlesBLUE,indexBLUE,ParticlesBLUE,indexBLUE,g*FactorBLUEtoBLUE);
        rule(ParticlesBLUE,indexBLUE,ParticlesWHITE,indexWHITE,g*FactorBLUEtoWHITE);
        rule(ParticlesBLUE,indexBLUE,ParticlesGREEN,indexGREEN,g*FactorBLUEtoGREEN);
        rule(ParticlesBLUE,indexBLUE,ParticlesRED,indexRED,g*FactorBLUEtoRED);

        /* GREEN */
        rule(ParticlesGREEN,indexGREEN,ParticlesGREEN,indexGREEN,g*FactorGREENtoGREEN);
        rule(ParticlesGREEN,indexGREEN,ParticlesWHITE,indexWHITE,g*FactorGREENtoWHITE);
        rule(ParticlesGREEN,indexGREEN,ParticlesBLUE,indexBLUE,g*FactorGREENtoBLUE);
        rule(ParticlesGREEN,indexGREEN,ParticlesRED,indexRED,g*FactorGREENtoRED);



        DrawParticles(ParticlesRED,indexRED);
        DrawParticles(ParticlesWHITE,indexWHITE);
        DrawParticles(ParticlesGREEN,indexGREEN);
        DrawParticles(ParticlesBLUE,indexBLUE);

        EndDrawing();
        }

    CloseWindow();


    return EXIT_SUCCESS;
}
