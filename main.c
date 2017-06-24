// steg.c
// Encoder/decoder de mensagens por esteganografia em imagens PPM e BMP
// Felipe da Silva Andrade e Antonio Marcos de Oliveira
// 26/05/2017
//https://github.com/felpsisonfire/Esteganografia.git
#include "lerImagem.h"

//Modificar para ler BMP e PPM
int main(int argc, char **argv){
  Imagem img;
  img = leituraDaImagemPPM(argv[1]);
  return 0;
}
