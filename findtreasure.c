

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
		FILE *file;
		FILE *file2;
		FILE *file3;

		//open files readable and writable format and its names are taken from command line
		file = fopen(argv[3], "r");
		file2 = fopen(argv[4], "r");
		file3 = fopen(argv[5], "w");

		//take arguments from command line
		int mapline,mapcolumn;
		sscanf(argv[1],"%dx%d",&mapline,&mapcolumn);
		int keysize;
		sscanf(argv[2],"%d",&keysize);

		//make dynamic memory allocation for inputs
		int	**arrayy;
		arrayy = malloc((mapline*mapcolumn)*sizeof(char*));
		int **arrayy2;
		arrayy2 = malloc((keysize*keysize)*sizeof(char*));
		//variables for  for loops
		int i,l,s,f,h;
		//dynamic memory allocations for key and map matrix

		int **matrix;
		matrix = malloc(mapline * sizeof(int *));
		for( i = 0; i < mapline; i++) {
			matrix[i] = malloc(mapcolumn * sizeof(int));

		}
		int **matrix2;
		matrix2 = malloc(keysize * sizeof(int *));
			for(i = 0; i < keysize; i++) {
				matrix2[i] = malloc(keysize * sizeof(int));

			}

		//read inputs to arrays(map and key)
		for (l = 0; l < mapline*mapcolumn; l++){
			fscanf(file, "%d", &arrayy[l]);
		}
		for (s = 0; s< keysize*keysize; s++){
			fscanf(file2, "%d", &arrayy2[s]);
		}

		//send the elements array to matrix
		int z=0;
		for (f = 0; f < mapline; f++){
			for(h=0; h< mapcolumn;h++){
				matrix[f][h]=arrayy[z++];
			}
		}
		int k=0;
		for ( z = 0; z< keysize; z++){
			for(h=0; h< keysize;h++){
				matrix2[z][h]=arrayy2[k++];
			}
		}

		//variable declarations for location in the map matrix
		int line=0;
		int column=0;
		//function findtreasure declaration
		void findtreasure(int **matrix,int **matrix2,int keysize,int line,int column, int mapline, int mapcolumn,FILE *file3);
		//function call
		findtreasure(matrix,matrix2,keysize,line,column,mapline,mapcolumn,file3);
		//free the memory allocations
		free(arrayy);
		free(arrayy2);
		free(matrix);
		free(matrix2);

}

void findtreasure(int **matrix,int **matrix2,int keysize,int line,int column, int mapline, int mapcolumn,FILE *file3){
	//variable which saves the result of matrix multiplication
	int result=0;
	//variable declaration for for loops
	int y,g;
	//this variable for determining the center of the submatrix(normally line and column variables saves the left corner of the submatrix)
	//when you add the difference variable to line and column variable you can find the center of the submatrix
	int difference=(keysize-1)/2;
	//this lines for writing the center of the submatrix to the output file
	fprintf(file3,"%d,",line+difference);
	fprintf(file3,"%d:",column+difference);

	//this variables for multiplication of key and submatrix.this variables takes the location and travels the submatrix for multiplication
	int travelline=line;
	int travelcolumn=column;
	//this two for loop for multiplication of key and submatrix.
	for(y=0;y<keysize;y++){
		travelcolumn=column;
		for(g=0;g<keysize;g++){
			result=result+((matrix[travelline][travelcolumn])*(matrix2[y][g]));
			travelcolumn++;
		}
		travelline++;
	}
	//this lines writes the result of multiplication to the output file
	fprintf(file3,"%d\n",result);
	//this code takes the mode of the result and assign it to the  result
	result=result%5;


	//if the result equals zero than you find the treasure
	if(result==0){
		return;
	}
	//if the result equals zero then go up
	if(result==1){//go up
		//if you can't go up then go down
		if(line-keysize<0){
			findtreasure(matrix,matrix2,keysize,line+keysize,column,mapline,mapcolumn,file3);

		}
		else{
			findtreasure(matrix,matrix2,keysize,line-keysize,column,mapline,mapcolumn,file3);
		}
	}
	//if the result equals two then go down
	if(result==2){//go down
		//if you can't go down then go up
		if(line+keysize>mapline-1){
			findtreasure(matrix,matrix2,keysize,line-keysize,column,mapline,mapcolumn,file3);

		}
		else{
			findtreasure(matrix,matrix2,keysize,line+keysize,column,mapline,mapcolumn,file3);
		}
	}
	//if the result equals three then go right
	if(result==3){//go right
		//if you can't go right then go left
		if(column+keysize>mapcolumn-1){
			findtreasure(matrix,matrix2,keysize,line,column-keysize,mapline,mapcolumn,file3);

		}
		else{
			findtreasure(matrix,matrix2,keysize,line,column+keysize,mapline,mapcolumn,file3);
		}
	}
	//if the result equals four then go left
	if(result==4){//go left
		//if you can't go left then go right
		if(column-keysize<0){
			findtreasure(matrix,matrix2,keysize,line,column+keysize,mapline,mapcolumn,file3);

		}
		else{
			findtreasure(matrix,matrix2,keysize,line,column-keysize,mapline,mapcolumn,file3);
		}
	}
}
