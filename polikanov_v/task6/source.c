#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <locale.h> 

int str_word_count(char* str) {
	int count = 0;
	for (int i = 0; str[i] != 0; i++){

	}// .. нашли, сколько слов
}

char** str_split(char* str) { // разбивает строку на слова char** - набор строк char* - строка   "cfghfhfhgfgh\0"
	int word_count = str_word_count(str);
	char** words = (char**)malloc(sizeof(char*) * word_count); // выделяем память под массив строк(ровно сколько нужно)
	int word_len,word_index,word_begin = 0;
	for (int i = 0; i < word_count; i++) {
		word_index = i;
			for (word_len = word_begin; str[word_len] != ' '; word_len++) {

		} // узнаем длину слова

		words[word_index] = (char*)malloc(sizeof(char) * word_len + 1); // выделяем память под слово
		memcpy(words[word_index], &str[word_begin], sizeof(char) * word_len); // копируем слово ( 1пар - куда 2пар - начиная с какой позиции 3пар - сколько байт копировать)

	}
} 

void main() {
	char* str = ""; //создание пустой строки
	char str1[100] = "hehehehe"; // 2  
	char* str2 = (char*)calloc(10 + 1, sizeof(char));

}