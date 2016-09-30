/* COPYRIGHT
* Copyright (C) 2016  Ahmad Waris Al H
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*
* AUTHOR
* Amad Waris Al H (warisafidz@gmail.com)
*/


#include <stdio.h>
#include <stdint.h>

typedef struct{
   uint8_t sig[2];
   uint32_t fileSize;
   uint32_t unused;
   uint32_t dataOff;
   
   uint32_t
      size,
      width,
      heigh;
   uint16_t
      plane,
      bitc;
   uint32_t 
      comp,
      imageSize,
      Xpixel,
      Ypixel,
      colorUsed,
      colorImp;
}Bitmap;

uint32_t bitsum(uint32_t bit){
   uint32_t sum;
   uint8_t * ptr;

   ptr = (uint8_t *)&bit;

   sum = (ptr[0] << 24);

   return sum;
}

int main(){
   Bitmap * gambar;
   int buf, w, h;
   uint8_t * ptr;
   register unsigned int i;
   FILE * image;

   ptr = malloc(56);
   image = fopen("./image.bmp", "r");
   
   for (i = 0; i < 54; i++){
      if (i == 2 || i == 3)
         continue;
      ptr[i] = getc(image);
   }
   gambar = (Bitmap *)ptr;

   uint8_t (* pixel)[(gambar->width * gambar->bitc / 8) / gambar->bitc][gambar->bitc / 8];
   pixel = malloc(gambar->imageSize);

   ptr = pixel;
   i--;
   while (i++ <= gambar->dataOff) 
      (void)getc(image);

   printf("%X\n", i);

   i = 0;
   w = 0;
   printf("RAW Data\n");
   for (h = 0; h < gambar->heigh; h++){
      for (w = 0; (buf = getc(image)) != EOF, w < gambar->width; w++){
         printf("%2X ", buf);
         ptr[i++] = buf;
      }
      printf("\n");
      while ((++w % 4) != 0)
         (void)getc(image);
   } 


   printf("Signautre :%c%c\n", gambar->sig[0], gambar->sig[1]);
   printf("File Size :%d\n", gambar->fileSize);
   printf("Offset : %X\n", gambar->dataOff);
   printf("Header Size : %d\n", gambar->size);
   printf("Width :%d\n", gambar->width);
   printf("Heigh :%d\n", gambar->heigh);
   printf("Bit/pixel : %d\n", gambar->bitc);
   printf("Image size :%d\n", gambar->imageSize);

   printf("%X\n", pixel[0][0][0]);


   return 0;
}









