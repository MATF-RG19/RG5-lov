#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
#include <stdbool.h>
#include<math.h>
#include <time.h>

#define GUSTINA 100
#define M_PI acos(-1.0)

void static on_display(void);
void static on_keyboard(unsigned char key, int x, int y);
void static on_reshape(int width, int height);

static float x, z;
static float X[100];
static float Z[100];

static float xMeda = 1;
static float yMeda = 1;
static float xMedaPom = 1;
static float yMedaPom = 1;

void static trava();
void static puc();
void static ruka();
void static meda();
void static drvo();
float static pom[] = {0, 0};
static float animation_parameter;
static float matrix[16];
static void on_motion(int x, int y);
static int window_width, window_height;
static float pitch = 0, yaw = 0;

static time_t start;

static float cameraPos[3]   = {0.0f, 0.0f,  3.0f};
static float cameraFront[3] = {0.0f, 0.0f, -1.0f};
static float cameraUp[3] = {0.0f, 1.0f,  0.0f};

static float lastX = 0, lastY = 0;


void static SpecialInput(int key, int x, int y);

static int animation_active;

static void on_timer(int value);

void hundred(){
    
    int i = 0;
    for (i = 0; i < GUSTINA; i++){
        x = rand() % (300 + 300 + 1) - 300;
        z = rand() % (300 + 300 + 1) - 300;
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
    glutDisplayFunc(on_display);
    
    glEnable(GL_DEPTH_TEST);
    glutSetCursor(GLUT_CURSOR_NONE);
    
    glClearColor(0.75, 0.75, 0.75, 0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
    
    hundred();
    
    glutMainLoop();
    
    return 0;
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
    
    

    animation_parameter++;
    xMeda += xMedaPom;
    yMeda += yMedaPom;
    if(xMeda >= 500 && yMeda >= 500){
        xMedaPom = -1;
        yMedaPom = -1;
    }
    if(xMeda >= 500 && yMeda <= -500){
        xMedaPom = -1;
        yMedaPom = 1;
    }
    if(xMeda <= -500 && yMeda >= 500){
        xMedaPom = 1;
        yMedaPom = -1;
    }
    if(xMeda <= -500 && yMeda <= -500){
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
    gluPerspective(60, (float) width / height, 1, 1000);
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

    glPushMatrix();
        glTranslatef(pom[1] + cameraFront[0], 0, pom[0] + cameraFront[2]);
        glTranslatef(0, 0, 4);
        float angl = acos(-cameraFront[2]/sqrt(cameraFront[2]*cameraFront[2] + cameraFront[0]*cameraFront[0]));
        if(cameraFront[0] < 0)
            glRotatef(angl*180/M_PI, 0, 1, 0);
        else
            glRotatef(360 - angl*180/M_PI, 0, 1, 0);
        glTranslatef(0,0, -4);
        ruka();
        puc();
    glPopMatrix();
    
    
    
    glPushMatrix();
        glTranslatef(xMeda*0.2 , 0, yMeda*0.2);
        float angle = acos((-yMedaPom)/sqrt(xMedaPom*xMedaPom + yMedaPom*yMedaPom));
        if(xMedaPom < 0)
            glRotatef(angle*180/M_PI, 0, 1, 0);
        else 
            glRotatef(360 - angle*180/M_PI, 0, 1, 0);
        meda();
    glPopMatrix();
    forest();
    trava();
    glutSwapBuffers();
}

void drska(){
    GLfloat ambient_coeffs[] = { 0.6, 0.6, 0.6, 1 };

    GLfloat diffuse_coeffs[] = { 0.4, 0.4, 0.4, 1 };

    GLfloat specular_coeffs[] = { 0.7, 0.7, 0.7, 1 };

    GLfloat shininess = 1;
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    glPushMatrix();
        glTranslatef(1, -2, -1);
        glScalef(1, 3.5, 1);
        glColor3f(1, 1, 1);
        glutSolidCube(0.2);
    glPopMatrix();
}
void cev(){
    GLfloat ambient_coeffs[] = { 0.6, 0.6, 0.6, 1 };

    GLfloat diffuse_coeffs[] = { 0.4, 0.4, 0.4, 1 };

    GLfloat specular_coeffs[] = { 0.7, 0.7, 0.7, 1 };

    GLfloat shininess = 1;
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    glPushMatrix();
        glTranslatef(1, -1.6, -1);
        glScalef(1.4, 1, 6);
        glColor3f(1, 1, 1);
        glutSolidCube(0.2);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(1, -1.5, -1);
        glScalef(1.2, 1, 6);
        glColor3f(1, 1, 1);
        glutSolidCube(0.2);
    glPopMatrix();
}

void static puc(){
    drska();
    cev();
}

void saka(){
    GLfloat ambient_coeffs[] = { 1, 0.8, 0.6, 1 };

    GLfloat diffuse_coeffs[] = { 0.4, 0.4, 0.4, 1 };

    GLfloat specular_coeffs[] = { 0.8, 0.7, 0.7, 1 };

    GLfloat shininess = 1;
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    glPushMatrix();
        glTranslatef(1, -2, -0.8);
        glColor3f(1, 1, 1);
        glutSolidSphere(0.3, 40, 40);
    glPopMatrix();
}

void podlaktica(){
    GLfloat ambient_coeffs[] = { 0, 0, 0, 1 };

    GLfloat diffuse_coeffs[] = { 0.4, 0.4, 0.4, 1 };

    GLfloat specular_coeffs[] = { 0.6, 0.6, 0.6, 1 };

    GLfloat shininess = 1;
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    glPushMatrix();
        glTranslatef(1.2, -2.4, 0.6);
        glRotatef(15, 1, 0.4, 0);
        glScalef(1,1, -4.4);
        glColor3f(1, 1, 1);
        glutSolidCube(0.6);
    glPopMatrix();
}

void static ruka(){
    saka();
    podlaktica();
}
void static trava(){
    GLfloat ambient_coeffs[] = { 0, 0.1, 0, 1 };

    GLfloat diffuse_coeffs[] = { 0, 0.1, 0, 1 };

    GLfloat specular_coeffs[] = {0, 0.3, 0.11, 1 };

    GLfloat shininess = 0;
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    glPushMatrix();
        glTranslatef(0, -9, 0);
        glScalef(10000,0.01,10000);
        glutSolidCube(1);
    glPopMatrix();
}

void static meda(){
    GLfloat ambient_coeffs[] = { 0.6, 0.4, 0.4, 1 };

    GLfloat diffuse_coeffs[] = { 0.4, 0.4, 0.4, 1 };

    GLfloat specular_coeffs[] = { 0.8, 0.7, 0.7, 1 };

    GLfloat shininess = 1;
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    glPushMatrix();
        glScalef(30, 30, 30);
        glPushMatrix();
            glScalef(1, 1.3, 1);
            glutSolidSphere(0.15, 20, 20);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0, 0.25, 0);
            glutSolidSphere(0.1, 20, 20);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0.06, 0.34, 0);
            glutSolidSphere(0.03, 20, 20);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-0.06, 0.34, 0);
            glutSolidSphere(0.03, 20, 20);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-0.06, -0.2, 0);
            glRotatef(
            sin(animation_parameter / 10.0f) * 30.0f,
            1, 0, 0
            );
            glScalef(1, 2, 1);
            glutSolidSphere(0.05, 20, 20);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0.06, -0.2, 0);
            glRotatef(
            -sin(animation_parameter / 10.0f) * 30.0f,
            1, 0, 0
            );
            glScalef(1, 2, 1);
            glutSolidSphere(0.05, 20, 20);
        glPopMatrix();
        glPushMatrix();
                glTranslatef(0.15, 0.11, 0);
                glRotatef(
                sin(animation_parameter/10.0f) * 30.0f,
                1, 0, 0
                );
                glTranslatef(0, -0.1, 0);
                glScalef(1, 2, 1);
                glutSolidSphere(0.05, 20, 20);
            glPopMatrix();
            
            glPushMatrix();
                glTranslatef(-0.15, 0.11, 0);
                glRotatef(
                -sin(animation_parameter/10.0f) * 30.0f,
                1, 0, 0
                );
                glTranslatef(0, -0.1, 0);
                glScalef(1, 2, 1);
                glutSolidSphere(0.05, 20, 20);
            glPopMatrix();
    glPopMatrix();
}


void stablo(){
    GLfloat ambient_coeffs[] = { 0.4, 0.2, 0.2, 1 };

    GLfloat diffuse_coeffs[] = { 0.3, 0.1, 0.1, 1 };

    GLfloat specular_coeffs[] = { 0.4, 0.2, 0.2, 1 };

    GLfloat shininess = 1;
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    
    glPushMatrix();
        glTranslatef(0,-0.5,0);
        glScalef(0.7,3,0.7);
        glutSolidCube(0.3);
    glPopMatrix();
    
}

void krosnja(){
    GLfloat ambient_coeffs[] = { 0, 0.4, 0, 1 };

    GLfloat diffuse_coeffs[] = { 0, 0.4, 0, 1 };

    GLfloat specular_coeffs[] = { 0, 0.7, 0, 1 };

    GLfloat shininess = 1;
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    
    glPushMatrix();
        glTranslatef(0, 1.3, 0);
        glScalef(0.5,2.5,0.5);
        glutSolidSphere(0.5, 20, 20);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0, 1.2, 0);
        glScalef(0.6,1.4,0.6);
        glutSolidSphere(0.6, 20, 20);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0, 0.5, 0);
        glScalef(0.7,1.5,0.7);
        glutSolidSphere(0.6, 20, 20);
    glPopMatrix();
    
}
void static drvo(){
    glPushMatrix();
        glTranslatef(0,3, 0);
        glScalef(15, 15, 15);
        stablo();
        krosnja();
    glPopMatrix();
}
