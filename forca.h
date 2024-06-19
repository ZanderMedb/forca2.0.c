#ifndef FORCA_H
#define FORCA_H

HANDLE hSemaphore;

int letraexiste(char letra);
int chuteserrados();
int enforcou();
int ganhou();
void abertura();
void chuta();
DWORD WINAPI thread_chuta(LPVOID arg);
int jachutou(char letra);
void desenhaforca();
void escolhepalavra(const char* arquivo);
void seleciona_dificuldade();
void seleciona_categoria(char* arquivo);

#endif