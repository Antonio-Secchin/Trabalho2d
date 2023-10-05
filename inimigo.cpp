#include "inimigo.h"
#include <math.h>
#include <stdio.h>

void Inimigo::DesenhaRect(GLint height, GLint width, GLfloat R, GLfloat G, GLfloat B)
{
    glColor3f(R,G,B);

    glBegin(GL_POLYGON);
        glVertex2f(0, 0);
        glVertex2f( width, 0);
        glVertex2f( width, height);
        glVertex2f(0, height);
    glEnd();
}

void Inimigo::DesenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B)
{
    GLfloat x, y;
    glColor3f(R, G, B);
    glPointSize(3);
    glBegin(GL_POLYGON);
        for(int i = 0; i < 36; i++){
            x = cos(M_PI*i/18) * radius;
            y = sin(M_PI*i/18) * radius;
            //printf("%d %d\n", x, y);
            glVertex2f(x, y);
        }
    glEnd();
}

void Inimigo::DesenhaArma(GLfloat x, GLfloat y)
{
    glPushMatrix();
    glTranslatef(x,y,0);
    glRotatef(gTheta, 0, 0, 1);
    DesenhaRect(-2*radiusHead, radiusHead/4, 1, 0, 0);
    glPopMatrix();
}

void Inimigo::DesenhaBarril()
{
    glPushMatrix();
    glTranslatef(-height/2,-widht/2,0);
    DesenhaRect(height, widht, 1, 0.64, 0);
    glPopMatrix();
}

void Inimigo::DesenhaPernas(GLfloat x, GLfloat y)
{
    glPushMatrix();
    glTranslatef(x,y,0);
    DesenhaRect(-1.2 * radiusHead, - radiusHead/4, 0, 0, 0);
    glTranslatef(-2*x,y,0);
    DesenhaRect(1.2 * radiusHead, + radiusHead/4, 0, 0, 0);
    glPopMatrix();
}

void Inimigo::DesenhaInimigo(GLfloat x, GLfloat y, GLfloat theta)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    DesenhaBarril();
    if(hasSniper){
        DesenhaPernas(radiusHead, 0);
        DesenhaCirc(radiusHead, 0.5, 0, 0.5);
        DesenhaArma(radiusHead, 0);
    }
    glPopMatrix();
}

void Inimigo::MoveEmY(GLfloat dy)
{
    gY += dy;
}

GLint Inimigo::GetVida(){
    return vida;
}


bool Inimigo::Atingido(Tiro *tiro){
    GLfloat tiroX, tiroY, dist;
    tiro->GetPos(tiroX, tiroY);
    if(tiroX >= gX - widht/2 && tiroX <= gX + widht/2 && tiroY >= gY - height/2 && tiroY <= gY + height/2){
        vida--;
        return true;
    }
    return false;
}

static void RotatePoint(GLfloat x, GLfloat y, GLfloat angle, GLfloat &xOut, GLfloat &yOut){
    GLfloat angleRad = 2 * M_PI * angle / 360;
    xOut = x * cos(angleRad) - y * sin(angleRad);
    yOut = x * sin(angleRad) + y * cos(angleRad);
}

bool Inimigo::SetAngulo(GLfloat x, GLfloat y){
    GLfloat dx,dy, angulo;
    dx = -(x - gX - 1.25 * radiusHead);
    dy = -(y - gY + 2* radiusHead);
    angulo = atan2(dy,dx) * (180.0 / M_PI);
    //printf("%f\n", angulo);
    if(angulo >= 60 && angulo <= 120){
        gTheta = angulo - 90;
        //printf("%f\n",gTheta);
        return true;
    }
    return false;
}

Tiro* Inimigo::Atira()
{
    GLfloat x, y, yFinal, xFinal, xBaseFinal, yBaseFinal,dx, dy;
    x = 0;
    y = -2* radiusHead;
    RotatePoint(x, y, gTheta, xFinal, yFinal);
    RotatePoint(0, 0, gTheta, xBaseFinal, yBaseFinal);
    xFinal = xFinal + 1.125 * radiusHead + gX;
    yFinal = yFinal + gY;
    xBaseFinal = xBaseFinal + 1.125 * radiusHead + gX;
    yBaseFinal = yBaseFinal + gY;
    dx = xFinal -xBaseFinal;
    dy = yFinal - yBaseFinal;
    Tiro * disparo = new Tiro(xFinal, yFinal, atan2(dy,dx), velocidadeTiro);
    return disparo;
}