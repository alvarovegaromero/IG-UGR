//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>

using namespace std;

const float AXIS_SIZE=5000;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:


	_puntos3D();
void 	draw_puntos(float r, float g, float b, int grosor);

vector<_vertex3f> vertices;
//vector<_vertex3f> colores;
//int color;
//Métodos para cambiar los valores de estos

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

//Crear sólido básico. Vértices y caras. Diamante por ejemplo, icosahedro

//*************************************************************************
// clase icosahedro - HECHA POR MI
//*************************************************************************

class _icosahedro: public _triangulos3D
{
public:
	_icosahedro(float tam=0.5, float al=1.5); //LA altura es la altura entre el vertice mas bajo y mas alto
};
