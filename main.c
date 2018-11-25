#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

/* Konstanta pi. */
const static float pi = 3.141592653589793;

/* Dimenzije prozora */
static int window_width, window_height;

/* Deklaracije callback funkcija. */
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display(void);

int main(int argc, char **argv)
{
    /* Inicijalizuje se GLUT. */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    /* Kreira se prozor. */
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Stoni hokej");

    /* Registruju se callback funkcije. */
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);

    /* Obavlja se OpenGL inicijalizacija. */
    glClearColor(0.8, 0.8, 0.2, 1);
    glEnable(GL_DEPTH_TEST);
    glLineWidth(2);

    /* Program ulazi u glavnu petlju. */
    glutMainLoop();

    return 0;
}

static void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        /* Zavrsava se program. */
        exit(0);
        break;
    }
}

static void on_reshape(int width, int height)
{
    /* Pamte se sirina i visina prozora. */
    window_width = width;
    window_height = height;

    /* Podesava se viewport. */
    glViewport(0, 0, width, height);

    /* Podesava se projekcija. */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float) width / height, 1, 25);
}

void draw_table_base()
{
    glScalef(1, 0.3, 1);
    glColor3f(0.7, 0.7, 0.7);
    glutSolidCube(0.5);
}

void draw_table(float height, float radius_top, float radius_bottom)
{
#define SEGMENTS 16


    /* postavljamo osnovnu boju objekta na belu */
    glColor3f(0.7, 0.7, 0.7);

    int u = 0;
    float angle = 0;

    /* crtamo zarubljenu kupu */
    glBegin(GL_TRIANGLE_STRIP);
        for (u = 0; u <= SEGMENTS; u++) {
            angle = u * (2 * pi / SEGMENTS);

            /* definisemo normalu povrsi */
            glNormal3f(cos(angle), 0, sin(angle));

            /* definisemo koordinate tacaka u prostoru */
            glVertex3f(radius_bottom * cos(angle), 0, radius_bottom * sin(angle));

            glVertex3f(radius_top * cos(angle), -height, radius_top * sin(angle));

        }
    glEnd();

    draw_table_base();

#undef SEGMENTS
}

static void on_display(void)
{
    /* Brise se prethodni sadrzaj prozora. */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    /* Podesava se tacka pogleda. */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
            1, 2, 3,
            0, 0, 0,
            0, 1, 0
        );

    /* Crtaju se noge stola */
    glPushMatrix();
        glTranslatef(-1, -1, -2);

        glPushMatrix();
            glTranslatef(1, 0, 0);
            draw_table(1, 0.1, 0.2);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(1, 0, -2);
            draw_table(1, 0.1, 0.2);
        glPopMatrix();

        glPushMatrix();
            draw_table(1, 0.1, 0.2);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0, 0, -2);
            draw_table(1, 0.1, 0.2);
        glPopMatrix();

    /* Crta se ploca stola */
    glColor3f(0.5, 0.5, 0.5);

    glPushMatrix();
       glTranslatef(0.5, 0.2, -1);
       glScalef(1.5, 0.2, 2.5);
       glutWireCube(1);
    glPopMatrix();

    /* Nova slika se salje na ekran. */
    glutSwapBuffers();
}
