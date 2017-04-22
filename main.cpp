//piramide

#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>

//Definimos variables
double rotate_y=0;
double rotate_x=0;
double rotate_z=0;

GLfloat X = 0.0f;
GLfloat Y = 0.0f;
GLfloat Z = 0.0f;
GLfloat scale = 1.0f;
GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

int id_menu[2];

void init (void){
    glLightfv(GL_LIGHT0,GL_POSITION,light_position); //configurando posicion de la luz
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
    glShadeModel(GL_SMOOTH);
}

void materiales(float amb1, float amb2, float amb3, float dif1, float dif2, float dif3, float esp1, float esp2, float esp3, float shi){
    // Configurando las variables del material
    GLfloat mat_ambient[] = { amb1, amb2, amb3, 1.0};
    GLfloat mat_diffuse[] = { dif1, dif2, dif3, 1.0};
    GLfloat mat_specular[] = {esp1, esp2, esp3, 1.0};
    GLfloat mat_shininess[] = {shi};

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode( GL_MODELVIEW_MATRIX );

    glLoadIdentity();

     glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
     glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
     glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
     glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glRotatef( rotate_x, 1.0, 0.0, 0.0 );
    glRotatef( rotate_y, 0.0, 1.0, 0.0 );
    glRotatef( rotate_z, 0.0, 0.0, 1.0 );
    
   //Base
glBegin(GL_QUADS);
glNormal3f(-0.4,0,-0.4);
glVertex3d(-0.4,0,-0.4);
glNormal3f(-0.4,0,0.4);
glVertex3d(-0.4,0,0.4);
glNormal3f(0.4,0,0.4);
glVertex3d(0.4,0,0.4);
glNormal3f(0.4,0,-0.4);
glVertex3d(0.4,0,-0.4);
glEnd();

//caras 1
glBegin(GL_TRIANGLES);
glNormal3f(0,0.4,0);
glVertex3d(0,0.4,0);
glNormal3f(-0.4,0,-0.4);
glVertex3d(-0.4,0,-0.4);
glNormal3f(0.4,0,-0.4);
glVertex3d(0.4,0,-0.4);
glEnd();

//cara 2
glBegin(GL_TRIANGLES);
glNormal3f(0,0.4,0);
glVertex3d(0,0.4,0);
glNormal3f(0.4,0,-0.4);
glVertex3d(0.4,0,-0.4);
glNormal3f(0.4,0,0.4);
glVertex3d(0.4,0,0.4);
glEnd();

//cara 3
glBegin(GL_TRIANGLES);
glNormal3f(0,0.4,0);
glVertex3d(0,0.4,0);
glNormal3f(-0.4,0,0.4);
glVertex3d(-0.4,0,0.4);
glNormal3f(-0.4,0,-0.4);
glVertex3d(-0.4,0,-0.4);
glEnd();
 
 //dejo una parte hueca para apreciarlo mejor
    glFlush();
    glutSwapBuffers();

}

void reshape(int w, int h){
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, -1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//teclas especiales
void specialKeys( int key, int x, int y )
{
    if (key == GLUT_KEY_RIGHT)
        rotate_y += 7;
    else if (key == GLUT_KEY_LEFT)
        rotate_y -= 7;
    else if (key == GLUT_KEY_UP)
        rotate_x += 7;
    else if (key == GLUT_KEY_DOWN)
        rotate_x -= 7;
    else if (key == GLUT_KEY_F2)
        rotate_z += 7;
    else if (key == GLUT_KEY_F2)
        rotate_z -= 7;
    glutPostRedisplay();

}

// Función para controlar teclas normales del teclado.
void keyboard(unsigned char key, int x, int y){
    id_menu[1]=key; // En el vector VF, en su campo 1, se almacenara el id de la imagen
    switch (key)
    {
    case '1': //esmeralda
        materiales(0.0215, 0.1745, 0.0215, //ambiente
                    0.07568, 0.61424, 0.07568, //difuso
                    0.633, 0.727811, 0.633, //especular
                    50.0); //shininess
        break;
    case '2': //perla
       materiales(0.25, 0.20725, 0.20725, //ambiente
                    1.0, 0.829, 0.829, //difuso
                    0.296648, 0.296648, 0.296648, //especular
                    0.088); //shininess
        break;
    case '3': //turquoise
       materiales(0.1, 0.18725, 0.1745, //ambiente
                    0.396, 0.74151, 0.69102, //difuso
                    0.297254, 0.30829, 0.306678, //especular
                    0.1); //shininess
        break;
    case '4': //gold
       materiales(0.24725, 0.1995, 0.0745, //ambiente
                    0.75164, 0.60648, 0.22648, //difuso
                    0.628281, 555802, 0.366065, //especular
                    0.4); //shininess
        break;
    case '5': //silver
       materiales(0.19225, 0.19225, 0.19225, //ambiente
                    0.50754, 0.50754, 0.50754, //difuso
                    0.508273, 0.508273, 0.508273, //especular
                    0.4); //shininess
        break;
    case '0':
        exit(0);			// exit
    }
    glutPostRedisplay();
}

void redraw( void ){
    glClear(GL_COLOR_BUFFER_BIT);
    keyboard(id_menu[1],X,Y);
	glutSwapBuffers();
}

int main(int argc, char* argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (800, 600);
    glutInitWindowPosition (100, 100);
    glutCreateWindow("Piramide controlada por teclas");
    glEnable(GL_DEPTH_TEST);
    init();
    glutDisplayFunc(redraw);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;

}
