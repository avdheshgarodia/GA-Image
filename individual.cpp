#include "individual.h"


Individual::Individual(){

	chromosome.resize(1);
}

Individual::Individual(int w,int h,int DnaSize){
	
	width=w;
	height=h;

	chromosome.resize(DnaSize);
		
}
Individual::Individual(vector<Circle> c,int w,int h){
		

	width=w;
	height=h;
	chromosome=c;

}
Individual::Individual(Individual const &other){
	
	width=other.width;	
 	height=other.height;
	fitness=other.fitness;
	chromosome=other.chromosome;
}	
Individual const & Individual::operator=(Individual const &other){

	if(this!=&other){
		width=other.width;	
 		height=other.height;
		fitness=other.fitness;
		chromosome=other.chromosome;
	}
	return  *this;
}

bool Individual::operator<(Individual const &other)
{
	return (fitness < other.fitness);
}

void Individual::setDimensions(int w,int h){

	width = w;
	height = h;
}

void Individual::generateRandomIndividual(){

			

		int r=(rand()%(width*2))+15;

		int x=rand()%width;

		int y=rand()%height;

		RGBAPixel color;

		color.red   =  rand()%256;		
		color.blue  =  rand()%256;
		color.green =  rand()%256;	
		color.alpha =  200;		
		Circle c(r,x,y,color);			
		chromosome[0]=c;
	
}		
PNG Individual::drawImage(){

	PNG image;
	image.resize(width,height);

	for(int i=0; i<chromosome.size();i++){
		chromosome[i].drawCircle(image);		
	}

	return image;
}










