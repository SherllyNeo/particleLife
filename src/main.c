#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <math.h>
#include <time.h>
#include <strings.h>
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define RADIUS 5
#define AMOUNT 2500
#define VELOCITYFACTOR 0.1
#define FRICTION 0
#define WALLBOUNCE 1
#define MAXSIZE 1
#define MAXSPEED 30
#define MINDISTANCE 1
#define FORCEDISTANCE RADIUS*SCREEN_WIDTH*SCREEN_HEIGHT*0.00004

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
    DrawCircle(p.x, p.y, p.mass*3, p.colour);
}

Particle InitParticle(Color colour) {
    Particle p = {(float)((rand() % SCREEN_WIDTH/4) + SCREEN_WIDTH/2),(float)((rand() % SCREEN_HEIGHT/4) + SCREEN_HEIGHT/2),0,0,(rand() % MAXSIZE) + 1,colour};
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
                    F = -g*particle1.mass*particle2.mass/distance;
                }


                fx += (F - particle1.xv*FRICTION) * dx;
                fy += (F - particle1.yv*FRICTION) * dy;
                particle1.xv = (particle1.xv + fx)*VELOCITYFACTOR;
                particle1.yv = (particle1.yv + fy)*VELOCITYFACTOR;
            }

        }

        Particle particleCopy = {particle1.x,particle1.y,particle1.xv,particle1.yv,particle1.mass,particle1.colour};

        particleCopy.x += particleCopy.xv;
        particleCopy.y += particleCopy.yv;

//        if (particleCopy.x <= 0 || particleCopy.x >= SCREEN_WIDTH) {
//            particleCopy.xv *= -1;
//            particleCopy.xv *= WALLBOUNCE;
//        }
//        if (particleCopy.y <= 0 || particleCopy.y >= SCREEN_HEIGHT) {
//            particleCopy.yv *= -1;
//            particleCopy.yv *= WALLBOUNCE;;
//
        particleCopy.x = (((int)particleCopy.x+SCREEN_WIDTH) % SCREEN_WIDTH);
        particleCopy.y = (((int)particleCopy.y+SCREEN_HEIGHT) % SCREEN_HEIGHT);



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
    Particle ParticlesYELLOW[AMOUNT];
    int indexRED = 0;
    int indexWHITE = 0;
    int indexBLUE = 0;
    int indexGREEN = 0;
    int indexYELLOW = 0;

    indexRED = createGroup(AMOUNT/5,RED,ParticlesRED,indexRED);
    indexWHITE = createGroup(AMOUNT/5,WHITE,ParticlesWHITE,indexWHITE);
    indexBLUE = createGroup(AMOUNT/5,BLUE,ParticlesBLUE,indexBLUE);
    indexGREEN = createGroup(AMOUNT/5,GREEN,ParticlesGREEN,indexGREEN);
    indexYELLOW = createGroup(AMOUNT/5,YELLOW,ParticlesYELLOW,indexYELLOW);


    /* make rules */
    



    float FactorREDtoRED = (float)rand()/(float)(RAND_MAX/2) - 1;
    float FactorREDtoWHITE = (float)rand()/(float)(RAND_MAX/2) - 1;
    float FactorREDtoBLUE = (float)rand()/(float)(RAND_MAX/2) - 1;
    float FactorREDtoGREEN = (float)rand()/(float)(RAND_MAX/2) - 1;
    float FactorREDtoYELLOW = (float)rand()/(float)(RAND_MAX/2) - 1;

    float FactorWHITEtoWHITE = (float)rand()/(float)(RAND_MAX/2) - 1;
    float FactorWHITEtoRED = (float)rand()/(float)(RAND_MAX/2) - 1;
    float FactorWHITEtoBLUE = (float)rand()/(float)(RAND_MAX/2) - 1;
    float FactorWHITEtoGREEN = (float)rand()/(float)(RAND_MAX/2) - 1;
    float FactorWHITEtoYELLOW = (float)rand()/(float)(RAND_MAX/2) - 1;

    float FactorBLUEtoBLUE = (float)rand()/(float)(RAND_MAX/2) - 1;
    float FactorBLUEtoWHITE = (float)rand()/(float)(RAND_MAX/2) - 1;
    float FactorBLUEtoRED = (float)rand()/(float)(RAND_MAX/2) - 1;
    float FactorBLUEtoGREEN = (float)rand()/(float)(RAND_MAX/2) - 1;
    float FactorBLUEtoYELLOW = (float)rand()/(float)(RAND_MAX/2) - 1;

    float FactorGREENtoGREEN = (float)rand()/(float)(RAND_MAX/2) - 1;
    float FactorGREENtoBLUE = (float)rand()/(float)(RAND_MAX/2) - 1;
    float FactorGREENtoWHITE = (float)rand()/(float)(RAND_MAX/2) - 1;
    float FactorGREENtoRED = (float)rand()/(float)(RAND_MAX/2) - 1;
    float FactorGREENtoYELLOW = (float)rand()/(float)(RAND_MAX/2) - 1;

    float FactorYELLOWtoYELLOW = (float)rand()/(float)(RAND_MAX/2) - 1;
    float FactorYELLOWtoGREEN = (float)rand()/(float)(RAND_MAX/2) - 1;
    float FactorYELLOWtoBLUE = (float)rand()/(float)(RAND_MAX/2) - 1;
    float FactorYELLOWtoWHITE = (float)rand()/(float)(RAND_MAX/2) - 1;
    float FactorYELLOWtoRED = (float)rand()/(float)(RAND_MAX/2) - 1;


    printf("Red to Red: %f\n",FactorREDtoRED);
    printf("Red to Blue: %f\n",FactorREDtoBLUE);
    printf("Red to WHITE: %f\n",FactorREDtoWHITE);
    printf("Red to GREEN: %f\n",FactorREDtoGREEN);
    printf("Red to Yellow: %f\n",FactorREDtoYELLOW);


    printf("White to White: %f\n",FactorWHITEtoWHITE);
    printf("White to Red: %f\n",FactorWHITEtoRED);
    printf("White to Blue: %f\n",FactorWHITEtoBLUE);
    printf("White to Green: %f\n",FactorWHITEtoGREEN);
    printf("White to Yellow: %f\n",FactorWHITEtoYELLOW);

    printf("Blue to Blue: %f\n",FactorBLUEtoBLUE);
    printf("Blue to RED: %f\n",FactorBLUEtoRED);
    printf("Blue to WHITE: %f\n",FactorBLUEtoWHITE);
    printf("Blue to GREEN: %f\n",FactorBLUEtoGREEN);
    printf("Blue to Yellow: %f\n",FactorBLUEtoYELLOW);


    printf("Green to Green: %f\n",FactorGREENtoGREEN);
    printf("Green to White: %f\n",FactorGREENtoWHITE);
    printf("Green to Blue: %f\n",FactorGREENtoBLUE);
    printf("Green to Red: %f\n",FactorGREENtoRED);
    printf("Green to Yellow: %f\n",FactorGREENtoYELLOW);

    printf("Yellow to Yellow: %f\n",FactorREDtoYELLOW);
    printf("Yellow to Green: %f\n",FactorYELLOWtoGREEN);
    printf("Yellow to White: %f\n",FactorYELLOWtoWHITE);
    printf("Yellow to Blue: %f\n",FactorYELLOWtoBLUE);
    printf("Yellow to Red: %f\n",FactorYELLOWtoRED);


    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        float g = -1.0;



        /* RED */
        rule(ParticlesRED,indexRED,ParticlesRED,indexRED,g*FactorREDtoRED);
        rule(ParticlesRED,indexRED,ParticlesWHITE,indexWHITE,g*FactorREDtoWHITE);
        rule(ParticlesRED,indexRED,ParticlesBLUE,indexBLUE,g*FactorREDtoBLUE);
        rule(ParticlesRED,indexRED,ParticlesGREEN,indexGREEN,g*FactorREDtoGREEN);
        rule(ParticlesRED,indexRED,ParticlesYELLOW,indexYELLOW,g*FactorREDtoYELLOW);

        /* WHITE */
        rule(ParticlesWHITE,indexWHITE,ParticlesWHITE,indexWHITE,g*FactorWHITEtoWHITE);
        rule(ParticlesWHITE,indexWHITE,ParticlesRED,indexRED,g*FactorWHITEtoRED);
        rule(ParticlesWHITE,indexWHITE,ParticlesGREEN,indexGREEN,g*FactorWHITEtoGREEN);
        rule(ParticlesWHITE,indexWHITE,ParticlesBLUE,indexBLUE,g*FactorWHITEtoBLUE);
        rule(ParticlesWHITE,indexWHITE,ParticlesYELLOW,indexYELLOW,g*FactorWHITEtoYELLOW);
        
        /* BLUE */
        rule(ParticlesBLUE,indexBLUE,ParticlesBLUE,indexBLUE,g*FactorBLUEtoBLUE);
        rule(ParticlesBLUE,indexBLUE,ParticlesWHITE,indexWHITE,g*FactorBLUEtoWHITE);
        rule(ParticlesBLUE,indexBLUE,ParticlesGREEN,indexGREEN,g*FactorBLUEtoGREEN);
        rule(ParticlesBLUE,indexBLUE,ParticlesRED,indexRED,g*FactorBLUEtoRED);
        rule(ParticlesBLUE,indexBLUE,ParticlesYELLOW,indexYELLOW,g*FactorBLUEtoYELLOW);

        /* GREEN */
        rule(ParticlesGREEN,indexGREEN,ParticlesGREEN,indexGREEN,g*FactorGREENtoGREEN);
        rule(ParticlesGREEN,indexGREEN,ParticlesWHITE,indexWHITE,g*FactorGREENtoWHITE);
        rule(ParticlesGREEN,indexGREEN,ParticlesBLUE,indexBLUE,g*FactorGREENtoBLUE);
        rule(ParticlesGREEN,indexGREEN,ParticlesRED,indexRED,g*FactorGREENtoRED);
        rule(ParticlesGREEN,indexGREEN,ParticlesYELLOW,indexYELLOW,g*FactorGREENtoYELLOW);

        /* YELLOW */
        rule(ParticlesYELLOW,indexYELLOW,ParticlesYELLOW,indexYELLOW,g*FactorYELLOWtoYELLOW);
        rule(ParticlesYELLOW,indexYELLOW,ParticlesWHITE,indexWHITE,g*FactorYELLOWtoWHITE);
        rule(ParticlesYELLOW,indexYELLOW,ParticlesBLUE,indexBLUE,g*FactorYELLOWtoBLUE);
        rule(ParticlesYELLOW,indexYELLOW,ParticlesRED,indexRED,g*FactorYELLOWtoRED);
        rule(ParticlesYELLOW,indexYELLOW,ParticlesGREEN,indexGREEN,g*FactorYELLOWtoGREEN);



        DrawParticles(ParticlesRED,indexRED);
        DrawParticles(ParticlesWHITE,indexWHITE);
        DrawParticles(ParticlesGREEN,indexGREEN);
        DrawParticles(ParticlesBLUE,indexBLUE);
        DrawParticles(ParticlesYELLOW,indexYELLOW);

        EndDrawing();
        }

    CloseWindow();


    return EXIT_SUCCESS;
}
