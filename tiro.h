#ifndef TIRO_H
#define	TIRO_H
#include <GL/gl.h>
#include <GL/glu.h>

#define radiusTiro 5

class Tiro {
    GLfloat gXInit; 
    GLfloat gYInit; 
    GLfloat gX; 
    GLfloat gY; 
    GLfloat gDirectionAng;
    GLfloat gVel;
    GLint limiteHorizontal;
    GLint limiteVertical;
private:
    void DesenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B);
    void DesenhaTiro(GLfloat x, GLfloat y);
public:
    Tiro(GLfloat x, GLfloat y, GLfloat directionAng, GLfloat speed){
        gXInit = x; 
        gYInit = y; 
        gX = x; 
        gY = y; 
        gDirectionAng = directionAng; 
        gVel = speed;
    };
    void Desenha(){ 
        DesenhaTiro(gX, gY);
    };
    void Move(GLdouble time);
    bool Valido();
    void GetPos(GLfloat &xOut, GLfloat &yOut){
        xOut = gX;
        yOut = gY;
    };
    void SetLimite(GLint height, GLint widht){
        limiteHorizontal = widht;
        limiteVertical = height;
    }
};

#endif	/* TIRO_H */
