#include "lab3.h"

int process_movies(const char *input_filename, const char *genre, const char *output_filename) {
    FILE *input_file = fopen(input_filename, "r");
    FILE *output_file = fopen(output_filename, "w");

    if (input_file == NULL || output_file == NULL) {
        perror("Ошибка открытия файла");
        return 1;
    }
    char* title[512];
    char* dirrector[512];
    char* filmGenre[512];
    int year;
    while (fscanf(input_file, "%[^,],%[^,],%d,%[^\n]\n", title, director, &year, filmGenre) == 4) {
        if (strcmp(filmGenre, genre) == 0) {
            fprintf(output_file, "%s,%s,%d\n", title, director, year);
        }
    }

    fclose(input_file);
    fclose(output_file);
    return 0;
}
