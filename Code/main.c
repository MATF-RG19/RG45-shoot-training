#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <GL/glut.h>

#include "hands.h"
#include "rifle.h"
#include "func.h"

#include "image.h"
static GLuint names[3];
#define FILENAME1 "tree.bmp"
#define FILENAME2 "garss.bmp"
static float matrix[16];

#define TIMER_INTERVAL 10
#define TIMER_ID 0

#define INF 2000000

static int mouse_y, mouse_x;
static int rand_rot, rand_trn;
static float anim_param, t;
static float rot_rl, rot_ud;
static int width, height;
static int targets_counter, bullet_counter;
static int on_going;

static void on_keyboard(unsigned char key, int x, int y);
static void on_display(void);
static void on_reshape(int width, int height);
static void init(void);
static void initLightAndMaterial(void);
static void on_mouse(int button, int state, int x, int y);
static void on_passive_motion(int x, int y);
static void on_timer(int);
void write_text(const char* text, int x, int y);

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
    glutPassiveMotionFunc(on_passive_motion);

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
        // Inicijalizcija misa
    mouse_x = 0;
    mouse_y = 0;
        //Inicijalizcija pocetne rotacije
    rot_rl = 0;
    rot_ud = 0;
        //Inicijalizacija pocetne mete
    rand_rot = 0;
    rand_trn = 15;
        //Animacija
    anim_param = 0;
    on_going = 0;
        //Brojace pogodjenig meta
    targets_counter = 0;
    bullet_counter = 10;

    glPointSize(5);
    glLineWidth(4);

     Image * image;

    //glEnable(GL_TEXTURE_2D);

    glTexEnvf(GL_TEXTURE_ENV,
              GL_TEXTURE_ENV_MODE,
              GL_REPLACE);


    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    image = image_init(0, 0);

    glGenTextures(3,names);

    image_read(image, FILENAME1);
    glBindTexture(GL_TEXTURE_2D, names[1]);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->width, image->height, 
                    0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);


    image_read(image, FILENAME2);
    glBindTexture(GL_TEXTURE_2D, names[0]);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 
                    0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    /* Iskljucujemo aktivnu teksturu */
    glBindTexture(GL_TEXTURE_2D, 0);

    /* Unistava se objekat za citanje tekstura iz fajla. */
    image_done(image);

}

static void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:    // Izlazak iz programa
        exit(0);
        break;
    case 'm':   //Random geerisanje mete
        rand_rot = (rand() % 60) - 30;
        rand_trn = (rand() % 20) + 10;
        glutPostRedisplay();
        break;
    case 'r':
    case 'R':
        bullet_counter = 10;
        break;
    case 32:    //Ispaljivanje metka
        if (bullet_counter == 0)
            break;
        bullet_counter--;
        anim_param = 1;
        glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
        anim_param = 0;
        glutPostRedisplay();
        break;
    }
    glutPostRedisplay();
}

static void on_timer(int v)
{
    if (v != TIMER_ID) return;
    anim_param += 1;
    anim_param *= 2;
    glutPostRedisplay();
        // TO DO postavi bolji pogodak
        //proverava da li je meta pogodjone i ako jeste zadaje se nova
    if(anim_param > rand_trn && (-rot_rl < rand_rot+25/25 && -rot_rl > rand_rot-25/25 ) && rot_ud > 0.5 && rot_ud < 3){
        srand(time(NULL));
        rand_rot = (rand() % 45) - 15;
        rand_trn = (rand() % 10) + 15;
        targets_counter ++;
        glutPostRedisplay();
        return;
    }

    if (anim_param != 0 && anim_param < 100) {
        glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }

}

static void on_mouse(int button, int state, int x, int y)
{
    mouse_x = x;
    mouse_y = y;

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) { 
        if (bullet_counter == 0)
            return;
    
        bullet_counter--;
        anim_param = 1;
        glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
        anim_param = 0;
        glutPostRedisplay();
    }	
}

static void on_passive_motion(int x, int y)
{
    int delta_x, delta_y;
    delta_x = x - mouse_x;
    delta_y = y - mouse_y;
    mouse_x = x;
    mouse_y = y;
    float mov = 0.5;

    if(delta_x > mov && rot_rl < 40)
        rot_rl += mov;
    else if(delta_x < -mov && rot_rl > -40)
        rot_rl -= mov;
    if(delta_y > mov && rot_ud < 30)
        rot_ud += mov;
    else if(delta_y < -mov && rot_ud > -20)
        rot_ud -= mov;

    glutPostRedisplay();
}

static void on_reshape(int w, int h)
{
    width = w;
    height = h;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float) w / h, 0.1, 150);

}

static void on_display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.35, 1.9, -0.7, 0, 0, 50, 0, 1, 0);

        //Ispis teksta
    char str[32];
    sprintf(str, "Targets: %d", targets_counter);
    glColor3f(1, 0, 0); 
    write_text(str, 40, height-40);
    sprintf(str, "Bullets: %d", bullet_counter);
    write_text(str, width-140, height-40);
    
    glColor3f(0, 0.9, 0.2); 
    write_text("-+-", width/2-10, height/2+10);

    //isacrtavanje puske
    float f_react = anim_param < 10 ? anim_param : 0;

    glRotatef(180,0,1,0);
    glRotatef(-90+f_react,1,0,0);
    glScalef(0.01,0.01,0.01);
    glTranslatef(0,0,165);  
        make_rifle();
        glPushMatrix();
            glTranslatef(-4,-6,-8);
            glRotatef(15,0,-1,0);
            glRotatef(40,0,0,1);
            glScalef(0.7,0.7,0.7);
            glRotatef(10,1,0,1);
            make_left_hand();
        glPopMatrix();    
        glPushMatrix();
            glTranslatef(-8.2,-6,-9);
            glRotatef(15,0,-1,0);
            glRotatef(45,0,0,1);
            glScalef(0.9,0.9,0.9);
            make_right_hand();
        glPopMatrix();
    glTranslatef(0,0,-165);
    glScalef(100,100,100);
    glRotatef(90-f_react,1,0,0);
    glRotatef(180,0,1,0);

    //Metak
    fire(anim_param);

    //Svet
    glPopMatrix();
    glRotatef(-rot_ud,1,0,0);
    glRotatef(rot_rl, 0,90,0);

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, names[0]);
        glBegin(GL_QUADS);
            glNormal3f(0,1,0);
            glTexCoord2f(0,0); glVertex3f(100,0,-10);
            glTexCoord2f(50,0); glVertex3f(-100,0,-10);
            glTexCoord2f(50,50);  glVertex3f(-100,0,300);
            glTexCoord2f(0,50); glVertex3f(100,0,300);
        glEnd();
        glBindTexture(GL_TEXTURE_2D, 0);
        //glDisable(GL_TEXTURE_2D);

        int i = 0;
        int tr,rt,d,sx,sy;
        srand(12);
        for (i = 0; i < 180; i++){
            d = i % 2 ? -1 : 1; // strana na kojoj je drvo;
            tr = (180-i)+20;
            rt = rand()%50+20;
            sx = rand()%10;
            sy = rand()%10;
            glPushMatrix();
            glRotatef(60*rt/tr, 0,d,0);
            glTranslatef(0,0,tr);
                glEnable(GL_BLEND);
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, names[1]);
                glScalef(0.5+sx/10.0,0.5+sy/20.0,.5);
                glBegin(GL_QUADS);
                    glTexCoord2f(0.2,0); glVertex3f(0,0,0);
                    glTexCoord2f(1.2,0); glVertex3f(8,0,0);
                    glTexCoord2f(1.2,1); glVertex3f(8,16,0);
                    glTexCoord2f(0.2,1); glVertex3f(0,16,0);
                glEnd();
                glBindTexture(GL_TEXTURE_2D, 0);
                glDisable(GL_TEXTURE_2D);
                glDisable(GL_BLEND);
            glPopMatrix();
        }

        // Meta
        float h = 1;
        draw_tarrget(h, rand_rot, rand_trn);
    glPopMatrix();

    glutSwapBuffers();
}

void
initLightAndMaterial(void)
{
    GLfloat light_position[] = {-100, 100, 100, 0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 1 };
    GLfloat light_diffuse[] = { 0.6, 0.7, 0.7, 1 };
    GLfloat light_specular[] = { 0.9, 0.9, 0.9, 1 };
    GLfloat ambient_coeffs[] = { 0.3, 0.5, 0.3, 1 };
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

void write_text(const char* text, int x, int y)
{
    glDisable(GL_LIGHTING); 
    glPushMatrix(); 
        glMatrixMode(GL_PROJECTION); 
        GLdouble matrix[16];
        glGetDoublev(GL_PROJECTION_MATRIX, matrix);
        glLoadIdentity();
        glOrtho(0, width, 0, height, -5, 5);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRasterPos2f(x,y); 
            //ispisivanje karakera
        for(int i = 0; text[i]; i++){
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int) text[i]); 
        }
        glMatrixMode(GL_PROJECTION);
        glLoadMatrixd(matrix); 
        glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glEnable(GL_LIGHTING);
}