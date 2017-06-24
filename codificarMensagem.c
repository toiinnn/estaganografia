#include "lerImagem.h"

//função para pegar os caracteres do arquivo txt e jogar em um ponteiro de char 
char* txtToChar(char* arqTexto)
{
  FILE* arq = fopen(arqTexto, "r");
    char* charTexto = malloc(1);
    int ultIndice = 0, tam = 0;
    char aux;
    if(arq == NULL)
    {
      fprintf(stderr, "Não foi possível abrir o arquivo.\n");
    }else
    { 
      while (fscanf(arq, "%c", &aux) != EOF)
      {
        charTexto[ultIndice++] = aux;
        charTexto = realloc(charTexto, ultIndice+1);
        tam++;
      }    
      printf("%d\n", tam);
    }
    return charTexto;
}

//função para transformar os caracteres de decimal em binário
char* getCharToBin(char* charTexto)
{
  int i, j, k, a = 0, aux = 1;
  k = strlen(charTexto);
  char* charBin = malloc(k*8);
  int bin[k*8];
  for(i = 0 ; i < k; i++)
  {
    for(j = 7; j >= 0; j--)
    {
      charTexto[i] & (1 << j) ? aux : aux--;
      bin[a] = aux;
      if(bin[a] == 0)
        charBin[a] = '0';
      else
        charBin[a] = '1';
      a++;
      aux = 1;
    }
  }
  charBin[a] = '\0';
  return charBin;
}

//seleciona o bit do caractere a ser trabalhado
int getBit (unsigned char byte, int pos) { 
	int valor;
	unsigned char mascara;
	mascara = 0x1 << pos;
	valor = byte & mascara;
	return valor >> pos;
}

//seleciona o RGB para ser inserido o bit recuperado na função anterior
void setBit (unsigned char* byte, int pos, int valor) {
	unsigned char mascara;
	mascara = 0x1 << pos;
	(*byte) &= (~mascara);
	mascara = (unsigned char) valor << pos;
	(*byte) |= mascara;
}

//insere a mensagem na imagem
void codificar(Pixel ***Matriz,int largura, char* mensagem, int tam_msg) 
{
	int i, l=0;
	int c=0;
    for (i = 0; i < tam_msg; ++i)
    {
    	if (c >= largura)
    	{
    		c=0;
    		l++;
    	}
    	setBit(&(*Matriz)[l][c].r, 0, getBit(mensagem[i],7));
    	setBit(&(*Matriz)[l][c].g, 0, getBit(mensagem[i],6));
    	setBit(&(*Matriz)[l][c].b, 0, getBit(mensagem[i],5));
    	c++;

    	setBit(&(*Matriz)[l][c].r, 0, getBit(mensagem[i],4));
    	setBit(&(*Matriz)[l][c].g, 0, getBit(mensagem[i],3));
    	setBit(&(*Matriz)[l][c].b, 0, getBit(mensagem[i],2));
    	c++;

    	setBit(&(*Matriz)[l][c].r, 0, getBit(mensagem[i],1));
    	setBit(&(*Matriz)[l][c].g, 0, getBit(mensagem[i],0));
    	c++;
    }
}

//gera uma nova imagem com a mensagem inserida
void gravarImagem(Imagem imgPPM, char* nomeImagem) 
{
int i, j;
//a imagem é escrita em um arquivo .pnm criado no momento da execução
FILE *arq;
arq = fopen(nomeImagem, "wb");
if(arq == NULL){
fprintf(stderr, "Erro na abertura da imagem.\n");
}else{
  //escrita da imagem no arquivo
  fprintf(arq, "%s\n%i %i\n%i\n",imgPPM.cabecalho, imgPPM.altura, imgPPM.largura, imgPPM.max);
   for(i = 0; i < imgPPM.altura; i++){
      for(j = 0; j < imgPPM.largura; j++){
        fprintf(arq,"%c%c%c", imgPPM.m[i][j].r, imgPPM.m[i][j].g, imgPPM.m[i][j].b);
      }
   }
  }
  fclose(arq);
}


int main(int argc, char** argv)
{
    char* msgChar;
    char* msgBin;
    Imagem imagem;
    
    imagem = leituraDaImagemPPM("balao.ppm");
    msgChar = txtToChar("teste.txt"); 
    printf("%s\n", msgChar);
    msgBin = getCharToBin(msgChar);
    printf("%s\n", msgBin);
    codificar(&imagem.m, imagem.largura, msgBin, strlen(msgBin));
    gravarImagem(imagem, "balao_nova.ppm");
    
    return 0;
}