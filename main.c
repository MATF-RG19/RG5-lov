#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>

void static on_display(void);
void static on_keyboard(unsigned char key, int x, int y);
void static on_reshape(int width, int height);
void static puc();
void static ruka();
void static meda();
void static drvo();

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    
    
    
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);
    
    glEnable(GL_DEPTH_TEST);
    
    glClearColor(0.75, 0.75, 0.75, 0);
    
    glutMainLoop();
    
    return 0;
}

void static on_keyboard(unsigned char key, int x, int y){
    switch(key){
        case 'q':
            exit(EXIT_SUCCESS);
            break;
    }
}

void static on_reshape(int width, int height){
    glViewport(0, 0, width, height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float)width/height, 1, 100);
}

void static on_display(void){
    GLfloat light_position[] = { 1, 1, 1, 0 };
    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1 };
    GLfloat light_diffuse[] = { 0.5, 0.5, 0.5, 1 };
    GLfloat light_specular[] = { 0.6, 0.6, 0.6, 1 };
    

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    ruka();
    puc();
    meda();
    drvo();

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
    glTranslatef(-1, 0, 2);
    glScalef(2, 2, 2);
    glPushMatrix();
        glScalef(1, 1.3, 1.5);
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
        glScalef(1, 2, 1);
        glutSolidSphere(0.05, 20, 20);
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(0.06, -0.2, 0);
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
        glTranslatef(0, 0.5, -2);
        glScalef(2, 2, 2);
        stablo();
        krosnja();
    glPopMatrix();
}
