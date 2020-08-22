#include "stdafx.h"
#include "subtracao.h"

Subtracao::Subtracao(IplImage* f, int limiar)
{
    id = 1;
	this->limiar=limiar;
	this->frameAtual=f;
	this->setFundo();
}

void Subtracao::setFundo()
{
    IplImage* g_gray ;
    g_gray = cvCreateImage(cvGetSize(this->frameAtual),IPL_DEPTH_8U,1);
    cvCvtColor(this->frameAtual, g_gray, CV_RGB2GRAY  );
    this->fundo = g_gray;
}

void Subtracao::setFundo(IplImage* f)
{
    IplImage* g_gray ;
    g_gray = cvCreateImage(cvGetSize(this->frameAtual),IPL_DEPTH_8U,1);
    cvCvtColor(f, g_gray, CV_RGB2GRAY  );
    this->fundo = g_gray;
}

IplImage* Subtracao::getFrameSubtraido(){
	return this->frameSubtraido;	
}

IplImage* Subtracao::getFrameAtual(){
	return this->frameAtual;	
}

void Subtracao::setFrameAtual(IplImage* f)
{
	IplImage* aux= cvCreateImage(cvGetSize(this->frameAtual),IPL_DEPTH_8U,1);;
	cvCvtColor(f, aux, CV_RGB2GRAY );
	this->frameAtual=aux;
}

void Subtracao::subtrair()
{
	//FUNCAO QUE SUBTRAI O FUNDO

	//Alocando espaço para a imagem subtraída
	this->frameSubtraido =cvCreateImage(cvGetSize(this->frameAtual), 8, 1);
	
	/* Efetua a subtração absoluta pixel a pixel do	background com o frame atual */
	cvAbsDiff(this->frameAtual, this->fundo, this->frameSubtraido);

	/* Aplicando o threshold na imagem subtraida */
	cvThreshold(this->frameSubtraido, this->frameSubtraido, this->limiar, 255,CV_THRESH_BINARY);

	/* Definição do elemento estruturante 3x3 pixels	*/
	IplConvKernel* matrix =	cvCreateStructuringElementEx(3, 3, 0, 0,CV_SHAPE_RECT, NULL);

	/* Erosão aplicada na imagem subtraída */
	cvErode(this->frameSubtraido, this->frameSubtraido, matrix, 1);

	/* Dilatação */
    cvDilate(this->frameSubtraido, this->frameSubtraido, matrix, 2);
}