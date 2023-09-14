#include <stdio.h>
#define _OPEN_SYS_ITOA_EXT
#include <string.h>
#include <stdlib.h>
#include "lib_ppm.h"

unsigned int decToBinary(int n)
{
    // Tamanho do número em bits (12 bits no caso)
    int tamanho = 12;
    unsigned int binario = 0;

    for (int i = tamanho - 1; i >= 0; i--)
    {
        // Verifica o bit no i-ésimo posição
        int bit = (n >> i) & 1;

        // Define o bit na representação binária
        binario |= (bit << i);
    }

    return binario;
}

int main()
{
    Img data, secreta;
    Img *image = &data;
    Img *secret = &secreta;
    int i, j, r, t;

    r = read_ppm("earth.ppm", image);
    t = read_ppm("british_summer.ppm", secret);
    
    //CHECA SE A IMAGEM A SER ESCONDIDA CABE DENTRO DA IMAGEM MAIOR OU NÃO
    if (r == 0)
    {
        printf("width: %d, height: %d\n", image->width, image->height);
        printf("width: %d, height: %d\n", secret->width, secret->height);

        double base = (image->width * image->height) / 4;
        int secret_size = secret->width * secret->height;

        if (secret_size > base)
        {
            printf("Secret image is too big to hide in this image\n");
            return 0;
        }
    //**************************************************************************
        for (j = 0; j < image->height; j++)
        {

            // for (i = 0; i < image->width; i++)
            // {
            //     printf("(%d %d) %02x %02x %02x\n", i, j,
            //            image->pix[j * image->width + i].r,
            //            image->pix[j * image->width + i].g,
            //            image->pix[j * image->width + i].b);
            // }
        }

        //TRANSFORMANDO AS DIMENSÕES DA IMAGEM SECRETA PARA BINÁRIO
        int hbit = secret->height;
        int wbit = secret->width;
        char buffer [33];
        char buffer2 [33];
        itoa(wbit,buffer,2);
        itoa(hbit,buffer2,2);
        printf("binario %s\n", buffer);
        printf("A representação binária de %d é: %s\n", wbit, buffer);
        printf("A representação binária de %d é: %s\n", hbit, buffer2);
        //**************************************************************************
        //ESCREVENDO A IMAGEM SECRETA NA IMAGEM MAIOR (ja tava aqui)
        // image->pix[50 * image->width + 20].r = 255;
        // image->pix[50 * image->width + 20].g = 255;
        // image->pix[50 * image->width + 20].b = 255;

        write_ppm("lena_copy.ppm", image);

        free_ppm(image);
    }

    r = new_ppm(image, 675, 428);

    if (r == 0)
    {
        image->pix[100 * image->width + 125].r = 255;
        image->pix[27 * image->width + 440].g = 255;

        image->pix[371 * image->width + 10].r = 192;
        image->pix[371 * image->width + 10].g = 192;
        image->pix[371 * image->width + 10].b = 192;

        write_ppm("test.ppm", image);
        free_ppm(image);
    }

    return 0;
}
