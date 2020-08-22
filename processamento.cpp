#include "stdafx.h"
#include "processamento.h"

void Processamento::detectarPonto()
{
	IplImage* img_bin ;
	img_bin = cvCreateImage(cvGetSize(this->Imagem),IPL_DEPTH_8U,1);
	cvCvtColor(this->Imagem, img_bin, CV_RGB2GRAY  ); // escalas de cinza
	cvThreshold(img_bin, img_bin, 50, 255,CV_THRESH_BINARY); // limiarizacao
	cvFlip(img_bin,img_bin,1); //flipa a imagem do resultado verticalmente
	cvFlip(this->Imagem,this->Imagem,1); //flipa a imagem real verticalmente

	CvMemStorage* g_storage = cvCreateMemStorage(0);
	CvSeq* contours = 0;
	cvFindContours( img_bin, g_storage, &contours,sizeof(CvContour), CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE );

	if( contours ){
		cvDrawContours(this->Imagem,contours,cvScalarAll(255),	cvScalarAll(255),100 );
	}
		
	CvSeq* tmpcontours=contours;
	CvSeq* result = 0;

    for( ; tmpcontours != 0; tmpcontours = tmpcontours->h_next )
	{
		// Approximates polygonal curves with desired precision
        result = cvApproxPoly(tmpcontours, sizeof(CvContour), g_storage, CV_POLY_APPROX_DP, cvContourPerimeter(tmpcontours)*0.02, 0);
		double reg = fabs(cvContourArea(result, CV_WHOLE_SEQ));
        //check if contour is big enough
		if( reg< (1) ){ continue; }
        CvRect retangulo = cvBoundingRect( tmpcontours, 0 );
		CvScalar pixel= cvScalar(255,0,255,0);
		this->y=retangulo.y+(retangulo.height/2);
		this->x=retangulo.x+(retangulo.width/2);
	}
}

int Processamento::getX(){
	return this->x;
}

int Processamento::getY(){
	return this->y;
}