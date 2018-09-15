#include <GL/glut.h>

static int year = 0, day = 0;

void init(void){
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_FLAT);
}

void display(void){
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0, 1.0, 1.0);
  glPushMatrix();
    glutWireSphere(1.0, 20, 16); /* draw sun */

    glRotatef((GLfloat)year, 0.0, 1.0, 0.0);
    glTranslatef(5.0, 0.0, 0.0);
    glRotatef((GLfloat)day, 0.0, 1.0, 0.0);
    glutWireSphere(0.2, 10, 8); /* draw smaller planet */
    //draw a moon
    glRotatef((GLfloat)day, 0.0, 1.0, -0.4);
    glTranslatef(1.5, 0.0, 0.0);
    glutWireSphere(0.07, 5, 8); /* draw the moon*/

  glPopMatrix();
  glPushMatrix();
    glRotatef((GLfloat)year, 0.0, 1.0, 0.0);
    glTranslatef(20.0, 0.0, 0.0);
    glutWireSphere(0.3, 10, 8); /* draw second planet */
  glPopMatrix();
  glutSwapBuffers();
}

void idle(void){
      year = (year + 1) % 360;
      day = (day + 2) % 360;
      glutPostRedisplay();
}

void reshape(int w, int h){
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION); //choose which stack to use
  glLoadIdentity(); //load the "origin" 0,0,0
  gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 60.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0.0, 7.0, 15.0,
	    0.0, -2.0, 0.0,
	    0.0, 1.0, 0.0);
}

void keyboard(unsigned char key, int x, int y){
    switch (key) {
    case 'd':
      day = (day + 10) % 360;
      glutPostRedisplay();
      break;
    case 'D':
      day = (day - 10) % 360;
      glutPostRedisplay();
      break;
    case 'y':
      year = (year + 5) % 360;
      day = (day + 10) % 360;
      glutPostRedisplay();
      break;
    case 'Y':
      year = (year - 5) % 360;
      glutPostRedisplay();
      break;
    default:
      break;
    }
}

int main(int argc, char** argv){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100);
  glutCreateWindow(argv[0]);
  init();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutIdleFunc(idle);
  glutMainLoop();
  return 0;
			
}

