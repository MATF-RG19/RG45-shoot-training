#include "rifle.hpp"

#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>

#define PI 3.1415926535
#define EPSILON 0.1
#define INF 2000000

void set_normal_and_vertex(float u, float v, float r) {
  glNormal3f(sin(v), 0, cos(v));
  glVertex3f(r * sin(v), u, r * cos(v));
}
// Crtanje cilindra kao na casu
void draw_cilindar(float l, float r) {
  float u, v;
  glPushMatrix();
  for (u = 0; u < l - .1; u += PI / 20) {
    glBegin(GL_TRIANGLE_STRIP);
    for (v = 0; v <= PI * 2 + EPSILON; v += PI / 20) {
      set_normal_and_vertex(u, v, r);
      set_normal_and_vertex(u + PI / 20, v, r);
    }
    glEnd();
  }
  glPopMatrix();
}
// Crtanje otvorene kupe kao na casu
void draw_cone(float l, float r) {
  float v;
  glPushMatrix();
  glBegin(GL_TRIANGLE_STRIP);
  for (v = 0; v <= PI * 2 + EPSILON; v += PI / 20) {
    glNormal3f(sin(v), -l, cos(v));
    glVertex3f(r * sin(v), 0, r * cos(v));
    glVertex3f(0, l, 0);
  }
  glEnd();
  glPopMatrix();
}
// Ova funkcija iscrtava telo puske
void draw_body() {
  // Telo puske sastavljeno od poligona
  glBegin(GL_POLYGON);
  glNormal3f(0, 0, 1);
  glVertex3f(-1, 0, 2);
  glVertex3f(1, 0, 2);
  glVertex3f(1, -30, 2);
  glVertex3f(-1, -30, 2);
  glEnd();

  glBegin(GL_POLYGON);
  glNormal3f(0, 0, 1);
  glVertex3f(1, 0, 2);
  glVertex3f(1, 0, 1);
  glVertex3f(1, -30, 1);
  glVertex3f(1, -30, 2);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(1, 0, 1);
  glVertex3f(1.5, 0, 0.5);
  glVertex3f(1.5, -30, 0.5);
  glVertex3f(1, -30, 1);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(1.5, 0, -2);
  glVertex3f(1.5, 0, 0.5);
  glVertex3f(1.5, -30, 0.5);
  glVertex3f(1.5, -30, -2);
  glEnd();

  glBegin(GL_POLYGON);
  glNormal3f(-1, 0, 0);
  glVertex3f(-1, 0, 2);
  glVertex3f(-1, -30, 2);
  glVertex3f(-1, -30, 1);
  glVertex3f(-1, 0, 1);
  glEnd();

  glBegin(GL_POLYGON);
  glNormal3f(-1, 0, 1);
  glVertex3f(-1, 0, 1);
  glVertex3f(-1.5, 0, 0.5);
  glVertex3f(-1.5, -30, 0.5);
  glVertex3f(-1, -30, 1);
  glEnd();

  glBegin(GL_POLYGON);
  glNormal3f(-1, 0, 0);
  glVertex3f(-1.5, 0, -2);
  glVertex3f(-1.5, 0, 0.5);
  glVertex3f(-1.5, -30, 0.5);
  glVertex3f(-1.5, -30, -2);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(-1.5, 0, -2);
  glVertex3f(1.5, 0, -2);
  glVertex3f(1.5, -30, -2);
  glVertex3f(-1.5, -30, -2);
  glEnd();

  // Sarzer sastavljen od poligona i valjkova
  glTranslatef(0, -32, -3);
  glRotatef(-80, 1, 0, 0);
  draw_cilindar(6, 0.8);
  glTranslatef(0, 0, 6);
  draw_cilindar(6, 0.8);
  glTranslatef(0, 0, -6);

  glBegin(GL_POLYGON);
  glNormal3f(-1, 0, 0);
  glVertex3f(-0.8, 0, 0);
  glVertex3f(-0.8, 6, 0);
  glVertex3f(-0.8, 6, 6);
  glVertex3f(-0.8, 0, 6);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(0.8, 0, 0);
  glVertex3f(0.8, 6, 0);
  glVertex3f(0.8, 6, 6);
  glVertex3f(0.8, 0, 6);
  glEnd();

  glRotatef(80, 1, 0, 0);
  glTranslatef(0, 32, 3);
}
// Ova funkcija iscrtava kundak duzine l, sirine r, visine h
void draw_gunstock(float l, float r, float h) {
  float u, v;
  glTranslatef(0, -42, 1);
  // Crtanje polu valjka
  for (u = 0; u < l - .2; u += PI / 20) {
    glBegin(GL_TRIANGLE_STRIP);
    for (v = -PI / 2; v <= PI / 2 + EPSILON; v += PI / 10) {
      set_normal_and_vertex(u, v, r);
      set_normal_and_vertex(u + PI / 10, v, r);
    }
    glEnd();
  }
  // Poklopac polu valjka
  glBegin(GL_TRIANGLE_STRIP);
  for (v = -PI / 2; v <= PI / 2 + EPSILON; v += PI / 20) {
    glNormal3f(0, -1, 0);
    glVertex3f(r * sin(v), 0, r * cos(v));
    glVertex3f(0, 0, 0);
  }
  glEnd();
  // Stranice kundaka
  glBegin(GL_POLYGON);
  glNormal3f(-1, 0, 0);
  glVertex3f(-r, 0, 0);
  glVertex3f(-r, 0, -h);
  glVertex3f(-r, l, -3);
  glVertex3f(-r, l, 0);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(r, 0, 0);
  glVertex3f(r, l, 0);
  glVertex3f(r, l, -3);
  glVertex3f(r, 0, -h);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(r, 0, -h);
  glVertex3f(-r, 0, -h);
  glVertex3f(-r, l, -3);
  glVertex3f(r, l, -3);
  glEnd();

  glBegin(GL_POLYGON);
  glNormal3f(0, -1, 0);
  glVertex3f(r, 0, -h);
  glVertex3f(-r, 0, -h);
  glVertex3f(-r, 0, 0);
  glVertex3f(r, 0, 0);
  glEnd();
  glPopMatrix();
  glTranslatef(0, 42, 1);
}
// Iscrtavanje delova za drzanje
void draw_hand_guard(float l, float w, float h) {
  glTranslatef(0, -11, -3.5);
  glBegin(GL_POLYGON);
  glNormal3f(-1, 0, 0);
  glVertex3f(-w, 0, 0);
  glVertex3f(-w, l, 0);
  glVertex3f(-w, l - 2, -h);
  glVertex3f(-w, 0, -h);
  glEnd();

  glBegin(GL_POLYGON);
  glNormal3f(1, 0, 0);
  glVertex3f(w, 0, 0);
  glVertex3f(w, l, 0);
  glVertex3f(w, l - 2, -h);
  glVertex3f(w, 0, -h);
  glEnd();

  glBegin(GL_POLYGON);
  glNormal3f(5, 0, -1);
  glVertex3f(w, 0, -h);
  glVertex3f(w, l - 2, -h);
  glVertex3f(w - 0.2, 0, -h - 1);
  glEnd();

  glBegin(GL_POLYGON);
  glNormal3f(-5, 0, -1);
  glVertex3f(-w, 0, -h);
  glVertex3f(-w, l - 2, -h);
  glVertex3f(-w + 0.2, 0, -h - 1);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(-w, l - 2, -h);
  glVertex3f(w, l - 2, -h);
  glVertex3f(w - 0.2, 0, -h - 1);
  glVertex3f(-w + 0.2, 0, -h - 1);
  glEnd();

  glBegin(GL_POLYGON);
  glNormal3f(0, -1, 0);
  glVertex3f(-w, 0, 0);
  glVertex3f(-w, 0, -h);
  glVertex3f(-w + 0.2, 0, -h - 1);
  glVertex3f(w + 0.2, 0, -h - 1);
  glVertex3f(w, 0, -h);
  glVertex3f(w, 0, 0);
  glEnd();

  glBegin(GL_POLYGON);
  glNormal3f(0, 0, 1);
  glVertex3f(-w, 0, 0);
  glVertex3f(-w, l, 0);
  glVertex3f(w, l, 0);
  glVertex3f(w, 0, 0);
  glEnd();

  glTranslatef(0, 11, 3.5);

  // deo za drzanje
  glTranslatef(0, -18, -1.5);
  glRotatef(-110, 1, 0, 0);

  float wd = 0.8; // Sirina drzaca
  draw_cilindar(10, wd);
  glTranslatef(0, 0, 3);
  draw_cilindar(10, wd);
  glTranslatef(0, 0, -3);

  glBegin(GL_POLYGON);
  glNormal3f(-1, 0, 0);
  glVertex3f(-wd, 10, 0);
  glVertex3f(-wd, 0, 0);
  glVertex3f(-wd, 0, 3);
  glVertex3f(-wd, 10, 3);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(wd, 0, 3);
  glVertex3f(wd, 0, 0);
  glVertex3f(wd, 10, 0);
  glVertex3f(wd, 10, 3);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(-wd, 10, 0);
  glVertex3f(-wd, 10, 3);
  glVertex3f(wd, 10, 3);
  glVertex3f(wd, 10, 0);
  glEnd();

  glRotatef(110, 1, 0, 0);
  glTranslatef(0, 18, 1.5);

  // dodatak iznad okidaca
  glBegin(GL_POLYGON);
  glVertex3f(wd, -16, -4.5);
  glVertex3f(wd, -16, -2);
  glVertex3f(wd, -10, -2);
  glVertex3f(wd, -10, -4.5);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(-wd, -16, -4.5);
  glVertex3f(-wd, -16, -2);
  glVertex3f(-wd, -10, -2);
  glVertex3f(-wd, -10, -4.5);
  glEnd();

  glBegin(GL_POLYGON);
  glNormal3f(0, 0, -1);
  glVertex3f(-wd, -16, -4.5);
  glVertex3f(wd, -16, -4.5);
  glVertex3f(wd, -10, -4.5);
  glVertex3f(-wd, -10, -4.5);
  glEnd();
}
// Nisani i delovi vezani za njih
void draw_sight(float l) {
  float w = 1.2;
  glTranslatef(0, -15, -0.5);

  glBegin(GL_POLYGON);
  glNormal3f(-1, 0, 0);
  glVertex3f(-w, 0, 0);
  glVertex3f(-w, 0, 1);
  glVertex3f(-w, l + 0.8, 1);
  glVertex3f(-w, l, 0);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(w, 0, 0);
  glVertex3f(w, 0, 1);
  glVertex3f(w, l + 0.8, 1);
  glVertex3f(w, l, 0);
  glEnd();

  glBegin(GL_POLYGON);
  glNormal3f(0, 0, 1);
  glVertex3f(-w, 0, 1);
  glVertex3f(w, 0, 1);
  glVertex3f(w, l + 0.8, 1);
  glVertex3f(-w, l + 0.8, 1);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(-w, 0, 0);
  glVertex3f(w, 0, 0);
  glVertex3f(w, l, 0);
  glVertex3f(-w, l, 0);
  glEnd();

  glBegin(GL_POLYGON);
  glNormal3f(0, -1, 0);
  glVertex3f(-w, 0, 0);
  glVertex3f(w, 0, 0);
  glVertex3f(w, 0, 1);
  glVertex3f(-w, 0, 1);
  glEnd();
  glTranslatef(0, 15, 0.5);

  // drazac snajpera
  float wr = 1; // Sirina drzaca
  glTranslatef(0, -10, 0);
  glColor3f(0.4, 0.4, 0.4);

  glBegin(GL_POLYGON);
  glNormal3f(-1, 0, 0);
  glVertex3f(-wr, 2, 0);
  glVertex3f(-wr, 0, 2);
  glVertex3f(-wr, 5, 2);
  glVertex3f(-wr, 7, 0);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(wr, 2, 0);
  glVertex3f(wr, 0, 2);
  glVertex3f(wr, 5, 2);
  glVertex3f(wr, 7, 0);
  glEnd();
  glTranslatef(0, 10, 0);

  // Snajper
  glColor3f(0.3, 0.3, 0.3);
  glTranslatef(0, -16, 3);
  draw_cilindar(12, 1.6);
  glTranslatef(0, 16, -3);

  glTranslatef(0, 0, 3);
  glRotatef(90, 1, 0, 0);
  glutSolidCone(2.21, 15, 40, 1);
  glRotatef(-90, 1, 0, 0);
  draw_cilindar(4, 2.2);
  glTranslatef(0, 0, -3);

  glTranslatef(0, -14, 3);
  glColor3f(.5, 0.6, 0.9);
  glutSolidSphere(1.5, 20, 20);
  glTranslatef(0, -2, 0);
  glColor3f(0.2, .2, .2);
  draw_cone(2.4, 1.6);
  glTranslatef(0, 16, -3);

  // Prednji nisan puske
  glTranslatef(0, 37, -3);
  glColor3f(0.2, 0.2, 0.2);
  glBegin(GL_POLYGON);
  glNormal3f(0, 0, 1);
  glVertex3f(1.5, -1, 2);
  glVertex3f(3, 1, 2);
  glVertex3f(3, 4, 2);
  glVertex3f(-3, 4, 2);
  glVertex3f(-3, 1, 2);
  glVertex3f(-1.5, -1, 2);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(1.5, -1, 0);
  glVertex3f(3, 1, 0);
  glVertex3f(3, 4, 0);
  glVertex3f(-3, 4, 0);
  glVertex3f(-3, 1, 0);
  glVertex3f(-1.5, -1, 0);
  glEnd();

  glBegin(GL_POLYGON);
  glNormal3f(-1, 0, 0);
  glVertex3f(-3, 4, 0);
  glVertex3f(-3, 4, 2);
  glVertex3f(-3, 1, 2);
  glVertex3f(-3, 1, 0);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(3, 4, 0);
  glVertex3f(3, 4, 2);
  glVertex3f(3, 1, 2);
  glVertex3f(3, 1, 0);
  glEnd();

  glBegin(GL_POLYGON);
  glNormal3f(-1, -2, 0);
  glVertex3f(-1.5, -1, 2);
  glVertex3f(-3, 1, 2);
  glVertex3f(-3, 1, 0);
  glVertex3f(-1.5, -1, 0);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(1.5, -1, 2);
  glVertex3f(3, 1, 2);
  glVertex3f(3, 1, 0);
  glVertex3f(1.5, -1, 0);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(1.5, -1, 0);
  glVertex3f(1.5, -1, 2);
  glVertex3f(-1.5, -1, 2);
  glVertex3f(-1.5, -1, 0);
  glEnd();

  glTranslatef(0, -37, 3);
}
// Okidac i delovi oko njega
void draw_trriger() {
  float w = 0.4;
  float h = 0.5;
  float e = 0.6;

  glTranslatef(0, -14, -6.3);

  // Okidac
  glBegin(GL_POLYGON);
  glNormal3f(-1, 0, 0);
  glVertex3f(0, 0, 3);
  glVertex3f(0, w + h, 0.2);
  glVertex3f(0, w + e, 0.2);
  glVertex3f(0, w, 3);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(w, 0, 3);
  glVertex3f(w, w + h, 0.2);
  glVertex3f(w, w + e, 0.2);
  glVertex3f(w, w, 3);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(w, 0, 3);
  glVertex3f(w, w + h, 0.2);
  glVertex3f(0, w + h, 0.2);
  glVertex3f(0, 0, 3);
  glEnd();

  // Zastitnik okidaca
  glBegin(GL_POLYGON);
  glVertex3f(-w, 0, 0);
  glVertex3f(-w, 0, -h);
  glVertex3f(-w, 4, -h);
  glVertex3f(-w, 4, 0);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(w, 0, 0);
  glVertex3f(w, 0, -h);
  glVertex3f(w, 4, -h);
  glVertex3f(w, 4, 0);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(-w, 0, 0);
  glVertex3f(w, 0, 0);
  glVertex3f(w, 4, 0);
  glVertex3f(-w, 4, 0);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(-w, 0, 0);
  glVertex3f(-w, 0, -h);
  glVertex3f(-w, -2, -h + e);
  glVertex3f(-w, -2, 0 + e);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(w, 0, 0);
  glVertex3f(w, 0, -h);
  glVertex3f(w, -2, -h + e);
  glVertex3f(w, -2, 0 + e);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(-w, 0, 0);
  glVertex3f(w, 0, 0);
  glVertex3f(w, -2, 0 + e);
  glVertex3f(-w, -2, 0 + e);
  glEnd();

  glTranslatef(0, 14, 6.3);
}
// Ovde sastavljamo sve delove puske u jednu celinu
void make_rifle() {
  glColor3f(0.8, 0.8, 0.4);
  draw_body();
  glColor3f(0.4, 0.4, 0.4);
  draw_cilindar(40, 1);
  glColor3f(0.3, 0.3, 0.3);
  draw_gunstock(20, 2, 10);
  draw_hand_guard(23, 2, 2.5);
  draw_sight(29);
  draw_trriger();
}
