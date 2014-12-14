   


#include "individual.h"
#include "png.h"
#include <algorithm>
#include <stdio.h>
#include <vector>
#include <iostream>

#define POPULATION  400
using namespace std;


long calcFitness(const PNG &target,const PNG &image);
Individual crossOver(Individual i1,Individual i2);
bool myfunction (Individual i,Individual j) { return (i.fitness>j.fitness); }
int mutate(Individual &im);

int main(){	


	long MAXFITNESS = 255*255*255*255*255*255*360*397;
	/*
   
	PNG imgOut;
	imgOut.resize(300,300);
		
	int r=40;

	int x=150;

	int y=150;

	RGBAPixel color;

	color.red   =  128;		
	color.blue  =  128;
	color.green =  0;	
	color.alpha =  255;		
	Circle c(r,x,y,color);	

	
	printf("The radius is:%d\n",c.radius);
	printf("The x is:%d\n",c.x);
	printf("The y is:%d\n",c.y);
	printf("The Red is:%d\n",c.color.red);
	printf("The Blue is:%d\n",c.color.blue);
	printf("The Green is:%d\n",c.color.green);
	printf("The Alpha is:%d\n",c.color.alpha);
	c.drawCircle(imgOut);
	imgOut.writeToFile("test1.png");
	
	*/




 /*  PNG target;
   target.readFromFile("target.png");
	double fitworst;
	double fitbest;	
	int indexbest=0;
	int indexbest2=0;
	int indexworst=0;	
	

     Individual pop[POPULATION];
	srand (time(NULL));
   for(int i=0;i<POPULATION;i++){
		
		pop[i].setDimensions(target.width(),target.height());
		pop[i].generateRandomIndividual();
		
		
   }
   for(int i=0;i<500000;i++){
		
		fitworst=0;
		fitbest=(255*255+255*255+255*255)*target.width()*target.height();
		
		indexbest2=0;
		indexworst=0;
		indexbest=0;
		for(int j=0;j<POPULATION;j++){
						
			pop[j].fitness=calcFitness(target,pop[j].drawImage());
			
			if(pop[j].fitness>fitworst){
				fitworst=pop[j].fitness;
				indexworst=j;			
			}
			else if(pop[j].fitness<fitbest){		
				fitbest=pop[j].fitness;
				indexbest2=indexbest;
				indexbest=j;
			}
									
		}
		//printbest

		
		if(i%10==0){
			PNG imgOut=pop[indexbest].drawImage();	
	
			cout<< "Generation: " << i<< " Fitness: "<< pop[indexbest].fitness<<endl;	
			imgOut.writeToFile("monaAD.png");
		}
			pop[indexworst].generateRandomIndividual();
		
		for(int j=0;j<POPULATION;j++){	
			int random=rand()%2;		
			if((j!=indexbest || j!=indexbest2) && (random==0)){
				pop[j]=crossOver(pop[indexbest],pop[j],target.width(),target.height());
				mutate(pop[j]);	
			}
			if((j!=indexbest || j!=indexbest2) && (random==1)){
				pop[j]=crossOver(pop[indexbest2],pop[j],target.width(),target.height());
				mutate(pop[j]);	
			}
		}

	}*/

	srand (time(NULL));
	PNG target;
	target.readFromFile("target.png");
	
	
	
	/*PNG targeti;
	targeti.readFromFile("targeti.png");
	
	long MAX = calcFitness(target,targeti);
	
	cout<<MAX<<endl;*/

    vector<Individual> pop;
    pop.resize(POPULATION);

   for(int i=0;i<POPULATION;i++)
   {	
		pop[i].setDimensions(target.width(),target.height());
		pop[i].generateRandomIndividual();	
   }
   int generation = 0;
   
   
   
   while(1)
   {
		for(int j=0;j<POPULATION;j++)
		{
			pop[j].fitness=calcFitness(target,pop[j].drawImage());
		}
    generation++;
    sort(pop.begin(), pop.end(), myfunction);
    int j = 399;
    for(int i = 0; i < POPULATION-40; i++)
    {
        int x = rand()%40;
        pop[i] = crossOver(pop[j], pop[359+x]);
        if(i & 1)
        {
            j--;
        }
        mutate(pop[i]);
    }
	
	if(generation%5==0)
	{
        PNG imgOut = pop[399].drawImage();    
       
         cout<< "Generation: " << generation << " Fitness: "<< (pop[399].fitness / MAXFITNESS) << endl;  
         imgOut.writeToFile("MONA_LISA_LONG.png");
		}
	if(generation==10000){
			
		for(int i=0; i< 400; i++){
	        PNG imgOut = pop[i].drawImage();    
       
	         
			 string result;
			 std::stringstream sstm;
			 sstm << "pop2/MONA_" << i<<".png";
			 result = sstm.str();
	         imgOut.writeToFile(result);
		}
		
	}	

   }

/*	PNG target;
   	target.readFromFile("target.png");
	
	

    	Individual best;
	 	Individual child;
	
		best.setDimensions(target.width(),target.height());
		best.generateRandomIndividual();

		child=best;

	

	for(int i=0;i<500000;i++){

		best.fitness=calcFitness(target,best.drawImage());
		child.fitness=calcFitness(target,child.drawImage());

		if(best.fitness<=child.fitness){
			child=best;
			mutate(child);
		}else{
			best=child;
			mutate(child);					
		}

		
		if(i%200==0){
		PNG imgOut=best.drawImage();	
	
		cout<< "Generation: " << i<< " Fitness: "<< (1-(best.fitness/MAXFITNESS)) << endl;	
		imgOut.writeToFile("mona2.png");
		}
	}*/


}


long calcFitness(const PNG &target,const PNG &image){

	long fitness = 0;
	
	for(int x=0;x<target.width();x++){
		for(int y=0;y<target.height();y++){	
		
	
		  fitness += (((double)(target(x,y)->red) - (double)(image(x,y)->red))*((double)(target(x,y)->red) - (double)(image(x,y)->red)));
          fitness += (((double)(target(x,y)->green) - (double)(image(x,y)->green))*((double)(target(x,y)->green) - (double)(image(x,y)->green)));
          fitness += (((double)(target(x,y)->blue) - (double)(image(x,y)->blue))*((double)(target(x,y)->blue) - (double)(image(x,y)->blue)));

		}
	}

	return fitness;
}
Individual crossOver(Individual i1,Individual i2){

	vector<Circle> c;
	c.resize((int)((i1.chromosome.size()+i2.chromosome.size())/2));
	
	
	if(i1.chromosome.size()==i2.chromosome.size()){
		
		for(int i=0;i<i1.chromosome.size();i++){
			
			
			if(rand()& 1){
				c[i]=i1.chromosome[i];
			}else{
				c[i]=i2.chromosome[i];
			}
		}
	
	}	

	if(i1.chromosome.size()>i2.chromosome.size()){
		
		for(int i=0;i<i2.chromosome.size();i++){
			
			
			if(rand()& 1){
				c[i]=i1.chromosome[i];
			}else{
				c[i]=i2.chromosome[i];
			}
		}
		for(int i=i2.chromosome.size();i<c.size();i++){
			c[i]=i1.chromosome[i];
		}	
		
	}	
	
	
	if(i1.chromosome.size()<i2.chromosome.size()){
		
		for(int i=0;i<i1.chromosome.size();i++){
			
			
			if(rand()& 1){
				c[i]=i1.chromosome[i];
			}else{
				c[i]=i2.chromosome[i];
			}
		}
		for(int i=i1.chromosome.size();i<c.size();i++){
			c[i]=i2.chromosome[i];
		}	
	}	
	
	
	
	
	Individual i3(c,360,397);
	return i3;
}

int mutate(Individual &im){

    for(int i=0;i<im.chromosome.size();i++){
		
		if((rand()%100)<4)
		{
			int r=(rand()%(360))+5;

			int x=rand()%360;

			int y=rand()%397;

			RGBAPixel color;

			color.red   =  rand()%256;		
			color.blue  =  rand()%256;
			color.green =  rand()%256;	
			color.alpha =  128;		
			Circle c(r,x,y,color);	
			
			im.chromosome.push_back(c);
		}
		if((rand()%160)<8)
		{
			int r=(rand()%(50))+2;

			int x=rand()%360;

			int y=rand()%397;

			RGBAPixel color;

			color.red   =  rand()%256;		
			color.blue  =  rand()%256;
			color.green =  rand()%256;	
			color.alpha =  128;		
			Circle c(r,x,y,color);	
			
			im.chromosome.push_back(c);
		}
			
		if((rand()%100)<5)
		{
			if(im.chromosome.size()>2)
			im.chromosome.erase(im.chromosome.begin()+i);
		}
		if((rand()%100)<5)
		{
		im.chromosome[i].color.red+=(rand()%24)-12;	
		}
		if((rand()%100)<5)
		{
		im.chromosome[i].color.blue+=(rand()%24)-12;	
		}
		if((rand()%100)<5)
		{
		im.chromosome[i].color.green+=(rand()%24)-12;	
		}
		if((rand()%100)<5)
		{
		im.chromosome[i].color.alpha+=(rand()%24)-12;	
		}
		if((rand()%500)<2)
		{
		im.chromosome[i].color.red+=(rand()%256)-128;	
		}
		if((rand()%500)<2)
		{
		im.chromosome[i].color.blue+=(rand()%256)-128;	
		}
		if((rand()%500)<2)
		{
		im.chromosome[i].color.green+=(rand()%256)-128;	
		}
		if((rand()%500)<2)
		{
		im.chromosome[i].color.alpha+=(rand()%256)-128;	
		}
		
		
		
		if((rand()%100)<5)
		{
			im.chromosome[i].x+=(rand()%80)-40;
			if(im.chromosome[i].x<0){
				im.chromosome[i].x=0;
			}
			if(im.chromosome[i].x>360)
			{
				im.chromosome[i].x=360;
			}
			
		}
		
		if((rand()%100)<5)
		{
			im.chromosome[i].y+=(rand()%80)-40;
			if(im.chromosome[i].y<0){
				im.chromosome[i].y=0;
			}
			if(im.chromosome[i].y>397)
			{
				im.chromosome[i].y=397;
			}
			
		}
		
		
		if((rand()%500)<3)
		{
			im.chromosome[i].x+=(rand()%200)-100;
			if(im.chromosome[i].x<0){
				im.chromosome[i].x=0;
			}
			if(im.chromosome[i].x>360)
			{
				im.chromosome[i].x=360;
			}
			
		}
		
		if((rand()%500)<3)
		{
			im.chromosome[i].y+=(rand()%200)-100;
			if(im.chromosome[i].y<0){
				im.chromosome[i].y=0;
			}
			if(im.chromosome[i].y>397)
			{
				im.chromosome[i].y=397;
			}
			
		}
		
		

    }	
    return 0;
}

