#include "stdafx.h"

enum Operacao
{
   MOVIMENTO,
   CLIQUE_ESQUERDO_UP,
   CLIQUE_ESQUERDO_DOWN,
   CLIQUE_DIREITO
};
class Mouse
{
private:
   int counter;
   int lastX;
   int lastY;
   int resol_height;
   int resol_width;
   bool wait;

public:
 
  void gerarEventoDeMouse(int x, int y, Operacao op);
  void Mouse::tratarMouse(int x, int y,int e );

  Mouse();
  ~Mouse();

};