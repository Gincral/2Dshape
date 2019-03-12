/*
 *  file: file.cpp
 */
#include "file.hpp"

extern GLsizei winWidth;
extern GLsizei winHeight;
extern GLint counter;
extern node *front, *back;

int SaveBitmap(const char *filename, int nX, int nY, int nWidth, int nHeight) {
	BITMAPFILEHEADER bf;
	BITMAPINFOHEADER bi;

	unsigned char *image_ptr = (unsigned char*) malloc(
			sizeof(unsigned char) * nWidth * nHeight * 3
					+ (4 - (3 * nWidth) % 4) * nHeight);
	if (image_ptr == NULL)
		return EXIT_FAILURE;

	FILE *fptr = fopen(filename, "wb");

	if (fptr == NULL) {
		free(image_ptr);
		return EXIT_FAILURE;
	}

	//read pixels from framebuffer
	glReadPixels(nX, nY, nWidth, nHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE,
			image_ptr);

	//clear memory buffer for bitmap header and information header
	memset(&bf, 0, sizeof(bf));
	memset(&bi, 0, sizeof(bi));

	// configure the header with the give parameters
	bf.bfType = 0x4d42;
	bf.bfSize = sizeof(bf) + sizeof(bi) + nWidth * nHeight * 3
			+ (4 - (3 * nWidth) % 4) * nHeight;
	bf.bfOffBits = sizeof(bf) + sizeof(bi);
	bi.biSize = sizeof(bi);
	bi.biWidth = nWidth + nWidth % 4;
	bi.biHeight = nHeight;
	bi.biPlanes = 1;
	bi.biBitCount = 24;
	bi.biSizeImage = nWidth * nHeight * 3 + (4 - (3 * nWidth) % 4) * nHeight;

	// to file
	fwrite(&bf, sizeof(bf), 1, fptr);
	fwrite(&bi, sizeof(bi), 1, fptr);
	fwrite(image_ptr, sizeof(unsigned char),
			nWidth * nHeight * 3 + (4 - (3 * nWidth) % 4) * nHeight, fptr);
	fclose(fptr);
	free(image_ptr);

	return EXIT_SUCCESS;
}

int save_svg(node *front, const char *filename) {

	FILE *outFile = fopen(filename, "w");

	char tmp[500];
	int objWidth, objHeight; //store calculated height and width

	//write header data for SVG
	sprintf(tmp, "<?xml version=\"1.0\" standalone=\"no\"?>\n");
	fputs(tmp, outFile);
	sprintf(tmp, "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"\n");
	fputs(tmp, outFile);
	sprintf(tmp, "\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n");
	fputs(tmp, outFile);
	sprintf(tmp,
			"<svg width=\"%d\" height=\"%d\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">\n",
			winWidth, winHeight);
	fputs(tmp, outFile);

	//scan through objects
	int topX, topY; //holds to pt at the top left corner

	node *p = front;
	shape *sp = NULL;

	while (p) {
		sp = p->sp;
		if (sp->t == 1) {
			if (sp->x2 >= sp->x1) //(x1,y1) are top left corner
					{
				//calculate width & height based on x2>x1
				objWidth = sp->x2 - sp->x1;
				topX = sp->x1;
			} else {
				//calculate width & height based on x2<x1
				objWidth = sp->x1 - sp->x2;
				topX = sp->x2;
			}

			if (sp->y2 >= sp->y1) //(x1,y1) are top left corner
					{
				objHeight = sp->y2 - sp->y1;
				topY = sp->y1;
			} else {
				objHeight = sp->y1 - sp->y2;
				topY = sp->y2;
			}

			if (sp->s == 1) {
				sprintf(tmp,
						"<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" style=\"fill:rgb(%d,%d,%d);stroke-width:1;stroke:rgb(%d,%d,%d)\"/>\n",
						topX, topY, objWidth, objHeight, (int) (sp->r * 255),
						(int) (sp->g * 255), (int) (sp->b * 255),
						(int) (sp->r * 255), (int) (sp->g * 255),
						(int) (sp->b * 255));
				fputs(tmp, outFile);
			}
			if (sp->s == 2) {
				sprintf(tmp,
						"<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" style=\"fill:none;stroke-width:1;stroke:rgb(%d,%d,%d)\"/>\n",
						topX, topY, objWidth, objHeight, (int) (sp->r * 255),
						(int) (sp->g * 255), (int) (sp->b * 255));
				fputs(tmp, outFile);
			}

		} else if (sp->t == 2) {
			GLint radius = (GLint) (sqrt(
					pow((sp->x1 - sp->x2), 2) + pow((sp->y1 - sp->y2), 2))); //find radius or circle

			if (sp->s == 1) {
				sprintf(tmp,
						"<circle cx=\"%d\" cy=\"%d\" r=\"%d\" style=\"fill:rgb(%d,%d,%d);stroke-width:1;stroke:rgb(%d,%d,%d)\"/>\n",
						sp->x1, sp->y1, radius, (int) (sp->r * 255),
						(int) (sp->g * 255), (int) (sp->b * 255),
						(int) (sp->r * 255), (int) (sp->g * 255),
						(int) (sp->b * 255));
				fputs(tmp, outFile);
			}
			if (sp->s == 2) {
				sprintf(tmp,
						"<circle cx=\"%d\" cy=\"%d\" r=\"%d\" style=\"fill:none;stroke-width:1;stroke:rgb(%d,%d,%d)\"/>\n",
						sp->x1, sp->y1, radius, (int) (sp->r * 255),
						(int) (sp->g * 255), (int) (sp->b * 255));
				fputs(tmp, outFile);
			}

		}

		p = p->next;
	}

	sprintf(tmp, "</svg>");
	fputs(tmp, outFile);
	fclose(outFile);
}

int open_svg(node **frontp, node **backp, char *filename) {
	char int_chr;
	char prev;
	GLint x1, y1, x2, y2, t, s;
	GLfloat r, g, b;

	FILE* in = fopen(filename, "r");

	do {
		prev = int_chr;
		int_chr = fgetc(in);

		if (int_chr == 'r' && prev == '<') {
			//parse rect
			t = 1;
			fscanf(in,
					"ect x=\" %d \" y=\" %d \" width=\" %d \" height=\" %d \" style=\"fill:",
					&x1, &y1, &x2, &y2);

			x2 += x1; //transform width into x2
			y2 += y1; //trasform height into y2

			if ((int_chr = fgetc(in)) == 'r') {
				fscanf(in, "gb( %f , %f , %f )", &r, &g, &b);
				s = 1;
			} else {
				fscanf(in, "one;stroke-width:1;stroke:rgb( %f , %f , %f )", &r,
						&g, &b);
				s = 2;
			}

			//convert colors back to float
			r = r / 255;
			g = g / 255;
			b = b / 255;

		} else if (int_chr == 'c' && prev == '<') {

			//parse circle
			t = 2;
			fscanf(in, "ircle cx=\" %d \" cy=\" %d \" r=\" %d \" style=\"fill:",
					&x1, &y1, &x2);

			x2 += x1; //transform width into x2
			y2 = y1; //trasform height into y2

			if ((int_chr = fgetc(in)) == 'r') {
				fscanf(in, "gb( %f , %f , %f )", &r, &g, &b);
				s = 1;
			} else {
				fscanf(in, "one;stroke-width:1;stroke:rgb( %f , %f , %f )", &r,
						&g, &b);
				s = 2;
			}

			//convert colors back to float
			r = r / 255;
			g = g / 255;
			b = b / 255;
		}

		insert_back(&front, &back, new_object(x1, y1, x2, y2, t, s, r, g, b));

	} while (int_chr != EOF);

	fclose(in);
}
