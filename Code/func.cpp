#include "func.hpp"
#include <GL/glut.h>
#include <stdlib.h>

// Iscrtavanje mete na daljini trn za rot stepeni od z ose
void draw_tarrget(int h, int rot, int trn) {
  glPushMatrix();
  glRotatef(rot, 0, 1, 0);
  glTranslatef(0, h, trn);
  // Tabla mete
  float r = 0.5;
  glBegin(GL_POLYGON);
  glColor3f(0.8, 0.8, 0.8);
  glNormal3f(0, 0, -1);
  glVertex3f(r, -r, 0);
  glVertex3f(-r, -r, 0);
  glVertex3f(-r, r, 0);
  glVertex3f(r, r, 0);
  glEnd();
  // Krugovi
  r -= 0.05;
  glTranslatef(0, 0, -0.1);
  glColor3f(1, 1, 0);
  glutSolidCone(r, 0, 40, 0);
  glTranslatef(0, 0, -0.2);
  glColor3f(1, 0, 0);
  glutSolidCone(r / 2, 0, 40, 0);
  glColor3f(0, 0, 0);
  glutSolidSphere(0.05, 5, 5);
  // Postolje
  glTranslatef(0, 0, 0.3);
  glBegin(GL_POLYGON);
  glColor3f(0.8, 0.8, 0.8);
  glNormal3f(0, 0, 1);
  glVertex3f(r, -r, 0);
  glVertex3f(r - 0.1, -r, 0);
  glVertex3f(r - 0.1, -h, 0);
  glVertex3f(r, -h, 0);
  glEnd();
  glBegin(GL_POLYGON);
  glColor3f(0.8, 0.8, 0.8);
  glNormal3f(0, 0, 1);
  glVertex3f(-r, -r, 0);
  glVertex3f(-r + 0.1, -r, 0);
  glVertex3f(-r + 0.1, -h, 0);
  glVertex3f(-r, -h, 0);
  glEnd();
  glPopMatrix();
}
// Metak na trn od puske
void fire(float bullet_trn) {
  glColor3f(1, 0, 0);
  glPushMatrix();
  glTranslatef(0, 1.6, bullet_trn);
  glutSolidSphere(0.01, 10, 10);
  glPopMatrix();
}
