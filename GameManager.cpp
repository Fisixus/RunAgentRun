/* This program illustrates the use of the glut library for
interfacing with a Window System */

#include <time.h>
#include <stdlib.h>
#include <vector>

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
	Location frontLocBot;
	Location frontLocTop;
	Location backLocBot;
	Location backLocTop;
	Color color;
	Velocity velocity;
} Truck;

typedef struct {
	Location frontLocBot;
	Location frontLocTop;
	Location backLocBot;
	Location backLocTop;
	Color color;
	Velocity velocity;
} Car;

typedef struct {
	Location center;
	Color color;
} Coin;

std::vector<Car> cars;
std::vector<Truck> trucks;
std::vector<Coin> coins;

std::vector<Location> vehicleLocations;

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

	glClearColor(0.0, 0.0, 0.0, 0.5);


}

/* reshaping routine called whenever window is resized
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

void fillVehicleLocations(int topRoady, int vehicleRotation)
{
	Location vehicleLocation;
	if(vehicleRotation % 2 == 0)
		vehicleLocation.x = 0;
	else
		vehicleLocation.x = ww;

	vehicleLocation.y = (topRoady + topRoady + wh / 24) / 2;
	vehicleLocations.push_back(vehicleLocation);

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
			fillVehicleLocations(topRoady, i);
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
		fillVehicleLocations(topRoady, 3);
	}
	else
	{
		for (int i = 0; i < 2; i++)
		{
			int leftTapeofRoadx = 0;
			int rightTapeofRoadx = ww / 50;
			fillVehicleLocations(topRoady, i);
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
		fillVehicleLocations(topRoady, 2);
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
	vehicleLocations.clear();
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

void drawCars()
{
	for (int i = 0; i < cars.size(); i++)
	{
		glBegin(GL_TRIANGLE_STRIP);
			glVertex2f(cars[i].backLocBot.x, cars[i].backLocBot.y);
			glVertex2f(cars[i].backLocTop.x, cars[i].backLocTop.y);
			glVertex2f(cars[i].frontLocBot.x, cars[i].frontLocBot.y);
			glVertex2f(cars[i].frontLocTop.x, cars[i].frontLocTop.y);
		glEnd();

	}
}

void drawTrucks()
{
	for (int i = 0; i < trucks.size(); i++)
	{
		glBegin(GL_TRIANGLE_STRIP);
			glVertex2f(trucks[i].backLocBot.x, trucks[i].backLocBot.y);
			glVertex2f(trucks[i].backLocTop.x, trucks[i].backLocTop.y);
			glVertex2f(trucks[i].frontLocBot.x, trucks[i].frontLocBot.y);
			glVertex2f(trucks[i].frontLocTop.x, trucks[i].frontLocTop.y);
		glEnd();

	}
}


/* display callback required by GLUT 3.0 */

void displayFunc(void)
{
	
	glClear(GL_COLOR_BUFFER_BIT);
	//Sidewalks
	drawMap();
	drawCars();
	drawTrucks();
	glFlush();
	glutSwapBuffers();
}

void generateVehicle(int id) 
{
	Location vehicleBackBot, vehicleBackTop , vehicleFrontBot, vehicleFrontTop;
	Car car;
	Truck truck;
	Location randomLocation;
	randomLocation.x = 0;
	randomLocation.y = 0;
	for (int i = 0; i < vehicleLocations.size(); i++)
	{
		randomLocation = vehicleLocations[rand() % 18];
		
	}
	int truckOrCar = rand() % 2 + 1;
	

	if(truckOrCar == 1) // Car
	{

		if(randomLocation.x == 0)
		{
			vehicleBackBot.x = randomLocation.x;
			vehicleBackTop.x = randomLocation.x;
			vehicleFrontBot.x = wh / 48;
			vehicleFrontTop.x = wh / 48;
		}
		else
		{
			vehicleBackBot.x = randomLocation.x;
			vehicleBackTop.x = randomLocation.x;
			vehicleFrontBot.x = ww - wh / 48;
			vehicleFrontTop.x = ww - wh / 48;
		}

		vehicleBackBot.y = randomLocation.y - wh / 96;
		
		vehicleBackTop.y = randomLocation.y + wh / 96;
		
		vehicleFrontBot.y = randomLocation.y - wh / 96;
		
		vehicleFrontTop.y = randomLocation.y + wh / 96;
		

		car.backLocBot = vehicleBackBot;
		car.backLocTop = vehicleBackTop;
		car.frontLocBot = vehicleFrontBot;
		car.frontLocTop = vehicleFrontTop;
		cars.push_back(car);
	}

	if (truckOrCar == 2) // Truck
	{
		if (randomLocation.x == 0)
		{
			vehicleBackBot.x = randomLocation.x;
			vehicleBackTop.x = randomLocation.x;
			vehicleFrontBot.x = wh / 12;
			vehicleFrontTop.x = wh / 12;
		}
		else
		{
			vehicleBackBot.x = randomLocation.x;
			vehicleBackTop.x = randomLocation.x;
			vehicleFrontBot.x = ww - wh / 12;
			vehicleFrontTop.x = ww - wh / 12; //height * 4 = width
		}

		vehicleBackBot.y = randomLocation.y - wh / 96;
		vehicleBackTop.y = randomLocation.y + wh / 96;
		vehicleFrontBot.y = randomLocation.y - wh / 96;
		vehicleFrontTop.y = randomLocation.y + wh / 96;
		
		truck.backLocBot = vehicleBackBot;
		truck.backLocTop = vehicleBackTop;
		truck.frontLocBot = vehicleFrontBot;
		truck.frontLocTop = vehicleFrontTop;
		trucks.push_back(truck);
	}

	glutTimerFunc(500 , generateVehicle, 0);
	glutPostRedisplay();
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
	glutTimerFunc(500, generateVehicle, 0);
	glutKeyboardFunc(keyboardFunc);
	glutSpecialFunc(specialKeyInputFunc);
	glutMainLoop();

}
