/**********************************************************************
 *  bmp.c: read and write bmp image in 24-bit color
 **********************************************************************/

/*
 * unsigned char *LoadBMP(const char *fname, int *width, int *height)
 * 
 * Load a Windows .bmp file and return a pointer to the image data.
 * Inputs: fname  - name of .bmp file to read
 * Output: width
 *         height
 * Return: pointer to image data or Null of error
 *
 * Format: GL_RBG
 * Alignment: 1; use under glPixelStorei(GL_UNPACK_ALIGNMENT, 1)
 */

/*
 * void SaveImageAs(const char *fname)
 *
 * Save image to a file in .bmp format.
 *
 */
/**********************************************************************/
 #include <stdio.h>
 #include <stdlib.h>
 #include <GL/glut.h>

typedef struct _bitmap_file_header {
    unsigned short bfType;
    unsigned long  bfSize;
    unsigned short bfReserved1;
    unsigned short bfReserved2;
    unsigned long  bfOffBits;
} bitmap_file_header;

typedef struct _bitmap_info_header {
    unsigned long  biSize;
      signed long  biWidth;
      signed long  biHeight;
    unsigned short biPlanes;
    unsigned short biBitCount;
    unsigned long  biCompression;
    unsigned long  biSizeImage;
      signed long  biXPelsPerMeter;
      signed long  biYPelsPerMeter;
    unsigned long  biClrUsed;
    unsigned long  biClrImportant;
} bitmap_info_header;

static unsigned short fget2c(FILE *fp)
{
    unsigned short retv;
    retv  = (unsigned short) getc(fp);
    retv |= (unsigned short) getc(fp) << 8;
    return retv;
}

static unsigned long fget4c(FILE *fp)
{
    unsigned long retv;
    retv  = (unsigned short) getc(fp);
    retv |= (unsigned short) getc(fp) << 8*1;
    retv |= (unsigned short) getc(fp) << 8*2;
    retv |= (unsigned short) getc(fp) << 8*3;
    return retv;
}

static bitmap_info_header *read_bmp_header(FILE *fp)
{
    static bitmap_file_header bmpfh;
    static bitmap_info_header bmpih;

    /* bitmap_file_header */
    bmpfh.bfType = (unsigned short)'B' + ((unsigned short)'M' << 8);
    if (fget2c(fp) != bmpfh.bfType) {
        fprintf(stderr,"Not a BMP-file\n"); return NULL;
    }
    bmpfh.bfSize      = fget4c(fp);
    bmpfh.bfReserved1 = fget2c(fp);
    bmpfh.bfReserved2 = fget2c(fp);
    bmpfh.bfOffBits   = fget4c(fp);

    /* bitmap_info_header */
    bmpih.biSize          = fget4c(fp);
    bmpih.biWidth         = fget4c(fp);
    bmpih.biHeight        = fget4c(fp);
    bmpih.biPlanes        = fget2c(fp);
    bmpih.biBitCount      = fget2c(fp);
    bmpih.biCompression   = fget4c(fp);
    bmpih.biSizeImage     = fget4c(fp);
    bmpih.biXPelsPerMeter = fget4c(fp);
    bmpih.biYPelsPerMeter = fget4c(fp);
    bmpih.biClrUsed       = fget4c(fp);
    bmpih.biClrImportant  = fget4c(fp);

    return &bmpih;
}

unsigned char *LoadBMP(const char *fname, int *width, int *height)
{
    bitmap_info_header *bmpih;
    unsigned char *buf;
    FILE *fp;
    int x, y;
    
    if (!(fp = fopen(fname, "rb"))) {
	fprintf(stderr, "connot open %s\n", fname); return NULL; 
    }
    if (!(bmpih = read_bmp_header(fp))) return NULL;
    if (bmpih->biBitCount != 24) {
	fprintf(stderr, "not 24-bit color\n"); return NULL;
    }
    *width  = (int) bmpih->biWidth;
    *height = (int) bmpih->biHeight;

    buf = (unsigned char *)malloc(sizeof(unsigned char)*(*width)*(*height)*3);
    if (!buf) {
	fprintf(stderr, "cannot allocate image buffer\n"); return NULL; 
    }
    for (y = 0; y < *height; y++) {
	for (x = 0; x < *width; x++) {
            buf[(y*(*width)+x)*3+2] = getc(fp); /* blue  */
	    buf[(y*(*width)+x)*3+1] = getc(fp); /* green */
	    buf[(y*(*width)+x)*3+0] = getc(fp); /* red   */
        }
        while ((x--)%4 != 0) { getc(fp); }      /* skip padding */
    }
    fclose(fp);
    return buf;
}

/**********************************************************************/

static void fput2c(unsigned short d, FILE *fp)
{
    putc((d)      & 0xff, fp);
    putc((d >> 8) & 0xff, fp);
}

static void fput4c(unsigned long d, FILE *fp)
{
    putc((d)        & 0xff, fp);
    putc((d >> 8*1) & 0xff, fp);
    putc((d >> 8*2) & 0xff, fp);
    putc((d >> 8*3) & 0xff, fp);
}

static void save_bmp24(FILE *fp, int left, int bottom, int width, int height)
{
    GLubyte *buf;
    GLint cur_alignment;
    int x, y;
 
    if (!(buf = (GLubyte *) malloc(sizeof(GLubyte)*width*height*3))) {
	fprintf(stderr, "cannot allocate image buffer\n"); return;
    }
    glGetIntegerv(GL_PACK_ALIGNMENT, &cur_alignment);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadPixels(left, bottom, width, height, GL_RGB, GL_UNSIGNED_BYTE, buf);
    glPixelStorei(GL_PACK_ALIGNMENT, cur_alignment);

    /* Header */
    fputs("BM", fp);      // bfType
    fput4c(14 + 40 + (3*width+width%4)*height, fp);  // bfSize
    fput2c(0,  fp);       // bfReserved1
    fput2c(0,  fp);       // bfReserved2
    fput4c(14 + 40, fp);  // bfOffBits

    fput4c(40, fp);       // biSize
    fput4c(width,  fp);   // biWidth
    fput4c(height, fp);   // biHeight
    fput2c(1,  fp);       // biPlanes
    fput2c(24, fp);       // biBitCount
    fput4c(0,  fp);       // biCompression
    fput4c(0,  fp);       // biSizeImage
    fput4c(2835, fp);     // biXPelsPerMeter
    fput4c(2835, fp);     // biYPelsPerMeter
    fput4c(0,  fp);       // biClrUsed
    fput4c(0,  fp);       // biClrImportant

    /* Image */
    for (y = 0; y < height; y++) {
	for (x = 0; x < width; x++) {
	    putc(buf[(y*width+x)*3+2], fp);      /* blue  */
	    putc(buf[(y*width+x)*3+1], fp);      /* green */
	    putc(buf[(y*width+x)*3+0], fp);      /* red   */
	}
	while ((x--)%4 != 0) { putc('\0', fp); } /* padding */
    }

    free(buf);
}

void SaveImageAs(const char *fname)
{
    FILE *fp;
    int	width  = glutGet((GLenum) GLUT_WINDOW_WIDTH);
    int height = glutGet((GLenum) GLUT_WINDOW_HEIGHT);

    if (!(fp = fopen(fname, "wb"))) {
	fprintf(stderr, "can't open %s\n", fname); return; 
    }
    //printf("Saving Image to \"%s\"... ", fname); fflush(stdout);
    save_bmp24(fp, 0, 0, width, height);
    //printf("Done!\n");
    fclose(fp);
}
