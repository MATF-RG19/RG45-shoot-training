#include "func.h"
#include <stdlib.h>
#include <GL/glut.h>

void draw_tarrget(int h, int rot, int trn){
    glPushMatrix();
    glRotatef(rot,0,1,0);
    glTranslatef(0,h,trn);
    
    float r = 0.5;
    
    glBegin(GL_POLYGON);
        glColor3f(1,1,1);
        glNormal3f(0,0,-1);
        glVertex3f(r,-r,0);
        glVertex3f(-r,-r,0);
        glVertex3f(-r,r,0);
        glVertex3f(r,r,0);
    glEnd();

    r -= 0.05;

    glTranslatef(0,0,-0.1);
    glColor3f(0,0,1);
    glutSolidCone(r, 0, 40, 0);
    glTranslatef(0,0,-0.2);
    glColor3f(1,0,0);
    glutSolidCone(r/2, 0, 40, 0);
    glColor3f(0,0,0);
    glutSolidSphere(0.05,5,5);
    
    glTranslatef(0,0,0.3);

    glBegin(GL_POLYGON);
        glColor3f(0,0,0);
        glNormal3f(0,0,1);
        glVertex3f(r,-r,0);
        glVertex3f(r-0.1,-r,0);
        glVertex3f(r-0.1,-h,0);
        glVertex3f(r,-h,0);
    glEnd();
    
     glBegin(GL_POLYGON);
        glColor3f(0,0,0);
        glNormal3f(0,0,1);
        glVertex3f(-r,-r,0);
        glVertex3f(-r+0.1,-r,0);
        glVertex3f(-r+0.1,-h,0);
        glVertex3f(-r,-h,0);
    glEnd();

    glPopMatrix();
}

void fire(float bullet_trn)
{
    glPushMatrix();
    glTranslatef(0,1.6,bullet_trn);
    
    glColor3f(1,0,0);
    glutSolidSphere(0.01,10,10);

    glPopMatrix();
}

void draw_tree(float s)
{
    glBegin(GL_POLYGON);
        glColor3f(0.5,0.3,0.3);
        glVertex3f(-2*s,0,0);
        glVertex3f(-2*s,6*s,0);
        glVertex3f(2*s, 6*s,0);
        glVertex3f(2*s,0,0);
    glEnd();

    
}