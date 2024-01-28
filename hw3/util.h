#ifndef _UTIL_H_
#define _UTIL_H_

void drawRoom(int size, int characterX, int characterY, int doorX, int doorY); 
int checkGameOver(int characterX, int characterY, int doorX, int doorY);
void startNewGame(); // Menu
void menu();//Main menu
void instructions();//help menu
//int part4(int num3);//Range

#endif /* _UTIL_H_ */