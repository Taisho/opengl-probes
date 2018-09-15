/** Compile with:
#include <GL/glu.h>
gcc -o cube-1 cube-1.c glut32.lib -lopengl32 -lglu32
 **/
//#include <GL/glut.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

static GLfloat offset = -1.0f;
static GLfloat rotate = 0.0f;
static GLuint texture[1];

SDL_Window* gWindow = NULL;
SDL_GLContext gContext;

pthread_t thread;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int InitGL(GLvoid);
//SDL_Surface *LoadBMP(char *Filename) {
//    FILE *File = NULL;
//    if(!Filename) {
//        return NULL;
//    }
//
//    File = fopen(Filename, "r");
//
//    if(File) {
//        fclose(File);
//        return auxDIBImageLoad(Filename);
//    }
//
//    return NULL;
//}

void handleKeys(unsigned char key, int x, int y) {
	if( key = 'x' ) {
		return;
	}

}

int LoadGLTextures() {
	int Status = FALSE;

	SDL_Surface *TextureImage[1];
	memset(TextureImage, 0, sizeof(void*)*1);

	if(TextureImage[0] = SDL_LoadBMP("texture.bmp")) {
		Status = TRUE;

		glGenTextures(1, &texture[0]);
		glBindTexture(GL_TEXTURE_2D, texture[0]);

		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->w, TextureImage[0]->h, 0,
				GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->pixels);

		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // Linear Filtering
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // Linear Filtering
	}

	if (TextureImage[0]) // If Texture Exists
	{
		SDL_FreeSurface(TextureImage[0]); // Free The Image Structure
	}

	return Status;
}

int init(void){
	//    glClearColor(0.0, 0.0, 0.0, 0.0);
	//    glShadeModel(GL_FLAT);

	int result = 1;
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Can't initialize SDL. ERROR: %s\n\nExitting.", SDL_GetError());
		result = 0;
	}
	else {
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		gWindow = SDL_CreateWindow("Sample", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

		if( gWindow = NULL ) {
			printf("Can't create window. ERROR: %s\n\nExitting.", SDL_GetError()); 
			result = 0;
		}
		else {
			gContext = SDL_GL_CreateContext(gWindow);
			if(gContext == NULL) {
				printf("Can't create OpenGL context. ERROR:%s\n\nExitting", SDL_GetError());
				result = 0;
			}
			else {
				if(SDL_GL_SetSwapInterval(1) < 0) {
					printf("Can't enable VSync. Video tearing may occur");
				}

				if( !InitGL() ) {
					printf("Can't initialize OpenGL. Exitting");
					result = 0;
				}
			}
		}
	}   

	return result;
}

int InitGL(GLvoid) {
	if (!LoadGLTextures()) {
		return FALSE;
	}

	glEnable(GL_TEXTURE_2D); // Enable Texture Mapping ( NEW )
	glShadeModel(GL_SMOOTH); // Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f); // Black Background
	glClearDepth(1.0f); // Depth Buffer Setup
	glEnable(GL_DEPTH_TEST); // Enables Depth Testing
	glDepthFunc(GL_LEQUAL); // The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Really Nice Perspective Calculations
	return TRUE; // Initialization Went OK
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

void drawTexture() {
	glBegin(GL_QUADS);
	// Front Face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f); // Bottom Left Of The Texture and Quad
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, 1.0f); // Bottom Right Of The Texture and Quad
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, 1.0f, 1.0f); // Top Right Of The Texture and Quad
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f); // Top Left Of The Texture and Quad
	// Back Face
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // Bottom Right Of The Texture and Quad
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f); // Top Right Of The Texture and Quad
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, 1.0f, -1.0f); // Top Left Of The Texture and Quad
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f); // Bottom Left Of The Texture and Quad
	// Top Face
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f); // Top Left Of The Texture and Quad
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f); // Bottom Left Of The Texture and Quad
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, 1.0f, 1.0f); // Bottom Right Of The Texture and Quad
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, 1.0f, -1.0f); // Top Right Of The Texture and Quad
	// Bottom Face
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // Top Right Of The Texture and Quad
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f); // Top Left Of The Texture and Quad
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, 1.0f); // Bottom Left Of The Texture and Quad
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f); // Bottom Right Of The Texture and Quad
	// Right face
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f); // Bottom Right Of The Texture and Quad
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, 1.0f, -1.0f); // Top Right Of The Texture and Quad
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, 1.0f, 1.0f); // Top Left Of The Texture and Quad
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, 1.0f); // Bottom Left Of The Texture and Quad
	// Left Face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // Bottom Left Of The Texture and Quad
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f); // Bottom Right Of The Texture and Quad
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f); // Top Right Of The Texture and Quad
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f); // Top Left Of The Texture and Quad
	glEnd();
}

void render(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glLoadIdentity();
	/* clear the matrix */
	/* viewing transformation */
	//gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glTranslatef(0.0, 0.0, offset);//HERE 
	glRotatef(rotate, 0.0f, 1.0f, 0.0f);
	glScalef(1.0, 2.0, 1.0);

	glBindTexture(GL_TEXTURE_2D, texture[0]); // Select Our Texture
	/* modeling transformation */

	drawCube();
	drawTexture();
	glFlush();
}

//void reshape(int w, int h){
//	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
//	//gluPerspective(30.0, 1.0, 1.5, 20.0);
//	glMatrixMode(GL_MODELVIEW);
//}

void spinMatrix(void){
	offset = offset - 0.008f;
	rotate = rotate - 0.8f;
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

void close_program() {
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	SDL_Quit();
}

int main(int argc, char** argv){

	if(!init()) {
		return 1;
	}

	int quit = 0;
	SDL_Event e;
	SDL_StartTextInput();	

	// here we create and let a thread run
	// in the background calculating next
	// frame every now and then and letting
	// glut know that it's time to redraw
	// scene
	pthread_create(&thread, NULL, threadProc, NULL);

	while( !quit ) {
		while(SDL_PollEvent(&e) != 0) {
			if(e.type == SDL_QUIT) {
				quit = 1;
			}
			else if(e.type == SDL_TEXTINPUT) {
				int x = 0, y = 0;
				SDL_GetMouseState(&x, &y);
				handleKeys(e.text.text[0], x, y);
			}
		}

		render();
		SDL_GL_SwapWindow(gWindow);
	}
	SDL_StopTextInput();
	close_program();

	return 0;
}
