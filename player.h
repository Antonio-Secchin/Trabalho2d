#ifndef PLAYER_H
#define	PLAYER_H
#include <GL/gl.h>
#include <GL/glu.h>
#include "tiro.h"
// Dimensions

class Player {
    GLfloat gX; 
    GLfloat gY; 
    GLfloat gTheta; 
    GLfloat direction;
    GLfloat radiusHead;


private:
    void DesenhaRect(  GLint height, GLint width, 
                    GLfloat R, GLfloat G, GLfloat B);
    void DesenhaCirc(  GLint radius, GLfloat R, 
                    GLfloat G, GLfloat B);
    void DesenhaArma(GLfloat x, GLfloat y);
    void DesenhaPernas(   GLfloat x, GLfloat y);
    void DesenhaPlayer( GLfloat x, GLfloat y, GLfloat theta);

public:
    Player(GLfloat head, GLfloat gXP, GLfloat gYP){
        radiusHead = head;
        gX = gXP; 
        gY = gYP; 
        gTheta = 0;
    };
    void Desenha(){ 
        DesenhaPlayer(gX, gY, gTheta);
    };
    void MoveEmX(GLfloat dx);
    void MoveEmY(GLfloat dy);
    void MoveAngulo(GLfloat da);
    void SetAngulo(GLfloat x, GLfloat y);
    Tiro* Atira();
    GLfloat ObtemX(){
        return gX;
    };
    GLfloat ObtemY(){
        return gY;
    };
};

#endif	/* Player_H */

