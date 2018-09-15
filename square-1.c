#include <GL/glut.h>

void setup(){
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}
void display() {
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       glColor3f(0.3f, 0.6f, 0.0f);

       glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
       glBegin(GL_POLYGON);
       glVertex3f(0.25, 0.25, 0.0);
       glVertex3f(0.75, 0.25, 0.0);
       glVertex3f(0.75, 0.75, 0.0);
       glVertex3f(0.25, 0.75, 0.0);
       glEnd();
       glFlush();
       glRectf(-0.5f,0.9f, 0.9f, -0.9f);
       glutSwapBuffers();
 }

int main(int argc, char *argv[])
{
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
        glutInitWindowSize(320,240);
        glutCreateWindow("Hello World");

	setup();//setup done here
	
        glutDisplayFunc(display);
        glutMainLoop();
        return 0;
}
