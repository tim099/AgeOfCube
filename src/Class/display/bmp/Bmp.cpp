#include <Bmp.h>

Bmp::Bmp(GLuint _tex) {
    w=0,h=0;
    pw=0,ph=0;
    rgb=0;
    tex=_tex;
}
Bmp::~Bmp() {
	if(rgb)free(rgb);
}
#pragma pack( push, 1 )
typedef struct _bmp_header_info{
  unsigned short bfType;
  unsigned int bfSize;
  unsigned short bfReserved1;
  unsigned short bfReserved2;
  unsigned int bfOffBits;
  // bitmap header
  unsigned int biSize;
  int biWidth;
  int biHeight;
  unsigned short biPlanes;
  unsigned short biBitCount;
  unsigned int biCompression;
  unsigned int biSizeImage;
  int biXpelsPerMeter;
  int biYpelsPerMeter;
  unsigned int biClrUsed;
  unsigned int biClrImportant;
} bmp_header_info;
//#pragma pack( pop, 1 )

void Bmp::load( const char *spath ){
  bmp_header_info bhi;
  {
    FILE *f0 = fopen( spath, "rb" );
     if( f0==NULL ){
    	printf( "[Error] Bmp::load, file %s not found.\n", spath );
    	exit(-1);
     }
     fread( &bhi,sizeof(bmp_header_info),1,f0);
    fclose(f0);
  }
  if( bhi.biCompression != 0 ){
    printf( "[Error] GBmp::load, only uncompressed bitmap is supported\n" );
    exit(-1);
  }
  if( bhi.biBitCount != 24 ){
    printf( "[Error] GBmp::load, must be RGB888 bitmap\n" );
    exit(-1);
  }
  if(rgb)free(rgb);
  w = bhi.biWidth;
  h = bhi.biHeight;
  rgb = (unsigned char*) malloc( w*h*3*sizeof(unsigned char) );
  {
    FILE *f0 = fopen( spath, "rb" );
     fseek( f0, bhi.bfOffBits, SEEK_SET );
     int j;
     for( j=0;j<h;j++){
    	 fread( &rgb[j*w*3], sizeof(unsigned char), w*3, f0 );
    	 fseek( f0, (4-w*3%4)%4, SEEK_CUR );
     }
    fclose(f0);
  }
  rb_swap();
}
void Bmp::load( int width, int height){
  if(rgb)free(rgb);
  w = width;
  h = height;
  rgb=(unsigned char*) malloc( w*h*3*sizeof(unsigned char) );
  memset( rgb, 0, w*h*3*sizeof(unsigned char) );
}
void Bmp::prepare_tex(const char *path){
	double sw,sh,tw,th;
    load(path);
    sw = w;
    sh = h;
    Bmp tmp;
    tw = pow(2,ceil(log(w-1)/log(2)));
    th = pow(2,ceil(log(h-1)/log(2)));
    double max=th>tw?th:tw;
    ph=sh/max;
    pw=sw/max;
    tmp.load(max,max);
    for( int j=0;j<h; j++ )memcpy(&tmp.rgb[j*tmp.w*3],&rgb[j*w*3],w*3 );

    if(!tex)glGenTextures(1,&tex );
    glBindTexture(GL_TEXTURE_2D,tex);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
    glTexImage2D( GL_TEXTURE_2D,0,GL_RGB, tmp.w, tmp.h, 0, GL_RGB, GL_UNSIGNED_BYTE, tmp.rgb );
}
void Bmp::rb_swap(){
  unsigned char tmp;
  int i,j;
  for( j=0; j<h; j++ ){
	  for( i=0; i<w; i++ ){
		  tmp = rgb[(j*w+i)*3];
		  rgb[(j*w+i)*3] = rgb[(j*w+i)*3+2];
		  rgb[(j*w+i)*3+2] = tmp;
	  }
  }
}
