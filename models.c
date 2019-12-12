#include "models.h"

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

extern void puc(){
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

extern void ruka(){
    saka();
    podlaktica();
}

extern void metak(){
    GLfloat ambient_coeffs[] = { 0, 0, 0, 1 };

    GLfloat diffuse_coeffs[] = { 0.4, 0.4, 0.4, 1 };

    GLfloat specular_coeffs[] = { 0.6, 0.6, 0.6, 1 };

    GLfloat shininess = 2;
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    glTranslatef(0,-1.5,0);
    glutSolidSphere(0.1, 20, 20);
}

extern void trava(GLuint names[]){
    glBindTexture(GL_TEXTURE_2D, names[1]);
    
    int i,j=0;
    for(i = -500; i <= 500; i+=50)
    {
        glBegin(GL_QUADS);
        for(j = -500; j <= 500; j+=50){
           
                glNormal3f(0, 0, 1);

                glTexCoord2f(0, 0);
                glVertex3f(i, -9, j);

                glTexCoord2f(5, 0);
                glVertex3f(i+50, -9, j);

                glTexCoord2f(5, 5);
                glVertex3f(i+50, -9, j+50);

                glTexCoord2f(0, 5);
                glVertex3f(i, -9, j+50);
            
        }
        glEnd();
    }
    

    /* Iskljucujemo aktivnu teksturu */
    glBindTexture(GL_TEXTURE_2D, 0);

}

extern void meda(float animation_parameter, float xMedaPom, float yMedaPom){
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
            sin(animation_parameter*sqrt(xMedaPom*xMedaPom + yMedaPom*yMedaPom)) * 30.0f,
            1, 0, 0
            );
            glScalef(1, 2, 1);
            glutSolidSphere(0.05, 20, 20);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0.06, -0.2, 0);
            glRotatef(
            -sin(animation_parameter *sqrt(xMedaPom*xMedaPom + yMedaPom*yMedaPom)) * 30.0f,
            1, 0, 0
            );
            glScalef(1, 2, 1);
            glutSolidSphere(0.05, 20, 20);
        glPopMatrix();
        glPushMatrix();
                glTranslatef(0.15, 0.11, 0);
                glRotatef(
                sin(animation_parameter*sqrt(xMedaPom*xMedaPom + yMedaPom*yMedaPom)) * 30.0f,
                1, 0, 0
                );
                glTranslatef(0, -0.1, 0);
                glScalef(1, 2, 1);
                glutSolidSphere(0.05, 20, 20);
            glPopMatrix();
            
            glPushMatrix();
                glTranslatef(-0.15, 0.11, 0);
                glRotatef(
                -sin(animation_parameter*sqrt(xMedaPom*xMedaPom + yMedaPom*yMedaPom)) * 30.0f,
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
extern void drvo(){
    glPushMatrix();
        glTranslatef(0,3, 0);
        glScalef(15, 15, 15);
        stablo();
        krosnja();
    glPopMatrix();
}