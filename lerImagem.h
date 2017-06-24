#ifndef LERIMAGEM_H
#define LERIMAGEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//Struct para leitura de pixels
typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;

}Pixel;

//Struct para leitura dos parametros da imagem.
typedef struct Imagem {
    Pixel **m; //Armazenamento da imagem
    int largura, altura, max; //Dados do cabeçalho
    char *nomeImagem, cabecalho[54]; //Nome da imagem e cabeçalho do arquivo
    unsigned int deslocamento; //deslocamento para mapa de bits BMP
}Imagem;

//Declaração das funções

//Função para verficar a extenção.
int lerArquivo(char *nomeImagem); 
//Função para leitura de imagens PPM
Imagem leituraDaImagemPPM(char *nomeImagem);
//Função para leitura de imagens BMP.
Imagem leituraDaImagemBMP(char *nomeImagem); 
//conversão de arquivo de texto para ponteiro de char (melhor manipulação)
char* txtToChar(char* arqTexto); 
//conversão de char para binário
char* getCharToBin(char* charTexto); 
//seleciona o bit do caractere a ser trabalhado
int getBit (unsigned char byte, int pos); 
//seleciona o RGB para ser inserido o bit recuperado na função anterior
void setBit (unsigned char* byte, int pos, int valor); 
//insere a mensagem na imagem
void codificar(Pixel ***Matriz,int largura, char* mensagem, int tam_msg);
//gera uma nova imagem com a mensagem inserida
void gravarImagem(Imagem imgPPM, char* nomeImagem);



#endif
