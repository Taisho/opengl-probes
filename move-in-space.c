#include <GL/glut.h>
#include <stdio.h>
//DONE move the "camera" with the mouse
//TODO move through space with keyboard
int windowW = 0;
int windowH = 0;
int mouseXPathLength = 0;
int mouseXPathStart = 0;
int mouseXCurrentPath = 0;
GLfloat camXAngle = 0.0;

int mouseYPathLength = 0;
int mouseYPathStart = 0;
int mouseYCurrentPath = 0;
GLfloat camYAngle = 0.0;

GLfloat z_offset = 0.0;
GLfloat x_offset = 0;
GLfloat y_offset = 0;
GLfloat eye_x = 0;
GLfloat eye_y = 0;
GLfloat eye_z = -100;

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

    gluLookAt(x_offset, y_offset, z_offset,
	    eye_x, eye_y, eye_z, 
	    0.0, 1.0, .0);
  eye_x = eye_y = 0;
  x_offset = y_offset = z_offset = 0;//"absorbing" XYZ offsets
  glPushMatrix();
  glTranslatef(0.0, 0.0, -5.0);
  glutSolidSphere(1.0, 40, 32);
  glPopMatrix();
  
  glPushMatrix();
  glTranslatef(0.0, 0.0, 15.0);
  glutSolidSphere(1.0, 40, 32);
  glPopMatrix();

  glFlush();
}
	  
void reshape(int w, int h){
  windowW = w;
  windowH = h;
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity(); //load the "origin" 0,0,0
  gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 0.1, 60.0);
  /* if (w <= h) */
  /*   glOrtho(-1.5, 1.5, -1.5*(GLfloat)h/(GLfloat)w, */
  /* 	    1.5*(GLfloat)h/(GLfloat)w, -10.0, 10.0); */
  /* else */
  /*   glOrtho(-1.5*(GLfloat)w/(GLfloat)h, */
  /* 	    1.5*(GLfloat)w/(GLfloat)h, -1.5, 1.5, -10.0, 10.0); */
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void mouseMove(int x, int y){

  mouseXCurrentPath = (mouseXPathStart - x) + mouseXPathLength;
  camXAngle = ((GLfloat)mouseXCurrentPath / (windowW ));
  camXAngle *= 40;

  mouseYCurrentPath = (mouseYPathStart - y) + mouseYPathLength;
  camYAngle = ((GLfloat)mouseYCurrentPath / (windowH ));
  camYAngle *= 40;

  glutPostRedisplay();
  //printf("Y:%4.2f X:%4.2f", camYAngle, camXAngle);
  //fflush(stdout);

}

void mouseClicked( int button, int state, int x, int y){
  if( button == GLUT_LEFT_BUTTON){
      if( state == GLUT_DOWN){
	mouseXPathStart = x;
	mouseYPathStart = y;
	//printf("Y:%f X:%f", camYAngle, camXAngle);
      }
      if( state == GLUT_UP){
	mouseXPathLength = mouseXCurrentPath;
	mouseYPathLength = mouseYCurrentPath;
	if(mouseXPathLength > 4500)
	   mouseXPathLength -= 4500;
	else if (mouseXPathLength < -0 )
	    mouseXPathLength = 4500 - mouseXPathLength;
	printf("X Angle:%4.2f  X Path: %d\n", camXAngle, mouseXPathLength);
	//printf("hello");
      }
  }
}

void keyboard(unsigned char key, int x, int y){
  switch(key){
    case 't':
    case 'T':
      eye_z = -100;
          glutPostRedisplay();
	  printf("eye_z: %3.4f\n", eye_z);
      break;
    case 'g':
    case 'G':
      eye_z = 100;
          glutPostRedisplay();
	  printf("eye_z: %3.4f\n", eye_z);
      break;
  case 'w':
  case 'W':
    //FIXME moving in only one axis is not sufficient. We need to
    //find a way to move at a point in the middle of the screen.
    if(camXAngle < 45.0)
      z_offset += 0.3;
    else if(camXAngle < 135.0)
      x_offset += 0.3;
    else if(camXAngle < 225.0)
      z_offset -= 0.3;
    else if(camXAngle < 315.0)
      x_offset -= 0.3;
    else if(camXAngle < 360.0)
      z_offset += 0.3;
    glutPostRedisplay();
    printf("Z offset: %4.3f\n", z_offset);
    break;
  case 's':
  case 'S':
    z_offset -= 0.3;
    glutPostRedisplay();
    printf("Z offset: %4.3f\n", z_offset);
    break;
  default:
    break;
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
  glutKeyboardFunc(keyboard);
  glutMainLoop();
  return 0;
}
