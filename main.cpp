#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "tinyxml.h"
#include "arena.h"
#include "player.h"
#include "inimigo.h"
#define INC_KEY 1
#define INC_KEYIDLE 0.1


//Key status
int keyStatus[256];

GLfloat MouseX = 0, MouseY = 0;

// Window dimensions
GLint Width;
GLint Height;
GLint WidthBarril;
GLint HeightBarril;
GLint RaioCabecaPer;
GLint RaioCabecaIni;

// Viewing dimensions
const GLint ViewingWidth = 500;
const GLint ViewingHeight = 500;


Arena arena(0,0);

Player player(0,0,0);


//Para teste:
Inimigo * inimigo = NULL;

Tiro * tiro = NULL;

Tiro * tiroIni = NULL;

void passiveMotion(int x, int y){

    MouseX = x - Width/2;
    MouseY = Height/2 - y;
    //printf("%f %f\n", MouseX, MouseY);
    // player.SetAngulo(x,y);

    // glutPostRedisplay();
}

void renderScene(void)
{
     // Clear the screen.
     glClear(GL_COLOR_BUFFER_BIT);
 
     arena.Desenha();

     player.Desenha();

    if(inimigo)
        inimigo->Desenha();
     
    if (tiro) tiro->Desenha();
     
     //alvo.Desenha();

     glutSwapBuffers(); // Desenha the new frame of the game.
}

void keyPress(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'a':
        case 'A':
             keyStatus[(int)('a')] = 1; //Using keyStatus trick
             break;
        case 'd':
        case 'D':
             keyStatus[(int)('d')] = 1; //Using keyStatus trick
             break;
        case 'w':
        case 'W':
             keyStatus[(int)('w')] = 1; //Using keyStatus trick
             break;
        case 's':
        case 'S':
             keyStatus[(int)('s')] = 1; //Using keyStatus trick
             break;
        case ' ':
             if (!tiro)
                tiro = player.Atira();
            break;
        case 27 :
             exit(0);
    }
    glutPostRedisplay();
}

void keyup(unsigned char key, int x, int y)
{
    keyStatus[(int)(key)] = 0;
    glutPostRedisplay();
}

void ResetKeyStatus()
{
    int i;
    //Initialize keyStatus
    for(i = 0; i < 256; i++)
       keyStatus[i] = 0; 
}



void init(void)
{
    ResetKeyStatus();
    // The color the windows will redraw. Its done to erase the previous frame.
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black, no opacity(alpha).
 
    glMatrixMode(GL_PROJECTION); // Select the projection matrix    
    glOrtho(-(Width/2),     // X coordinate of left edge             
            (Width/2),     // X coordinate of right edge            
            -(Height/2),     // Y coordinate of bottom edge             
            (Height/2),     // Y coordinate of top edge             
            -100,     // Z coordinate of the “near” plane            
            100);    // Z coordinate of the “far” plane
    glMatrixMode(GL_MODELVIEW); // Select the projection matrix    
    glLoadIdentity();
      
}

void idle(void)
{    
    double inc = INC_KEYIDLE;
    //Treat keyPress
    if(keyStatus[(int)('a')] && player.ObtemX() - RaioCabecaPer > -Width/2)
    {
        player.MoveEmX(-inc);
        //player.MoveAngulo(-inc);
    }
    if(keyStatus[(int)('d')] && player.ObtemX() + RaioCabecaPer < Width/2)
    {
        player.MoveEmX(inc);
        //player.MoveAngulo(inc);
    }

    if(keyStatus[(int)('s')] && player.ObtemY() - RaioCabecaPer > -Height/2)
    {
        player.MoveEmY(-inc);
    }
    if(keyStatus[(int)('w')] && player.ObtemY() + RaioCabecaPer < 0)
    {
        player.MoveEmY(inc);
    }

    player.SetAngulo(MouseX,MouseY);

    if(inimigo){
        //inimigo->MoveEmY(-inc);
        if(inimigo->SetAngulo(player.ObtemX(), player.ObtemY()))
            tiroIni = inimigo->Atira();
        if(player.Atingido(inimigo))
            exit(0);
    }
    if(tiroIni)
        tiroIni->Move();
    //Trata o tiro (soh permite um tiro por vez)
    //Poderia usar uma lista para tratar varios tiros
    if(tiro){
        tiro->Move();

        //Trata colisao
        if(inimigo){
            if (inimigo->Atingido(tiro)){
                if(inimigo->GetVida() == 0){
                    inimigo = NULL;
                }                
                tiro = NULL;
            }
        }

        if (tiro && !tiro->Valido()){ 
            delete tiro;
            tiro = NULL;
        }
    }
    
    glutPostRedisplay();
}


int main(int argc, char *argv[])
{
    TiXmlDocument doc ("configuracoes.xml");
    if (doc.LoadFile()) {
    TiXmlElement* root = doc.RootElement();
    if (root) {
        TiXmlElement* arena  = root->FirstChildElement("arena");
        TiXmlElement* jogador  = root->FirstChildElement("jogador");
        TiXmlElement* inimigo  = root->FirstChildElement("inimigo");
        TiXmlElement* barril  = root->FirstChildElement("barril");
        if(arena){
            Height = atoi(arena->Attribute("altura"));
            Width = atoi(arena->Attribute("largura"));
        }
        if(jogador)
            RaioCabecaPer = atoi(jogador->Attribute("raioCabeca"));
        if(inimigo)
            RaioCabecaIni = atoi(inimigo->Attribute("raioCabeca"));
        if(barril){
            HeightBarril = atoi(barril->Attribute("altura"));
            WidthBarril = atoi(barril->Attribute("largura"));
        }
    }
    } else {
        printf("Erro ao carregar o arquivo XML!\n");
    }

    arena = Arena(Height, Width);

    player = Player(RaioCabecaPer, 0, (-Height/2) + RaioCabecaPer);

    inimigo = new Inimigo(0, Height/2 - HeightBarril, RaioCabecaIni, 5, WidthBarril, HeightBarril);
    
    // Initialize openGL with Double buffer and RGB color without transparency.
    // Its interesting to try GLUT_SINGLE instead of GLUT_DOUBLE.
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
 
    // Create the window.
    glutInitWindowSize(Width, Height);
    glutInitWindowPosition(150,50);
    glutCreateWindow("Trabalho 2D");
    glutPassiveMotionFunc(passiveMotion);
 
    // Define callbacks.
    glutDisplayFunc(renderScene);
    glutKeyboardFunc(keyPress);
    glutIdleFunc(idle);
    glutKeyboardUpFunc(keyup);
    
    init();
 
    glutMainLoop();
 
    return 0;
}
