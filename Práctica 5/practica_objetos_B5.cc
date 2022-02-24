//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <GL/glut.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include "objetos_B5.h"


using namespace std;

// tipos
typedef enum{CUBO, PIRAMIDE, OBJETO_PLY, ROTACION, ARTICULADO, CONO, CILINDRO, ESFERA} _tipo_objeto;
_tipo_objeto t_objeto=CUBO;
_modo   modo=POINTS;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Size_x,Size_y,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int Window_x=50,Window_y=50,Window_width=450,Window_high=450;
float mov=0;
float mov2=0;
float giro_luz=0;

// objetos - pruebas
_cubo cubo;
_piramide piramide(0.85,1.3);
_objeto_ply  ply;
_rotacion rotacion;
_esfera esfera(0.7,8,8);
_cono cono(0.5,1,10);
_cilindro cilindro(0.5,1,10);
///* Pruebas para la P3 --------
_nave nave;
_paralelepipedo paralelepipedo;
_pata pata;
_base base;
_arma arma;
_cabina cabina;
_escudo escudo;

_torreta torreta;
// _objeto_ply *ply1;

int estadoRaton[3], xc, yc,cambio=0;
float factor=1.0;
float Ancho, Alto;

void pick_color(int x, int y);


//**************************************************************************
//
//***************************************************************************

void clean_window()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

// formato(x_minimo,x_maximo, y_minimo, y_maximo,plano_delantero, plano_traser)
//  plano_delantero>0  plano_trasero>PlanoDelantero)
glFrustum(-Size_x,Size_x,-Size_y,Size_y,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación*ply1 de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{

glDisable(GL_LIGHTING);
glLineWidth(2);
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos
//****************************2***********************************************

void draw_objects()
{

switch (t_objeto){
	case CUBO: nave.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
	case PIRAMIDE: piramide.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
        case OBJETO_PLY: ply.draw(modo,1.0,0.6,0.0,0.0,1.0,0.3,2);break;
        case ROTACION: rotacion.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
				case ARTICULADO: torreta.draw(modo,1.0,0.0,1.0,0.0,1.0,0.0,2); break;
				case CONO: cono.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2); break;
				case CILINDRO: cilindro.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2); break;
				case ESFERA: esfera.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2); break;
	}

}

void vista_orto()
{
	//Planta
	glViewport(Ancho/2, Alto/2, Ancho/2, Alto/2);

	glMatrixMode(GL_PROJECTION); //PROJECTIONS PARA CAM. MODELVIEW PARA OBJETOS
	glLoadIdentity();
	glOrtho(-5*factor,5*factor,-5*factor,5*factor,-100,100); //parametros iniciales de cam;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	draw_axis();
	draw_objects();

 	//otra vusta = planta
	glViewport(0, Alto/2, Ancho/2, Alto/2);

	glMatrixMode(GL_PROJECTION); //PROJECTIONS PARA CAM. MODELVIEW PARA OBJETOS
	glLoadIdentity();
	glOrtho(-5*factor,5*factor,-5*factor,5*factor,-100,100); //parametros iniciales de cam;
	glRotatef(90,1,0,0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	draw_axis();
	draw_objects();


 	//otra vusta = perfil
	glViewport(0, 0, Ancho/2, Alto/2);

	glMatrixMode(GL_PROJECTION); //PROJECTIONS PARA CAM. MODELVIEW PARA OBJETOS
	glLoadIdentity();
	glOrtho(-5*factor,5*factor,-5*factor,5*factor,-100,100); //parametros iniciales de cam;
	glRotatef(90,0,1,0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	draw_axis();
	draw_objects();

//Y si quisieramos tener la camara normal arriba a la derecha copiar todo y poner glFrustrum(-Size.x, Size.x, -Size_y, Size_y, Front_plane, Front_back)
//y copiar los angulos y eso

	glViewport(Ancho/2, 0, Ancho/2, Alto/2);
	glMatrixMode(GL_PROJECTION); //PROJECTIONS PARA CAM. MODELVIEW PARA OBJETOS
	glLoadIdentity();

	glFrustum(-Size_x,Size_x,-Size_y,Size_y,Front_plane,Back_plane);

	change_projection();
	change_observer();

	draw_axis();
	draw_objects();

}

void luces (float alfa)
{
float  luz1[]={0.0, 0.0, 1.0, 1.0},
       pos1[]= {0, 10.0, 10.0, 1.0},
			 luz2[]={1.0, 0.0, 0.0, 1.0},
			 pos2[]= {0, -10.0, -10.0, 1.0};

			glLightfv (GL_LIGHT1, GL_DIFFUSE, luz1);
			glLightfv (GL_LIGHT1, GL_SPECULAR, luz1);
			glLightfv (GL_LIGHT1, GL_POSITION, pos1);

			glLightfv (GL_LIGHT2, GL_DIFFUSE, luz2);
			glLightfv (GL_LIGHT2, GL_SPECULAR, luz2);

			glPushMatrix();
			glRotatef(alfa,0,1,0);
			glLightfv (GL_LIGHT2, GL_POSITION, pos2);
			glPopMatrix();

			glDisable (GL_LIGHT0);
			glEnable (GL_LIGHT1);
			glEnable (GL_LIGHT2);
}

//**************************************************************************
//
//***************************************************************************

void draw(void)
{

//glDrawBuffer(GL_FRONT);
clean_window();

if (cambio==0)
{
	glViewport(0,0,Ancho,Alto);
	change_projection();
	change_observer();
	draw_axis();
	draw_objects();

}
else
{
	vista_orto();
}

luces(giro_luz);
//draw_axis(); //creo que si quito lo comentado, quitaria esto
//draw_objects();
glutSwapBuffers();


if(t_objeto==ARTICULADO) //aqui no se dibuja, es para la seleccion
{
	glDrawBuffer(GL_BACK);
	clean_window();
	change_observer();
	torreta.seleccion();
}

// PONER LO QUE VAYAMOS A SELECCIONAR DE UN COLOR DIFERENTE. AL SELECCIONAR SE VE EL BUFFER BACK.
// Crear dos imagenes, una que si vemos y la otra que no vemos  que es la que seleccionamos (el if)

}



//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
float Aspect_ratio;

Aspect_ratio=(float) Alto1/(float )Ancho1;
Size_y=Size_x*Aspect_ratio;
change_projection();
glViewport(0,0,Ancho1,Alto1);
Ancho = Ancho1;
Alto = Alto1;
glutPostRedisplay();
}


//**********-o*****************************************************************
// Funcion llamada cuando se aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_key(unsigned char Tecla1,int x,int y)
{
switch (toupper(Tecla1)){
	case 'Q':exit(0);
	case '1':modo=POINTS;break;
	case '2':modo=EDGES;break;
	case '3':modo=SOLID;break;
	case '4':modo=SOLID_CHESS;break;
	case '5':modo=SOLID_ILUMINATED_FLAT;break;
	case '6':modo=SOLID_ILUMINATED_GOURAUD;break;
	case '7':modo=SELECT;break;
	case '8':mov=0.25;break;
	case '9':mov=0;break;
	case '0':mov2=2;break;
	case '¡':mov2=0;break;
	  case 'P':t_objeto=PIRAMIDE;break;
	  case 'C':t_objeto=CUBO;break;
	  case 'O':t_objeto=OBJETO_PLY;break;
	  case 'R':t_objeto=ROTACION;break;
		case 'T':t_objeto=ARTICULADO;break;
		case 'S':t_objeto=ESFERA;break;
		case 'A':t_objeto=CONO;break;
		case 'Z':t_objeto=CILINDRO;break;
		case ',':cambio=0;break;
		case ';':cambio=1;break;
		case '+':factor*=0.9;break;
		case '-':factor*=1.1;break;
	}
glutPostRedisplay();
}

//***************************************************************************
// Funcion l-olamada cuando se aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_key(int Tecla1,int x,int y)
{

switch (Tecla1){
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
	case GLUT_KEY_UP:Observer_angle_x--;break;
	case GLUT_KEY_DOWN:Observer_angle_x++;break;
	case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
	case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;

	case GLUT_KEY_F1: torreta.giro_base+=5;break;
	case GLUT_KEY_F2: torreta.giro_base-=5;break;
	case GLUT_KEY_F3: torreta.giro_cabina+=2;
	if(torreta.giro_cabina > torreta.giro_cabina_max)
		torreta.giro_cabina-=2;
	break;

	case GLUT_KEY_F4: torreta.giro_cabina-=2;
	if(torreta.giro_cabina < torreta.giro_cabina_min)
		torreta.giro_cabina+=2;
	break;

	case GLUT_KEY_F5: torreta.giro_arma+=2;
	if(torreta.giro_arma > torreta.giro_arma_max)
		torreta.giro_arma-=2;
	break;

	case GLUT_KEY_F6: torreta.giro_arma-=2;
	if(torreta.giro_arma < torreta.giro_arma_min)
		torreta.giro_arma+=2;
	break;

	case GLUT_KEY_F7: torreta.giro_escudo_izq+=2;
	if(torreta.giro_escudo_izq > torreta.giro_escudo_max)
		torreta.giro_escudo_izq-=2;
	break;

	case GLUT_KEY_F8: torreta.giro_escudo_izq-=2;
	if(torreta.giro_escudo_izq < torreta.giro_escudo_min)
		torreta.giro_escudo_izq+=2;
	break;

	case GLUT_KEY_F9: torreta.giro_escudo_dcha+=2;
	if(torreta.giro_escudo_dcha > torreta.giro_escudo_max)
		torreta.giro_escudo_dcha-=2;
	break;

	case GLUT_KEY_F10: torreta.giro_escudo_dcha-=2;
	if(torreta.giro_escudo_dcha < torreta.giro_escudo_min)
		torreta.giro_escudo_dcha+=2;
	break;
	}

glutPostRedisplay();
}


void movimiento()
{
torreta.giro_nave+=mov;
if (mov!=0) glutPostRedisplay();


giro_luz+=mov2;
if(giro_luz!=0)
	draw();
}


//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{

// se inicalizan la ventana y los planos de corte
Size_x=0.5;
Size_y=0.5;
Front_plane=1;
Back_plane=1000;

// se incia la posicion del observador, en el eje z
Observer_distance=4*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;

// se indica cua*ply1l sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(1,1,1,1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
change_projection();
glViewport(0,0,Window_width,Window_high);



}

//------------------ COSAS DE LA P5

//***************************************************************************
// Funciones para manejo de eventos del ratón
//***************************************************************************

void clickRaton( int boton, int estado, int x, int y )
{
if(boton== GLUT_RIGHT_BUTTON) {
   if( estado == GLUT_DOWN) {
      estadoRaton[2] = 1;
      xc=x;
      yc=y;
     }
   else estadoRaton[2] = 1;
   }

if(boton== GLUT_LEFT_BUTTON) {
  if( estado == GLUT_DOWN) {
      estadoRaton[2] = 2;
      xc=x;
      yc=y;
      pick_color(xc, yc);
    }
  }

	if(boton==3){
		if(estado == GLUT_UP){ //Zoom con rueda del raton - NOTA: hay que hundir a rueda
			estadoRaton[0] = 3;
			factor*=0.9;
		}
		else
				estadoRaton[0] = 3;
		}

		if(boton==4){
			if(estado==GLUT_DOWN){ //Zoom con rueda del raton
				estadoRaton[0] = 4;
				factor*=1.1;
			}
			else
					estadoRaton[0] = 3;
			}

}

/*************************************************************************/

void getCamara (GLfloat *x, GLfloat *y)
{
*x=Observer_angle_x;
*y=Observer_angle_y;
}

/*************************************************************************/

void setCamara (GLfloat x, GLfloat y)
{
Observer_angle_x=x;
Observer_angle_y=y;
}



/*************************************************************************/

void RatonMovido( int x, int y )
{
float x0, y0, xn, yn;
if(estadoRaton[2]==1)
    {getCamara(&x0,&y0);
     yn=y0+(y-yc);
     xn=x0-(x-xc);
     setCamara(xn,yn);
     xc=x;
     yc=y;
     glutPostRedisplay();
    }
}

void procesar_color(unsigned char color[3])
{
int i;

for (i=0;i<torreta.piezas;i++)
   {
		 if (color[0]==torreta.color_selec[0][i])
       {
				 if (torreta.activo[i]==0)
                      {
												torreta.activo[i]=1;
                      }
                  else
                      {
												torreta.activo[i]=0;
                      }
         glutPostRedisplay();
        }
    }
 }

void pick_color(int x, int y)
{
GLint viewport[4];
unsigned char pixel[3];

glGetIntegerv(GL_VIEWPORT, viewport);
glReadBuffer(GL_BACK);
glReadPixels(x,viewport[3]-y,1,1,GL_RGB,GL_UNSIGNED_BYTE,(GLubyte *) &pixel[0]);
printf(" valor x %d, valor y %d, color %d, %d, %d \n",x,y,pixel[0],pixel[1],pixel[2]);

procesar_color(pixel);
}



///////////////////////////////////////////

//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************


int main(int argc, char *argv[] )
{




// perfil
vector<_vertex3f> perfil2; //copa
_vertex3f aux;

aux.x=0.1; aux.y=0; aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.3; aux.y=0.3; aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.7; aux.y=0.5; aux.z=0.0;
perfil2.push_back(aux);

rotacion.parametros(perfil2,6,0);


// se llama a la inicialización de glut
glutInit(&argc, argv);

// se indica las caracteristicas que se desean para la visualización con OpenGL
// Las posibilidades son:
// GLUT_SIMPLE -> memoria de imagen simple
// GLUT_DOUBLE -> memoria de imagen doble
// GLUT_INDEX -> memoria de imagen con color indizado
// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
// GLUT_DEPTH -> memoria de profundidad o z-bufer
// GLUT_STENCIL -> memoria de estarcido_rotation Rotation;
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

// posicion de la esquina inferior izquierdad de la ventana
glutInitWindowPosition(Window_x,Window_y);

// tamaño de la ventana (ancho y alto)
glutInitWindowSize(Window_width,Window_high);

// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
// al bucle de eventos)
glutCreateWindow("PRACTICA - 2");

// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw);
// asignación de la funcion llamada "change_window_size" al evento correspondiente
glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "normal_key" al evento correspondiente
glutKeyboardFunc(normal_key);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_key);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////glutIdleFunc(movimiento);
glutIdleFunc(movimiento);

// eventos ratón
glutMouseFunc( clickRaton );
glutMotionFunc( RatonMovido );

// funcion de inicialización
initialize();

// creación del objeto ply
ply.parametros(argv[1]);

//ply1 = new _objeto_ply(argv[1]);

// inicio del bucle de eventos
glutMainLoop();
return 0;
}
