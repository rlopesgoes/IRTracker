class Deteccao
{
private:
	int x;
	int y;
	IplImage* imagem;
	IplImage* imagemResultado;
public:
	Deteccao(IplImage* imagem);
	~Deteccao();
	void detectarPonto();
	int getX();
	void setX(int x);
	void setY(int y);
	int getY();
	IplImage* getImagem();
	IplImage* getImagemResultado();
};