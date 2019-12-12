#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
#include <stdbool.h>
#include<math.h>
#include <time.h>
#include "image.h"
#include "models.h"

#define GUSTINA 300
#define M_PI acos(-1.0)

#define FILENAME0 "grass.bmp"
#define FILENAME1 "grass.bmp"

void static on_display(void);
void static on_keyboard(unsigned char key, int x, int y);
void static on_reshape(int width, int height);
static void on_mouse(int button, int state, int x, int y);


static GLuint names[2];
static float x, z;
static float X[GUSTINA+1];
static float Z[GUSTINA+1];


static float xBulletPos = 0, yBulletPos = 0;
static float xBulletMov, yBulletMov;
static int fired = 0;
static int canShoot = 1;


static float xMeda = 300;
static float yMeda = 300;
static float xMedaPom = 1;
static float yMedaPom = 1;


static GLint fogMode;
float static pom[] = {0, 0};
static float animation_parameter;
static float matrix[16];
static void on_motion(int x, int y);
static int window_width, window_height;
static float pitch = 0, yaw = 0;

static void initialize(void); 

static time_t start;

static float cameraPos[3]   = {-450.0f, 0.0f,  -450.0f};
static float cameraFront[3] = {0.0f, 0.0f, -1.0f};
static float cameraUp[3] = {0.0f, 1.0f,  0.0f};

static float lastX = 0, lastY = 0;


void static SpecialInput(int key, int x, int y);

static int animation_active;

static void on_timer(int value);

void hundred(){
    
    int i = 0;
    for (i = 0; i < GUSTINA; i++){
        x = rand() % (500 + 500 + 1) - 500;
        z = rand() % (500 + 500 + 1) - 500;
        X[i] = x;
        Z[i] = z;
    }
}

void forest(){
    int i =0;
    for(i = 0; i < GUSTINA; i++){
        glPushMatrix();
            glTranslatef(X[i], 0, Z[i]);
            drvo();
        glPopMatrix();
    }
}

void generateMedaVec(){
    xMedaPom = (float)rand()/((float)RAND_MAX)*4 - 2;
    yMedaPom =  (float)rand()/((float)RAND_MAX)*4 - 2;
}

int main(int argc, char** argv){
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    start = time(NULL);
    srand(time(NULL));
    
    glEnable(GL_TEXTURE_2D);

    glTexEnvf(GL_TEXTURE_ENV,
              GL_TEXTURE_ENV_MODE,
              GL_REPLACE);

    
    
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    
    animation_parameter = 0;
    animation_active = 0;
    pom[0] = 0;
    pom[1] = 0;
    
    
    glutPassiveMotionFunc(on_motion);
    glutSpecialFunc(SpecialInput);
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutMouseFunc(on_mouse);
    glutDisplayFunc(on_display);
    
    glEnable(GL_DEPTH_TEST);
    glutSetCursor(GLUT_CURSOR_NONE);
    
    glClearColor(0.75, 0.75, 0.75, 0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
    
    hundred();
    
    initialize();
    
    glutMainLoop();
    
    return 0;
}

static void initialize(void)
{
    /* Objekat koji predstavlja teskturu ucitanu iz fajla. */
    Image * image;


    /* Ukljucuje se testiranje z-koordinate piksela. */
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_FOG);
   {
      GLfloat fogColor[4] = {0, 0, 0, 1.0};

      fogMode = GL_EXP;
      glFogi (GL_FOG_MODE, fogMode);
      glFogfv (GL_FOG_COLOR, fogColor);
      glFogf (GL_FOG_DENSITY, 0.01);
      glHint (GL_FOG_HINT, GL_DONT_CARE);
      glFogf (GL_FOG_START, 100.0);
      glFogf (GL_FOG_END, 120.0);
   }
   glClearColor(0, 0, 0, 1.0); 

    /* Ukljucuju se teksture. */
    glEnable(GL_TEXTURE_2D);

    glTexEnvf(GL_TEXTURE_ENV,
              GL_TEXTURE_ENV_MODE,
              GL_REPLACE);

    /*
     * Inicijalizuje se objekat koji ce sadrzati teksture ucitane iz
     * fajla.
     */
    image = image_init(0, 0);

    /* Kreira se prva tekstura. */
    image_read(image, FILENAME0);

    /* Generisu se identifikatori tekstura. */
    glGenTextures(2, names);

    glBindTexture(GL_TEXTURE_2D, names[0]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    /* Kreira se druga tekstura. */
    image_read(image, FILENAME1);

    glBindTexture(GL_TEXTURE_2D, names[1]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    /* Iskljucujemo aktivnu teksturu */
    glBindTexture(GL_TEXTURE_2D, 0);

    /* Unistava se objekat za citanje tekstura iz fajla. */
    image_done(image);

    /* Inicijalizujemo matricu rotacije. */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
}


static void on_mouse(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && canShoot == 1)
    {
        canShoot = 0;
        fired = 1;
        xBulletPos = cameraPos[0];
        yBulletPos = cameraPos[2];
        xBulletMov = cameraFront[0];
        yBulletMov = cameraFront[2];
    }
}

void static on_keyboard(unsigned char key, int x, int y){
    switch(key){
        case 'q':
            exit(EXIT_SUCCESS);
            break;
        case 'g':
        case 'G':
        if (!animation_active) {
            glutTimerFunc(10, on_timer, 0);
            animation_active = 1;
        }
        break;
    }
}

void SpecialInput(int key, int x, int y)
{
    float normalized[2];
    float sum = sqrt(cameraFront[0]* cameraFront[0] + cameraFront[2]*cameraFront[2]);
    normalized[0] = cameraFront[0]/sum;
    normalized[1] = cameraFront[2]/sum;
    switch(key)
    {
        case GLUT_KEY_UP:
            pom[0]+=0.5*normalized[1];
            pom[1]+=0.5*normalized[0];
        break;
        case GLUT_KEY_DOWN:
            pom[0]-=0.5*normalized[1];
            pom[1]-=0.5*normalized[0];
        break;
        case GLUT_KEY_LEFT:
            pom[0]-=0.5*normalized[0];
            pom[1]+=0.5*normalized[1];
        break;
        case GLUT_KEY_RIGHT:
            pom[0]+=0.5*normalized[0];
            pom[1]-=0.5*normalized[1];
        break;
    }

    glutPostRedisplay();

}

static void on_timer(int value)
{
    if (value != 0)
        return;

    if(fired == 1){
        xBulletPos = xBulletPos + xBulletMov;
        yBulletPos = yBulletPos + yBulletMov;
    }
    

    animation_parameter++;
    xMeda += xMedaPom;
    yMeda += yMedaPom;
    if(xMeda >= 400 && yMeda >= 400){
        xMedaPom = -1;
        yMedaPom = -1;
    }
    if(xMeda >= 400 && yMeda <= -400){
        xMedaPom = -1;
        yMedaPom = 1;
    }
    if(xMeda <= -400 && yMeda >= 400){
        xMedaPom = 1;
        yMedaPom = -1;
    }
    if(xMeda <= -400 && yMeda <= -400){
        xMedaPom = 1;
        yMedaPom = 1;
    }
    time_t t1 = time(NULL);
    if(t1-start >= 10){
        start = t1;
        generateMedaVec();
    }
    
    
    glutPostRedisplay();

    if (animation_active)
        glutTimerFunc(10, on_timer, 0);
}

static void on_reshape(int width, int height)
{

    window_width = width;
    window_height = height;

    glViewport(0, 0, width, height);
    
    lastX = window_width/2;
    lastY = window_height/2;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float) width / height, 1, 200);
}

static void on_motion(int x, int y)
{
    float xoffset = x - lastX;
    float yoffset = lastY - y; 
    lastX = x;
    lastY = y;

    float sensitivity = 0.3;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    cameraFront[0] = cos(yaw*M_PI/180) * cos(pitch*M_PI/180);
    cameraFront[1] = sin(pitch*M_PI/180);
    cameraFront[2] = sin(yaw*M_PI/180) * cos(pitch*M_PI/180);
    
    
    glutPostRedisplay();
}

void static on_display(void){
    GLfloat light_position[] = { 100, 100, 100, 0 };
    GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 1 };
    GLfloat light_diffuse[] = { 0.6, 0.6, 0.6, 1 };
    GLfloat light_specular[] = { 0.8, 0.8, 0.8, 1 };
    

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    
    
    

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

   
    gluLookAt(cameraPos[0]+ pom[1], cameraPos[1], cameraPos[2]+ pom[0], cameraPos[0] + cameraFront[0]+ pom[1], cameraPos[1]  + cameraFront[1], cameraPos[2] + cameraFront[2]+ pom[0], cameraUp[0], cameraUp[1], cameraUp[2]);
    
    float t1=1.5*cameraFront[0];
    float t2=1.5*cameraFront[2];

    glPushMatrix();
        glTranslatef(t1, 0, t2);
        glTranslatef(cameraPos[0] + cameraFront[0]+ pom[1], 0, cameraPos[2] + cameraFront[2]+ pom[0] );
        float angl = acos(-cameraFront[2]/sqrt(cameraFront[2]*cameraFront[2] + cameraFront[0]*cameraFront[0]));
        if(cameraFront[0] < 0)
            glRotatef(angl*180/M_PI, 0, 1, 0);
        else
            glRotatef(360 - angl*180/M_PI, 0, 1, 0);
        glTranslatef(-1,0, -1);
        ruka();
        puc();
    glPopMatrix();
    
    
    
    
    
    glPushMatrix();
        glTranslatef(xMeda , 0, yMeda);
        float angle = acos((-yMedaPom)/sqrt(xMedaPom*xMedaPom + yMedaPom*yMedaPom));
        if(xMedaPom < 0)
            glRotatef(angle*180/M_PI, 0, 1, 0);
        else 
            glRotatef(360 - angle*180/M_PI, 0, 1, 0);
        meda(animation_parameter, xMedaPom, yMedaPom);
    glPopMatrix();

    if((xBulletPos > -500 && xBulletPos < 500 && yBulletPos < 500 && yBulletPos > -500) && fired == 1){
        glPushMatrix();
            glTranslatef(xBulletPos, 0, yBulletPos);
            metak();
        glPopMatrix();
    }

    forest();
    trava(names);
    glutSwapBuffers();
}


