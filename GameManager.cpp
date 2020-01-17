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
	glutPostRedisplay();
}

void keyboardFunc(unsigned char key, int x, int y)
{
	if ((key == 'Q') || (key == 'q')) 
	{
		exit(0);
	}
}

// Callback routine for non-ASCII key entry.
void specialKeyInputFunc(int key, int x, int y)
{

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

	glutPostRedisplay();
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

void drawRoads(int sideWalkNumber, int topSidewalky) 
{
	int topRoady = topSidewalky;
	int totalNumberOfTape = (ww / (ww / 50 + ww / 100)) + 1;
	if(sideWalkNumber == 1 || sideWalkNumber == 3 || sideWalkNumber == 5 )
	{
		for (int i = 0; i < 3; i++) 
		{
			int leftTapeofRoadx = 0;
			int rightTapeofRoadx = ww / 50;
			topRoady += wh / 24;
			for (int j = 0; j < totalNumberOfTape; j++)
			{
				glBegin(GL_LINES);
					glVertex2f(leftTapeofRoadx, topRoady);
					glVertex2f(rightTapeofRoadx, topRoady);
				glEnd();
				leftTapeofRoadx = rightTapeofRoadx + ww / 100;
				rightTapeofRoadx = leftTapeofRoadx + ww / 50;
			}
		}
	}
	else
	{
		for (int i = 0; i < 2; i++)
		{
			int leftTapeofRoadx = 0;
			int rightTapeofRoadx = ww / 50;
			topRoady += wh / 24;
			for (int j = 0; j < totalNumberOfTape; j++)
			{
				glBegin(GL_LINES);
				glVertex2f(leftTapeofRoadx, topRoady);
				glVertex2f(rightTapeofRoadx, topRoady);
				glEnd();
				leftTapeofRoadx = rightTapeofRoadx + ww / 100;
				rightTapeofRoadx = leftTapeofRoadx + ww / 50;
			}
		}
	}
}

void drawSideWalks(int bottomSidewalky, int topSidewalky)
{	
	glBegin(GL_TRIANGLE_STRIP);
		glVertex2f(0, bottomSidewalky);
		glVertex2f(0, topSidewalky);
		glVertex2f(ww, bottomSidewalky);
		glVertex2f(ww, topSidewalky);
	glEnd();
}

void drawMap() 
{
	int bottomSidewalky, topSidewalky, totalRoadLengthy;
	totalRoadLengthy = wh - wh / 4;
	bottomSidewalky = 0;
	topSidewalky = wh / 24;
	for (int i = 1; i <= 6; i++)
	{
		drawSideWalks(bottomSidewalky, topSidewalky);
		drawRoads(i, topSidewalky);

		if (i==1 || i == 3 || i == 5)
		{
			bottomSidewalky = topSidewalky + (4*totalRoadLengthy) / 18;
			topSidewalky = bottomSidewalky + wh / 24;
		}
		else
		{
			bottomSidewalky = topSidewalky + (3*totalRoadLengthy) / 18;
			topSidewalky = bottomSidewalky + wh / 24;
		}

	}
}

/* display callback required by GLUT 3.0 */

void displayFunc(void)
{
	
	glClear(GL_COLOR_BUFFER_BIT);
	//Sidewalks
	drawMap();
	
	glFlush();
	glutSwapBuffers();
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
	glutSpecialFunc(specialKeyInputFunc);

	glutMainLoop();

}
