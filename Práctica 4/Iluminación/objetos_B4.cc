
//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include "objetos_B4.h"
#include "file_ply_stl.hpp"


//*************************************************************************
// _puntos3D
//*************************************************************************

_puntos3D::_puntos3D()
{
}

//*************************************************************************
// dibujar puntos
//*************************************************************************

void _puntos3D::draw_puntos(float r, float g, float b, int grosor)
{
int i;
glPointSize(grosor);
glColor3f(r,g,b);
glBegin(GL_POINTS);
for (i=0;i<vertices.size();i++){
	glVertex3fv((GLfloat *) &vertices[i]);
	}
glEnd();
}


//*************************************************************************
// _triangulos3D
//*************************************************************************

_triangulos3D::_triangulos3D()
{
b_normales_caras=false;
b_normales_vertices=false;

ambiente_difusa=_vertex4f(0.2,0.4,0.9,1.0);  //coeficientes ambiente y difuso
especular=_vertex4f(0.5,0.5,0.5,1.0);        //coeficiente especular
brillo=50;                                   //exponente del brillo
}


//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
glLineWidth(grosor);
glColor3f(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();
}

//*************************************************************************
// dibujar en modo sólido
//*************************************************************************

void _triangulos3D::draw_solido(float r, float g, float b)
{
	int i;
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glColor3f(r,g,b);
	glBegin(GL_TRIANGLES);
	for (i=0;i<caras.size();i++){
		glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
		}
	glEnd();
}

//*************************************************************************
// dibujar en modo sólido con apariencia de ajedrez
//*************************************************************************

void _triangulos3D::draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2)
{
	int i;
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glBegin(GL_TRIANGLES);
	for (i=0;i<caras.size();i++)
	{
			if ( i %2 == 0 )
				glColor3f(r1, g1, b1);
			else
				glColor3f(r2, g2, b2);

			glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
			glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
			glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}

	glEnd();
}

void _triangulos3D::draw_iluminacion_plana( )
{
	int i;
	if (b_normales_caras==false) calcular_normales_caras(); //si no las hemos calculado ya

	//glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
	glEnable (GL_LIGHTING);
	glShadeModel(GL_FLAT);  //GL_SMOOTH
	glEnable(GL_NORMALIZE); //por si hemos escalado, tenemos que normalizar

	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,(GLfloat *) &ambiente_difusa);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *) &especular);
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,brillo);

	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glBegin(GL_TRIANGLES);
	for (i=0;i<caras.size();i++){
		glNormal3fv((GLfloat *) &normales_caras[i]);
	  glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
		}
	glEnd();

	glDisable(GL_LIGHTING);
}

void _triangulos3D::calcular_normales_caras()
{
	_vertex3f a1, a2, n;
	normales_caras.resize(caras.size());

	for(int i=0; i<caras.size(); i++){
	// obtener dos vectores en el triángulo y calcular el producto vectorial
		a1=vertices[caras[i]._1]-vertices[caras[i]._0];
  	a2=vertices[caras[i]._2]-vertices[caras[i]._0];
    n=a1.cross_product(a2);
		// modulo
		float m=sqrt(n.x*n.x+n.y*n.y+n.z*n.z);
		// normalización
    normales_caras[i]= _vertex3f(n.x/m, n.y/m, n.z/m);
	}

	b_normales_caras=true;
}

void _triangulos3D::draw_iluminacion_suave( )
{
	if(!b_normales_vertices)
		calcular_normales_vertices();

	//glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);

	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
	//glEnable(GL_NORMALIZE);

	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,(GLfloat *) &ambiente_difusa);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *) &especular);
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,brillo);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);

	for(int i =0; i < caras.size(); i++){
		glNormal3fv((GLfloat*) &normales_vertices[caras[i]._0]);
		glVertex3fv((GLfloat*) &vertices[caras[i]._0]);

		glNormal3fv((GLfloat*) &normales_vertices[caras[i]._1]);
		glVertex3fv((GLfloat*) &vertices[caras[i]._1]);

		glNormal3fv((GLfloat*) &normales_vertices[caras[i]._2]);
		glVertex3fv((GLfloat*) &vertices[caras[i]._2]);
	}

	glEnd();
	glDisable(GL_LIGHTING);
}

void _triangulos3D::calcular_normales_vertices()
{
	//Para hacer la normal a un vértice, necesitamos las normales a las caras
	if(!b_normales_caras)
		calcular_normales_caras();

	int n = vertices.size();

	normales_vertices.resize(n);

	for(int i = 0; i < n; i++) //Poner todas las normales a 0
		normales_vertices[i] = _vertex3f(0.0,0.0,0.0);

	for(int i = 0; i < caras.size(); i++)
	{
		//Procedimiento: sumarle a los 3 vértices que pertenecen a una cara,
		//el valor de la normal a esa cara. Luego normalizamos
		normales_vertices[caras[i]._0] += normales_caras[i];
		normales_vertices[caras[i]._1] += normales_caras[i];
		normales_vertices[caras[i]._2] += normales_caras[i];
	}

	for(int i = 0; i < n; i++) //Normalizar la normal a cada vertice
		normales_vertices[i].normalize(); //función de vector<_vertex3f> para normalizar

		b_normales_vertices=true;
}

void _esfera::calcular_normales_vertices() //Práctica 4
{
	normales_vertices.resize(vertices.size());

	for(int i = 0; i < vertices.size(); i++) //Poner todas las normales a 0
	{
		normales_vertices[i] = _vertex3f(0.0,0.0,0.0);
		normales_vertices[i]._0 = vertices[i]._0;
		normales_vertices[i]._1 = vertices[i]._1;
		normales_vertices[i]._2 = vertices[i]._2;
		normales_vertices[i].normalize(); //función de vector<_vertex3f> para normalizar
	}

	b_normales_vertices=true;
}

//*************************************************************************
// dibujar con distintos modos
//*************************************************************************

void _triangulos3D::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
switch (modo){
	case POINTS:draw_puntos(r1, g1, b1, grosor);break;
	case EDGES:draw_aristas(r1, g1, b1, grosor);break;
	case SOLID_CHESS:draw_solido_ajedrez(r1, g1, b1, r2, g2, b2);break;
	case SOLID:draw_solido(r1, g1, b1);break;
	case SOLID_ILUMINATED_FLAT:draw_iluminacion_plana();break;
	case SOLID_ILUMINATED_GOURAUD:draw_iluminacion_suave();break;
	}
}

//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam)
{
	vertices.resize(8);
	vertices[0].x=0;vertices[0].y=0;vertices[0].z=tam; //0 (0,0,tam)
	vertices[1].x=tam;vertices[1].y=0;vertices[1].z=tam; //1 (tam, 0, tam)
	vertices[2].x=tam;vertices[2].y=tam;vertices[2].z=tam; //2 (tam,tam,tam)
	vertices[3].x=0;vertices[3].y=tam;vertices[3].z=tam; //3 (0,tam,tam)
	vertices[4].x=0;vertices[4].y=0;vertices[4].z=0; //4 (0,0,0)
	vertices[5].x=tam;vertices[5].y=0;vertices[5].z=0; //5 (tam,0,0)
	vertices[6].x=tam;vertices[6].y=tam;vertices[6].z=0; //6 (tam,tam,0)
	vertices[7].x=0;vertices[7].y=tam;vertices[7].z=0; //7 (0,tam,0)

	caras.resize(12);
	caras[0]._0=0;caras[0]._1=1;caras[0]._2=3;
	caras[1]._0=3;caras[1]._1=1;caras[1]._2=2;
	caras[2]._0=1;caras[2]._1=5;caras[2]._2=2;
	caras[3]._0=5;caras[3]._1=6;caras[3]._2=2;
	caras[4]._0=5;caras[4]._1=4;caras[4]._2=6;
	caras[5]._0=4;caras[5]._1=7;caras[5]._2=6;
	caras[6]._0=0;caras[6]._1=7;caras[6]._2=4;
	caras[7]._0=0;caras[7]._1=3;caras[7]._2=7;
	caras[8]._0=3;caras[8]._1=2;caras[8]._2=7;
	caras[9]._0=2;caras[9]._1=6;caras[9]._2=7;
	caras[10]._0=4;caras[10]._1=1;caras[10]._2=0; //0-1-4
	caras[11]._0=1;caras[11]._1=4;caras[11]._2=5; //1-5-4
}


//*************************************************************************
// clase piramide
//*************************************************************************

_piramide::_piramide(float tam, float al)
{
	//vertices
	vertices.resize(5);
	vertices[0].x=-tam;vertices[0].y=0;vertices[0].z=tam;
	vertices[1].x=tam;vertices[1].y=0;vertices[1].z=tam;
	vertices[2].x=tam;vertices[2].y=0;vertices[2].z=-tam;
	vertices[3].x=-tam;vertices[3].y=0;vertices[3].z=-tam;
	vertices[4].x=0;vertices[4].y=al;vertices[4].z=0;

	caras.resize(6);
	caras[0]._0=0;caras[0]._1=1;caras[0]._2=4;
	caras[1]._0=1;caras[1]._1=2;caras[1]._2=4;
	caras[2]._0=2;caras[2]._1=3;caras[2]._2=4;
	caras[3]._0=3;caras[3]._1=0;caras[3]._2=4;
	caras[4]._0=3;caras[4]._1=1;caras[4]._2=0;
	caras[5]._0=3;caras[5]._1=2;caras[5]._2=1;
}

//*************************************************************************
// clase objeto ply
//*************************************************************************


_objeto_ply::_objeto_ply()
{
   // leer lista de coordenadas de vértices y lista de indices de vértices -- POR HACER

}



int _objeto_ply::parametros(char *archivo)
{
int n_ver,n_car;

vector<float> ver_ply ; //vector para ver. una va por casilla. por tanto, se almacena xyz de forma consecutiva. antes lo haciamos que cada casilla tenia .x, .y y .z
vector<int>   car_ply ;

_file_ply::read(archivo, ver_ply, car_ply ); //se usara como argv[1]. guarda ver y caras.

n_ver=ver_ply.size()/3;
n_car=car_ply.size()/3;

printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);

vertices.resize(n_ver);

for(int i = 0; i < n_ver ; i++ )
{
	vertices[i].x = ver_ply[3*i];
	vertices[i].y = ver_ply[3*i+1];
	vertices[i].z = ver_ply[3*i+2];
}

caras.resize(n_car);
for(int i = 0; i < n_car ; i++ )
{
	caras[i]._0 = car_ply[3*i];
	caras[i]._1 = car_ply[3*i+1];
	caras[i]._2 = car_ply[3*i+2];
}

return(0);
}


//************************************************************************
// objeto por revolucion
//************************************************************************

_rotacion::_rotacion()
{
 //
}


void _rotacion::parametros(vector<_vertex3f> perfil, int num, int tipo) //giramos perfil el num veces
{
	//Si es cilindro = 0 y cualquier figura, cono es tipo = 1, esfera = 2

int i,j;
_vertex3f vertice_aux; //auxiliar, tiene comp x,y,z
_vertex3i cara_aux;
int num_aux; //num de vertices en un perfil
float radio, altura;

if(tipo==2) //SI es esfera, calcular su radio
	radio = sqrt((perfil[0].x*perfil[0].x) + (perfil[0].y*perfil[0].y));
else if(tipo == 0 || tipo == 1)
{
	radio = abs(perfil[0].x);
	altura = abs(perfil[1].y); //altura solo lo usamos para el cono
}

// tratamiento de los vértices - colocar cada punto ya rotado

num_aux=perfil.size();

//No rotar punto de arriba si estamos en cono -> num_aux a 1

if(tipo==1) // Cono. Perfil tiene dos puntos.
	num_aux=1;


vertices.resize(num_aux*num+2); //tam vertices: num lados * num vertices iniciales, +2 por punto central inf y sup
for (j=0;j<num;j++)  //PAra cada "perfil"
  {for (i=0;i<num_aux;i++) //Para cada punto del perfil
     {
			 //Para cada punto, aplicar la matriz de rotacion
      vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
      vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
      vertice_aux.y=perfil[i].y; //la y no se mueve
      vertices[i+j*num_aux]=vertice_aux;
     }
  }

// tratamiento de las caras

caras.resize(2*(num_aux-1)*num + 2*num); //num de caras es el num de vertices * 2 - 1. -1 porque lineas es num punto -1 siempre
																	//num_aux - 1 = lineas en un perfil
																	//*2 porque por cada linea, hay 2 caras (cada linea se usa 2 veces)
																	 //num porque es el numero de perfiles que hay
																	 //+2*num para la cara sup e inferior


int c = 0; //índice dentro del vector de caras

if(tipo == 0 || tipo == 2) //Cono solo tiene tapa superior e inferior, NO caras laterales
{
	for(j = 0 ; j < num - 1 ; j+=1) //Número de perfiles. -1 porque ult cara se procesa independiente
	{
		for(i = 0 ; i < (num_aux-1) ; i++)//último vertice no, porque al hacer i+1 nos saldriamos
		{
			//j*num_aux es para cambiar entre el perfil e i que es el núm del vertice

			//				1
			//			/ |
			//		/   |
			//	0-----2

			caras[c]._0=i + j*num_aux;
			caras[c]._2=i+num_aux+1 + j*num_aux; //seg punto del sig perfil. num vertices del primero, pues el sig
			caras[c]._1=num_aux+i + j*num_aux	; //primer punto del sig perfil

			// 1----2
			// |   /
			// | /
			// 0

			c++;
			caras[c]._0=i + j*num_aux;
			caras[c]._2=i+1 + j*num_aux;
			caras[c]._1=i+num_aux+1 + j*num_aux;

			c++;
		}
	}

	//Ultimo perfil con primer perfil - última cara lateral
	int verts_ult_perfil = j*num_aux;

	for(i = 0 ; i < (num_aux-1) ; i++) //Núm de líneas de un perfil)
	{
		//El perfil "primer" es el último, y el "segundo" es el inicial
		caras[c]._0=i + verts_ult_perfil;
		caras[c]._2=i+1;
		caras[c]._1=i;

		c++;
		caras[c]._0=i + verts_ult_perfil;
		caras[c]._2=i+1 + verts_ult_perfil;
		caras[c]._1=i+1;

		c++;
	}

} //Fin procesamiento de caras laterales


// tapa inferior
if (fabs(perfil[0].x)>0.0) //que no coincida punto con eje
{
	vertice_aux.x = 0.0;

	if(tipo==0) vertice_aux.y = perfil[0].y;
	else if(tipo == 1) vertice_aux.y = 0.0;
	else if(tipo == 2) vertice_aux.y = -radio;

	vertice_aux.z = 0.0;

	vertices[num*num_aux] = vertice_aux;

	for(i = 0 ; i < num ; i++) //num-1 -> casi todas de primeras y cara de ult con primero de forma indepe
															 //num -> módulo para proceso conjunto
		{
			caras[c]._0=num*num_aux; //el del centro
			caras[c]._2=i*num_aux;
			caras[c]._1=((i+1)%num)*num_aux;
			//SI no hicieramos módulo sería (i+1)*num_aux
			c++;
		}
}


 // tapa superior
 if (fabs(perfil[num_aux-1].x)>0.0)
  {
			vertice_aux.x = 0.0;

			if(tipo==0) vertice_aux.y = perfil[num_aux-1].y;
			else if(tipo == 1) vertice_aux.y = altura;
			else if(tipo == 2) vertice_aux.y = radio;

			vertice_aux.z = 0.0;

			vertices[num*num_aux+1] = vertice_aux;

			if(tipo == 0 || tipo == 2)
			{
				for(i = 0 ; i < num-1 ; i++) //num-1 -> casi todas de primeras y cara de ult con primero de forma indepe
				{
					caras[c]._0=num*num_aux+1; //el del centro
					caras[c]._1=i*num_aux+(num_aux-1);
					caras[c]._2=(i+1)*num_aux+(num_aux-1);

					c++;
				}


				//última cara
				caras[c]._0=num*num_aux+1; //el del centro
				caras[c]._1=i*num_aux+(num_aux-1); //el ult
				caras[c]._2=(num_aux-1); //el primero
				c++;
			}

			else if (tipo == 1) //tipo =1 --> Cono
			{
				for(j = 0 ; j < num ; j++)
				{
					caras[c]._0=num*num_aux+1; //el del centro
					caras[c]._1=j*num_aux;
					caras[c]._2=num_aux*((j+1)%num); //Procesamos la última cara grx a %

					c++;
				}
			}

  } //Fin tapa superior
} //Fin método

_esfera::_esfera(float radio, int n, int m)
{
	vector <_vertex3f> perfil;
	_vertex3f vert_aux;

	for(int i = 1 ; i < n ; i++)
	{
		vert_aux.x = radio*cos(M_PI*i/n-M_PI/2.0);
		vert_aux.y = radio*sin(M_PI*i/n-M_PI/2.0);
		vert_aux.z = 0.0;
		perfil.push_back(vert_aux);
	}

	parametros(perfil, m, 2);
	calcular_normales_vertices();
}

_cono::_cono(float radio, float altura, int m)
{
	vector <_vertex3f> perfil;
	_vertex3f vert_aux;

	vert_aux.x = radio;
	vert_aux.y = 0.0;
	vert_aux.z = 0.0;
	perfil.push_back(vert_aux);

	vert_aux.x = 0.0;
	vert_aux.y = altura;
	vert_aux.z = 0.0;
	perfil.push_back(vert_aux);


	parametros(perfil, m, 1);
}

_cilindro::_cilindro(float radio, float altura, int m)
{
	vector <_vertex3f> perfil;
	_vertex3f vert_aux;

	vert_aux.x = radio;
	vert_aux.y = -altura/2.0;
	vert_aux.z = 0.0;
	perfil.push_back(vert_aux);

	vert_aux.x = radio;
	vert_aux.y = altura/2.0;
	vert_aux.z = 0.0;
	perfil.push_back(vert_aux);


	parametros(perfil, m, 0);
}

/////////////////////////////////////////////////////////
// Práctica 3
/////////////////////////////////////////////////////////

_paralelepipedo::_paralelepipedo(float ancho, float alto, float largo)
{
	vertices.resize(8);
	vertices[0].x=0;vertices[0].y=0;vertices[0].z=largo; //0 (0,0,largo)
	vertices[1].x=ancho;vertices[1].y=0;vertices[1].z=largo; //1 (ancho, 0, largo)
	vertices[2].x=ancho;vertices[2].y=alto;vertices[2].z=largo; //2 (ancho,alto,largo)
	vertices[3].x=0;vertices[3].y=alto;vertices[3].z=largo; //3 (0,alto,largo)
	vertices[4].x=0;vertices[4].y=0;vertices[4].z=0; //4 (0,0,0)
	vertices[5].x=ancho;vertices[5].y=0;vertices[5].z=0; //5 (ancho,0,0)
	vertices[6].x=ancho;vertices[6].y=alto;vertices[6].z=0; //6 (ancho,alto,0)
	vertices[7].x=0;vertices[7].y=alto;vertices[7].z=0; //7 (0,alto,0)

	caras.resize(12);
	caras[0]._0=0;caras[0]._1=1;caras[0]._2=3;
	caras[1]._0=3;caras[1]._1=1;caras[1]._2=2;
	caras[2]._0=1;caras[2]._1=5;caras[2]._2=2;
	caras[3]._0=5;caras[3]._1=6;caras[3]._2=2;
	caras[4]._0=5;caras[4]._1=4;caras[4]._2=6;
	caras[5]._0=4;caras[5]._1=7;caras[5]._2=6;
	caras[6]._0=0;caras[6]._1=7;caras[6]._2=4;
	caras[7]._0=0;caras[7]._1=3;caras[7]._2=7;
	caras[8]._0=3;caras[8]._1=2;caras[8]._2=7;
	caras[9]._0=2;caras[9]._1=6;caras[9]._2=7;
	caras[10]._0=0;caras[10]._1=4;caras[10]._2=1; //0-1-4
	caras[11]._0=4;caras[11]._1=5;caras[11]._2=1; //1-5-4

	ambiente_difusa=_vertex4f(0.7,0.4,0,1.0);  //coeficientes ambiente y difuso
	especular=_vertex4f(0,0.6,1,1.0);        //coeficiente especular
	brillo=100;
}

_pata::_pata()
{
//
}

void _pata::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
	pata.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
}


_base::_base()
{
//
}


void _base::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
	//Nota, la y del cilindro, empieza desde -altura/2 a altura y Esfera tiene el punto más abajo en -radio
	//Pondremos la base, sobre el plano X-Y


	//Nota, hemos modificado los parametros del draw
	glPushMatrix();

	glScalef(1, 0.25, 1);
	glTranslatef(0,0.5,0);
	//Queremos que afecte a la pieza superior e inferior, que tienen el mismo escalado

	inferior.draw(modo, 0.8, 0, 1, r2, g2, b2, grosor);

		glPushMatrix();
		glTranslatef(0,2,0);
		superior.draw(modo, 0.8, 0, 1, r2, g2, b2, grosor);
		glPopMatrix();

	glPopMatrix();


	glPushMatrix();
	glScalef(0.75, 0.25, 0.75);
	glTranslatef(0,1.5,0);
	central.draw(modo, 0.3, 0, 1, 0,0,0, grosor);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.5, 0.25, 0.5);
	glTranslatef(0,3.5,0);
	superior_conector.draw(modo, 0.3, 0, 1, 0,0,0, grosor);
	glPopMatrix();
}

_arma::_arma()
{
	//
}

void _arma::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
	glPushMatrix();

	glScalef(1,0.25,0.25);
	glRotatef(90,0,0,1);
	glTranslatef(0.5,0,0);

	canon_abajo.draw(modo, 0.8, 0, 1, r2, g2, b2, grosor);

		glPushMatrix();
		glTranslatef(2,0,0);
		canon_arriba.draw(modo, 0.8, 0, 1, r2, g2, b2, grosor);
		glPopMatrix();

	glPopMatrix();

	glPushMatrix();
	glScalef(0.1,0.75,0.25);
	glTranslatef(4.25,0,-0.125*4);
	une_canones.draw(modo, 0.5, 0.1, 1, r2, g2, b2, grosor);
	glPopMatrix();
}

_cabina::_cabina()
{
	//
}

void _cabina::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{

	glPushMatrix();
	//glScalef(1,1,1);
	glRotatef(90,1,0,0);
	glTranslatef(0,0,-0.5);
	cabina.draw(modo, r1, g1, b1, r2, g2, b2, grosor); //siempre por aristas
	glPopMatrix();

	glPushMatrix();
	glScalef(1,0.5,1);
	glTranslatef(-0.25,0.1,-0.25);
	//Ponemos color rojo
	asiento.draw(modo, 1, 0, 0, r2, g2, b2, grosor);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.1, 0.5, 0.5);
	glTranslatef(1.75,0.5,-0.5);
	espalda_asiento.draw(modo, 1, 0, 0, r2, g2, b2, grosor);
	glPopMatrix();

}

_escudo::_escudo()
{
	//
}

void _escudo::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
	//Centrados
	glScalef(0.05,0.25,0.25);
	glTranslatef(-0.5,0,-0.5);
	escudo.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
}

_torreta::_torreta()
{
	 giro_base = 0; //No tiene límites. - 1

	 giro_cabina = 0; // 2
	 giro_cabina_min = -15;
	 giro_cabina_max = 10;

	 giro_arma = 0; //3 y 4
	 giro_arma_min = -10;
	 giro_arma_max = 10;

	 giro_arma = 0; //3 y 4
	 giro_arma_min = -10;
	 giro_arma_max = 10;

	 giro_escudo_izq = 0; //5
	 giro_escudo_izq = 0; //6
	 giro_escudo_min = -6;
	 giro_escudo_max = 6;
}


_nave::_nave()
{
	//
}
void _nave::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
	glPushMatrix();
	glScalef(0.1,1,1);

		glPushMatrix();
		//glRotatef(90,0,0,1);
		glTranslatef(-4.5,0,-0.5);
		ala_izq.draw(modo, 0,0,0, 0.6, 0.6, 0.6, grosor);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(3.5,0,-0.5);
		ala_dcha.draw(modo, 0,0,0, 0.6, 0.6, 0.6, grosor);
		glPopMatrix();

	glPopMatrix();

	glPushMatrix();
	glScalef(0.75,0.25,0.25);
	glRotatef(90,0,0,1);
	glTranslatef(2,0,0);
	une_alas.draw(modo, 0.6,0.6,0.6, 0, 0, 0, grosor);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.5,0.5,0.5);
	glTranslatef(0,1,0);
	cabina.draw(modo, 0,0,1, 0, 0, 0, grosor);
	glPopMatrix();
}

void _torreta::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
	//Nota: ponemos los colores estáticos y no que dependan de los parámetros.
	//De abajo a arriba iremos haciendo la figura final

//////////////////////////////PATAS/////////////////////////////

	glPushMatrix();
	glTranslatef(-0.5, 0, 0.5);
	pata_delantera_izq.draw(modo, 0.5, 0, 1, 0,0,0, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.5, 0, -0.5);
	pata_delantera_dcha.draw(modo, 0.5, 0, 1, 0,0,0, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5, 0, 0.5);
	pata_trasera_izq.draw(modo, 0.5, 0, 1, 0,0,0, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5, 0, -0.5);
	pata_trasera_dcha.draw(modo, 0.5, 0, 1, 0,0,0, grosor);
	glPopMatrix();

/////////////////////////BASE///////////////////////////////////

glPushMatrix(); //Giro de base y todo de arriba
glRotatef(giro_base, 0, 1, 0);

	glPushMatrix();
	glScalef(1.5,0.5,1.5);
	glTranslatef(0,0.40,0);
	base.draw(modo, 0.7, 0, 1, 0.5,0.5,0.5, grosor);
	glPopMatrix();

////////////////////////CABINA/////////////////////////////////

	glPushMatrix(); //Giro de toda la cabina y armas y eso
	glRotatef(giro_cabina, 0, 0, 1);

		glPushMatrix();
		glTranslatef(0,0.2+0.5,0);
		cabina.draw(modo, 0.5, 0, 1, 0,0,0, grosor);
		glPopMatrix();

///////////////////////ARMAS////////////////////////////////////

		glPushMatrix(); //Giro Armas
		glRotatef(giro_arma, 0, 1, 0);

			glPushMatrix();
			glScalef(0.5,0.25,0.5);

				glPushMatrix();
				glTranslatef(-1.25,4.25,1.15);
				arma_izq.draw(modo, r1, g1, b1, 1,0,0.5, grosor);
				glPopMatrix();

				glPushMatrix();
				glTranslatef(-1.25,4.25,-1.15);
				arma_dcha.draw(modo, r1, g1, b1, 1,0,0.5, grosor);
				glPopMatrix();

			glPopMatrix();

		glPopMatrix(); //FIn giro armas

/////////////////////ESCUDOS////////////////////////////////////

	glPushMatrix(); //giro escudo izq
	glRotatef(giro_escudo_izq,0,1,0);

			glPushMatrix();
			glRotatef(45,0,1,0);
			glTranslatef(-0.7,1,0.1);
			escudo_izq.draw(modo, 1, 0, 1, r2, g2, b2, grosor);
			glPopMatrix();

		glPopMatrix(); //fin giro escudo izq

		glPushMatrix(); //giro escudo dcha
		glRotatef(giro_escudo_dcha,0,1,0);

			glPushMatrix();
			glRotatef(-45,0,1,0);
			glTranslatef(-0.7,1,-0.1);
			escudo_dcha.draw(modo, 1, 0, 1, r2, g2, b2, grosor);
			glPopMatrix();

		glPopMatrix(); //fin giro escudo dcha
	glPopMatrix(); //FIN giro cabina
glPopMatrix(); //FIN giro base y lo de arriba

glPushMatrix();
glRotatef(giro_nave, 0, 1, 0);
glTranslatef(0,2.5,-5);
nave.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();
	/////////////////////////////////////////////////////////////////
}
