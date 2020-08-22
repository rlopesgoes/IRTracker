/*
Uso:
$ significa que é uma entrada que deve ser passada por parâmetro.

Subtracao s($IMG_FUNDO,$LIMIAR);
s.setFrameAtual($FRAME_ATUAL);
s.subtrair();
s.getFrameSubtraido();

*/

class Subtracao
{
private:
	int id;
	IplImage* frameAtual;
	IplImage* frameAtualCinza;
	IplImage* fundo;
	IplImage* frameSubtraido;
	int limiar;
public:
	Subtracao(IplImage* f, int limiar);
	void setFrameAtual(IplImage* f);
	void setFundo();
	void setFundo(IplImage* f);
	IplImage* getFrameSubtraido();
	IplImage* getFrameAtual();
	void subtrair();
};