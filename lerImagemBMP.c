#include "lerImagem.h"

//Função para leitura e armazenamento de uma imagem BMP.
Imagem leituraDaImagemBMP(char *nomeImagem)
{
  int i, j, lixo[3]; //Variáveis auxiliares.
  Imagem resultado; //Struct de armazenamento das informações da imagem.

  //Abertura do arquivo para leitura e verificação.
  FILE *arq;
  arq = fopen(nomeImagem, "r");
  if(arq == NULL)
  {
    fprintf(stderr, "Nao foi possivel abrir o arquivo.\n");
  }else
  {
    //Leitura do cabeçalho BMP.
    fread(resultado.cabecalho, sizeof(char), 2, arq);
    printf("%s\n", resultado.cabecalho);

    if(strcmp(resultado.cabecalho, "BM"))
    {  //Verifica se o arquivo é BMP pela assinatura do cabeçalho.
      fprintf(stderr, "O arquivo nao eh uma imagem BMP.\n");
    }else
    {
      fseek(arq, 10, SEEK_SET); //Definindo para a posição do deslocamento, segundo a documentação BMP File.
      fread(&resultado.deslocamento, sizeof(int), 1, arq);//Armazenando o valor de deslocamento.
      printf("%d\n", resultado.deslocamento);
      fseek(arq, 18, SEEK_SET); //Definindo para a posição de altura e largura.
      fread(&resultado.largura, sizeof(int), 1, arq); //Armazenando o valor de largura e altura.
      printf("%d\n", resultado.largura);
      fread(&resultado.altura, sizeof(int), 1, arq);
      printf("%d\n", resultado.altura);
      fseek(arq, resultado.deslocamento, SEEK_SET); //Definindo a posição de deslocamento para o começo da matriz de pixels.

      //Alocando dinamicamente a matriz de pixels.
      resultado.m = malloc(resultado.altura*sizeof(Pixel *));
      for(i=0; i<resultado.altura; i++)
      {
        resultado.m[i] = malloc(resultado.largura*sizeof(Pixel));
      }

      //Lendo e armazenando os pixels na struct resultado.
      for(i=resultado.altura-1;i>=0;i--)
      {//eu demorei mt para achar isso, mas o problema todo estava aqui, o seu for estava errado, da uma olhada no original.
        for(j=0;j<resultado.largura;j++)
        {
          fscanf(arq, "%c%c%c", &resultado.m[i][j].b, &resultado.m[i][j].g, &resultado.m[i][j].r);
        }
	      fread(&lixo, sizeof(unsigned char), resultado.largura%4, arq);//adicionei isso para aceitar qualquer imagem, pq a imagem tem que ter o numero de colunas multiplo de 4.
      }

      FILE *img;
      img = fopen("imagem.ppm", "w");
      if(img == NULL) //Verificação do arquivo.
      {  
      fprintf(stderr, "Erro na abertura da imagem.\n");
      }else
      {
        //char *nomeImagem = argv[1];
        Imagem imgPPM = resultado;//leituraDaImagemBMP(nomeImagem);
        imgPPM.max = 255;
        //Armazenamento da imagem no arquivo.
        fprintf(img, "P6\n");
        fprintf(img, "%d %d\n%d\n", imgPPM.largura, imgPPM.altura, imgPPM.max);//mudei aqui tb, vc estava printando altura primeiro, mas na vdd é largura primeiro.
         for(i = 0; i < imgPPM.altura; i++)
         {
            for(j = 0; j < imgPPM.largura; j++)
            {
              fprintf(img,"%c%c%c", imgPPM.m[i][j].r, imgPPM.m[i][j].g, imgPPM.m[i][j].b);
            }
         }
        }
      fclose(img);
    }
  }
  fclose(arq);
  return resultado;
  }
