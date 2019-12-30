#include "models.h"

int calculated = 0;
float transition = 0;

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
/*model za cev pistolja*/
void cev(float animation_parameter){
	/*osvetljenje pistolja*/
    GLfloat ambient_coeffs[] = { 0.6, 0.6, 0.6, 1 };

    GLfloat diffuse_coeffs[] = { 0.4, 0.4, 0.4, 1 };

    GLfloat specular_coeffs[] = { 0.7, 0.7, 0.7, 1 };

    GLfloat shininess = 1;
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    
    /*cev se sastoji iz 2 dela, kao i svaka normalna cev,
     * stacini deo cevo*/
    glPushMatrix();
        glTranslatef(1, -1.6, -1);
        glScalef(1.4, 1, 6);
        glutSolidCube(0.2);
    glPopMatrix();
    /*dinamicni deo cevi*/
    glPushMatrix();
        glTranslatef(1, -1.5, -1);
        glTranslatef(0, 0, sin(animation_parameter)/2);
        glScalef(1.2, 1, 6);
        glColor3f(1, 1, 1);
        glutSolidCube(0.2);
    glPopMatrix();
}
/*PISTOLJ!!!!!!!!!!!*/
extern void puc(float animation_parameter){
    drska();
    cev(animation_parameter);
}

/*model sake koja drzi pistolj*/
void saka(){
	
	/*boja i osvetljenje sake*/
    GLfloat ambient_coeffs[] = { 1, 0.8, 0.6, 1 };

    GLfloat diffuse_coeffs[] = { 0.4, 0.4, 0.4, 1 };

    GLfloat specular_coeffs[] = { 0.8, 0.7, 0.7, 1 };

    GLfloat shininess = 1;
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

	/*saka najobicnija moguca*/
    glPushMatrix();
        glTranslatef(1, -2, -0.8);
        glColor3f(1, 1, 1);
        glutSolidSphere(0.3, 40, 40);
    glPopMatrix();
}

/*podlaktica koja pripada coveku*/
void podlaktica(){
	/*osvetljenje i boja ruke*/
    GLfloat ambient_coeffs[] = { 0, 0, 0, 1 };

    GLfloat diffuse_coeffs[] = { 0.4, 0.4, 0.4, 1 };

    GLfloat specular_coeffs[] = { 0.6, 0.6, 0.6, 1 };

    GLfloat shininess = 1;
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    
    /*podlaktica najobicnija moguca*/
    glPushMatrix();
        glTranslatef(1.2, -2.4, 0.6);
        glRotatef(15, 1, 0.4, 0);
        glScalef(1,1, -4.4);
        glColor3f(1, 1, 1);
        glutSolidCube(0.6);
    glPopMatrix();
}
/*ruka se sastoji od sake i podlaktice*/
extern void ruka(){
    saka();
    podlaktica();
}

extern void metak(){
	
	/*boja metka i osvetljenje*/
    GLfloat ambient_coeffs[] = { 0, 0, 0, 1 };

    GLfloat diffuse_coeffs[] = { 0.4, 0.4, 0.4, 1 };

    GLfloat specular_coeffs[] = { 0.6, 0.6, 0.6, 1 };

    GLfloat shininess = 2;
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    
    /*opet najobicniji metak*/
    glPushMatrix();
        glTranslatef(0,-1.5,0);
        glutSolidSphere(0.1, 20, 20);
    glPopMatrix();
}
/*trava od tekstura sastavljena*/
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
/*model mede uz sve animacije koje moze da radi*/
extern void meda(float animation_parameter, float xMedaPom, float yMedaPom, int dead){
	/*kada meda nije mrtav ima lepu boju krzna, medjutim kada umre, meda se u pokoji i ide na putovanje*/
	if(dead == 0){
		GLfloat ambient_coeffs[] = { 0.6, 0.4, 0.4, 1 };

		GLfloat diffuse_coeffs[] = { 0.4, 0.4, 0.4, 1 };

		GLfloat specular_coeffs[] = { 0.8, 0.7, 0.7, 1 };

		GLfloat shininess = 1;
		
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
		glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	}else{
		GLfloat ambient_coeffs[] = { 1, 1, 1, 1 };

		GLfloat diffuse_coeffs[] = { 0.9, 0.9, 0.9, 1 };

		GLfloat specular_coeffs[] = { 0.9, 0.9, 0.9, 1 };

		GLfloat shininess = 1;
		
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
		glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	}
    
    
    /*ako je meda mrtav treba da krene da se vrti jer je to zamisao programera, bez ikakve moguce logike iza toga*/
    if(dead == 1 && calculated == 0){
		calculated = 1;
		transition= animation_parameter;
	}
    
    glPushMatrix();
		if(dead){
			glTranslatef(0, animation_parameter - transition, 0);
			glRotatef(animation_parameter*100, 0, 1, 0);
		}
        glScalef(30, 30, 30);
        /*medvedja glava*/
        glPushMatrix();
            glScalef(1, 1.3, 1);
            glutSolidSphere(0.15, 20, 20);
        glPopMatrix();
        /*medvedji trup*/
        glPushMatrix();
            glTranslatef(0, 0.25, 0);
            glutSolidSphere(0.1, 20, 20);
        glPopMatrix();
        /*medvedje usi*/
        glPushMatrix();
            glTranslatef(0.06, 0.34, 0);
            glutSolidSphere(0.03, 20, 20);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-0.06, 0.34, 0);
            glutSolidSphere(0.03, 20, 20);
        glPopMatrix();
        /*medvedji udovi*/
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

/*funkcija koja iscrtava stablo drveta*/
void stablo(){
	/*boja stabla i osvetljenje*/
    GLfloat ambient_coeffs[] = { 0.4, 0.2, 0.2, 1 };

    GLfloat diffuse_coeffs[] = { 0.3, 0.1, 0.1, 1 };

    GLfloat specular_coeffs[] = { 0.4, 0.2, 0.2, 1 };

    GLfloat shininess = 1;
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    
    
    /*stablo ko stablo*/
    glPushMatrix();
        glTranslatef(0,-0.5,0);
        glScalef(0.7,3,0.7);
        glutSolidCube(0.3);
    glPopMatrix();
    
}

/*krosnja stabla sastvaljenja od 3 lopte*/

void krosnja(){
	/*boja krosnje i osvetljenje*/
    GLfloat ambient_coeffs[] = { 0, 0.4, 0, 1 };

    GLfloat diffuse_coeffs[] = { 0, 0.4, 0, 1 };

    GLfloat specular_coeffs[] = { 0, 0.7, 0, 1 };

    GLfloat shininess = 1;
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    
    /*3 deformisane lopte radi bolje simulacije*/
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

/*funkcija koja crta drvo
 * drvo se sastoji izstabla i krosnje*/
extern void drvo(){
    glPushMatrix();
        glTranslatef(0,3, 0);
        glScalef(15, 15, 15);
        stablo();
        krosnja();
    glPopMatrix();
}
