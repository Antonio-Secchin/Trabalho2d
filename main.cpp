#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "tinyxml.h"
#define INC_KEY 1
#define INC_KEYIDLE 0.1


//Key status
int keyStatus[256];

// Window dimensions
GLint Width = 700;
GLint Height = 700;
GLint RaioCabecaPer;
GLint RaioCabecaIni;

// Viewing dimensions
const GLint ViewingWidth = 500;
const GLint ViewingHeight = 500;


int main(int argc, char *argv[])
{
    TiXmlDocument doc ("configuracoes.xml");
    if (doc.LoadFile()) {
    TiXmlElement* root = doc.RootElement();
    if (root) {
        TiXmlElement* arena  = root->FirstChildElement("arena");
        TiXmlElement* jogador  = root->FirstChildElement("jogador");
        TiXmlElement* inimigo  = root->FirstChildElement("inimigo");
        if(arena){
            Height = atoi(arena->Attribute("altura"));
            Width = atoi(arena->Attribute("largura"));
        }
        if(jogador)
            RaioCabecaPer = atoi(jogador->Attribute("raioCabeca"));
        if(jogador)
            RaioCabecaIni = atoi(jogador->Attribute("raioCabeca"));
    }
    } else {
        printf("Erro ao carregar o arquivo XML!\n");
    }

    // Initialize openGL with Double buffer and RGB color without transparency.
    // Its interesting to try GLUT_SINGLE instead of GLUT_DOUBLE.
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
 
    // Create the window.
    glutInitWindowSize(Width, Height);
    glutInitWindowPosition(150,50);
    glutCreateWindow("Trabalho 2D");
 
    // Define callbacks.
    // glutDisplayFunc(renderScene);
    // glutKeyboardFunc(keyPress);
    // glutIdleFunc(idle);
    // glutKeyboardUpFunc(keyup);
    
    // init();
 
    glutMainLoop();
 
    return 0;
}
