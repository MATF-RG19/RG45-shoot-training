#include "hands.hpp"
#include "rifle.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define PI 3.1415926535
#define EPSILON 0.1
#define INF 2000000

void draw_hand() 
{
    // Crtamo nadlakticu
    glutSolidSphere(4.5,10,10);
    glPushMatrix();
        GLdouble plane0[] = {0,0,-1,1};
        glEnable(GL_CLIP_PLANE0);
        glClipPlane(GL_CLIP_PLANE0, plane0);
            glTranslatef(0,0,-50);
            glutSolidCone(10,90,30,30);
        glDisable(GL_CLIP_PLANE0);
    glPopMatrix();
        // Saka
    glPushMatrix();
        glRotatef(10,1,0,0);
        glScalef(1.8,2,1.2);
        glTranslatef(-.2,0,5);
        glScalef(5,1,10);
        glRotatef(-6,0,1,0);
        glutSolidCube(1);   
    glPopMatrix();
}
    // Prsti sa velicinom scl i iskrivljenost prsta rot
void draw_finger(float rot, float scl)
{
    glPushMatrix();
        draw_cilindar(5.3*scl,1.2*scl);
        glTranslatef(0,5*scl,0);
        glRotatef(rot,0,0,1);
        glutSolidSphere(1.3*scl,10,5);
        draw_cilindar(4.3*scl,1.1*scl);
        glTranslatef(0,4*scl,0);
        glRotatef(rot,0,0,1);
        glutSolidSphere(1.2*scl,10,5);
        draw_cilindar(2*scl,1*scl);
        glTranslatef(0,2*scl,0);
        glutSolidSphere(1*scl,10,5);
    glPopMatrix();
}
    // Iscrtavanje leve ruke
void make_left_hand()
{
    glRotatef(90,0,1,0);
    glRotatef(90,0,0,1);
    glScalef(0.7,0.7,0.7);
    glColor3f(0.9,0.8,0.5);
        // Pozicioniranje prstiju
    glPushMatrix();
        draw_hand();
        glPushMatrix(); // Palac
            glTranslatef(2,-3,-1);
            glRotatef(50,1,0,0);
            glRotatef(70,0,1,0);
            glRotatef(40,0,0,-1);
            draw_finger(30,1.2);
        glPopMatrix();
        glPushMatrix();// Kaziprst
            glTranslatef(3,-2,10);
            glRotatef(-20,0,1,0);
            glRotatef(50,1,0,0);
            glRotatef(-80,0,1,0);
            draw_finger(20,1.05);
        glPopMatrix();
        glPushMatrix();// Srednji
            glTranslatef(0,-2.2,10);
            glRotatef(-20,0,1,0);
            glRotatef(50,1,0,0);
            glRotatef(-80,0,1,0);
            draw_finger(22,1.1);
        glPopMatrix();
        glPushMatrix();// Domali
            glTranslatef(-2.5,-2,10);
            glRotatef(-25,0,1,0);
            glRotatef(50,1,0,0);
            glRotatef(-80,0,1,0);
            draw_finger(25,1);
        glPopMatrix();
        glPushMatrix();// Mali
            glTranslatef(-5,-1.5,10);
            glRotatef(-30,0,1,0);
            glRotatef(50,1,0,0);
            glRotatef(-80,0,1,0);
            draw_finger(30,0.85);
        glPopMatrix();
    glPopMatrix();
}
    // Crtanje desne ruke
void make_right_hand()
{
    glRotatef(90,0,1,0);
    glRotatef(90,0,0,1);
    glScalef(0.5,0.5,0.5);
    glColor3f(0.9,0.8,0.5);
    glPushMatrix(); 
        glTranslatef(-40,0,-10);
        glRotatef(40,0,1,0);
        glRotatef(-80,0,0,1);
        draw_hand();
        glPushMatrix(); // Palac
            glTranslatef(-4,0,-1);
            glRotatef(90,0,1,0);
            draw_finger(50,1.2);
        glPopMatrix();
        glPushMatrix();// Kaziprst
            glTranslatef(-3,-2,10);
            glRotatef(20,0,1,0);
            glRotatef(50,1,0,0);
            glRotatef(-80,0,1,0);
            draw_finger(50,1.05);
        glPopMatrix();
        glPushMatrix();// Srednji
            glTranslatef(0,-2.2,10);
            glRotatef(20,0,1,0);
            glRotatef(50,1,0,0);
            glRotatef(-80,0,1,0);
            draw_finger(52,1.1);
        glPopMatrix();
        glPushMatrix();// Domali
            glTranslatef(2.5,-2,10);
            glRotatef(25,0,1,0);
            glRotatef(50,1,0,0);
            glRotatef(-80,0,1,0);
            draw_finger(55,1);
        glPopMatrix();
        glPushMatrix();// Mali
            glTranslatef(5,-1.5,10);
            glRotatef(30,0,1,0);
            glRotatef(50,1,0,0);
            glRotatef(-80,0,1,0);
            draw_finger(50,0.85);
        glPopMatrix();
    glPopMatrix();  
}
