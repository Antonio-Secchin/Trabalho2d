#include "player.h"
#include <stdio.h>
#include <math.h>

void Player::DesenhaRect(GLint height, GLint width, GLfloat R, GLfloat G, GLfloat B)
{
    glColor3f(R,G,B);

    glBegin(GL_POLYGON);
        glVertex2f(0, 0);
        glVertex2f( width, 0);
        glVertex2f( width, height);
        glVertex2f(0, height);
    glEnd();
}

void Player::DesenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B)
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

void Player::DesenhaArma(GLfloat x, GLfloat y)
{
    glPushMatrix();
    glTranslatef(x,y,0);
    glRotatef(gTheta, 0, 0, 1);
    DesenhaRect(2*radiusHead, radiusHead/4, 1, 0, 0);
    glPopMatrix();
}

void Player::DesenhaPernas(GLfloat x, GLfloat y)
{
    glPushMatrix();
    glTranslatef(x,y,0);
    DesenhaRect(1.2 * radiusHead, - radiusHead/4, 0, 0, 0);
    glTranslatef(-2*x,y,0);
    DesenhaRect(-1.2 * radiusHead, radiusHead/4, 0, 0, 0);
    glPopMatrix();
}

void Player::DesenhaPlayer(GLfloat x, GLfloat y, GLfloat theta)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    DesenhaPernas(radiusHead, 0);
    DesenhaCirc(radiusHead, 0, 1, 0);
    DesenhaArma(radiusHead, 0);
    glPopMatrix();
}

void Player::MoveEmX(GLfloat dx)
{
    gX += dx;
}

void Player::MoveEmY(GLfloat dy)
{
    gY += dy;
}

void Player::MoveAngulo(GLfloat da){
    // if(gTheta<=30 && gTheta>=-30)
        gTheta+= da;
}

void Player::SetAngulo(GLfloat x, GLfloat y){
    GLfloat dx,dy, angulo;
    dx = x - gX - 1.25 * radiusHead;
    dy = y - gY + 2* radiusHead;
    angulo = atan2(dy,dx) * (180.0 / M_PI);
    //printf("%f %f\n", dy, dx);
    if(angulo >= 60 && angulo <= 120){
        gTheta = angulo - 90;
        //printf("%f\n",gTheta);
    }
}

//Funcao auxiliar de rotacao
void RotatePoint(GLfloat x, GLfloat y, GLfloat angle, GLfloat &xOut, GLfloat &yOut){
    GLfloat angleRad = 2 * M_PI * angle / 360;
    xOut = x * cos(angleRad) - y * sin(angleRad);
    yOut = x * sin(angleRad) + y * cos(angleRad);
}

Tiro* Player::Atira()
{  
    GLfloat x, y, yFinal, xFinal, xBaseFinal, yBaseFinal,dx, dy;
    x = 0;
    y = 2* radiusHead;
    RotatePoint(x, y, gTheta, xFinal, yFinal);
    RotatePoint(0, 0, gTheta, xBaseFinal, yBaseFinal);
    xFinal = xFinal + 1.125 * radiusHead + gX;
    yFinal = yFinal + gY;
    xBaseFinal = xBaseFinal + 1.125 * radiusHead + gX;
    yBaseFinal = yBaseFinal + gY;
    dx = xFinal -xBaseFinal;
    dy = yFinal - yBaseFinal;
    Tiro * disparo = new Tiro(xFinal, yFinal, atan2(dy,dx));
    return disparo;
}

bool Player::Atingido(Inimigo * barril){
    GLfloat dist;
    dist = (barril->ObtemX() - gX) * (barril->ObtemX() - gX) + (barril->ObtemY() - gY) * (barril->ObtemY() - gY); 
    if(dist <= radiusHead * radiusHead){
        return true;
    }
    return false;
}
