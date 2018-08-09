#include <GL/glut.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

static GLfloat offset = -1.0f;

pthread_t thread;

void init(void){
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_FLAT);
}

void display(void){
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0, 1.0, 1.0);
  glLoadIdentity();
  /* clear the matrix */
  /* viewing transformation */
  //gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  glTranslatef(0.0, 0.0, offset);//HERE 
  glScalef(1.0, 2.0, 1.0);
  /* modeling transformation */
  glutWireCube(1.0);
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
