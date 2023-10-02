#include "arena.h"

void Arena:: DesenhaRect(GLint height, GLint width, GLfloat R, GLfloat G, GLfloat B){
    glColor3f(R,G,B);

    glBegin(GL_POLYGON);
        glVertex2f(-width/2, -height/2);
        glVertex2f( width/2, -height/2);
        glVertex2f( width/2, height/2);
        glVertex2f(-width/2, height/2);
    glEnd();
}


void Arena:: DesenhaArena(){
    DesenhaRect(height, width, 0, 0, 1);
}