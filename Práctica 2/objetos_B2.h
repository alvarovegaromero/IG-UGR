//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>


const float AXIS_SIZE=5000;
typedef enum{POINTS,EDGES,SOLID_CHESS,SOLID} _modo;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:


	_puntos3D();
void 	draw_puntos(float r, float g, float b, int grosor);

vector<_vertex3f> vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D
{
public:

	_triangulos3D();
void 	draw_aristas(float r, float g, float b, int grosor);
void    draw_solido(float r, float g, float b);
void 	draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

vector<_vertex3i> caras;
};


//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D
{
public:

	_cubo(float tam=0.5);
};


//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
public:

	_piramide(float tam=0.5, float al=0.75);
};

//*************************************************************************
// clase objeto ply
//*************************************************************************

class _objeto_ply: public _triangulos3D
{
public:
   _objeto_ply();

int   parametros(char *archivo); //verdadero constructo
};

//************************************************************************
// objeto por revolución
//************************************************************************

class _rotacion: public _triangulos3D
{
public:
       _rotacion();
void  parametros(vector<_vertex3f> perfil1, int num1, int tipo); //verdadero constructor

//Si es cilindro = 0, cono es tipo =1, esfera = 2, y resto = 3

vector<_vertex3f> perfil;
int num; //num de lados del perfil
};

class _esfera: public _rotacion
{
public:
	_esfera(float radio = 1, int n = 2, int m = 20); 	//n -> num de meridianos //m para paralelos
};

class _cono: public _rotacion
{
public:
	_cono(float radio = 1, float altura = 1, int m = 10); //m eseria el num de la op parametros
	//Ojo, cono no tiene caras laterales, superior e inferior unicamente
};

class _cilindro: public _rotacion
{
public:
	_cilindro(float radio = 1, float altura = 2, int m = 15);
};
