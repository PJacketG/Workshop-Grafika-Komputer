#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h> 

static float X = 0.0;
static float Y = 0.0;
static float Z = -15.0;

//void glutSolidCube(GLdouble size);

// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glLoadIdentity();

	// Modeling transformations.
	glTranslatef(X, Y, Z);

	// Sphere
	//glutWireSphere(5, 5, 5);
	//glutSolidSphere(5, 5, 5);

	// Cube
	//glutWireCube(5.0);
	//glutSolidCube(5.0);

	// Cone
	//glutWireCone(5, 5, 5, 5);
	//glutSolidCone(5, 5, 5, 5); 

	// Torus
	//glutWireTorus(5, 5, 5, 5); 
	//glutSolidTorus(5, 5, 5, 5); 

	// Dodecahedron
	//glutWireDodecahedron(); 
	//glutSolidDodecahedron(); 

	// Octahedron
	//glutWireOctahedron(); 
	//glutSolidOctahedron(); 

	// Tetrahedron
	//glutWireTetrahedron(); 
	//glutSolidTetrahedron();

	// Icosahedron
	//glutWireIcosahedron(); 
	//glutSolidIcosahedron(); 

	// Teapot
	//glutWireTeapot(5.0);
	//glutSolidTeapot(5.0);

	//glutWireRhombicDodecahedron();
	//glutSolidRhombicDodecahedron();
	glutWireCylinder(2.0, 5.0, 100.0, 1.0);

	glFlush();
}

// Initialization routine.
void setup(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);
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
		X+=0.5;
		glutPostRedisplay();
		break;
	case 'd':
		X -= 0.5;
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
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}

