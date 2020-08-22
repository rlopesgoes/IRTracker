/*
Uso:
$ significa que é uma entrada que deve ser passada por parâmetro.

Scanline s($X1,$Y1,$X2,$Y2);
s.QuantidadeDePontos; // diz a quantidade de pontos(x,y) gerados pelo algoritmo de bresenham que liga os dois pontos 1 e 2 de entrada.
s.getX($PONTO); // retorna o valor X do ponto de numero PONTO
s.getY($PONTO); // retorna o valor Y do ponto de numero PONTO

*/

class Scanline
{
private:
	typedef struct{
		int x;
		int y;
	} Ponto;
	Ponto p[1000];
	int quantidadeDePontos;
	int id;
	int x1;
	int y1;
	int x2;
	int y2;
public:
	Scanline(int x1,int y1,int x2,int y2);
	void bresenham();
	int getQuantidadeDePontos();
	int getY(int ponto);
	int getX(int ponto);
};