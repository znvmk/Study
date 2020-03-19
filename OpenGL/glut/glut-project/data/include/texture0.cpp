#include "stdafx.h"
#include "texture0.h"

// LoadBitmapFile
// desc: Returns a pointer to the bitmap image of the bitmap specified
//       by filename. Also returns the bitmap header information.
//		 No support for 8-bit bitmaps.
unsigned char *CTexture::LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader)
{
	FILE *filePtr;							// the file pointer
	BITMAPFILEHEADER	bitmapFileHeader;		// bitmap file header
	unsigned char		*bitmapImage;			// bitmap image data
	int				imageIdx = 0;			// image index counter
	unsigned char		tempRGB;				// swap variable

	// open filename in "read binary" mode
	filePtr = fopen(filename, "rb");
	if (filePtr == NULL)
		return NULL;

	// read the bitmap file header
	fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
	
	// verify that this is a bitmap by checking for the universal bitmap id
	if (bitmapFileHeader.bfType != BITMAP_ID)
	{
		fclose(filePtr);
		return NULL;
	}

	// read the bitmap information header
	fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);

	// move file pointer to beginning of bitmap data
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);

	// allocate enough memory for the bitmap image data
	bitmapImage = (unsigned char*)malloc(bitmapInfoHeader->biSizeImage);

	// verify memory allocation
	if (!bitmapImage)
	{
		free(bitmapImage);
		fclose(filePtr);
		return NULL;
	}

	// read in the bitmap image data
	fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);

	// make sure bitmap image data was read
	if (bitmapImage == NULL)
	{
		fclose(filePtr);
		return NULL;
	}

	// swap the R and B values to get RGB since the bitmap color format is in BGR
	for (imageIdx = 0; imageIdx < (int)bitmapInfoHeader->biSizeImage; imageIdx+=3)
	{
		tempRGB = bitmapImage[imageIdx];
		bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
		bitmapImage[imageIdx + 2] = tempRGB;
	}

	// close the file and return the bitmap image data
	fclose(filePtr);
	return bitmapImage;
}

/*****************************************************************************
 LoadBitmapFileWithAlpha

 Loads a bitmap file normally, and then adds an alpha component to use for
 blending
*****************************************************************************/
unsigned char *CTexture::LoadBitmapFileWithAlpha(char *filename, BITMAPINFOHEADER *bitmapInfoHeader)
{
  unsigned char *bitmapImage = LoadBitmapFile(filename, bitmapInfoHeader);
  unsigned char *bitmapWithAlpha = (unsigned char *)malloc(bitmapInfoHeader->biSizeImage * 4 / 3);

  // loop through the bitmap data
  for (unsigned int src = 0, dst = 0; src < bitmapInfoHeader->biSizeImage; src +=3, dst +=4)
  {
    // if the pixel is black, set the alpha to 0. Otherwise, set it to 255.
    if (bitmapImage[src] == 0 && bitmapImage[src+1] == 0 && bitmapImage[src+2] == 0)
      bitmapWithAlpha[dst+3] = 0;
    else
      bitmapWithAlpha[dst+3] = 0xFF;

    // copy pixel data over
    bitmapWithAlpha[dst] = bitmapImage[src];
    bitmapWithAlpha[dst+1] = bitmapImage[src+1];
    bitmapWithAlpha[dst+2] = bitmapImage[src+2];
  }

  free(bitmapImage);

  return bitmapWithAlpha;
} // end LoadBitmapFileWithAlpha()

// LoadPCXFile()
// desc: loads a PCX file into memory
unsigned char *CTexture::LoadPCXFile(char *filename, PCXHEADER *pcxHeader)
{
     int idx = 0;                  // counter index
     int c;                             // used to retrieve a char from the file
     int i;                             // counter index
     int numRepeat;      
     FILE *filePtr;                // file handle
     int width;                         // pcx width
     int height;                        // pcx height
     unsigned char *pixelData;     // pcx image data
     unsigned char *paletteData;   // pcx palette data

     // open PCX file
     filePtr = fopen(filename, "rb");
     if (filePtr == NULL)
          return NULL;

     // retrieve first character; should be equal to 10
     c = getc(filePtr);
     if (c != 10)
     {
          fclose(filePtr);
          return NULL;
     }

     // retrieve next character; should be equal to 5
     c = getc(filePtr);
     if (c != 5)
     {
          fclose(filePtr);
          return NULL;
     }

     // reposition file pointer to beginning of file
     rewind(filePtr);

     // read 4 characters of data to skip
     fgetc(filePtr);
     fgetc(filePtr);
     fgetc(filePtr);
     fgetc(filePtr);

     // retrieve leftmost x value of PCX
     pcxHeader->xMin = fgetc(filePtr);       // loword
     pcxHeader->xMin |= fgetc(filePtr) << 8; // hiword

     // retrieve bottom-most y value of PCX
     pcxHeader->yMin = fgetc(filePtr);       // loword
     pcxHeader->yMin |= fgetc(filePtr) << 8; // hiword

     // retrieve rightmost x value of PCX
     pcxHeader->xMax = fgetc(filePtr);       // loword
     pcxHeader->xMax |= fgetc(filePtr) << 8; // hiword

     // retrieve topmost y value of PCX
     pcxHeader->yMax = fgetc(filePtr);       // loword
     pcxHeader->yMax |= fgetc(filePtr) << 8; // hiword

     // calculate the width and height of the PCX
     width = pcxHeader->xMax - pcxHeader->xMin + 1;
     height = pcxHeader->yMax - pcxHeader->yMin + 1;

     // allocate memory for PCX image data
     pixelData = (unsigned char*)malloc(width*height);

     // set file pointer to 128th byte of file, where the PCX image data starts
     fseek(filePtr, 128, SEEK_SET);
     
     // decode the pixel data and store
     while (idx < (width*height))
     {
          c = getc(filePtr);
          if (c > 0xbf)
          {
               numRepeat = 0x3f & c;
               c = getc(filePtr);

               for (i = 0; i < numRepeat; i++)
               {
                    pixelData[idx++] = c;
               }
          }
          else
               pixelData[idx++] = c;

          fflush(stdout);
     }

     // allocate memory for the PCX image palette
     paletteData = (unsigned char*)malloc(768);

     // palette is the last 769 bytes of the PCX file
     fseek(filePtr, -769, SEEK_END);

     // verify palette; first character should be 12
     c = getc(filePtr);
     if (c != 12)
     {
          fclose(filePtr);
          return NULL;
     }

     // read and store all of palette
     for (i = 0; i < 768; i++)
     {
          c = getc(filePtr);
          paletteData[i] = c;
     }

     // close file and store palette in header
     fclose(filePtr);
     pcxHeader->palette = paletteData;

     // return the pixel image data
     return pixelData;
}

// LoadPCXTexture()
// desc: loads a PCX image file as a texture
void CTexture::LoadPCXTexture(char *filename)
{
     PCXHEADER texInfo;            // header of texture
//     texture_t *thisTexture;       // the texture
     unsigned char *unscaledData;// used to calculate pcx
     int i;                             // index counter
     int j;                             // index counter
     int w;                         // width of texture
     int h;                        // height of texture

     // load the PCX file into the texture struct
     data = LoadPCXFile(filename, &texInfo);
     if (data == NULL)
     {
          free(data);
     //     return NULL;
     }

     // store the texture information
     palette = texInfo.palette;
     width = texInfo.xMax - texInfo.xMin + 1;
     height = texInfo.yMax - texInfo.yMin + 1;
     textureType = PCX;

	w = width;
     h = height;

     // allocate memory for the unscaled data
     unscaledData = (unsigned char*)malloc(w*h*4);

     // store the unscaled data via the palette
     for (j = 0; j < h; j++) 
     {
          for (i = 0; i < w; i++) 
          {
               unscaledData[4*(j*w+i)+0] = (unsigned char)palette[3*data[j*w+i]+0];
               unscaledData[4*(j*w+i)+1] = (unsigned char)palette[3*data[j*w+i]+1];
               unscaledData[4*(j*w+i)+2] = (unsigned char)palette[3*data[j*w+i]+2];
               unscaledData[4*(j*w+i)+3] = (unsigned char)255;
          }
     }

     // find width and height's nearest greater power of 2

     // find width's
     i = 0;
     while (w)
     {
          w /= 2;
          i++;
     }
     scaledHeight = (long)pow(2, i-1);

     // find height's
     i = 0;
     while (h)
     {
          h /= 2;
          i++;
     }
     scaledWidth = (long)pow(2, i-1);

     // clear the texture data
     if (data != NULL)
     {
          free(data);
          data = NULL;
     }

     // reallocate memory for the texture data
     data = (unsigned char*)malloc(scaledWidth*scaledHeight*4);
     
     // use the GL utility library to scale the texture to the unscaled dimensions
     gluScaleImage(GL_RGBA, this->width, this->height, GL_UNSIGNED_BYTE, unscaledData, scaledWidth, scaledHeight, GL_UNSIGNED_BYTE, data);

	free(unscaledData);
//     return thisTexture;

}

// LoadBMPTexture()
// desc: loads a texture of the BMP format
void CTexture::LoadBMPTexture(char *filename)
{
	BITMAPINFOHEADER texInfo;		// BMP header

	// store BMP data in texture
	data = LoadBitmapFileWithAlpha(filename, &texInfo);
	if (data == NULL)
	{
		free(data);
	}
	
	// store texture information
	width = texInfo.biWidth;
	height = texInfo.biHeight;
	palette = NULL;
	scaledHeight = 0;
	scaledWidth = 0;
	textureType = BMP;
}

// LoadTexture()
// desc: loads a texture given the filename
void CTexture::LoadTexture(char *filename)
{
	char *extStr;

	// get extension from filename
	extStr = strchr(filename, '.');
	extStr++;

	// set the texture type based on extension of filename
	if ((strcmpi(extStr, "BMP") == 0) || (strcmpi(extStr, "bmp") == 0))
		LoadBMPTexture(filename);
	else if ((strcmpi(extStr, "PCX") == 0) || (strcmpi(extStr, "pcx") == 0) )
		LoadPCXTexture(filename);
	
	else if ((strcmpi(extStr, "TGA") == 0) || (strcmpi(extStr, "tga") == 0) )
		LoadTGATexture(filename);
}

// LoadTGAFile()
// desc: loads a TGA file defined by filename
unsigned char *CTexture::LoadTGAFile(char *filename, TGAHEADER *tgaHeader)
{
	FILE *filePtr;
	unsigned char ucharBad;	// garbage data
	short int	sintBad;		// garbage data
	long	imageSize;		// size of TGA image
	int colorMode;			// 4 for RGBA, 3 for RGB
	long imageIdx;			// counter variable
	unsigned char colorSwap;	// swap variable
	unsigned char *imageData;	// the TGA data

	// open the TGA file
	filePtr = fopen(filename, "rb");
	if (!filePtr)
		return NULL;
	
	// read first two bytes of garbage
	fread(&ucharBad, sizeof(unsigned char), 1, filePtr);
	fread(&ucharBad, sizeof(unsigned char), 1, filePtr);

	// read in the image type
	fread(&tgaHeader->imageTypeCode, sizeof(unsigned char), 1, filePtr);

	// for our purposes, the image type should be either a 2 or a 3
	if ((tgaHeader->imageTypeCode != 2) && (tgaHeader->imageTypeCode != 3))
	{
		fclose(filePtr);
		return NULL;
	}

	// read 13 bytes of garbage data
	fread(&sintBad, sizeof(short int), 1, filePtr);
	fread(&sintBad, sizeof(short int), 1, filePtr);
	fread(&ucharBad, sizeof(unsigned char), 1, filePtr);
	fread(&sintBad, sizeof(short int), 1, filePtr);
	fread(&sintBad, sizeof(short int), 1, filePtr);

	// read image dimensions
	fread(&tgaHeader->imageWidth, sizeof(short int), 1, filePtr);
	fread(&tgaHeader->imageHeight, sizeof(short int), 1, filePtr);

	// read bit depth
	fread(&tgaHeader->bitCount, sizeof(unsigned char), 1, filePtr);

	// read garbage
	fread(&ucharBad, sizeof(unsigned char), 1, filePtr);

	// colormode -> 3 = BGR, 4 = BGRA
	colorMode = tgaHeader->bitCount / 8;
	imageSize = tgaHeader->imageWidth * tgaHeader->imageHeight * colorMode;

	// allocate memory for image data
	imageData = (unsigned char*)malloc(sizeof(unsigned char)*imageSize);

	// read image data
	fread(imageData, sizeof(unsigned char), imageSize, filePtr);

	// change BGR to RGB so OpenGL can use the data
	for (imageIdx = 0; imageIdx < imageSize; imageIdx += colorMode)
	{
		colorSwap = imageData[imageIdx];
		imageData[imageIdx] = imageData[imageIdx+2];
		imageData[imageIdx + 2] = colorSwap;
	}

	// close the file
	fclose(filePtr);

	return imageData;
}

// LoadTGATexture()
// desc: loads a TGA as a texture
void CTexture::LoadTGATexture(char *filename)
{
	TGAHEADER tga;		// BMP header

	// store BMP data in texture
	data = LoadTGAFile(filename, &tga);
	if (data == NULL)
	{
		free(data);
	}
	
	// store texture information
	width = tga.imageWidth;
	height = tga.imageHeight;
	palette = NULL;
	scaledHeight = 0;
	scaledWidth = 0;
	tgaImageCode = tga.imageTypeCode;
	bitDepth = tga.bitCount;
	textureType = TGA;
}