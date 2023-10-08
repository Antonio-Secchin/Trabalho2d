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

//Posicao do mouse
GLfloat MouseX = 0, MouseY = 0;

// Window dimensions
GLint Width;
GLint Height;

//Variaveis relacionadas ao barril
GLint WidthBarril;
GLint HeightBarril;
GLfloat VelocidadeBarril;
GLint TirosNecessa;

//Variaveis relacionadas ao inimigo
GLint RaioCabecaIni;
GLfloat VelocidadeTiroIni;
GLfloat FrequenciaTiroIni;

//Variaveis relacionadas ao personagem
GLint RaioCabecaPer;
GLfloat VelocidadePer;

//Variaveis de configuracao
int InimigoSpawna;
int InimigoAtira;

//Variaveis para realizar a impressao na tela
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

//Listas para tratar os casos que tem mais de um do mesmo objeto na tela

list<Inimigo*> listaEnemy{};

list<Tiro*> listaTiroEnemy{};

list<Tiro*> listaTiroAliado{};

//Imprime a quantidade de barris que faltam para o jogo acabar
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

//Imprime o texto de vitoria
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

//Imprime o texto de derrota
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

//Pega a posicao do mouse e coloca ela no nosso sistema de cordenadas
void passiveMotion(int x, int y){

    MouseX = x - Width/2;
    MouseY = Height/2 - y;

}

//Renderiza a cena
void renderScene(void)
{
    // Clear the screen.
    glClear(GL_COLOR_BUFFER_BIT);
 
     arena.Desenha();

    if(BarrilNec == 0){
        // Criar um iterador para percorrer a lista
        auto inicio = listaEnemy.begin();

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
    
    if (!listaTiroEnemy.empty()) {
        for(Tiro * tiroIni :  listaTiroEnemy){
            if(tiroIni) tiroIni->Desenha();
        }
    }
    if (!listaTiroAliado.empty()) {
        for(Tiro * tiro :  listaTiroAliado){
            if (tiro) tiro->Desenha();
        }
    }

    ImprimeBarrilNec(Width/2 -100, Height/2 - 15);

     glutSwapBuffers(); // Desenha the new frame of the game.
}

//Verifica se uma tecla foi pressionada
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

//Capta quando uma tecla para de ser pressionada
void keyup(unsigned char key, int x, int y)
{
    keyStatus[(int)(key)] = 0;
    glutPostRedisplay();
}

//Reinicia todas as teclas do teclado
void ResetKeyStatus()
{
    int i;
    //Initialize keyStatus
    for(i = 0; i < 256; i++)
       keyStatus[i] = 0; 
}

//funcao que detecta se o botao esquerdo do mouse foi clicado
void mouse(int button, int state, int x, int y){

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        if (listaTiroAliado.size()< TirosNecessa*2){
                Tiro * tiro;
                tiro = player.Atira();
                tiro->SetLimite(Height,Width);
                listaTiroAliado.push_back(tiro);
             }
    }

}


//Funcao de inicializacao
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

    //double inc = INC_KEYIDLE;

    contSpawnIni += VelocidadeBarril*timeDiference;

    if(InimigoSpawna && contSpawnIni>=HeightBarril * 1.5){
        contSpawnIni = 0;
        listaEnemy.push_back(new Inimigo(rand()%(Width - WidthBarril/2) - Width/2, Height/2 - HeightBarril/2, RaioCabecaIni, TirosNecessa, WidthBarril, HeightBarril, VelocidadeTiroIni));
    }

    //Treat keyPress
    if(keyStatus[(int)('a')] && player.ObtemX() - RaioCabecaPer > -Width/2)
    {
        player.MoveEmX(-VelocidadePer * timeDiference);
        //player.MoveAngulo(-inc);
    }
    if(keyStatus[(int)('d')] && player.ObtemX() + RaioCabecaPer < Width/2)
    {
        player.MoveEmX(VelocidadePer * timeDiference);
        //player.MoveAngulo(inc);
    }

    if(keyStatus[(int)('s')] && player.ObtemY() - RaioCabecaPer > -Height/2)
    {
        player.MoveEmY(-VelocidadePer * timeDiference);
    }
    if(keyStatus[(int)('w')] && player.ObtemY() + RaioCabecaPer < 0)
    {
        player.MoveEmY(VelocidadePer * timeDiference);
    }

    player.SetAngulo(MouseX,MouseY);

    if (!listaEnemy.empty()) {
        for(Inimigo * inimigo :  listaEnemy){
            if(inimigo){
                inimigo->MoveEmY(-VelocidadeBarril * timeDiference);
                inimigo->IncrementaCooldownTiro(timeDiference);
                if(InimigoAtira &&inimigo->HasSniper() && inimigo->SetAngulo(player.ObtemX(), player.ObtemY()) && inimigo->ObtemCooldownTiro()>=FrequenciaTiroIni){
                    Tiro * tiroIni = inimigo->Atira();
                    tiroIni->SetLimite(Height,Width);
                    listaTiroEnemy.push_back(tiroIni);
                    inimigo->ReiniciaCooldownTiro();
                }
                if(player.AtingidoBarril(inimigo))
                    Perdeu = true;
            }
        }
    }

    if (!listaTiroEnemy.empty()) {
        list<Tiro*> aux{};
        for(Tiro * tiroIni :  listaTiroEnemy){
            if(tiroIni){
                tiroIni->Move(timeDiference);
                if(player.AtingidoTiro(tiroIni)){
                    Perdeu = true;
                    break;
                }
                if (tiroIni && !tiroIni->Valido()){ 
                    aux.push_back(tiroIni);
                }
            }
        }

        // Percorrer a lista com um loop while
        for (Tiro * tiroIni : aux) {
            listaTiroEnemy.remove(tiroIni);
            delete tiroIni;
        }
    }
    //Poderia usar uma lista para tratar varios tiros
    
    if (!listaTiroAliado.empty()) {
        list<Tiro*> tirosParaRemover;
        for(Tiro * tiro :  listaTiroAliado){
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
                                }
                                tirosParaRemover.push_back(tiro);
                                break;
                            }
                        }
                    }
                }

                if (tiro && !tiro->Valido()) {
                    tirosParaRemover.push_back(tiro);
                }
            }
        }

        for (Tiro* tiro : tirosParaRemover) {
            listaTiroAliado.remove(tiro);
            delete tiro;
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
        TiXmlElement* conf  = root->FirstChildElement("configuracoes");
        if(arena){
            Height = atoi(arena->Attribute("altura"));
            Width = atoi(arena->Attribute("largura"));
        }
        if(jogador){
            RaioCabecaPer = atoi(jogador->Attribute("raioCabeca"));
            VelocidadePer = stof(jogador->Attribute("velocidade"));
        }
        if(inimigo){
            RaioCabecaIni = atoi(inimigo->Attribute("raioCabeca"));
            VelocidadeTiroIni = stof(inimigo->Attribute("velocidadeTiro"));
            FrequenciaTiroIni = 1000/stof(inimigo->Attribute("tirosPorSegundo"));
        }
        if(barril){
            HeightBarril = atoi(barril->Attribute("altura"));
            WidthBarril = atoi(barril->Attribute("largura"));
            BarrilNec = atoi(barril->Attribute("nParaGanhar"));
            TirosNecessa = atoi(barril->Attribute("numeroTiros"));
            VelocidadeBarril = stof(barril->Attribute("velocidade"));
        }
        if(conf){
            InimigoSpawna = atoi(conf->Attribute("spawnInimigos"));
            InimigoAtira = atoi(conf->Attribute("atirarInimigos"));
        }
    }
    } else {
        printf("Erro ao carregar o arquivo XML!\n");
    }

    arena = Arena(Height, Width);

    player = Player(RaioCabecaPer, 0, (-Height/2) + RaioCabecaPer);

    
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
