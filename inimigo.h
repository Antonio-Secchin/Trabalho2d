#ifndef INIMIGO_H
#define	INIMIGO_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include "tiro.h"


class Inimigo {
    GLfloat gX; 
    GLfloat gY;
    GLfloat gTheta;
    GLfloat widht;
    GLfloat height;
    GLint radiusHead;
    GLint vida;
    int gColor;
    int hasSniper;
    GLfloat velocidadeTiro;
private:
    void DesenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B);
    void DesenhaRect(  GLint height, GLint width, 
                    GLfloat R, GLfloat G, GLfloat B);
    void DesenhaArma(GLfloat x, GLfloat y);
    void DesenhaPernas(   GLfloat x, GLfloat y);
    void DesenhaBarril();
    void DesenhaInimigo(GLfloat x, GLfloat y, GLfloat theta);
public:
    Inimigo(GLfloat x, GLfloat y, GLfloat radiusIni, GLint vidamax, GLfloat widhtRet, GLfloat heightRet, GLfloat veloTiro){
        gX = x; 
        gY = y;
        gColor = 0;
        radiusHead = radiusIni;
        vida = vidamax;
        widht = widhtRet;
        height = heightRet;
        hasSniper = rand()%2;
        velocidadeTiro = veloTiro;
    };
    void Desenha(){ 
        DesenhaInimigo(gX, gY, gTheta);
    };
    void MoveEmY(GLfloat dy);
    GLint GetVida();
    void Recria(GLfloat x, GLfloat y);
    bool SetAngulo(GLfloat x, GLfloat y);
    Tiro* Atira();
    bool Atingido(Tiro *tiro);
    GLfloat ObtemWidht(){
        return widht;
    };
    GLfloat ObtemHeight(){
        return height;
    };
    GLfloat ObtemX(){
        return gX;
    };
    GLfloat ObtemY(){
        return gY;
    };
    int HasSniper(){
        return hasSniper;
    };
};

#endif	/* Inimigo_H */

