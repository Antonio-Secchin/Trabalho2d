#include "tiro.h"
#include <math.h>
#define DISTANCIA_MAX 500

void Tiro::DesenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B)
{
    GLfloat x, y;
    glColor3f(R, G, B);
    glPointSize(3);
    glBegin(GL_POLYGON);
        for(int i = 0; i < 18; i++){
            x = cos(M_PI*i/9) * radius;
            y = sin(M_PI*i/9) * radius;
            //printf("%d %d\n", x, y);
            glVertex2f(x, y);
        }
    glEnd();
}

void Tiro::DesenhaTiro(GLfloat x, GLfloat y)
{
    glPushMatrix();
    glTranslatef(x,y, 0);
    DesenhaCirc(radiusTiro, 1, 1, 1);
    glPopMatrix();
}

void Tiro::Move()
{
    gX += cos(gDirectionAng) * gVel;
    gY += sin(gDirectionAng) * gVel;
}

bool Tiro::Valido()
{
    if(gX > DISTANCIA_MAX || gY > DISTANCIA_MAX || gX < -DISTANCIA_MAX || gY < -DISTANCIA_MAX){
        return false;
    }
    return true;
}