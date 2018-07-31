#include <GL/glut.h>

static GLfloat spin = 0.0;
static GLfloat sq_top = -0.2f;
static GLfloat sq_bot = 0.2f;
static GLbyte enlarging = 1;

void init(void){
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_FLAT);
}

void display(void){
  glClear(GL_COLOR_BUFFER_BIT);
  glPushMatrix();//TODO what's this matrix ?
  glRotatef(spin, 0.0, 0.0, 1.0);
  glColor3f(1.0, 1.0, 1.0);
  glRectf(sq_top, sq_top, sq_bot, sq_bot);
  glPopMatrix();
  glutSwapBuffers();
}

void spinDisplay(void){
  if(sq_bot < 0.2)
    enlarging = 1;
  if(sq_bot > 0.8)
    enlarging = 0;

  if(enlarging == 1){
  sq_top = sq_top - 0.002f;
  sq_bot = sq_bot + 0.002f;
  }
  else{
    sq_top = sq_top + 0.002f;
    sq_bot = sq_bot - 0.002f;
  }

  spin = spin + 0.5;
  if (spin > 360.0)
    spin = spin - 360.0;
  glutPostRedisplay();
}

void reshape(int w, int h){
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);//values here set viewport.
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void mouse(int button, int state, int x, int y){
switch (button) {
 case GLUT_LEFT_BUTTON:
   if (state == GLUT_DOWN)
     glutIdleFunc(spinDisplay);
   break;
 case GLUT_MIDDLE_BUTTON:
   if (state == GLUT_DOWN)
     glutIdleFunc(NULL);
   break;
 default:
   break;
 }
}
/*
* Request double buffer display mode.
* Register mouse input callback functions
*/
int main(int argc, char** argv){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(250, 250);
  glutInitWindowPosition(100, 100);
  glutCreateWindow(argv[0]);
  init();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);
  glutMainLoop();
  return 0;
}
