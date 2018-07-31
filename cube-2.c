#include <GL/glut.h>

static GLfloat offset = -1.0f;

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
  gluLookAt(offset, 0.0, -5.0,
	    1.0, 1.0, 0.0,
	    0.0, 1.0, 0.0);
  //glTranslatef(0.0, 0.0, offset);//HERE 
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
  if(offset > -12.0){
    offset = offset - 0.0008f;
    glutPostRedisplay();
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
  glutIdleFunc(spinMatrix);
  glutMainLoop();
  return 0;
}
