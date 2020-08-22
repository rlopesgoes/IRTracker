#include "stdafx.h"
#include "deteccao.h"

Deteccao::Deteccao(IplImage* imagem)
{
	this->imagem=imagem;
	this->x=0;
	this->y=0;
}

Deteccao::~Deteccao(){
	cvReleaseImage(&(this->imagemResultado));
	cvReleaseImage(&(this->imagem));
}

void Deteccao::detectarPonto()
{
	this->imagemResultado = cvCreateImage(cvGetSize(this->imagem),IPL_DEPTH_8U,1);
	cvCvtColor(this->imagem, this->imagemResultado, CV_RGB2GRAY  ); // escalas de cinza
	cvThreshold(this->imagemResultado, this->imagemResultado, 15, 255,CV_THRESH_BINARY); // limiarizacao
	//cvFlip(this->imagemResultado, this->imagemResultado,1); //flipa a imagem do resultado verticalmente
	//cvFlip(this->imagem,this->imagem,1); //flipa a imagem real verticalmente
	//cvDilate(this->imagemResultado, this->imagemResultado, 0, 1);

	
	CvMemStorage* g_storage = cvCreateMemStorage(0);
	CvSeq* contours = 0;
	cvFindContours( this->imagemResultado, g_storage, &contours,sizeof(CvContour), CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE );

	if( contours ){
		cvDrawContours(this->imagem,contours,cvScalarAll(255),	cvScalarAll(255),100 );
	}
		
	CvSeq* tmpcontours=contours;
	CvSeq* result = 0;
	int maiorx=0;
	int maiory=0;
	double maior_reg=0.1;

    for( ; tmpcontours != 0; tmpcontours = tmpcontours->h_next )
	{
		// Approximates polygonal curves with desired precision
        result = cvApproxPoly(tmpcontours, sizeof(CvContour), g_storage, CV_POLY_APPROX_DP, cvContourPerimeter(tmpcontours)*0.02, 0);
		double reg = fabs(cvContourArea(result, CV_WHOLE_SEQ));
        //check if contour is big enough
		if( reg>maior_reg){
		    CvRect retangulo = cvBoundingRect( tmpcontours, 0 );
			CvScalar pixel= cvScalar(255,0,255,0);
			maiory=retangulo.y+(retangulo.height/2);
			maiorx=retangulo.x+(retangulo.width/2);
			maior_reg=reg;
		}
	}
	this->x=maiorx;
	this->y=maiory;

	cvReleaseMemStorage(&g_storage);
}

int Deteccao::getX(){
	return this->x;
}

int Deteccao::getY(){
	return this->y;
}

void Deteccao::setX(int x){
	this->x=x;
}

void Deteccao::setY(int y){
	this->y=y;
}

IplImage* Deteccao::getImagemResultado(){
	return this->imagemResultado;
}

IplImage* Deteccao::getImagem(){
	return this->imagem;
}