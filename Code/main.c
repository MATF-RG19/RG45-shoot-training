#include <stdlib.h>
#include <GL/glut.h>

#include "rifle.h"

#define INF 2000000

static int veiw_point_x;
static int mouse_y, mouse_x;
 int rand_x, rand_y;

static float rot_y, rot_x;

static void on_keyboard(unsigned char key, int x, int y);
static void on_display(void);
static void on_reshape(int width, int height);
static void init(void);
void initLightAndMaterial(void);
static void on_mouse(int button, int state, int x, int y);
static void on_motion(int x, int y);

void draw_tarrget(int x, int y){
    glBegin(GL_POLYGON);
        glColor3f(1,1,1);
        glVertex3f(x+1,0,y);
        glVertex3f(x,0,y);
        glVertex3f(x,2,y);
        glVertex3f(x+1,2,y);
    glEnd();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    glutInitWindowSize(1600, 900);
    glutInitWindowPosition(64, 32);
    glutCreateWindow(argv[0]);

    glutReshapeFunc(on_reshape);
    glutKeyboardFunc(on_keyboard);
    glutDisplayFunc(on_display);
    glutMouseFunc(on_mouse);
    glutMotionFunc(on_motion);

    init();
    glutMainLoop();
    return 0;
}

static void init(void)
{
    glClearColor(0.529, 0.808, 0.922, 0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    //Inicijalizujemo osvetljenje
    initLightAndMaterial();
    // Postavljanje pocetne kordinate pogleda po x
    veiw_point_x = 0;
    // Inicijalizcija misa
    mouse_x = 0;
    mouse_y = 0;
    //Inicijalizcija pocetne rotacije
    rot_x = 0;
    rot_y = 0;
    //Inicijalizacija pocetne mete
    rand_y = 30;
    rand_x = 1;
    glPointSize(5);
    glLineWidth(4);
}

static void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        // Izlazak iz programa
        exit(0);
        break;
    case 'l':
        // Kretanje pogleda levo po x
        veiw_point_x++;
        glutPostRedisplay();
        break;
    case 'r':
        // Kretanje pogleda desno po x
        veiw_point_x--;
        glutPostRedisplay();
        break;
    case 'm':
        rand_x = (rand() % 30) - 15;
        rand_y = (rand() % 50) + 15;
        glutPostRedisplay();
        break;
    }
}

static void on_mouse(int button, int state, int x, int y)
{
    mouse_x = x;
    mouse_y = y;
}
static void on_motion(int x, int y)
{
    int delta_x, delta_y;

    delta_x = x - mouse_x;
    delta_y = y - mouse_y;

    mouse_x = x;
    mouse_y = y;

    float mov = 0.5;

    if(delta_y > mov)
        rot_y += mov;
    else if(delta_y < -mov)
        rot_y -= mov;

    if(delta_x > mov)
        rot_x += mov;
    else if(delta_x < -mov)
        rot_x -= mov;

    glutPostRedisplay();
}

static void on_reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float) width / height, 0.1, 1500);
}

static void on_display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.4, 2, -0.85, 0, 0, 50, 0, 1, 0);

    //isacrtavanje puske
    glRotatef(180,0,1,0);
    glRotatef(-90,1,0,0);
    glScalef(0.01,0.01,0.01);
    glTranslatef(0,0,165);  
        make_rifle();
    glTranslatef(0,0,-165);
    glScalef(100,100,100);
    glRotatef(90,1,0,0);
    glRotatef(180,0,1,0);

    //Svet
    glRotatef(-rot_y,90-rot_x,0,rot_x);
    glRotatef(rot_x, 0,90,0);
    
    // Kordinatni sistem radi lakse orijetacije
    glBegin(GL_LINES);
        glColor3f(1,0,0);
        glVertex3f(0,0,0);
        glVertex3f(INF,0,0);
    glEnd();

    glBegin(GL_LINES);
        glColor3f(0,1,0);
        glVertex3f(0,0,0);
        glVertex3f(0,INF,0);
    glEnd();

    glBegin(GL_LINES);
        glColor3f(0,0,1);
        glVertex3f(0,0,0);
        glVertex3f(0,0,INF);
    glEnd();

    // Teren na kome ce biti streliste
    glColor3f(0.3, 0.60, 0.1);
    glBegin(GL_POLYGON);
        glNormal3f(0,1,0);
        glVertex3f(120,0,-10);
        glVertex3f(-100,0,-10);
        glVertex3f(-100,0,300);
        glVertex3f(120,0,300);
    glEnd();

    // Meta
    draw_tarrget(rand_x, rand_y);
   
    glRotatef(-rot_x, 0,90,0);    
    glRotatef(rot_y,90-rot_x,0,rot_x);

    glutSwapBuffers();
}

void
initLightAndMaterial(void)
{
    GLfloat light_position[] = { -100, 100, -100, 0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 1 };
    GLfloat light_diffuse[] = { 0.7, 0.7, 0.7, 1 };
    GLfloat light_specular[] = { 0.9, 0.9, 0.9, 1 };
    GLfloat ambient_coeffs[] = { 0.3, 0.7, 0.3, 1 };
    GLfloat diffuse_coeffs[] = { 1, 1, 1, 1 };
    GLfloat specular_coeffs[] = { 0.1, 0.1, 0.1, 1 };

    GLfloat shininess = 30;

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
  
}
