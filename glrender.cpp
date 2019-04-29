#include <GL/freeglut.h>
#include <cmath>
#include <iostream>

#include "FiguresRainPolygon.hpp"
#include "FiguresRainScene.hpp"

#include <vector>

// Global var, not nice,
FiguresRainScene* sceneToRender;

// Will be provided in separate source,
// not nice, but allows to create separate debug main without GL
FiguresRainScene* getScene();

static void animateScene()
{
    sceneToRender->doTimeStep();
    glutPostRedisplay();
}

static void cleanupScene()
{
    delete sceneToRender;
    // TODO: cleanup GL and GLUT resources as well
}

static void reshapeScene(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)width / height, 1.0f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

static void renderFigure(const VisPolygon* polygon) {
    vector<VisPoint> vertices = polygon->getVertices();

    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    for (int ii = 0; ii < vertices.size(); ++ii)   {
        glVertex2d(vertices[ii].getX(), vertices[ii].getY());
    }
    glEnd();
}

static void renderScene()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0f, 0.0f, 100.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    for(unsigned int i = 0; i < sceneToRender->getNumberOfFigures(); ++i)
        renderFigure(sceneToRender->getFigure(i));

    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Rain of figures problem");

    sceneToRender = getScene();

    glutDisplayFunc(renderScene);
    glutReshapeFunc(reshapeScene);
    glutIdleFunc(animateScene);
    glutCloseFunc(&cleanupScene);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glutMainLoop();

    return 0;
}