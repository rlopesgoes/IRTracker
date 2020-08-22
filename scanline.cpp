#include "stdafx.h"
#include "scanline.h"

Scanline::Scanline(int x1,int y1,int x2,int y2){
	this->x1=x1;
	this->x2=x2;
	this->y1=y1;
	this->y2=y2;
	quantidadeDePontos=0;
	this->bresenham();
}

int Scanline::getQuantidadeDePontos(){
    return this->quantidadeDePontos;
}

int Scanline::getX(int ponto){
    return (p[ponto].x);
}

int Scanline::getY(int ponto){
    return (p[ponto].y);
}

void Scanline::bresenham(){        
    int slope;
	int dx, dy, incE, incNE, d, x, y;
     
	if (this->x1 > this->x2){
		int x1,y1,x2,y2;
		x1=this->x1;
		x2=this->x2;
		y1=this->y1;
		y2=this->y2;
		this->x1=x2;
		this->y1=y2;
		this->x2=x1;
		this->y2=y1;
    }        
    dx = (this->x2)-(this->x1);
    dy = (this->y2)-(this->y1);
   
    if (dy < 0){            
		slope = -1;
		dy = -dy;
    }
    else{            
		slope = 1;
    }

    incE = 2 * dy;
    incNE = 2 * dy - 2 * dx;
    d = 2 * dy - dx;
    y = y1;       
    for (x = this->x1; x <= x2; x++){
		(p[this->quantidadeDePontos].x)=x;
		(p[this->quantidadeDePontos].y)=y;
		this->quantidadeDePontos++;
		
		if (d <= 0){
			d += incE;
		}
		else{
			d += incNE;
			y += slope;
		}
	}
}