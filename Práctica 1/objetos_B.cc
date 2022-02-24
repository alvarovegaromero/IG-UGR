//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include "objetos_B.h"


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
//pag 28. si es par con un color, si no, otro color
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



//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam)
{
//8 puntos - 12 triangulos
//vertices
vertices.resize(8);
vertices[0].x=0;vertices[0].y=0;vertices[0].z=0; //0 -> (0,0,0)
vertices[1].x=tam;vertices[1].y=0;vertices[1].z=0; //1 -> (tam,0,0)
vertices[2].x=0;vertices[2].y=tam;vertices[2].z=0; //2 -> (0,tam,0)
vertices[3].x=0;vertices[3].y=0;vertices[3].z=tam; //3 -> (0,0,tam)
vertices[4].x=tam;vertices[4].y=tam;vertices[4].z=0; //4 -> (tam,tam,0)
vertices[5].x=tam;vertices[5].y=0;vertices[5].z=tam; //5 -> (tam,0, tam)
vertices[6].x=0;vertices[6].y=tam;vertices[6].z=tam; //6 -> (0,tam,tam)
vertices[7].x=tam;vertices[7].y=tam;vertices[7].z=tam; //7 -> (tam,tam,tam)

// triangulos
caras.resize(12);
caras[0]._0=3;caras[0]._1=7;caras[0]._2=5; //Cara entre 3,7 y 5 //CARA FRONTAL
caras[1]._0=3;caras[1]._1=7;caras[1]._2=6; //Cara entre 3,7,6
caras[2]._0=3;caras[2]._1=0;caras[2]._2=6; //3,0,6 //CARA IZQUIERDA
caras[3]._0=0;caras[3]._1=2;caras[3]._2=6; //0,2,6
caras[4]._0=5;caras[4]._1=1;caras[4]._2=7; //5,1,7 //CARA DERECHA
caras[5]._0=4;caras[5]._1=7;caras[5]._2=1; //4,7,1
caras[6]._0=3;caras[6]._1=0;caras[6]._2=5; //3,0,5 PARTE DE ABAJO
caras[7]._0=0;caras[7]._1=1;caras[7]._2=5; //0,5,1
caras[8]._0=6;caras[8]._1=2;caras[8]._2=7; //6,2,7 PARTE DE ARRIBA
caras[9]._0=2;caras[9]._1=7;caras[9]._2=4; //2,7,4
caras[10]._0=0;caras[10]._1=1;caras[10]._2=4; //0,1,4 PARTE TRASERA
caras[11]._0=0;caras[11]._1=4;caras[11]._2=2; //0,4,2

}


//*************************************************************************
// clase piramide
//*************************************************************************

_piramide::_piramide(float tam, float al)
{

//vertices
vertices.resize(5);
vertices[0].x=-tam;vertices[0].y=0;vertices[0].z=tam; //0
vertices[1].x=tam;vertices[1].y=0;vertices[1].z=tam; //1
vertices[2].x=tam;vertices[2].y=0;vertices[2].z=-tam; //2
vertices[3].x=-tam;vertices[3].y=0;vertices[3].z=-tam; //3
vertices[4].x=0;vertices[4].y=al;vertices[4].z=0; //Punto de altura max - 4

caras.resize(6);
//Las caras estan hechas por triángulos
//Da igual el orden de las caracteristicas
caras[0]._0=0;caras[0]._1=1;caras[0]._2=4;  //Cara entre 0,1 y 4
caras[1]._0=1;caras[1]._1=2;caras[1]._2=4; //Cara entre 1,2 y 4
caras[2]._0=2;caras[2]._1=3;caras[2]._2=4;
caras[3]._0=3;caras[3]._1=0;caras[3]._2=4;
caras[4]._0=3;caras[4]._1=1;caras[4]._2=0;
caras[5]._0=3;caras[5]._1=2;caras[5]._2=1;
}

//*************************************************************************
// clase icosahedro
//*************************************************************************

_icosahedro::_icosahedro(float tam, float al)
{
//vertices
vertices.resize(6);
vertices[0].x=0;vertices[0].y=0;vertices[0].z=0; //0 -> (0,0,0)
vertices[1].x=tam;vertices[1].y=al/2;vertices[1].z=tam; //1 -> (tam,al/2,tam)
vertices[2].x=tam;vertices[2].y=al/2;vertices[2].z=-tam; //2 -> (tam,al/2,-tam)
vertices[3].x=-tam;vertices[3].y=al/2;vertices[3].z=-tam; //3 -> (-tam,al/2,-tam)
vertices[4].x=-tam;vertices[4].y=al/2;vertices[4].z=tam; //4 -> (-tam,al/2,tam)
vertices[5].x=0;vertices[5].y=al;vertices[5].z=0; //5 -> (0,al,0)


caras.resize(8);
//Las caras estan hechas por triángulos
//OJO NO DEBE HABER CARA ENTRE 1,2,3 Y 2,3,4 (cara oculta)
caras[0]._0=0;caras[0]._1=1;caras[0]._2=2; //Cara entre 0,1 y 2
caras[1]._0=0;caras[1]._1=2;caras[1]._2=3;
caras[2]._0=0;caras[2]._1=3;caras[2]._2=4;
caras[3]._0=0;caras[3]._1=4;caras[3]._2=1;
caras[4]._0=2;caras[4]._1=3;caras[4]._2=5; //SUperiores
caras[5]._0=3;caras[5]._1=4;caras[5]._2=5;
caras[6]._0=4;caras[6]._1=1;caras[6]._2=5;
caras[7]._0=1;caras[7]._1=2;caras[7]._2=5;

}
