//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

//Dudas que preguntar:
//necesario cambiar de modos? O puedo poner el modo ya previamente y que sea estático?
//colores. el metodo draw puede recibir ya los colores que quiero?
//hay que enseñar el objeto y sus giros. ¿Nada sobre cambio de parámetros?



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
void  draw_solido(float r, float g, float b);
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

	_piramide(float tam=0.25, float al=0.35);
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
	_esfera(float radio = 0.5, int n = 10, int m = 25); 	//n -> num de meridianos //m para paralelos
};

class _cono: public _rotacion
{
public:
	_cono(float radio = 0.5, float altura = 1, int m=10); //m eseria el num de la op parametros
	//Ojo, cono no tiene caras laterales, superior e inferior unicamente
};

class _cilindro: public _rotacion
{
public:
	_cilindro(float radio = 0.5, float altura = 1, int m=25);
};

//*****************************************************************
// Práctica 3
//*****************************************************************

class _paralelepipedo: public _triangulos3D
{
public:
	_paralelepipedo(float ancho = 1, float alto = 1, float largo = 1);
};

class _pata: public _triangulos3D //4 objetos de esta clase.
{
public:
	_pata(); //tam 0.25 - alt = 0.35
	void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
protected:
	_piramide pata;
};

class _base: public _triangulos3D
{
public:
	_base();
	void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
protected:
	_cilindro central; //Esto no "tocaria" el suelo
	_cilindro superior;
	_cilindro inferior;
	_cilindro superior_conector;
};

class _arma: public _triangulos3D // Cada arma tendra dos cilindros unidos por un cubo
{
public:
	_arma();
	void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
protected:
	_cilindro canon_arriba;
	_cilindro canon_abajo;
	_paralelepipedo une_canones;
};



class _cabina: public _triangulos3D  //Cabina, con asiento y sus escudos a los lados
{
public:
	_cabina();
	void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
protected:
	_cilindro cabina;
	_cubo asiento;
	_paralelepipedo espalda_asiento;

};

class _escudo: public _triangulos3D
{
public:
	_escudo();
	void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
protected:
	_paralelepipedo escudo;
};


class _nave: public _triangulos3D //nave parecida a los cazas tie del imperio - ANIMACION
{
public:
	_nave();
	void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

protected:
	_paralelepipedo ala_izq;
	_paralelepipedo ala_dcha;
	_cilindro une_alas;
	_esfera cabina;
};

class _torreta: public _triangulos3D
{
public:

_torreta();
void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

	float giro_base; //No tiene límites. - 1

	float giro_cabina; // 2
	float giro_cabina_min;
	float giro_cabina_max;

	float giro_arma; // 3 y 4. Movemos las dos armas a la vez
	float giro_arma_min;
	float giro_arma_max;

	//Nota, el movimiento de los escudos es por proteger la parte de atrás de las armas
	float giro_escudo_dcha; //5
	float giro_escudo_izq; //6
	float giro_escudo_max;
	float giro_escudo_min;

	float giro_nave;
protected:
	_pata pata_delantera_izq; //delantera respecto a como nos sentariamos en la torreta
	_pata pata_delantera_dcha;
	_pata pata_trasera_izq;
	_pata pata_trasera_dcha;
	_base base;
	_cabina cabina;
	_arma arma_izq;
	_arma arma_dcha;
	_escudo escudo_izq;
	_escudo escudo_dcha;

	_nave nave; //nave para la ANIMACION
};
