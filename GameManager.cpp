/* This program illustrates the use of the glut library for
interfacing with a Window System */

#include <time.h>
#include <stdlib.h>

#include <GL/glut.h>

/* globals */

GLsizei wh = 600, ww = 500; /* initial window size */

enum Direction {
	left,
	right,
	up,
	down
};

typedef struct {
	GLint x;
	GLint y;
} Location;

typedef struct {
	GLubyte r;
	GLubyte g;
	GLubyte b;
} Color;

typedef struct {
	GLint speed;
	Direction direction;
} Velocity;

typedef struct {
	Location center;
	Color color;
	Velocity velocity;
} Agent;

typedef struct {
	Location center;
	Color color;
	Velocity velocity;
} Truck;

typedef struct {
	Location center;
	Color color;
	Velocity velocity;
} Car;

typedef struct {
	Location center;
	Color color;
} Coin;

/* rehaping routine called whenever window is resized
or moved */

void reshapeFunc(GLsizei w, GLsizei h)
{

	/* adjust clipping box */

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/* adjust viewport and clear */

	glViewport(0, 0, w, h);

	/* set global size for use by drawing routine */

	ww = w;
	wh = h;
}

void initFunc(void)
{

	glViewport(0, 0, ww, wh);

	/* Pick 2D clipping window to match size of screen window
	This choice avoids having to scale object coordinates
	each time window is resized */

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)ww, 0.0, (GLdouble)wh);

	/* set clear color to black and clear window */

	glClearColor(0.0, 0.0, 0.0, 1.0);


}

void keyboardFunc(unsigned char key, int x, int y)
{
	if ((key == 'Q') || (key == 'q')) 
	{
		exit(0);
	}
	if (key == GLUT_KEY_UP)
	{
		//TODO
	}
	if (key == GLUT_KEY_DOWN)
	{
		//TODO
	}
	if (key == GLUT_KEY_LEFT)
	{
		//TODO
	}
	if (key == GLUT_KEY_RIGHT)
	{
		//TODO
	}

}


void mouseFunc(int btn, int state, int x, int y)
{
	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) 
	{
		//TODO

	}
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
	{

		//TODO
	}
}

/* display callback required by GLUT 3.0 */

void displayFunc(void)
{
	int i, x, y;
	glClear(GL_COLOR_BUFFER_BIT);

	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(ww, wh);
	glutCreateWindow("RunAgentRun");
	initFunc();
	glutReshapeFunc(reshapeFunc);
	glutMouseFunc(mouseFunc);
	glutDisplayFunc(displayFunc);
	//glutTimerFunc(20, myTimeout, 0);
	glutKeyboardFunc(keyboardFunc);

	glutMainLoop();

}
