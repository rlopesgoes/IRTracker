/******************************************************
         PROGRAMA PARA TRACKING DE OBJETOS
AUTORES: RICARDO LOPES DE GÓES
         THIAGO FERNANDES MASSA
ÚLTIMA MODIFICAÇÃO: 13/03/2011
*********************************************************/

#include "stdafx.h"
#include "calibracao.h"
#include "deteccao.h"
#include "mouse.h"

using namespace std;

//Variáveis globais -- callbacks infelizmente "obrigam" o uso disso.
IplImage* img;
int cliques=0;
int xs, ys;
int cam_height=640;
int cam_width=480;
int resol_height=::GetSystemMetrics( SM_CYSCREEN );
int resol_width=::GetSystemMetrics( SM_CXSCREEN );
int deltaX;
int deltaY;
int lastX;
int lastY;
int counter;//Guarda o valor de interações
bool wait;

void printScreenSize()
{
	  double fScreenWidth    = ::GetSystemMetrics( SM_CXSCREEN ); 
	  double fScreenHeight  = ::GetSystemMetrics( SM_CYSCREEN ); 
	  printf("\nSua resolucao atual e: %4.0f x %4.0f\n",fScreenWidth,fScreenHeight);
}

int main(int argc, char *argv[])
{ 
	/*
	if(argc>=1){
		printf("%s, %d",argv[1],argc);
		for(int i=1;i<argc;i++){
		  char attribute[100];
		  char value[100] = "";
		  int posicao = 0;
		  bool add_char_to_attribute = true;

		  while(argv[i][posicao]!= '\0'){
			  if(argv[i][posicao]=='='){ add_char_to_attribute= false; }
			  printf("Aqui");
			  if(add_char_to_attribute){strcat_s(attribute,(const char*) argv[i][posicao]); }
			  posicao++;
		  }
		}
	}
	*/


	//BLOCO DE VARIAVEIS
	int key=0;
	IplImage* frame;
	int limiar = 50;
	bool p=false;
	Calibracao c(resol_height,resol_width, cam_height, cam_width);
	Mouse *m = new Mouse();
	CvCapture* captura = cvCaptureFromCAM( 1 );
	cvSetCaptureProperty(captura,CV_CAP_PROP_FRAME_HEIGHT,cam_height);
	cvSetCaptureProperty(captura,CV_CAP_PROP_FRAME_WIDTH,cam_width);
	printf("\n**************\nIR Tracking\n**************\nPressione q para sair.\nRicardo Lopes, Thiago Massa - 2011\n");
	printScreenSize();
	if( !captura )
	    printf("Erro: camera não foi encontrada.");	
	cvNamedWindow( "resultado", CV_WINDOW_AUTOSIZE );
	cvNamedWindow( "real", CV_WINDOW_AUTOSIZE );
	frame = cvQueryFrame( captura );

	int flag_up=0;
	int flag_down=0;

	while(key != 'q') 
	{ 
		bool detectado = true;
	    frame = cvQueryFrame( captura ); 
		img=cvCloneImage(frame);
        Deteccao d(img);
		d.detectarPonto();
		c.setImagem(img);
		if(key == '1'){c.calibrar(d.getX(),d.getY(),1);}
		if(key == '2'){c.calibrar(d.getX(),d.getY(),2);}
		if(key == '3'){c.calibrar(d.getX(),d.getY(),3);}
		if(key == '4'){c.calibrar(d.getX(),d.getY(),4);}

		if(key == 'p'||p==true)
		{
			c.converterPerspectiva(d.getX(),d.getY());
			c.pintarAreaDeNaoInteresse();
			p=true;
			if(c.validarArea(d.getX(),d.getY())){
				printf("p(x)={%d,%d}\n", c.getX(), c.getY());detectado = true;
			} else { detectado = false; }
			if(d.getX()!=0&&d.getY()!=0 && detectado == true){
				if(flag_up==0){
					flag_up=1;
					m->tratarMouse(c.getX(),c.getY(),1);
					m->tratarMouse(c.getX(),c.getY(),2);
					flag_down=1;
				}
				else if(flag_up==1){
					m->tratarMouse(c.getX(),c.getY(),1);
					flag_down=1;
				}
			}
			if(flag_up==2){
				m->tratarMouse(c.getX(),c.getY(),3);
				flag_up=0;
				flag_down=0;
			}
			if(detectado==false&&flag_down==1){flag_up=2;flag_down=0;}
		}
		else {if(d.getX()!=0&&d.getY()!=0){m->tratarMouse(c.getX(),c.getY(),1);}}
		if(key == 'c'){c.mostrar();}
		c.pintarVertices();
		img=c.getImagem();
		cvRectangle(img, cvPoint((d.getX())-1,(d.getY())-1), cvPoint((d.getX())+1,(d.getY())+1), cvScalar(0,0,255), 2);
		//m->tratarMouse(resol_height/2, resol_width/2);
				
		cvShowImage("resultado",d.getImagemResultado());
		cvShowImage("real",img);
		key = cvWaitKey( 1 );
		
	}  	
	cvReleaseCapture( &captura );   
	delete m;

	return 0; 
}   

