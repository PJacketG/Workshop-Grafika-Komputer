#include <iostream>
#include <cmath>

#include <GL/glew.h>
#include <GL/freeglut.h>

static float X = 0.0;
static float Y = 0.0;
static float Z = -15.0;

static float A = 0.0;
static float B = 0.0;
static float C = 0.0;
static float D = 0.0;

// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	// Modeling transformations.
	glTranslatef(X, Y, Z);
	glRotatef(A, B, C, D);

  float radius = 10;
  float twoPI = 2 * M_PI;

  glBegin(GL_TRIANGLE_FAN);
  glColor4f(1.0, 1.0, 1.0, 1.0);      
  glVertex2f(0.0, 0.0);
  glColor3f(0.0, 1.0, 0.0);      
  for (float i = -0.5; i <= 0.5; i += 0.001)
      glVertex2f((sin(i)*radius), (cos(i)*radius));


  glColor3f(0.0, 0.0, 1.0);      
  glVertex2f(0.0, 0.0);
  for (float i = -1.5; i <= -0.5; i += 0.001)
      glVertex2f((sin(i)*radius), (cos(i)*radius));

  glColor3f(1.0, 1.0, 0.0);      
  glVertex2f(0.0, 0.0);
  for (float i = -2.5; i <= -1.5; i += 0.001)
      glVertex2f((sin(i)*radius), (cos(i)*radius));


  glColor3f(1.0, 0.0, 1.0);      
  glVertex2f(0.0, 0.0);
  for (float i = -4.5; i <= -2.5; i += 0.001)
      glVertex2f((sin(i)*radius), (cos(i)*radius));
  

  glColor3f(1.0, 0.0, 0.0);      
  glVertex2f(0.0, 0.0);
  for (float i = 0.5; i <= 1.5; i += 0.001)
      glVertex2f((sin(i)*radius), (cos(i)*radius));

  glColor4f(0.0f, 1.0f, 1.0f, 1.0f);     
  glVertex2f(0.0, 0.0);
  for (float i = 1.5; i <= 2.5; i += 0.001)
      glVertex2f((sin(i)*radius), (cos(i)*radius));

  glEnd();
  glFlush();
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);
	glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 25.0);
	//glOrtho(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	case 'a':
		X -= 0.5;
		glutPostRedisplay();
		break;
	case 'd':
		X+=0.5;
		glutPostRedisplay();
		break;
	case 's':
		Y -= 0.5;
		glutPostRedisplay();
		break;
	case 'w':
		Y += 0.5;
		glutPostRedisplay();
		break;
	case 'q':
		Z -= 0.5;
		glutPostRedisplay();
		break;
	case 'e':
		Z += 0.5;
		glutPostRedisplay();
		break;
  
	case 'i':
		A += 0.5;
		glutPostRedisplay();
		std::cout << A << "\n";
		break;
	case 'k':
		A -= 0.5;
		glutPostRedisplay();
		std::cout << A << "\n";
		break;
	case 'o':
		B += 0.5;
		glutPostRedisplay();
		std::cout << B << "\n";
		break;
	case 'l':
		B -= 0.5;
		glutPostRedisplay();
		std::cout << B << "\n";
		break;
	case 'u':
		C += 0.5;
		glutPostRedisplay();
		std::cout << C << "\n";
		break;
	case 'j':
		C -= 0.5;
		glutPostRedisplay();
		std::cout << C << "\n";
		break;
	case 'y':
		D += 0.5;
		glutPostRedisplay();
		std::cout << D << "\n";
		break;
	case 'h':
		D -= 0.5;
		glutPostRedisplay();
		std::cout << D << "\n";
		break;
	case 'p':
		std::cout << A << "\n";
		std::cout << B << "\n";
		std::cout << C << "\n";
		std::cout << D << "\n";
    break;
  
	default:
		break;
	}
}

// Main routine.
int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("5221600015_Ananta Miyoru Wijaya.cpp");
  glClearColor(1.0, 1.0, 1.0, 0.0); 
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);

	glewExperimental = GL_TRUE;
	glewInit();

	glutMainLoop();
}

