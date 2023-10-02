#include "inimigo.h"
#include <math.h>

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
        DesenhaCirc(radiusHead, 0, 1, 0);
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

// Tiro* Inimigo::Atira()
// {

// }
