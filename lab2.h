char** readFile(char* filename, int* size);
void doSwap(char** file, const int size, char* old_text, char* new_text);
void extractRegex(char* input, char** output1, char** output2, int type);
void addFront(char** file, const int size, char* output1, char* output2);
void addEnd(char** file, const int size, char* output1, char* output2);
void delText(char** file, const int size, char* output1, char* output2);
void writeFile(char** text, char* filename, const int size);
