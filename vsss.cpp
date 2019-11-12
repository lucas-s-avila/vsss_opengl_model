#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

GLdouble angleView;
int anglex, angley;
GLfloat fAspect;

void drawPP(GLdouble px, GLdouble py, GLdouble pz, GLdouble x, GLdouble y, GLdouble z) {
    glBegin(GL_QUAD_STRIP);
    
    glVertex3f(px, py, pz);
    glVertex3f(px+x, py, pz);
    glVertex3f(px, py+y, pz);
    glVertex3f(px+x, py+y, pz);
    glVertex3f(px, py+y, pz+z);
    glVertex3f(px+x, py+y, pz+z);
    glVertex3f(px, py, pz+z);
    glVertex3f(px+x, py, pz+z);
    glVertex3f(px, py, pz);
    glVertex3f(px+x, py, pz);
    glVertex3f(px+x, py+y, pz+z);
    glVertex3f(px+x, py, pz+z);
    glVertex3f(px+x, py+y, pz);
    glVertex3f(px+x, py, pz);
    glVertex3f(px, py+y, pz+z);
    glVertex3f(px, py, pz);
    glVertex3f(px, py+y, pz);
    glVertex3f(px, py, pz+z);
    glVertex3f(px, py+y, pz+z);
    
    glEnd();
}

void drawCilinder(GLdouble r, GLdouble px, GLdouble py, GLdouble pz, GLdouble h) {
    glBegin(GL_QUAD_STRIP);
    for(float i = 0; i < 360; i += 2) {
        double theta = 3.1415926 * i / 180.0;
        double z = r * cosf(theta);
        double x = r * sinf(theta);
        glVertex3f(x+px, py, z+pz);
        glVertex3f(x+px, py+h, z+pz); 
    }
    glEnd();
}

void drawWheel(GLdouble x) {
    GLdouble r = 2.8;
    GLdouble theta, y, z;
    for(float i = 0;  i < 360; i += 0.5) {
        theta = 3.1415926 * i / 180.0;
        z = r * cosf(theta);
        y = r * sinf(theta);
        glPushMatrix();
        glTranslatef (0.0, -1.09, 0.0);
        glRotatef(i, -1, 0, 0);
        drawCilinder(0.2, x, y, z, 0.1);
        glTranslatef (0.0, 1.09, 0.0);
        glPopMatrix();
    }
}

void drawRim(GLdouble x) {
    for(float i = 0; i <= 360; i += (360/5)) {
        glPushMatrix();
        glTranslatef (x, -1.09, 0.0);
        glRotatef(i, -1, 0, 0);
        drawCilinder(0.2, 0, 0, 0, 2.8);
        glTranslatef (-x, 1.09, 0.0);
        glPopMatrix();
    }
}

void internalParts() {
    // Supports
    drawPP(-3.5, 1, 4, 7, 0.3, -8);
    drawPP(-3.5, -2, 4, 7, 0.3, -8);
    
    // Circuit
    glColor3f(0.5, 0.5, 0.5);
    drawPP(-2.5, 1.31, 2.5, 5, 1.5, -5);

    // Motors
    drawPP(-3.5, -1.69, 1, 2.5, 1.2, -2);
    glPushMatrix();
    glRotatef(90, 0, 0, 1);
    drawCilinder(0.2, -1.09, 3.5, 0, 0.3);
    glPopMatrix();
    drawPP(3.5, -1.69, 1, -2.5, 1.2, -2);
    glPushMatrix();
    glRotatef(90, 0, 0, 1);
    drawCilinder(0.2, -1.09, -3.8, 0, 0.3);
    glPopMatrix();

    // Battery
    drawPP(-2, -3.9, 3, 4, 1.89, -6);    
}

void sideA(GLdouble z){
    // Kick bar
    glColor3f(0, 0, 0);
    drawPP(-3.5, -3.9, z, 7, 1.9, -0.8);
}

void sideUp() {
    drawPP(-4, 3.5, 4, 8, 0.26, -8);

    glColor3f(1, 0, 0.8);
    drawPP(-4, 3.74, 0, 4, 0.26, -4);

    glColor3f(0, 0.1, 0.8);
    drawPP(0, 3.74, 0, 4, 0.26, 4);
}

void sideB(GLdouble x) {
    glColor3f(0.1, 0.1, 0.1);
    drawWheel(x);
    drawRim(x);

    glColor3f(0, 0, 0);
    if(x < 0) {
        x = -4.0;
    } else {
        x = 3.5;
    }
    
    GLdouble vx = 0.5, y = -4, z = 4, vy = 7.5, vz = -8, cy, theta, pz, py;

    cy = -1.09;

    glBegin(GL_QUAD_STRIP);
    for(float i = -55; i < 235; i+=0.25) {
        theta = 3.1415926 * i / 180.0;
        pz = 3.2 * cosf(theta);
        py = 3.2 * sinf(theta) + cy;
        glVertex3f(x, py, pz);
        glVertex3f(x+vx, py, pz);

        if(i >= -55 && i<0) {
            glVertex3f(x, py, z);
            glVertex3f(x+vx, py, pz);
            glVertex3f(x+vx,py, z);
            glVertex3f(x, py, z);
            glVertex3f(x+vx, py, z);
            glVertex3f(x+vx, py, pz);
        }

        if(i>=0 && i <45) {
            glVertex3f(x, y+vy, z);
            glVertex3f(x+vx, py, z);
            glVertex3f(x, py, z);
            glVertex3f(x+vx, y+vy, pz);
            glVertex3f(x+vx, py, pz);
            glVertex3f(x, py, pz);
            glVertex3f(x, py, z);
            glVertex3f(x+vx, py, z);
            glVertex3f(x+vx, py, pz);
            glVertex3f(x, y+vy, pz);
            glVertex3f(x+vx, y+vy, z);
        }

        if(i>=45 && i<90) {
            glVertex3f(x, y+vy, z);
            glVertex3f(x+vx, py, z);
            glVertex3f(x, py, pz);
            glVertex3f(x+vx, y+vy, pz);
            glVertex3f(x+vx, py, z);
            glVertex3f(x, y+vy, z);
            glVertex3f(x+vx, y+vy, pz);
            glVertex3f(x, y+vy, pz);
            glVertex3f(x+vx, py, pz);
        }

        if(i>=90 && i<135) {
            glVertex3f(x, y+vy, z+vz);
            glVertex3f(x+vx, py, z+vz);
            glVertex3f(x, py, pz);
            glVertex3f(x+vx, y+vy, pz);
            glVertex3f(x+vx, py, z+vz);
            glVertex3f(x, y+vy, z+vz);
            glVertex3f(x+vx, py, z+vz);
            glVertex3f(x, y+vy, pz);
            glVertex3f(x+vx, y+vy, pz);
            glVertex3f(x+vx, py, z+vz);
            glVertex3f(x+vx, y+vy, z+vz);
            glVertex3f(x, py, z+vz);
            glVertex3f(x, y+vy, z+vz);
            glVertex3f(x, py, z+vz);
            glVertex3f(x+vx, py, z+vz);
        }

        if(i>=135 && i<180) {
            glVertex3f(x+vx, y+vy, z+vz);
            glVertex3f(x, y+vy, pz);
            glVertex3f(x+vx, py, z+vz);
            glVertex3f(x, py, z+vz);
            glVertex3f(x, py, pz);
            glVertex3f(x+vx, py, pz);
            glVertex3f(x+vx, y+vy, pz);
            glVertex3f(x, py, z+vz);
            glVertex3f(x+vx, py, z+vz);
            glVertex3f(x, y+vy, z+vz);
        }

        if(i>=180 && i<235) {
            glVertex3f(x+vx, py, pz);
            glVertex3f(x+vx, py, z+vz);
            glVertex3f(x, py, z+vz);
            glVertex3f(x+vx,py, z+vz);
            glVertex3f(x+vx, py, pz);
            glVertex3f(x, py, z+vz);
        }
    }
    glEnd();
}

void drawRobot() {
    internalParts();
    
    sideA(4);
    sideA(-3.2);
    
    sideUp();

    sideB(-3.8);
    sideB(3.8);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0, 0, 0);
    
    glPushMatrix();
    glRotatef((GLfloat) anglex, 1, 0, 0);
    glRotatef((GLfloat) angley, 0, 1, 0);
    drawRobot();
    glPopMatrix();

    glutSwapBuffers();
}

void init() {
    glClearColor(0.3, 0.2, 0.4, 1);
    
    GLfloat ambLight[4] = {0.2, 0.2, 0.2, 1.0};
    GLfloat difLight[4] = {0.7, 0.7, 0.7, 1.0};
    GLfloat espLight[4] = {1.0, 1.0, 1.0, 1.0};
    GLfloat posLight[4] = {-20, 10, 0, 1};

    GLfloat espec[4] = {1, 1, 1, 1};
    GLint especMat = 60;

    glShadeModel(GL_SMOOTH);

    glMaterialfv(GL_FRONT, GL_SPECULAR, espec);
    glMateriali(GL_FRONT, GL_SHININESS, especMat);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambLight);

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambLight); 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, difLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, espLight);
	glLightfv(GL_LIGHT0, GL_POSITION, posLight);

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);  
	glEnable(GL_LIGHT0);
    glEnable(GL_MULTISAMPLE_ARB);
	glEnable(GL_DEPTH_TEST);
    anglex = angley = 0;
    angleView = 45;
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    fAspect = (GLfloat)w/(GLfloat)h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(angleView, fAspect, 0.4, 100.0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 20, 0.0, 0.0, 0.0, 0,1,0);
}

void callbackKey(unsigned char key, int x, int y) {
    switch (key) {
   
    case 'W':
    case 'w':
        anglex = (anglex + 10) % 360;
        break;
    case 'A':
    case 'a':
        angley = (angley - 10) % 360;
        break;
    case 'S':
    case 's':
        anglex = (anglex - 10) % 360;
        break;
    case 'D':
    case 'd':
        angley = (angley + 10) % 360;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

void callbackMouse(int button, int state, int x, int y) {
    if(button == GLUT_LEFT_BUTTON) {
        if(state == GLUT_DOWN) {
            if(angleView > 10) {
                angleView -= 5;
            }
        }
    }
    if(button == GLUT_RIGHT_BUTTON) {
        if(state == GLUT_DOWN) {
            if(angleView < 150) {
                angleView += 5;
            }
        }
    }
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(angleView, fAspect, 0.4, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 20, 0.0, 0.0, 0.0, 0,1,0);
    glutPostRedisplay();
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowSize(650, 600);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("VSSS robot");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(callbackKey);
    glutMouseFunc(callbackMouse);
    init();
    glutMainLoop();

    return 0;
}