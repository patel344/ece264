#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <libgen.h>
#include <string.h>

#include "answer07.h"

#define TRUE 1
#define FALSE 0

Image* Image_load(const char* filename){
	FILE* fp = NULL;
	size_t read;
	ImageHeader header;
	Image* tmp_im = NULL;
	Image* im = NULL;
	size_t n_bytes = 0;
	int err = FALSE;

	if(!err){
		fp = fopen(filename,"rb");
		if(!fp){
			fprintf(stderr,"Failed to open file '%s'\n",filename);
			err = TRUE;
		}
	}

	if(!err){
		read = fread(&header, sizeof(ImageHeader),1,fp);
		if(read != 1){
			fprintf(stderr,"Failed to read header from '%s'\n",filename);
			err = TRUE;
		}
	}

	if(!err){
		if(!(header.magic_number = ECE264_IMAGE_MAGIC_NUMBER)){
			fprintf(stderr,"Invalid header in '%s'\n",filename);
			err = TRUE;
		}
	}
	if(!err){
		if(!(header.width * header.height)){
			fprintf(stderr,"Invalid header in '%s'\n",filename);
			err = TRUE;
		}
	}
	if(!err){
		if(!(header.comment_len)){
			fprintf(stderr, "Invalid header in '%s'\n",filename);
			err = TRUE;
		}
	}
	if(!err){
		tmp_im = malloc(sizeof(Image));
		if(tmp_im == NULL){
			fprintf(stderr,"Failed to allocate image structure\n");
			err = TRUE;
		}
	}

	if(!err){ //reading comment
		tmp_im -> width = header.width;
		tmp_im -> height = header.height;
		tmp_im -> comment = malloc(header.comment_len * sizeof(char));
		
		if(tmp_im -> comment == NULL){
			fprintf(stderr, "Failed to allocate enough bytes for image data\n");
			err = TRUE;
		}else{
			read = fread(tmp_im -> comment, sizeof(char), header.comment_len, fp);
			if(read != header.comment_len || tmp_im -> comment[header.comment_len] != '\0'){
				fprintf(stderr,"Failed to allocate enough bytes for image data\n");
				err = TRUE;
			}
		}
	}

	if(!err){ //reading pixel data
		n_bytes = sizeof(uint8_t) * header.width * header.height;
		tmp_im -> data = malloc(n_bytes);
		if(tmp_im -> data == NULL){
			fprintf(stderr, "Failed to allocate %zd bytes for image data\n",n_bytes);
			err = TRUE;
		}else{
			read = fread(tmp_im -> data,sizeof(uint8_t),n_bytes,fp);
			if(read != n_bytes){
				fprintf(stderr, "Only read %zd of %zd bytes of image data\n",read,n_bytes);
				err = TRUE;
			}
		}
	}
	if(!err){
		uint8_t byte;
		read = fread(&byte, sizeof(uint8_t),1,fp);
		if(read == 1){
			fprintf(stderr,"Stray bytes at end of file\n");
			err = TRUE;
		}
	}
	if(!err){
		im = tmp_im;
		tmp_im = NULL;
	}
	if(fp){
		fclose(fp);
	}
	return im;
}//end of Image_load function

void linearNormalization(int width,int height, uint8_t * intensity){
	int i;
	uint8_t min = 255;
	uint8_t max = 0;
	ImageHeader header;
	
	for(i= 0; i < (header.height * header.width); i++){
		if(intensity[i] < min){
			min = intensity[i];
		}
		if(intensity[i] > max){
			max = intensity[i];
		}
	}
	for(i= 0; i < (header.height * header.width); i++){
		intensity[i] = (intensity[i] - min) * 255.0 / (max-min);
	}
}//end of linearNormalization

int Image_save(const char* filename, Image* image){
	int err = FALSE;
	FILE* fp = NULL;
	uint8_t* buffer = NULL;
	size_t written = 0;

	//open file for writing
	fp = fopen(filename,"wb");
	if(fp == NULL){
		fprintf(stderr,"Failed to open '%s' for writing \n", filename);
		return FALSE; //no file -> exit
	}

	//number of bytes stored on each row
	size_t bytes_per_row = image -> width;

	//Prepare the header
	ImageHeader header;
	header.magic_number = ECE264_IMAGE_MAGIC_NUMBER;
	header.width = image -> width;
	header.height = image -> height;
	header.comment_len = strlen(image -> comment);

	if(!err){
		written = fwrite(&header,sizeof(ImageHeader),1,fp);
		if(written != 1){
			fprintf(stderr,"Error: only wrote %zd of %zd of file header to '%s'\n",written,sizeof(ImageHeader),filename);
			err = TRUE;
		}
	}
	if(!err){ //write buffer
		buffer = malloc(bytes_per_row);
		if(buffer == NULL){
			fprintf(stderr,"Error:failed to allocate write buffer\n");
			err = TRUE;
		}else{
			memset(buffer,0,bytes_per_row);
		}
	}
	if(!err){ //write pixels
		uint8_t* read_ptr = image -> data;
		int row;
		int col;
		
		for(row = 0; row < header.height && !err; row++){
			uint8_t* write_ptr = buffer;
			for(col = 0; col < header.width; col++){
				*write_ptr++ = *read_ptr;
				read_ptr++; //advance to next pixel
			}
			//written line to file
			written = fwrite(buffer,sizeof(uint8_t),bytes_per_row,fp);
			if(written != bytes_per_row){
				fprintf(stderr,"Failed to write pixel data to file\n");
				err = TRUE;
			}
		}
	}
	free(buffer);
	if(fp){
		fclose(fp);
	}
	return !err;
}//end of Image_save

void Image_free(Image * image){
	free(image -> comment);
	free(image -> data);
	free(image);
}//end of Image_free
