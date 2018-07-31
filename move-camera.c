#include <GL/glut.h>
#include <stdio.h>
//TODO move the "camera" with the mouse
//TODO move through space with keyboard
int windowW = 0;
int windowH = 0;
int mouseXPathLength = 0;
int mouseXPathStart = 0;
int mouseCurrentPath = 0;
GLfloat camAngle = 0.0;

void init(void){
  GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat mat_shininess[] = { 50.0 };
  GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
  GLfloat white_light[] = { .3, .7, .2, 1.0 };
  GLfloat lmodel_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_SMOOTH);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
  glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);

  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);

}

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glRotatef(camAngle, 0, 1, 0);
  glTranslatef(0.0, 0.0, -5.0);

  glutSolidSphere(1.0, 20, 16);
  glFlush();
}
	  
void reshape(int w, int h){
  windowW = w;
  windowH = h;
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (w <= h)
    glOrtho(-1.5, 1.5, -1.5*(GLfloat)h/(GLfloat)w,
	    1.5*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
  else
    glOrtho(-1.5*(GLfloat)w/(GLfloat)h,
	    1.5*(GLfloat)w/(GLfloat)h, -1.5, 1.5, -10.0, 10.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void mouseMove(int x, int y){
  //cameraX = (GLfloat)x / 100;
  /* cameraY = (GLfloat)y / 1000; */
  /* printf("cameraY=%d", y); */
  
  /*  glutPostRedisplay(); */
  // if((windowW / 2) > x){//looking at left
  //if(mouseXPathStart == 0){
    
    //}
  mouseCurrentPath = (mouseXPathStart - x) + mouseXPathLength;
  camAngle = ((GLfloat)mouseCurrentPath / (windowW ));
  camAngle *= 40;
    // }
  /* else if ((windowW / 2) < x){//looking at right */
  /*   camAngle = ((GLfloat)x / (windowW / 2)); */
  /*   camAngle *= 90;  */
  /* } */
  glutPostRedisplay();
  //printf("currentPath=%d PathLength=%d\n", mouseCurrentPath, mouseXPathLength );
  //fflush(stdout);
}

void mouseClicked( int button, int state, int x, int y){
  if( button == GLUT_LEFT_BUTTON){
      if( state == GLUT_DOWN){
	mouseXPathStart = x;
      }
      if( state == GLUT_UP){
	mouseXPathLength = mouseCurrentPath;
      }
  }
}

int main(int argc, char** argv){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100);
  glutCreateWindow(argv[0]);
  init();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMotionFunc(mouseMove);
  glutMouseFunc(mouseClicked);
  glutMainLoop();
  return 0;
}
