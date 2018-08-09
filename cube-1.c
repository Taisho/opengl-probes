#include <GL/glut.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

static GLfloat offset = -1.0f;
static GLfloat rotate = 0.0f;

pthread_t thread;

void init(void){
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_FLAT);
}


void drawCube() {
    glLoadIdentity();
    glTranslatef(1.5f, 0.0f, -7.0f);
    glRotatef(rotate, 1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);

    glColor3f(0.0f,1.0f,0.0f); // Set The Color To Green
    glVertex3f( 1.0f, 1.0f,-1.0f); // Top Right Of The Quad (Top)
    glVertex3f(-1.0f, 1.0f,-1.0f); // Top Left Of The Quad (Top)
    glVertex3f(-1.0f, 1.0f, 1.0f); // Bottom Left Of The Quad (Top)
    glVertex3f( 1.0f, 1.0f, 1.0f); // Bottom Right Of The Quad (Top)

    glColor3f(1.0f,0.5f,0.0f); // Set The Color To Orange
    glVertex3f( 1.0f,-1.0f, 1.0f); // Top Right Of The Quad (Bottom)
    glVertex3f(-1.0f,-1.0f, 1.0f); // Top Left Of The Quad (Bottom)
    glVertex3f(-1.0f,-1.0f,-1.0f); // Bottom Left Of The Quad (Bottom)
    glVertex3f( 1.0f,-1.0f,-1.0f); // Bottom Right Of The Quad (Bottom)

    glColor3f(1.0f,0.0f,0.0f); // Set The Color To Red
    glVertex3f( 1.0f, 1.0f, 1.0f); // Top Right Of The Quad (Front)
    glVertex3f(-1.0f, 1.0f, 1.0f); // Top Left Of The Quad (Front)
    glVertex3f(-1.0f,-1.0f, 1.0f); // Bottom Left Of The Quad (Front)
    glVertex3f( 1.0f,-1.0f, 1.0f); // Bottom Right Of The Quad (Front)

    glColor3f(1.0f,1.0f,0.0f); // Set The Color To Yellow
    glVertex3f( 1.0f,-1.0f,-1.0f); // Bottom Left Of The Quad (Back)
    glVertex3f(-1.0f,-1.0f,-1.0f); // Bottom Right Of The Quad (Back)
    glVertex3f(-1.0f, 1.0f,-1.0f); // Top Right Of The Quad (Back)
    glVertex3f( 1.0f, 1.0f,-1.0f); // Top Left Of The Quad (Back)

    glColor3f(0.0f,0.0f,1.0f); // Set The Color To Blue
    glVertex3f(-1.0f, 1.0f, 1.0f); // Top Right Of The Quad (Left)
    glVertex3f(-1.0f, 1.0f,-1.0f); // Top Left Of The Quad (Left)
    glVertex3f(-1.0f,-1.0f,-1.0f); // Bottom Left Of The Quad (Left)
    glVertex3f(-1.0f,-1.0f, 1.0f); // Bottom Right Of The Quad (Left)

    glColor3f(1.0f,0.0f,1.0f); // Set The Color To Violet
    glVertex3f( 1.0f, 1.0f,-1.0f); // Top Right Of The Quad (Right)
    glVertex3f( 1.0f, 1.0f, 1.0f); // Top Left Of The Quad (Right)
    glVertex3f( 1.0f,-1.0f, 1.0f); // Bottom Left Of The Quad (Right)
    glVertex3f( 1.0f,-1.0f,-1.0f); // Bottom Right Of The Quad (Right)
    glEnd(); // Done Drawing The Quad
    //return TRUE; // Keep Going
}

void display(void){
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0, 1.0, 1.0);
  glLoadIdentity();
  /* clear the matrix */
  /* viewing transformation */
  //gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  glTranslatef(0.0, 0.0, offset);//HERE 
  glRotatef(rotate, 0.0f, 1.0f, 0.0f);
  glScalef(1.0, 2.0, 1.0);
  /* modeling transformation */
  glutWireCube(1.0);

  drawCube();
  glFlush();
}

void reshape(int w, int h){
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
  //gluPerspective(30.0, 1.0, 1.5, 20.0);
  glMatrixMode(GL_MODELVIEW);
}

void spinMatrix(void){
    offset = offset - 0.008f;
    rotate = rotate - 0.8f;
    glutPostRedisplay();
    printf("%f\n", offset);
}

void* threadProc(void* arg) {
    while(1) {
        if(offset > -12.0){
            spinMatrix();
            usleep(1000 * 30); //300 milliseconds
        }
        else {
            break;
        }
    }
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    //glutIdleFunc(spinMatrix);

    // here we create and let a thread run
    // in the background calculating next
    // frame every now and then and letting
    // glut know that it's time to redraw
    // scene
    pthread_create(&thread, NULL, threadProc, NULL);

    glutMainLoop();
    return 0;
}
