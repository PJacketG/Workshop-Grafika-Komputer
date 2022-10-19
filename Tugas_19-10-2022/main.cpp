#define _USE_MATH_DEFINES 

#include <cstdlib>
#include <cmath>
#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h> 


//struct titik 2D
typedef struct {
    float x,y;
} point2D_t;

//struct titik 3D
typedef struct {
    float x,y,z;
} point3D_t;

//struct faces
typedef struct {
    int NumberofVertices;
    short int pnt[32];
} face_t;

//struct objek 3D
typedef struct {
    int NumberofVertices;
    point3D_t pnt[100];
    int NumberofFaces;
    face_t fc[32];
} object3D_t;

//struct vektor 3D
typedef struct {
    float v[4];
} vector3D_t;

typedef struct{
    float m[4][4];
} matrix3D_t;

matrix3D_t createIdentity(void) 
{
    matrix3D_t u;
    int i,j;
    for(i=0;i<4;i++) 
    {
        for(j=0;j<4;j++) 
            u.m[i][j]=0.;
            u.m[i][i]=1.;
    }
    return u;
}

matrix3D_t operator* (matrix3D_t a,matrix3D_t b) 
{
    matrix3D_t c;//c=a*b
    int i,j,k;
    for(i=0;i<4;i++)
        for(j=0;j<4;j++) 
        {
            c.m[i][j]=0;
            for(k=0;k<4;k++)
                c.m[i][j]+=a.m[i][k]*b.m[k][j];
        }
    return c;
}

vector3D_t operator* (matrix3D_t a, vector3D_t b) 
{
    vector3D_t c;//c=a*b
    int i,j;
    for(i=0;i<4;i++) 
    {
        c.v[i]=0;
        for(j=0;j<4;j++) 
            c.v[i]+=a.m[i][j]*b.v[j];
    }
    return c;
}

matrix3D_t rotationXMTX(float theta) 
{
    matrix3D_t rotate=createIdentity();
    float cs=cos(theta);
    float sn=sin(theta);
    rotate.m[1][1]=cs; 
    rotate.m[1][2]=-sn;
    rotate.m[2][1]=sn; 
    rotate.m[2][2]=cs;
    return rotate;
}

matrix3D_t rotationYMTX(float theta) 
{
    matrix3D_t rotate=createIdentity();
    float cs=cos(theta);
    float sn=sin(theta);
    rotate.m[0][0]=cs; 
    rotate.m[0][2]=sn;
    rotate.m[2][0]=-sn; 
    rotate.m[2][2]=cs;
    return rotate;
}

//Implementasi Konversi vektor 3D menjadi titik 2D
point2D_t Vector2Point2D(vector3D_t vec)
{
    point2D_t pnt;
    pnt.x=vec.v[0];
    pnt.y=vec.v[1];
    return pnt;
}

//Implementasi Konversi titik 3D menjadi vektor 3D
vector3D_t Point2Vector(point3D_t pnt)
{
    vector3D_t vec;
    vec.v[0]=pnt.x;
    vec.v[1]=pnt.y;
    vec.v[2]=pnt.z;
    vec.v[3]=1.;
    return vec;
}

vector3D_t operator^ (vector3D_t a, vector3D_t b)
{
    vector3D_t c;//c=a*b
    c.v[0]=a.v[1]*b.v[2]-a.v[2]*b.v[1];
    c.v[1]=a.v[2]*b.v[0]-a.v[0]*b.v[2];
    c.v[2]=a.v[0]*b.v[1]-a.v[1]*b.v[0];
    c.v[3]=1.;
    return c;
}

vector3D_t operator-(vector3D_t v1,vector3D_t v0) 
{
    vector3D_t c;//c=v1-v0
    c.v[0]=v1.v[0]-v0.v[0];
    c.v[1]=v1.v[1]-v0.v[1];
    c.v[2]=v1.v[2]-v0.v[2];
    c.v[3]=1.;
    return c;
}

void setColor(float red,float green,float blue) 
{
    glColor3f(red, green, blue);
}

void drawPolygon(point2D_t pnt[],int n) 
{
    int i;
    glBegin(GL_LINE_LOOP);
    for(i=0;i<n;i++) 
    {
        glVertex2f(pnt[i].x, pnt[i].y);
    }
    glEnd();
}

void drawPrism1()
{
    float theta=0.5;
    matrix3D_t mat;
    matrix3D_t tilting=rotationXMTX(theta)*rotationYMTX(-theta);
    int i, j;
    vector3D_t vec[1600], vecbuff[50], vecNormal;
    point2D_t titik2D[50];

    object3D_t prisma={5,
        {{0,100,0},{100,0,0},{0,0,100},
        {-100,0,0},{0,0,-100}},
        5,
        {{3,{0,1,2}},{3,{0,2,3}},
        {3,{0,3,4}},{3,{0,4,1}},
        {4,{1,4,3,2}}}};

    mat=tilting;

    setColor(0, 0, 1);
    for(i=0;i<prisma.NumberofVertices;i++)
    {
        vec[i]=Point2Vector(prisma.pnt[i]);
        vec[i]=mat*vec[i];
    }
    for(i=0;i<prisma.NumberofFaces;i++)
    {
        for(j=0;j<prisma.fc[i].NumberofVertices;j++)
            vecbuff[j]=vec[prisma.fc[i].pnt[j]];
            
        for(j=0;j<prisma.fc[i].NumberofVertices;j++)
            titik2D[j]=Vector2Point2D(vec[prisma.fc[i].pnt[j]]);
        drawPolygon(titik2D,prisma.fc[i].NumberofVertices);
    }
}

void drawPrism2()
{
    float theta=0.5;
    matrix3D_t mat;
    matrix3D_t tilting=rotationXMTX(theta)*rotationYMTX(-theta);
    int i, j;
    vector3D_t vec[1600], vecbuff[50], NormalVector; 
    float normalzi;
    point2D_t titik2D[50];

    object3D_t prisma={5,
        {{0,100,0},{100,0,0},{0,0,100},
        {-100,0,0},{0,0,-100}},
        5,
        {{3,{0,1,2}},{3,{0,2,3}},
        {3,{0,3,4}},{3,{0,4,1}},
        {4,{1,4,3,2}}}};

    mat=tilting;

    //bagian invisible
    setColor(0,0,1);
    for(i=0;i<prisma.NumberofVertices;i++)
    {
        vec[i]=Point2Vector(prisma.pnt[i]);
        vec[i]=mat*vec[i];
    }
    for(i=0;i<prisma.NumberofFaces;i++)
    {
        for(j=0;j<prisma.fc[i].NumberofVertices;j++)
            vecbuff[j]=vec[prisma.fc[i].pnt[j]];
        NormalVector=(vecbuff[1]-vecbuff[0])^(vecbuff[2]-vecbuff[0]);
        normalzi=NormalVector.v[2];
        if(normalzi<0.0)
        {
            for(j=0;j<prisma.fc[i].NumberofVertices;j++)
                titik2D[j]=Vector2Point2D(vec[prisma.fc[i].pnt[j]]);
            drawPolygon(titik2D,prisma.fc[i].NumberofVertices);
        }
    }

    //bagian visible
    setColor(0,1,1);
    for(i=0;i<prisma.NumberofVertices;i++)
    {
        vec[i]=Point2Vector(prisma.pnt[i]);
        vec[i]=mat*vec[i];
    }
    for(i=0;i<prisma.NumberofFaces;i++)
    {
        for(j=0;j<prisma.fc[i].NumberofVertices;j++)
            vecbuff[j]=vec[prisma.fc[i].pnt[j]];
        NormalVector=(vecbuff[1]-vecbuff[0])^(vecbuff[2]-vecbuff[0]);
        normalzi=NormalVector.v[2];
        if(normalzi>0.0)
        {
            for(j=0;j<prisma.fc[i].NumberofVertices;j++)
                titik2D[j]=Vector2Point2D(vec[prisma.fc[i].pnt[j]]);
            drawPolygon(titik2D,prisma.fc[i].NumberofVertices);
        }
    }
}

void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
    
    // Place scene in frustum.
	glTranslatef(0.0, 0.0, -50.0);
	
    //uncomment ini untuk prisma biasa
    drawPrism1();
    
    //uncomment ini untuk prisma visible-invisible
    //drawPrism2();

	glutSwapBuffers();
}


// Initialization routine.
void setup(void)
{
	//glClearColor(1.0, 1.0, 1.0, 0.0);
	glClearColor(0.0, 0.0, 0.0, 0.0);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-10.0, 10.0, -10.0, 10.0, 5.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
}

// Main routine.
int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("5221600015_Ananta Miyoru Wijaya");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}


