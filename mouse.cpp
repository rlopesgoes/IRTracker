#include "stdafx.h"
#include "mouse.h"

Mouse::Mouse()
{
	this->counter =0;
	resol_height=::GetSystemMetrics( SM_CXSCREEN );
    resol_width=::GetSystemMetrics( SM_CYSCREEN );
	resol_height = 65535/resol_height;
	resol_width = 65535/resol_width;
	printf("\n\nResolucao %d, %d",resol_height, resol_width);
}
Mouse::~Mouse()
{
  //printf("destrutor de mouse");
  system("PAUSE");
}

void Mouse::gerarEventoDeMouse(int x, int y, Operacao op)
{

	INPUT  Input={0};
	Input.type      = INPUT_MOUSE;
	Input.mi.dx = x*resol_height;
	Input.mi.dy = y*resol_width;


	switch (op)
	{
	   case MOVIMENTO:{Input.mi.dwFlags  = MOUSEEVENTF_MOVE|MOUSEEVENTF_ABSOLUTE; break;}		
	   case CLIQUE_ESQUERDO_UP:
	   {
		   Input.mi.dwFlags  = MOUSEEVENTF_LEFTUP;
		   ::SendInput(1,&Input,sizeof(INPUT));
		   break;
	   }
	   case CLIQUE_ESQUERDO_DOWN:
	   {
		   Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		   ::SendInput(1,&Input,sizeof(INPUT));
		   break;
	   }
	}
	::SendInput(1,&Input,sizeof(INPUT));
}


void Mouse::tratarMouse(int x, int y, int e)
{
	/**************************************
	       ROTINA DE HANDLER DO MOUSE
	**************************************/
	printf("\nposicao: %d, %d",x,y);
	if(e==1){gerarEventoDeMouse(x,y,MOVIMENTO);}
	else if(e==2){gerarEventoDeMouse(x,y,CLIQUE_ESQUERDO_DOWN);}
	else if(e==3){gerarEventoDeMouse(x,y,CLIQUE_ESQUERDO_UP);printf("mouse up");}
	/*
		if(x!=0 && y!=0)
		{
			if(counter < 10 && x >= (lastX -10) && (x <= lastX +10) && y >= (lastY -10) && y <= (lastY +10) && wait) 
				gerarEventoDeMouse(x,y,CLIQUE_ESQUERDO);
			if(counter < 20 && counter > 10 && x >= (lastX -10) && (x <= lastX +10) && y >= (lastY -10) && y <= (lastY +10) && wait) 
					gerarEventoDeMouse(x,y,CLIQUE_DIREITO);
			else
			{
				gerarEventoDeMouse(x,y,CLIQUE_ESQUERDO);
				counter = 0;
				wait = false;
				lastX = x;
				lastY = y;
			}

		}
		else
		{wait = true; counter++;}*/
}