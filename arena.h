#ifndef ARENA_H
#define ARENA_H
#include <GL/gl.h>
#include <GL/glu.h>

class Arena{
    GLint width;
    GLint height;
    int contador;

private:
    void DesenhaRect(  GLint height, GLint width, 
                    GLfloat R, GLfloat G, GLfloat B);
    void DesenhaArena();

public:
    Arena(GLint heightP, GLint widthP){
        width = widthP;
        height = heightP;
        contador = 0;
    };
    void Desenha(){ 
        DesenhaArena();
    };
};


#endif