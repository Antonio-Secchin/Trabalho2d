#ifndef INIMIGO_H
#define	INIMIGO_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>


class Inimigo {
    GLfloat gX; 
    GLfloat gY;
    GLfloat theta;
    GLfloat widht;
    GLfloat height;
    GLint radiusHead;
    GLint vida;
    int gColor;
    int hasSniper;
private:
    void DesenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B);
    void DesenhaRect(  GLint height, GLint width, 
                    GLfloat R, GLfloat G, GLfloat B);
    void DesenhaArma(GLfloat x, GLfloat y);
    void DesenhaPernas(   GLfloat x, GLfloat y);
    void DesenhaBarril();
    void DesenhaInimigo(GLfloat x, GLfloat y, GLfloat theta);
public:
    Inimigo(GLfloat x, GLfloat y, GLfloat radiusIni, GLint vidamax, GLfloat widhtRet, GLfloat heightRet){
        gX = x; 
        gY = y;
        gColor = 0;
        radiusHead = radiusIni;
        vida = vidamax;
        widht = widhtRet;
        height = heightRet;
        hasSniper = rand()%2;
    };
    void Desenha(){ 
        DesenhaInimigo(gX, gY, theta);
    };
    void MoveEmY(GLfloat dy);
    void Recria(GLfloat x, GLfloat y);
    //bool Atingido(Tiro *tiro);
};

#endif	/* Inimigo_H */

