#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

void codigoPostal(int codigo);
void distritos(int cod_distrito);
void concelhos(int cod_distrito, int cod_concelho);
bool validar(char *cod);

int main(int argc, char *argv[]){
    if(argc == 2){
      char *cod = malloc(strlen(argv[1]));
      if (cod == NULL){
        printf("Erro na alocação.\n");
        return 1;
      }
      strcpy(cod, argv[1]);
      for (int i = 4; i < 8; i++){
        cod[i] = cod[i + 1];
      }
      if(!validar(cod)){
        printf("Utiliza o seguinte formato:\n./codpostal 9650-007\n");
        return 1;
      }
      int cod_postal = atoi(cod);
      codigoPostal(cod_postal);
    }else{
      printf("Utiliza o seguinte formato:\n./codpostal 9650-007\n");
    }
    return 0;
}

bool validar(char *cod){
  for (long unsigned int i = 0; i < strlen(cod); i++){
    if(!isdigit(cod[i])){
      return false;
    }
  }
  if(strlen(cod) != 7){
     return false;
  }
  return true;
}

void codigoPostal(int codigo){
    FILE *ficheiro;
    char linha[1024];
    char *token;
    int encontrado = 0;
    ficheiro = fopen("data/codigos_postais.csv", "r");
    if (ficheiro == NULL){
        printf("Erro ao abrir.\n");
    }else {
        while (!feof(ficheiro)){ 
        fgets(linha, sizeof(linha), ficheiro);
        token = strtok(linha, ",");
        char *tokens[100];
        int total_tokens = 0;
        while(token != NULL){
            tokens[total_tokens] = token;
            total_tokens++;
            token = strtok(NULL, ",");
        }
        if (total_tokens >= 3 && tokens[total_tokens - 3] != NULL && tokens[total_tokens - 2] != NULL){ 
            int num = (atoi(tokens[total_tokens - 3]) * 1000) + atoi(tokens[total_tokens -2]);
            if (num == codigo){
                distritos(atoi(tokens[0]));
                concelhos(atoi(tokens[0]), atoi(tokens[1]));
                printf("Localidade: %s\n", tokens[3]);
                printf("Designação Postal: %s", tokens[total_tokens - 1]);
                printf("Código Postal: %s-%s\n", tokens[total_tokens - 3], tokens[total_tokens - 2]);
                encontrado = 1;
                break;
            }
        }
    }
    }
    fclose(ficheiro);
    if(!encontrado){
        printf("Código Postal não encontrado ou inválido. Por favor, utiliza o seguinte formato:\n./codpostal 9650-007\n");
        return;
    }
}

void distritos(int cod_distrito){
  FILE *ficheiro;
  char linha[64];
  char *token;
  ficheiro = fopen("data/distritos.csv", "r");
  if(ficheiro == NULL){
    printf("Erro ao abrir.\n");
  }else{
    while(!feof(ficheiro)){
      fgets(linha, sizeof(linha), ficheiro);
      token = strtok(linha, ",");
      char *tokens[2];
      int total_tokens = 0;
      while(token != NULL){
        tokens[total_tokens] = token;
        total_tokens++;
        token = strtok(NULL, ",");
      }
      if(atoi(tokens[0]) == cod_distrito){
        printf("Distrito: %s", tokens[1]);
      }
    }
  }
  fclose(ficheiro);
}

void concelhos(int cod_distrito, int cod_concelho){
  FILE *ficheiro;
  char linha[128];
  char *token;
  ficheiro = fopen("data/concelhos.csv", "r");
  if(ficheiro == NULL){
    printf("Erro ao abrir.\n");
  }else{
    while(!feof(ficheiro)){
      fgets(linha, sizeof(linha), ficheiro);
      token = strtok(linha, ",");
      char *tokens[3];
      int total_tokens = 0;
      while(token != NULL){
        tokens[total_tokens] = token;
        total_tokens++;
        token = strtok(NULL, ",");
      }
      if(atoi(tokens[0]) == cod_distrito && atoi(tokens[1]) == cod_concelho){
        printf("Concelho: %s", tokens[2]);
      }
    }
  }
  fclose(ficheiro);
}
