/* This program illustrates the use of the glut library for
interfacing with a Window System */

#include <time.h>
#include <stdlib.h>
#include <vector>

#include <GL/glut.h>

/* globals */

GLsizei wh = 600, ww = 500; /* initial window size */

enum Colors {
	green,
	red,
	purple,
	blue,
	yellow,
	white,
	black,
	grey
};

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
	Location backLocBotLeft;
	Location backLocBotRight;
	Location frontLocTop;
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

#define PI 3.14159265

std::vector<Car> cars;
std::vector<Truck> trucks;
std::vector<Coin> coins;

std::vector<Location> vehicleLocations;
std::vector<Location> coinLocations;

Agent agent;
//Location agentLocations[3];

bool isPaused = false;
bool framePerMove = false;
int frameTime = 100;

Color giveColor(Colors colors) 
{
	Color color;
	switch(colors)	{
	case green:
		color.r = (GLubyte)60;
		color.g = (GLubyte)179;
		color.b = (GLubyte)113;
		break;
	case red:
		color.r = (GLubyte)220;
		color.g = (GLubyte)20;
		color.b = (GLubyte)60;
		break;
	case blue:
		color.r = (GLubyte)135;
		color.g = (GLubyte)206;
		color.b = (GLubyte)250;
		break;
	case yellow:
		color.r = (GLubyte)255;
		color.g = (GLubyte)255;
		color.b = (GLubyte)0;
		break;
	case purple:
		color.r = (GLubyte)238;
		color.g = (GLubyte)130;
		color.b = (GLubyte)238;
		break;
	case white:
		color.r = (GLubyte)1;
		color.g = (GLubyte)1;
		color.b = (GLubyte)1;
		break;
	case black:
		color.r = (GLubyte)0;
		color.g = (GLubyte)0;
		color.b = (GLubyte)0;
		break;
	case grey:
		color.r = (GLubyte)112;
		color.g = (GLubyte)128;
		color.b = (GLubyte)144;
		break;
	default:
		break;

	}

	return color;
}

template<class T>
constexpr const T& clamp(const T& v, const T& lo, const T& hi)
{
	return (v < lo) ? lo : (hi < v) ? hi : v;
}

void initAgent()
{
	agent.backLocBotLeft.x = (int)ceil((GLdouble)ww / 2) - (int)ceil((GLdouble)wh / 48);
	agent.backLocBotRight.x = (int)ceil((GLdouble)ww / 2) + (int)ceil((GLdouble)wh / 48);
	agent.frontLocTop.x = (int)ceil((GLdouble)ww / 2);
	agent.backLocBotLeft.y = 0;
	agent.backLocBotRight.y = 0;
	agent.frontLocTop.y = (int)ceil((GLdouble)wh / 24);

	agent.velocity.speed = (int)ceil((GLdouble)wh / 24);
	agent.velocity.direction = up;
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

	glClearColor(1.0, 1.0, 1.0, 1);
	initAgent();
}

/* reshaping routine called whenever window is resized
or moved */

void reshapeFunc(GLsizei w, GLsizei h)
{
	coins.clear();
	cars.clear();
	trucks.clear();

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
	initAgent();
	glutPostRedisplay();
}

void keyboardFunc(unsigned char key, int x, int y)
{
	if ((key == 'Q') || (key == 'q')) 
	{
		exit(0);
	}
	else if ((key == 'R') || (key == 'r'))
	{
		//TODO
	}
}

void reverseAgent()
{
	if(agent.frontLocTop.y >= wh)
	{
		agent.backLocBotLeft.y = wh;
		agent.backLocBotRight.y = wh;
		agent.frontLocTop.y = wh - (int)ceil((GLdouble)wh / 24);
		agent.velocity.direction = down;
	}

	else if (agent.frontLocTop.y <= 0)
	{
		agent.backLocBotLeft.y = 0;
		agent.backLocBotRight.y = 0;
		agent.frontLocTop.y = (int)ceil((GLdouble)wh / 24);
		agent.velocity.direction = up;
	}
}

void agentMoveUP()
{
	agent.backLocBotLeft.y += agent.velocity.speed;
	agent.backLocBotRight.y += agent.velocity.speed;
	agent.frontLocTop.y += agent.velocity.speed;
	//printf("OpenGL version supported %d\n", agent.frontLocTop.y);


	if(agent.frontLocTop.y >= wh)
	{
		printf("OpenGL version supported %d\n", agent.frontLocTop.y);
		reverseAgent();
	}

	glutPostRedisplay();
}

void agentMoveDOWN()
{
	agent.backLocBotLeft.y -= agent.velocity.speed;
	agent.backLocBotRight.y -= agent.velocity.speed;
	agent.frontLocTop.y -= agent.velocity.speed;

	if (agent.frontLocTop.y <= 0)
	{
		reverseAgent();
	}

	glutPostRedisplay();
}

void agentMoveLEFT()
{
	agent.velocity.direction = left;
	agent.backLocBotLeft.x -= agent.velocity.speed;
	agent.backLocBotRight.x -= agent.velocity.speed;
	agent.frontLocTop.x -= agent.velocity.speed;

	if (agent.backLocBotLeft.x <= 0)
	{
		agent.backLocBotLeft.x += agent.velocity.speed;
		agent.backLocBotRight.x += agent.velocity.speed;
		agent.frontLocTop.x += agent.velocity.speed;
	}

	glutPostRedisplay();
}

void agentMoveRIGHT()
{
	agent.velocity.direction = right;
	agent.backLocBotLeft.x += agent.velocity.speed;
	agent.backLocBotRight.x += agent.velocity.speed;
	agent.frontLocTop.x += agent.velocity.speed;

	if (agent.backLocBotRight.x >= ww)
	{
		agent.backLocBotLeft.x -= agent.velocity.speed;
		agent.backLocBotRight.x -= agent.velocity.speed;
		agent.frontLocTop.x -= agent.velocity.speed;
	}

	glutPostRedisplay();
}

// Callback routine for non-ASCII key entry.
void specialKeyInputFunc(int key, int x, int y)
{
	if (isPaused) return;

	if (key == GLUT_KEY_UP)
	{
		if (agent.velocity.direction == down)
		{
			//TODO		
		}
		agentMoveUP();
	}
	if (key == GLUT_KEY_DOWN)
	{
		if (agent.velocity.direction == up) 
		{
			//TODO		
		}
		agentMoveDOWN();
	}
	if (key == GLUT_KEY_LEFT)
	{
		agentMoveLEFT();
	}
	if (key == GLUT_KEY_RIGHT)
	{
		agentMoveRIGHT();
	}

	glutPostRedisplay();
}

void fillCoinLocations(int topRoady)
{
	Location coinLocation;
	int allWidth;
	allWidth = rand() % ww;
	coinLocation.x = clamp(allWidth, (int)ceil((GLdouble)ww / 50), ww- (int)ceil((GLdouble)ww / 50));

	coinLocation.y = (topRoady + topRoady + (int)ceil((GLdouble)wh / 24)) / 2;
	coinLocations.push_back(coinLocation);

}


void fillVehicleLocations(int topRoady, int vehicleRotation)
{
	Location vehicleLocation;
	if(vehicleRotation % 2 == 0)
		vehicleLocation.x = 0;
	else
		vehicleLocation.x = ww;

	vehicleLocation.y = (topRoady + topRoady + (int)ceil((GLdouble)wh / 24)) / 2;
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
			fillCoinLocations(topRoady);
			fillVehicleLocations(topRoady, i);
			topRoady += (int)ceil((GLdouble)wh / 24);


			for (int j = 0; j < totalNumberOfTape; j++)
			{
				Color color = giveColor(black);
				glColor3ub(color.r, color.g, color.b);
				glBegin(GL_LINES);
					glVertex2f(leftTapeofRoadx, topRoady);
					glVertex2f(rightTapeofRoadx, topRoady);
				glEnd();
				leftTapeofRoadx = rightTapeofRoadx + ww / 100;
				rightTapeofRoadx = leftTapeofRoadx + ww / 50;
			}
		}
		fillVehicleLocations(topRoady, 3);
		fillCoinLocations(topRoady);
	}
	else
	{
		for (int i = 0; i < 2; i++)
		{
			int leftTapeofRoadx = 0;
			int rightTapeofRoadx = ww / 50;
			fillCoinLocations(topRoady);
			fillVehicleLocations(topRoady, i);
			topRoady += (int)ceil((GLdouble)wh / 24);


			for (int j = 0; j < totalNumberOfTape; j++)
			{
				Color color = giveColor(black);
				glColor3ub(color.r, color.g, color.b);
				glBegin(GL_LINES);
					glVertex2f(leftTapeofRoadx, topRoady);
					glVertex2f(rightTapeofRoadx, topRoady);
				glEnd();
				leftTapeofRoadx = rightTapeofRoadx + ww / 100;
				rightTapeofRoadx = leftTapeofRoadx + ww / 50;
			}
		}
		fillVehicleLocations(topRoady, 2);
		fillCoinLocations(topRoady);
	}
}

void drawSideWalks(int bottomSidewalky, int topSidewalky)
{	
	Color color = giveColor(grey);
	glColor3ub(color.r, color.g, color.b);
	glBegin(GL_POLYGON);
		glVertex2f(0, bottomSidewalky);
		glVertex2f(0, topSidewalky);
		glVertex2f(ww, topSidewalky);
		glVertex2f(ww, bottomSidewalky);
	glEnd();
}

void drawMap() 
{
	coinLocations.clear();
	vehicleLocations.clear();
	int bottomSidewalky, topSidewalky, totalRoadLengthy;
	totalRoadLengthy = wh - (int)ceil((GLdouble )wh / 4);
	bottomSidewalky = 0;
	topSidewalky = (int)ceil((GLdouble)wh / 24);
	for (int i = 1; i <= 6; i++)
	{
		drawSideWalks(bottomSidewalky, topSidewalky);
		drawRoads(i, topSidewalky);

		if (i==1 || i == 3 || i == 5)
		{
			bottomSidewalky = topSidewalky + (int)ceil((GLdouble)(4*totalRoadLengthy) / (GLdouble)18);
			topSidewalky = bottomSidewalky + (int)ceil((GLdouble)wh / (GLdouble)24);
		}
		else
		{
			bottomSidewalky = topSidewalky + (int)ceil(((GLdouble)3 * (GLdouble)totalRoadLengthy) / (GLdouble)18);
			topSidewalky = bottomSidewalky + (int)floor((GLdouble)wh / (GLdouble)24);
		}

	}
}

void drawAgent()
{
	Color color = giveColor(black);
	glColor3ub(color.r, color.g, color.b);
	glBegin(GL_POLYGON);
		glVertex2f(agent.backLocBotLeft.x, agent.backLocBotLeft.y);
		glVertex2f(agent.backLocBotRight.x, agent.backLocBotRight.y);
		glVertex2f(agent.frontLocTop.x, agent.frontLocTop.y);
	glEnd();
}

void drawCars()
{
	for (int i = 0; i < cars.size(); i++)
	{
		glColor3ub(cars[i].color.r, cars[i].color.g, cars[i].color.b);
		glBegin(GL_POLYGON);
			glVertex2f(cars[i].backLocBot.x, cars[i].backLocBot.y);
			glVertex2f(cars[i].backLocTop.x, cars[i].backLocTop.y);
			glVertex2f(cars[i].frontLocTop.x, cars[i].frontLocTop.y);
			glVertex2f(cars[i].frontLocBot.x, cars[i].frontLocBot.y);
		glEnd();

	}
}

void drawTrucks()
{
	for (int i = 0; i < trucks.size(); i++)
	{
		glColor3ub(trucks[i].color.r, trucks[i].color.g, trucks[i].color.b);
		glBegin(GL_POLYGON);
			glVertex2f(trucks[i].backLocBot.x, trucks[i].backLocBot.y);
			glVertex2f(trucks[i].backLocTop.x, trucks[i].backLocTop.y);
			glVertex2f(trucks[i].frontLocTop.x, trucks[i].frontLocTop.y);
			glVertex2f(trucks[i].frontLocBot.x, trucks[i].frontLocBot.y);
		glEnd();
	}
}

void drawCoins()
{
	float angle;
	Color color = giveColor(yellow);
	for (int i = 0; i < coins.size(); i++)
	{
		glColor3ub(color.r, color.g, color.b);
		glBegin(GL_POLYGON);
		for (int j = 0; j < 30; ++j)
		{
			angle = 2 * PI * j / 30;
			glVertex2f((float)coins[i].center.x + cos(angle) * (int)ceil((GLdouble)ww / 100),
				(float)coins[i].center.y + sin(angle) * (int)ceil((GLdouble)ww / 100));
		}

		glEnd();
	}
}


/* display callback required by GLUT 3.0 */

void displayFunc(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	drawMap();
	drawAgent();
	drawCars();
	drawTrucks();
	drawCoins();
	glFlush();
	glutSwapBuffers();
}

void generateVehicle(int id) 
{
	if (isPaused && !framePerMove)
	{		
		return;
	}

	Color randomColor = giveColor(static_cast<Colors>(rand() % 4)); // It gives random color to vehicle

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
			vehicleFrontBot.x = (int)ceil((GLdouble)wh / 48);
			vehicleFrontTop.x = (int)ceil((GLdouble)wh / 48);
			car.velocity.direction = right;
		}
		else
		{
			vehicleBackBot.x = randomLocation.x;
			vehicleBackTop.x = randomLocation.x;
			vehicleFrontBot.x = ww - (int)ceil((GLdouble)wh / 48);
			vehicleFrontTop.x = ww - (int)ceil((GLdouble)wh / 48);
			car.velocity.direction = left;
		}

		vehicleBackBot.y = randomLocation.y - (int)ceil((GLdouble)wh / 96);
		
		vehicleBackTop.y = randomLocation.y + (int)ceil((GLdouble)wh / 96);
		
		vehicleFrontBot.y = randomLocation.y - (int)ceil((GLdouble)wh / 96);
		
		vehicleFrontTop.y = randomLocation.y + (int)ceil((GLdouble)wh / 96);
		

		car.backLocBot = vehicleBackBot;
		car.backLocTop = vehicleBackTop;
		car.frontLocBot = vehicleFrontBot;
		car.frontLocTop = vehicleFrontTop;
		car.velocity.speed = (int)ceil((GLdouble)ww / 200);
	
		car.color = randomColor;
		cars.push_back(car);
	}

	if (truckOrCar == 2) // Truck
	{
		if (randomLocation.x == 0)
		{
			vehicleBackBot.x = randomLocation.x;
			vehicleBackTop.x = randomLocation.x;
			vehicleFrontBot.x = (int)ceil((GLdouble)wh / 12);
			vehicleFrontTop.x = (int)ceil((GLdouble)wh / 12);
			truck.velocity.direction = right;
		}
		else
		{
			vehicleBackBot.x = randomLocation.x;
			vehicleBackTop.x = randomLocation.x;
			vehicleFrontBot.x = ww - (int)ceil((GLdouble)wh / 12);
			vehicleFrontTop.x = ww - (int)ceil((GLdouble)wh / 12); //height * 4 = width
			truck.velocity.direction = left;
		}

		vehicleBackBot.y = randomLocation.y - (int)ceil((GLdouble)wh / 96);

		vehicleBackTop.y = randomLocation.y + (int)ceil((GLdouble)wh / 96);

		vehicleFrontBot.y = randomLocation.y - (int)ceil((GLdouble)wh / 96);

		vehicleFrontTop.y = randomLocation.y + (int)ceil((GLdouble)wh / 96);
		
		truck.backLocBot = vehicleBackBot;
		truck.backLocTop = vehicleBackTop;
		truck.frontLocBot = vehicleFrontBot;
		truck.frontLocTop = vehicleFrontTop;
		truck.velocity.speed = (int)ceil((GLdouble)ww / 200);

		truck.color = randomColor;
		trucks.push_back(truck);
	}
	if(!framePerMove)
		glutTimerFunc(1000 , generateVehicle, 0);
	glutPostRedisplay();
}

void moveVehicle(int id)
{
	if (isPaused && !framePerMove)
	{
		return;
	}

	for (int i = 0; i < trucks.size(); i++)
	{
		if(trucks[i].backLocBot.x == 1 && trucks[i].velocity.direction == left) 
		{
			trucks.erase(trucks.begin() + i);
		}

		if (trucks[i].backLocBot.x == ww - 1 && trucks[i].velocity.direction == right)
		{
			trucks.erase(trucks.begin() + i);
		}

		if(trucks[i].velocity.direction == right)
		{
			trucks[i].frontLocBot.x += trucks[i].velocity.speed;
			trucks[i].frontLocTop.x += trucks[i].velocity.speed;
			trucks[i].backLocBot.x += trucks[i].velocity.speed;
			trucks[i].backLocTop.x += trucks[i].velocity.speed;
		}
		else if (trucks[i].velocity.direction == left)
		{
			trucks[i].frontLocBot.x -= trucks[i].velocity.speed;
			trucks[i].frontLocTop.x -= trucks[i].velocity.speed;
			trucks[i].backLocBot.x -= trucks[i].velocity.speed;
			trucks[i].backLocTop.x -= trucks[i].velocity.speed;
		}
	}

	for (int i = 0; i < cars.size(); i++)
	{
		if (cars[i].frontLocBot.x == 1 || cars[i].frontLocBot.x == ww - 1)
		{
			cars.erase(cars.begin() + i);
		}

		if (cars[i].velocity.direction == right)
		{
			cars[i].frontLocBot.x += cars[i].velocity.speed;
			cars[i].frontLocTop.x += cars[i].velocity.speed;
			cars[i].backLocBot.x += cars[i].velocity.speed;
			cars[i].backLocTop.x += cars[i].velocity.speed;
		}
		else if (cars[i].velocity.direction == left)
		{
			cars[i].frontLocBot.x -= cars[i].velocity.speed;
			cars[i].frontLocTop.x -= cars[i].velocity.speed;
			cars[i].backLocBot.x -= cars[i].velocity.speed;
			cars[i].backLocTop.x -= cars[i].velocity.speed;
		}
	}
	if(!framePerMove)
		glutTimerFunc(20, moveVehicle, 0);
	glutPostRedisplay();
}

void generateCoin(int id)
{
	if(isPaused && !framePerMove)
	{
		return;
	}

	if(coins.size() == 8)
	{
		coins.erase(coins.begin());
	}
	Location randomLocation;
	Coin coin;
	//printf("OpenGL version supported %d\n", coinLocations.size());
	for (int i = 0; i < coinLocations.size(); i++)
	{
		randomLocation = coinLocations[rand() % 18];
	}
	coin.center = randomLocation;
	coin.color = giveColor(yellow);
	coins.push_back(coin);
	if(!framePerMove)
		glutTimerFunc(2000, generateCoin, 2);
	glutPostRedisplay();
}

void mouseFunc(int btn, int state, int x, int y)
{
	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		if (!isPaused) isPaused = true;
		else
		{
			framePerMove = true;
			frameTime += 100;
			if(frameTime == 2000)
			{
				generateVehicle(0);
				generateVehicle(0);
				generateVehicle(0);
				generateVehicle(0);
				generateVehicle(0);
				generateVehicle(0);
				generateVehicle(0);			
				generateCoin(2);
				frameTime = 100;
			}			
			moveVehicle(1);
			
		}

	}
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		framePerMove = false;
		isPaused = !isPaused;
		if(!isPaused)
		{
			glutTimerFunc(1000, generateVehicle, 0);
			glutTimerFunc(1000, generateVehicle, 0);
			glutTimerFunc(1000, generateVehicle, 0);
			glutTimerFunc(1000, generateVehicle, 0);
			glutTimerFunc(1000, generateVehicle, 0);
			glutTimerFunc(1000, generateVehicle, 0);
			glutTimerFunc(1000, generateVehicle, 0);
			glutTimerFunc(20, moveVehicle, 1);
			glutTimerFunc(2000, generateCoin, 2);
		
		}
	}
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
	glutTimerFunc(1000, generateVehicle, 0);
	glutTimerFunc(1000, generateVehicle, 0);
	glutTimerFunc(1000, generateVehicle, 0);
	glutTimerFunc(1000, generateVehicle, 0);
	glutTimerFunc(1000, generateVehicle, 0);
	glutTimerFunc(1000, generateVehicle, 0);
	glutTimerFunc(1000, generateVehicle, 0);
	glutTimerFunc(20, moveVehicle, 1);
	glutTimerFunc(2000, generateCoin, 2);
	glutKeyboardFunc(keyboardFunc);
	glutSpecialFunc(specialKeyInputFunc);
	glutMainLoop();

}
