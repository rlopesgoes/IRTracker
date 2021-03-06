#include "stdafx.h"
#include "calibracao.h"

Calibracao::Calibracao(int resolucaoAltura, int resolucaoLargura, int cameraAltura, int cameraLargura)
{
	this->cameraAltura = cameraAltura;
	this->cameraLargura = cameraLargura;
	this->resolucaoAltura=resolucaoAltura;
	this->resolucaoLargura=resolucaoLargura;
	this->x=0;
	this->y=0;
	this->x1=0;
	this->y1=0;
	this->x2=0;
	this->y2=0;
	this->x3=0;
	this->x4=0;
}

Calibracao::~Calibracao(){
	cvReleaseImage(&(this->imagem));
}

//G�nio, rs
void Calibracao::converterPerspectiva(int x, int y){
	float h1,h2,w1,w2,dx,dy = 0.0;
	int aux_x,aux_y = 0;

	aux_x = x-this->x1; //calcula o offset de x
	aux_y = y-this->y1; //calcula o offset de y

	h1 = this->cameraAltura;
	w1 = this->cameraLargura;
	h2 = this->y3 - this->y1;
	w2 = this->x2 - this->x1;

	dx= w1/w2;
	dy= h1/h2;

	aux_x = aux_x*dx;
	aux_y = aux_y*dy;
	//Primeiro converte a perspectiva da resolu��o do local calibrado para a resolu��o da c�mera

	h2 = this->resolucaoAltura;
	w2 = this->resolucaoLargura;

	dx= w2/w1;
	dy= h2/h1;

	aux_x = aux_x*dx;
	aux_y = aux_y*dy;
	//Agora converte a perspectiva da resolu��o da c�mera para a resolu��o do monitor

	this->x = aux_x;
	this->y = aux_y;
}

void Calibracao::calibrar(int x, int y, int c)
{
	if(c==1)
	{
		this->x1=x;
		this->y1=y;
	}
	if(c==2)
	{
		this->x2=x;
		this->y2=y;
	}
	if(c==3)
	{
		this->x3=x;
		this->y3=y;
	}
	if(c==4)
	{
		this->x4=x;
		this->y4=y;
	}
}
bool Calibracao::validarArea(int x, int y){
	//1
	if(x<(this->x1)&&(y<(this->y1))){ return false; }
	if(x<(this->x1)){ return false; }
	if(y<(this->y1)){ return false; }
	//2
	if(x>(this->x2)&&(y<(this->y2))){ return false; }
	if(x>(this->x2)){ return false; }
	if(y<(this->y2)){ return false; }
	//3
	if(x<(this->x3)&&(y>(this->y3))){ return false; }
	if(x<(this->x3)){ return false; }
	if(y>(this->y3)){ return false; }
	//4
	if(x>(this->x4)&&(y>(this->y4))){ return false; }
	if(x>(this->x4)){ return false; }
	if(y>(this->y4)){ return false; }
	return true;
}

void Calibracao::mostrar(){
	printf("Calibracao Atual:");
	printf("p(1)={%d,%d}\n", x1, y1);
	printf("p(2)={%d,%d}\n", x2, y2);
	printf("p(3)={%d,%d}\n", x3, y3);
	printf("p(4)={%d,%d}\n", x4, y4);
}

void Calibracao::setImagem(IplImage* img){
	this->imagem=img;
}

IplImage* Calibracao::getImagem(){
	return this->imagem;
}

void Calibracao::pintarAreaDeNaoInteresse(){
	for (int i=0 ; i < this->imagem->height; i++) { 
		for (int j=0 ; j < this->imagem->width; j++)  { 
			if (!this->validarArea(j,i))
			{ 
				cvSet2D(this->imagem, i, j,  cvScalar(255,255,255,0));
			} 
		} 
	}
}

void Calibracao::pintarVertices(){
	cvRectangle(this->imagem, cvPoint((this->x1)-1,(this->y1)-1), cvPoint((this->x1)+1,(this->y1)+1), cvScalar(255,0,0), 2);
	cvRectangle(this->imagem, cvPoint(this->x2-1,this->y2-1), cvPoint(this->x2+1,this->y2+1), cvScalar(255,0,0), 2);
	cvRectangle(this->imagem, cvPoint(this->x3-1,this->y3-1), cvPoint(this->x3+1,this->y3+1), cvScalar(255,0,0), 2);
	cvRectangle(this->imagem, cvPoint(this->x4-1,this->y4-1), cvPoint(this->x4+1,this->y4+1), cvScalar(255,0,0), 2);
}

int Calibracao::getX1(){
	return this->x1;
}

int Calibracao::getY1(){
	return this->y1;
}

int Calibracao::getX(){
	return this->x;
}

int Calibracao::getY(){
	return this->y;
}

int Calibracao::getX2(){
	return this->x2;
}

int Calibracao::getY2(){
	return this->y2;
}

int Calibracao::getX3(){
	return this->x3;
}

int Calibracao::getY3(){
	return this->y3;
}

int Calibracao::getX4(){
	return this->x4;
}

int Calibracao::getY4(){
	return this->y4;
}

void Calibracao::setX1(int x){
	this->x1=x;
}

void Calibracao::setX2(int x){
	this->x2=x;
}

void Calibracao::setX3(int x){
	this->x3=x;
}

void Calibracao::setX4(int x){
	this->x4=x;
}

void Calibracao::setY1(int y){
	this->y1=y;
}

void Calibracao::setY2(int y){
	this->y2=y;
}

void Calibracao::setY3(int y){
	this->y3=y;
}

void Calibracao::setY4(int y){
	this->y4=y;
}

void Calibracao::bresenham(int x1, int y1, int x2, int y2){        
       int slope;
       int dx, dy, incE, incNE, d, x, y;
       // Onde inverte a linha x1 > x2       
       if (x1 > x2){
           bresenham(x2, y2, x1, y1);
            return;
       }        
       dx = x2 - x1;
       dy = y2 - y1;
   
       if (dy < 0){            
           slope = -1;
           dy = -dy;
       }
       else{            
          slope = 1;
       }
       // Constante de Bresenham
       incE = 2 * dy;
       incNE = 2 * dy - 2 * dx;
       d = 2 * dy - dx;
       y = y1;       
       for (x = x1; x <= x2; x++){
		   cvSet2D(imagem, y, x, cvScalar(255,0,255,0));
           if (d <= 0){
             d += incE;
           }
           else{
             d += incNE;
             y += slope;
           }
       }
 }