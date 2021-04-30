#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <GL/glut.h>

#include "hands.hpp"
#include "rifle.hpp"
#include "func.hpp"
#include "image.hpp"

#define TIMER_INTERVAL 10
#define TIMER_ID 0
#define INF 2000000

static char* FILENAME1 = "../tree.bmp"; // Slika teksture objekta
static char* FILENAME2 = "../grass.bmp"; // Slika teksture podloge
static float matrix[16]; 
static GLuint names[3];

static long t; // Vreme pocetka partije
static int mouse_y, mouse_x;
static float rand_rot, rand_trn; // Promenljive postavvljanja mete
static float anim_param;
static float rot_rl, rot_ud; // Kretanje kamere u odnosu na svet (right-left  up-down)
static int width, height; // Dimezije ekrana
static int targets_counter, bullet_counter; // Brojaci pogodaka i metkova
static int best_score = -1; // Najbolji uspeh tokom igre
static int on_going; // Oznacavanje toka igre
static int texture_param; // Parametar koji regulise sirinu slike texture drvo-zgrada
int target_limit = 0; // Broj meta potrebnih za produzetak igre
int time_limit = 0; // Preostalo vreme za igranje

static void on_keyboard(unsigned char key, int x, int y);
static void on_display(void);
static void on_reshape(int width, int height);
static void init(void);
static void initLightAndMaterial(void);
static void on_mouse(int button, int state, int x, int y);
static void on_passive_motion(int x, int y);
static void on_timer(int);
void write_text(const char* text, int x, int y);
void init_texture();

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    glutInitWindowSize(1920,1080);
    glutInitWindowPosition(32, 16);
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
    glEnable(GL_MULTISAMPLE);
        // Inicijalizujemo osvetljenje
    initLightAndMaterial();
        // Inicijalizcija misa
    mouse_x = 0;
    mouse_y = 0;
        // Inicijalizcija pocetne rotacije
    rot_rl = 0;
    rot_ud = 0;
        // Inicijalizacija pocetne mete
    rand_rot = 0;
    rand_trn = 15;
        // Animacija
    anim_param = 0;
    on_going = 0;
    t = time(NULL);
        // Brojace pogodjenig meta
    targets_counter = 0;
    bullet_counter = 10;
	// Inicijalizcija primitiva
    glPointSize(5);
    glLineWidth(4);
	// Inicijalizacija promenljive za scaliranje texture
    texture_param = 10;
        // Inicijalizacij teksture
    init_texture();
}

static void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:    // Izlazak iz programa
        exit(0);
        break;
    case 's':
    case 'S':   // Pokrecemo igru ako nije pokrenuta
	if (on_going < 1){
		on_going = 1;
		t = time(NULL);
		target_limit = 5;	
		time_limit = 10;
		targets_counter = 0;
		bullet_counter = 10;
	}
        break;
    case 'e':
    case 'E':   // Zavrsavamo partiju
	on_going = -1;
        break;
    case 'c':
    case 'C':   // Ukljucujemo city mode
	texture_param = 30;
	FILENAME1 = "build.bmp";
        FILENAME2 = "asph.bmp";
	init_texture();
        break;
    case 'f':
    case 'F':   // Ukljucujemo forest mode
	texture_param = 10;
	FILENAME1 = "tree.bmp";
        FILENAME2 = "grass.bmp";
	init_texture();
        break;
    case 'r':
    case 'R': // Brojac metkova u sarzeru
        bullet_counter = 10;
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
        // Proverava da li je meta pogodjone i ako jeste zadaje se nova
    if(anim_param > rand_trn && (-rot_rl < rand_rot+25/(float)rand_trn && -rot_rl > rand_rot-25/(float)rand_trn ) && rot_ud > 0.5/(float)rand_trn && rot_ud < 3*25/(float)rand_trn){
        srand(time(NULL)); // Meta dobije novu slucajnu poziciju
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
        if (bullet_counter == 0 || on_going <= 0) 
            return;
            // Ispaljivanje metka klikom misa
        bullet_counter--;
        anim_param = 1; // Pokrece se animacija metka
        glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
        anim_param = 0;
        glutPostRedisplay();
    }	
}

static void on_passive_motion(int x, int y)
{
    int delta_x, delta_y;
    delta_x = x - mouse_x; // Pomeraj x
    delta_y = y - mouse_y; // Pomeraj y
    mouse_x = x;
    mouse_y = y;
    float mov = 0.5; // Pomeranje kamere
    float eps = 0.01; // Detekcija pomeraja
        // Kretanje kamere u granicama terena (l:-40, r:40, u:30, d:-20)
    if(delta_x > eps && rot_rl < 40)
        rot_rl += mov;
    else if(delta_x < -eps && rot_rl > -40)
        rot_rl -= mov;
    if(delta_y > eps && rot_ud < 30)
        rot_ud += mov;
    else if(delta_y < -eps && rot_ud > -20)
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
    gluPerspective(60, (float) w / h, 0.1, 200);
}

static void on_display(void)
{
    long current_time = time(NULL) - t; // Vreme za igru
    char str[32]; // Bafer teksta 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.35, 1.9, -0.7, 0, 0, 50, 0, 1, 0);
        // Nisan
    glColor3f(1, 0.4, 0.1); 
    write_text("-+-", width/2-10, height/2+10);
        // Isacrtavanje puske i ruku
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
        // Metak
    fire(anim_param);
        // Okolina
    glPopMatrix();
    glRotatef(-rot_ud,1,0,0);
    glRotatef(rot_rl, 0,90,0);
        glEnable(GL_TEXTURE_2D); // Ukljucivanje tekstura
        glBindTexture(GL_TEXTURE_2D, names[0]);
        glBegin(GL_QUADS);
            glNormal3f(0,1,0);
            glTexCoord2f(0,0); glVertex3f(100,0,-10);
            glTexCoord2f(3*texture_param,0); glVertex3f(-100,0,-10);
            glTexCoord2f(3*texture_param,3*texture_param); glVertex3f(-100,0,300);
            glTexCoord2f(0,3*texture_param); glVertex3f(100,0,300);
        glEnd();
        glBindTexture(GL_TEXTURE_2D, 0);
        int i = 0;
        int tr,rt,d,sx,sy; // Parametrii za definisanje objeata(drvo) na slici 
        srand(12);
        for (i = 0; i < 180; i++){
            d = i % 2 ? -1 : 1; // Strana na kojoj je objekat;
            tr = (180-i)+20; // Translacija od koo pocetka
            rt = rand()%50+20; // Rotacija
            sx = rand()%texture_param; // Sirina slike (objekta)
            sy = rand()%10; // Visina slike (objekta)
            glPushMatrix();
                glRotatef(60*rt/tr, 0,d,0);
                glTranslatef(0,0,tr);
                    // Tekstura trave
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
            // Meta sa parametrima u odnosu na koo pocetak
        float h = 1;
        draw_tarrget(h, rand_rot, rand_trn);
    glPopMatrix();
	// Pocetak igre
    if(on_going <= 0 && on_going == 0) {
	glColor3f(0,0,0);
	write_text("Welcome To Shoot Training", width/2-100, height*0.95);
	write_text("Click 'F' for forest mode or 'C' for city mode", width/2-160, height*0.90);
	write_text("Start Game on 'S' Button", width/2-80, height*0.85);
    }
	// Produzenje igre
    if(targets_counter >= target_limit) {
	target_limit += 5;	
	time_limit += 5;
    }
	// Kraj igre
    if(current_time > time_limit && targets_counter != 0){
	on_going = -1;
	glColor3f(0.1,0.1,0.1);
	write_text("GAME OVER", width/2-40, height*0.75);
	write_text("Cilck 'S' for New Game", width/2-100, height*0.70);
	    // Racunanje najboljeg dosadasnjeg uspeha
    	best_score = targets_counter > best_score ? targets_counter : best_score;
	sprintf(str, "Best score: %d", best_score);
	write_text(str, width/2-40, height*0.65);
	glColor3f(0,0.2,1);
	sprintf(str, "Your score: %d", targets_counter);
	write_text(str, width/2-40, height*0.60);
    }
	// Ispisuje broj pogodjenih meta
    glColor3f(0.9, 0.5, 0); 
    sprintf(str, "Targets: %d / %d", targets_counter, target_limit);
    write_text(str, 40, height-40);
	// Ispisuje broj preostalih metkova
    sprintf(str, "Bullets: %d", bullet_counter);
    write_text(str, width-140, height-40);
	// Ispisujemo upozorenje za nedostatak municije
    if(bullet_counter <= 2 && on_going > 0) {
	glColor3f(1,0,0);
	write_text(" Low Ammuniton", width/2-40, height*0.75);
	write_text("Reload on 'R' ", width/2-40, height*0.70);
    }
	// Ispisujemo preostalo vreme
    if(on_going > 0){
	    glColor3f(0,0,1);
	    sprintf(str, "Time: %ld", time_limit - current_time);
	    write_text(str, width/2, height-40);
    }

    glutPostRedisplay();
    glutSwapBuffers();
}

void initLightAndMaterial(void)
{
    GLfloat light_position[] = {-100, 100, 100, 0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        // Parametri svetlosti
    GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 1 };
    GLfloat light_diffuse[] = { 0.8, 0.7, 0.7, 1 };
    GLfloat light_specular[] = { 0.9, 0.9, 0.9, 1 };
    GLfloat ambient_coeffs[] = { 0.5, 0.5, 0.3, 1 };
    GLfloat diffuse_coeffs[] = { 1, 1, 1, 1 };
    GLfloat specular_coeffs[] = { 0.1, 0.1, 0.1, 1 };
    GLfloat shininess = 30;
        // Ukljucivanje svetlosti
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	// Osobine Materijala
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
            // Ispisivanje karakera
        for(int i = 0; text[i]; i++){
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int) text[i]); 
        }
        glMatrixMode(GL_PROJECTION);
        glLoadMatrixd(matrix); 
        glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glEnable(GL_LIGHTING);
}

void init_texture(){
	Image * image;
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    image = image_init(0, 0);

    glGenTextures(3,names);
	// Inicijalizacija teksture objekata
    image_read(image, FILENAME1);
    glBindTexture(GL_TEXTURE_2D, names[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->width, image->height, 0, 
                 GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
	// Inicijalizacija teksture podloge
    image_read(image, FILENAME2);
    glBindTexture(GL_TEXTURE_2D, names[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 
                    0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    glBindTexture(GL_TEXTURE_2D, 0);
    image_done(image);
}
