#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct rgb_data{
		float r, g, b;
} rgb_data;

void save_bitmap(const char *file_name, int width, int height, int dpi, rgb_data *pixel_data){
	FILE *image;
	int image_size = width * height;
	int file_size = 54 + 4 * image_size;
	int ppm = dpi * 39.375;

	struct bitmap_file_header {
		unsigned char   bitmap_type[2];     // 2 bytes
		int             file_size;          // 4 bytes
		short           reserved1;          // 2 bytes
		short           reserved2;          // 2 bytes
		unsigned int    offset_bits;        // 4 bytes
	} bfh;

	struct bitmap_image_header {
		unsigned int    size_header;        // 4 bytes
		unsigned int    width;              // 4 bytes
		unsigned int    height;             // 4 bytes
		short int       planes;             // 2 bytes
		short int       bit_count;          // 2 bytes
		unsigned int    compression;        // 4 bytes
		unsigned int    image_size;         // 4 bytes
		unsigned int    ppm_x;              // 4 bytes
		unsigned int    ppm_y;              // 4 bytes
		unsigned int    clr_used;           // 4 bytes
		unsigned int    clr_important;      // 4 bytes
	} bih;

	memcpy(&bfh.bitmap_type, "BM", 2);
	bfh.file_size       = file_size;
	bfh.reserved1       = 0;
	bfh.reserved2       = 0;
	bfh.offset_bits     = 0;

	bih.size_header     = sizeof(bih);
	bih.width           = width;
	bih.height          = height;
	bih.planes          = 1;
	bih.bit_count       = 24;
	bih.compression     = 0;
	bih.image_size      = file_size;
	bih.ppm_x           = ppm;
	bih.ppm_y           = ppm;
	bih.clr_used        = 0;
	bih.clr_important   = 0;

	image = fopen(file_name, "wb");
	fwrite(&bfh, 1, 14, image);
	fwrite(&bih, 1, sizeof(bih), image);	

	for (int i = 0; i < image_size; i++){

	rgb_data BGR = pixel_data[i];

	float red   = (BGR.r);
	float green = (BGR.g);
	float blue  = (BGR.b);

	unsigned char color[3] = {
		blue, green, red
	};

	fwrite(color, 1, sizeof(color), image);
	}

	fclose(image);
}

int main(){

	int width  = 1000, height = 1000, dpi = 600;

	rgb_data *pixels = (rgb_data *)malloc(width * height* 3*sizeof(float));

	int numberline_length = 4;
	double divisions = 1000/8;

	//color the backgorund black
	for(int x = 0; x < width; x++) {
		for(int y = 0; y < height; y++) {
			int a = y * width + x;

				pixels[a].r = 24;
				pixels[a].g = 25;
				pixels[a].b = 26;
			
				// pixels[a].r = 55;
				// pixels[a].g = 55;
				// pixels[a].b = 55;
		}
	}

	
	for(int x = 0; x < width; x++){
		double number_line_x = (x/divisions)-numberline_length;
		double number_line_y = sin(number_line_x);
		int y = round((number_line_y+numberline_length)*divisions) ;
		if(y<=1000 && y>=0){
			int a = y * width + x;

			pixels[a].r = 255;
			pixels[a].g = 255;
			pixels[a].b = 255;
		}
	}

	for(int x = 0; x < width; x++){
		double number_line_y = 0;
		int y = round((number_line_y+numberline_length)*divisions) ;
		if(y<=1000 && y>=0){
			int a = y * width + x;

			pixels[a].r = 255;
			pixels[a].g = 255;
			pixels[a].b = 255;
		}
	}

	for(int y = 0; y < height; y++){
		double number_line_x = 0;
		int x = round((number_line_x+numberline_length)*divisions) ;
		if(x<=1000 && x>=0){
			int a = y * width + x;

			pixels[a].r = 255;
			pixels[a].g = 255;
			pixels[a].b = 255;
		}
	}


	save_bitmap("fucntion.bmp", width, height, dpi, pixels);
	free(pixels);
 	
	return 0;
}
