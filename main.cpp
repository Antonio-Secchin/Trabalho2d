#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <list>
#include "tinyxml.h"
#include "arena.h"
#include "player.h"
#include "inimigo.h"
#define INC_KEY 1
#define INC_KEYIDLE 0.1


using namespace std;


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
GLfloat VelocidadeTiroIni;

static char str[1000];
int BarrilNec;
GLdouble contSpawnIni = 0;
void * font = GLUT_BITMAP_9_BY_15;

bool Perdeu = false;

// Viewing dimensions
const GLint ViewingWidth = 500;
const GLint ViewingHeight = 500;


Arena arena(0,0);

Player player(0,0,0);

list<Inimigo*> listaEnemy{};

//Para teste:
//Inimigo * inimigo = NULL;

Tiro * tiro = NULL;

Tiro * tiroIni = NULL;

void ImprimeBarrilNec(GLfloat x, GLfloat y)
{
    glColor3f(1.0, 1.0, 1.0);
    //Cria a string a ser impressa
    char *tmpStr;
    sprintf(str, "Barris: %d", BarrilNec );
    //Define a posicao onde vai comecar a imprimir
    glRasterPos2f(x, y);
    //Imprime um caractere por vez
    tmpStr = str;
    while( *tmpStr ){
        glutBitmapCharacter(font, *tmpStr);
        tmpStr++;
    }
}

void ImprimeVitoria(GLfloat x, GLfloat y)
{
    glColor3f(1.0, 1.0, 1.0);
    //Cria a string a ser impressa
    char *tmpStr;
    sprintf(str, "Voce ganhou!!!!");
    //Define a posicao onde vai comecar a imprimir
    glRasterPos2f(x, y);
    //Imprime um caractere por vez
    tmpStr = str;
    while( *tmpStr ){
        glutBitmapCharacter(font, *tmpStr);
        tmpStr++;
    }
}

void ImprimeDerrota(GLfloat x, GLfloat y)
{
    glColor3f(1.0, 1.0, 1.0);
    //Cria a string a ser impressa
    char *tmpStr;
    sprintf(str, "Voce Perdeu :( :( :(");
    //Define a posicao onde vai comecar a imprimir
    glRasterPos2f(x, y);
    //Imprime um caractere por vez
    tmpStr = str;
    while( *tmpStr ){
        glutBitmapCharacter(font, *tmpStr);
        tmpStr++;
    }
}

void passiveMotion(int x, int y){

    MouseX = x - Width/2;
    MouseY = Height/2 - y;

}


void renderScene(void)
{
    // Clear the screen.
    glClear(GL_COLOR_BUFFER_BIT);
 
     arena.Desenha();

    if(BarrilNec == 0){
        // Criar um iterador para percorrer a lista
        auto inicio = listaEnemy.begin();
        
        // if(tiro){
        //     delete tiro;
        // }
        // if(tiroIni){
        //     delete tiro;
        // }

        // Percorrer a lista com um loop while
        while (inicio != listaEnemy.end()) {
            Inimigo* inimigo = *inicio;
            ++inicio;
            listaEnemy.remove(inimigo);
            delete inimigo;
        }

            
        ImprimeVitoria(-60,0);
        glutSwapBuffers();
        return;
    }

    if(Perdeu){
        ImprimeDerrota(-60,0);
        glutSwapBuffers();
        return;
    }

    player.Desenha();

    if (!listaEnemy.empty()) {
        for(Inimigo * inimigo :  listaEnemy){
            if(inimigo){
                inimigo->Desenha();
            }
        }
    }
     
     if(tiroIni) tiroIni->Desenha();

    if (tiro) tiro->Desenha();

    ImprimeBarrilNec(Width/2 -100, Height/2 - 15);
     
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


void mouse(int button, int state, int x, int y){
    //Corrige a posicao do mouse para a posicao da janela de visualizacao

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        if (!tiro){
                tiro = player.Atira();
                tiro->SetLimite(Height,Width);
             }
    }

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
    static GLdouble previousTime = glutGet(GLUT_ELAPSED_TIME);
    GLdouble currentTime, timeDiference;
    //Pega o tempo que passou do inicio da aplicacao
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    // Calcula o tempo decorrido desde de a ultima frame.
    timeDiference = currentTime - previousTime;
    //Atualiza o tempo do ultimo frame ocorrido
    previousTime = currentTime;
    //for(int i = 0; i < 90000000; i++);

    double inc = INC_KEYIDLE;

    contSpawnIni += inc*timeDiference;

    if(contSpawnIni>=HeightBarril * 1.5){
        contSpawnIni = 0;
        listaEnemy.push_back(new Inimigo(rand()%(Width - WidthBarril/2) - Width/2, Height/2 - HeightBarril/2, RaioCabecaIni, 5, WidthBarril, HeightBarril, VelocidadeTiroIni));
    }

    //Treat keyPress
    if(keyStatus[(int)('a')] && player.ObtemX() - RaioCabecaPer > -Width/2)
    {
        player.MoveEmX(-inc * timeDiference);
        //player.MoveAngulo(-inc);
    }
    if(keyStatus[(int)('d')] && player.ObtemX() + RaioCabecaPer < Width/2)
    {
        player.MoveEmX(inc * timeDiference);
        //player.MoveAngulo(inc);
    }

    if(keyStatus[(int)('s')] && player.ObtemY() - RaioCabecaPer > -Height/2)
    {
        player.MoveEmY(-inc * timeDiference);
    }
    if(keyStatus[(int)('w')] && player.ObtemY() + RaioCabecaPer < 0)
    {
        player.MoveEmY(inc * timeDiference);
    }

    player.SetAngulo(MouseX,MouseY);

    if (!listaEnemy.empty()) {
        for(Inimigo * inimigo :  listaEnemy){
            if(inimigo){
                inimigo->MoveEmY(-inc * timeDiference);
                if(inimigo->HasSniper() && inimigo->SetAngulo(player.ObtemX(), player.ObtemY()) && !tiroIni){
                    tiroIni = inimigo->Atira();
                    tiroIni->SetLimite(Height,Width);
                }
                if(player.AtingidoBarril(inimigo))
                    Perdeu = true;
            }
        }
    }

    if(tiroIni){
        tiroIni->Move(timeDiference);
        if(player.AtingidoTiro(tiroIni)){
            Perdeu = true;
        }
        if (tiroIni && !tiroIni->Valido()){ 
            delete tiroIni;
            tiroIni = NULL;
        }
    }
    //Poderia usar uma lista para tratar varios tiros
    if(tiro){
        tiro->Move(timeDiference);

        //Trata colisao
        if (!listaEnemy.empty()) {
            for(Inimigo * inimigo :  listaEnemy){
                if(inimigo){
                    if (tiro && inimigo->Atingido(tiro)){
                        if(inimigo->GetVida() == 0){
                            BarrilNec--;
                            listaEnemy.remove(inimigo);
                            delete inimigo;
                            inimigo = NULL;
                            break;
                        }
                        delete tiro;                
                        tiro = NULL;
                        break;
                    }
                }
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
        if(inimigo){
            RaioCabecaIni = atoi(inimigo->Attribute("raioCabeca"));
            VelocidadeTiroIni = (GLfloat)atoi(inimigo->Attribute("velocidadeTiro"))/100;
        }
        if(barril){
            HeightBarril = atoi(barril->Attribute("altura"));
            WidthBarril = atoi(barril->Attribute("largura"));
            BarrilNec = atoi(barril->Attribute("nParaGanhar"));
        }
    }
    } else {
        printf("Erro ao carregar o arquivo XML!\n");
    }

    arena = Arena(Height, Width);

    player = Player(RaioCabecaPer, 0, (-Height/2) + RaioCabecaPer);

    //listaEnemy.push_front(new Inimigo(0, Height/2 - HeightBarril, RaioCabecaIni, 5, WidthBarril, HeightBarril, VelocidadeTiroIni));

    //listaEnemy.push_front(new Inimigo(200, Height/2 - HeightBarril, RaioCabecaIni, 5, WidthBarril, HeightBarril, VelocidadeTiroIni));

    
    // Initialize openGL with Double buffer and RGB color without transparency.
    // Its interesting to try GLUT_SINGLE instead of GLUT_DOUBLE.
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
 
    // Create the window.
    glutInitWindowSize(Width, Height);
    glutInitWindowPosition(150,50);
    glutCreateWindow("Trabalho 2D");
    glutMouseFunc(mouse);
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
