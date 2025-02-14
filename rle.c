#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void compress(FILE *inputFile, FILE *outputFile) {
    char currentChar, previousChar;
    int count;

    previousChar = fgetc(inputFile);
    if (previousChar == EOF) return;

    count = 1;
    while ((currentChar = fgetc(inputFile)) != EOF) {
        if (currentChar == previousChar) {
            count++;
        } else {
            fprintf(outputFile, "%c%d", previousChar, count);
            previousChar = currentChar;
            count = 1;
        }
    }
    fprintf(outputFile, "%c%d", previousChar, count);
}

void decompress(FILE *inputFile, FILE *outputFile) {
    char currentChar;
    int count;

    while ((currentChar = fgetc(inputFile)) != EOF) {
        if (isdigit(currentChar)) {
            ungetc(currentChar, inputFile);
            fscanf(inputFile, "%d", &count);
            char ch = fgetc(inputFile);
            for (int i = 0; i < count; i++) {
                fputc(ch, outputFile);
            }
        }
    }
}

int main() {
    FILE *inputFile, *outputFile;
    char filename[100];

    printf("Enter input file name: ");
    scanf("%s", filename);

    inputFile = fopen(filename, "r");
    if (inputFile == NULL) {
        printf("Error opening input file.\n");
        return 1;
    }

    printf("Enter output file name (for compression): ");
    scanf("%s", filename);

    outputFile = fopen(filename, "w");
    if (outputFile == NULL) {
        printf("Error opening output file.\n");
        fclose(inputFile);
        return 1;
    }

    compress(inputFile, outputFile);

    fclose(inputFile);
    fclose(outputFile);

    printf("File compressed successfully.\n");

    printf("Enter input file name (for decompression): ");
    scanf("%s", filename);

    inputFile = fopen(filename, "r");
    if (inputFile == NULL) {
        printf("Error opening input file.\n");
        return 1;
    }

    printf("Enter output file name (for decompression): ");
    scanf("%s", filename);

    outputFile = fopen(filename, "w");
    if (outputFile == NULL) {
        printf("Error opening output file.\n");
        fclose(inputFile);
        return 1;
    }

    decompress(inputFile, outputFile);

    fclose(inputFile);
    fclose(outputFile); 

    printf("File decompressed successfully.\n");

    return 0;
}
