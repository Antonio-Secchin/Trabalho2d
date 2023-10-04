#include "tiro.h"
#include <math.h>

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
    DesenhaCirc(radiusTiro, 0, 0, 0);
    glPopMatrix();
}

void Tiro::Move(GLdouble time)
{
    gX += cos(gDirectionAng) * gVel * time;
    gY += sin(gDirectionAng) * gVel * time;
}

bool Tiro::Valido()
{
    if(gX > limiteHorizontal || gY > limiteVertical || gX < -limiteHorizontal || gY < -limiteVertical){
        return false;
    }
    return true;
}