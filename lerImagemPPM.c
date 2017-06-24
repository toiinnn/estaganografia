#include "lerImagem.h"

//Função para leitura e armazenamento de uma imagem BMP.
Imagem leituraDaImagemPPM(char *nomeImagem)
{
  int i, j; //Variáveis auxiliares.
  Imagem resultado; //Struct de armazenamento das informações da imagem.

  //Abertura do arquivo para leitura e verificação.
  FILE *arq;
  arq = fopen(nomeImagem, "rb");
  if(arq == NULL)
  {
    fprintf(stderr, "Nao foi possivel abrir o arquivo.\n");
  }else
  {
    //Leitura do cabeçalho PPM.
    fscanf(arq, "%s", resultado.cabecalho);
    if(strcmp(resultado.cabecalho, "P6"))
    {  //Verifica se o arquivo é PPM pela assinatura do cabeçalho.
      fprintf(stderr, "O arquivo nao eh uma imagem PPM.\n\n");
    }else
    {
      fscanf(arq, "%d %d %d\n", &resultado.largura, &resultado.altura, &resultado.max); //Armazenando largura, altura e intensidade máxima.

      //Alocando dinamicamente a matriz de pixels.
      resultado.m = malloc(resultado.altura*sizeof(Pixel *));
      for(i=0; i<resultado.altura; i++)
      {
        resultado.m[i] = malloc(resultado.largura*sizeof(Pixel));
      }
      //Lendo e armazenando os pixels na struct resultado.
      for(i=0; i<resultado.altura; i++)
      {
		    for(j=0; j<resultado.largura; j++)
        {
			    fscanf(arq, "%c%c%c", &(resultado.m[i][j]).r, &(resultado.m[i][j]).g, &(resultado.m[i][j]).b);
		    }
    	}
    }
    fclose(arq);
  }
  return resultado;
}
