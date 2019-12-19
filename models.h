#ifndef MODELS_H_
#define MODELS_H_

#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
#include <stdbool.h>
#include<math.h>
#include <time.h>


#define M_PI acos(-1.0)

#define FILENAME0 "grass.bmp"



extern void metak();
extern void trava(GLuint names[]);
extern void puc(float animation_parameter);
extern void ruka();
extern void meda(float animation_parameter, float xMedaPom, float yMedaPom);
extern void drvo();


#endif
