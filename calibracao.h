class Calibracao
{
private:
	IplImage* imagem;
	int resolucaoAltura;
	int resolucaoLargura;
	int cameraAltura;
	int cameraLargura;
	int x,y;
	int x1,y1,x2,y2,x3,y3,x4,y4;
	typedef struct{
		int x;
		int y;
	} Ponto;
	typedef struct{
		int quantidadeDePontos;
		Ponto ponto[10000];
	} Pontos;
	Pontos pontos;
public:
	Calibracao(int resolucaoAltura, int resolucaoLargura, int cameraAltura, int cameraLargura);
	~Calibracao();
	void calibrar(int x, int y, int c);
	bool validarArea(int x, int y);
	void mostrar();
	void converterPerspectiva(int x, int y);
	void bresenham(int x1, int y1, int x2, int y2);
	void setImagem(IplImage* img);
	void pintarAreaDeNaoInteresse();
	void pintarVertices();
	IplImage* getImagem();
	int getX();
	int getY();
	int getX1();
	int getY1();
	int getX2();
	int getY2();
	int getX3();
	int getY3();
	int getX4();
	int getY4();
	void setX1(int x);
	void setX2(int x);
	void setX3(int x);
	void setX4(int x);
	void setY1(int y);
	void setY2(int y);
	void setY3(int y);
	void setY4(int y);

};