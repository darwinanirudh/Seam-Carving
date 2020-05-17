#include "sc.h"

using namespace cv;
using namespace std;

#define MAXR 2000
#define MAXC 2000


int seam[MAXR][MAXC];
int direction[MAXR][MAXC];
int nextpixel[MAXR][MAXC];


Mat contructEnergyMatrix(Mat inImage)
{
	
	  int rows = inImage.rows;
	  int column = inImage.cols;

	  Mat energyMatrix = Mat(rows, column, CV_32S);
    
    	for(int i = 0;i < column;i++)
		{
      	for(int j = 0;j < rows;j++)
		  {
          int energy = 0;
        
		     if(i > 0)
			{
				 	if(i + 1 > column)
				 	{
				 		energy = energy + abs((int)inImage.at<uchar>(j,i + 1) - (int)inImage.at<uchar>(j,i - 1));
					}
					else
					{
						energy = energy + abs((int)inImage.at<uchar>(j,i) - (int)inImage.at<uchar>(j,i - 1));
					}
			}   
             else
			{
			 	 energy = energy + abs((int)inImage.at<uchar>(j,i));
			}   
			
			
                
            if( j > 0)
			{
					if(j + 1 > rows)
				 	{
				 		energy = energy + abs((int)inImage.at<uchar>(j + 1,i) - (int)inImage.at<uchar>(j - 1,i));
					}
					else
					{
					 energy = energy + abs((int)inImage.at<uchar>(j,i) - (int)inImage.at<uchar>(j - 1,i));
           
					}
			}    
            else
			{
				energy = energy + abs((int)inImage.at<uchar>(j,i));	
			}    
        	
			energyMatrix.at<int>(j,i) = energy;
        }
    }
    
    return energyMatrix;
}

Mat contructEnergyMatrixHorizontal(Mat inImage)
{
	
	  int rows = inImage.rows;
	  int column = inImage.cols;

	  Mat energyMatrix = Mat(rows, column, CV_32S);
    
    	for(int i = 0;i < column;i++)
		{
      	for(int j = 0;j < rows;j++)
		  {
          int energy = 0;
        
		     if(i > 0)
			{
				 	if(i + 1 > column)
				 	{
				 		energy = energy + abs((int)inImage.at<uchar>(j,i + 1) - (int)inImage.at<uchar>(j,i - 1));
					}
					else
					{
						energy = energy + abs((int)inImage.at<uchar>(j,i) - (int)inImage.at<uchar>(j,i - 1));
					}
			}   
             else
			{
			 	 energy = energy + abs((int)inImage.at<uchar>(j,i));
			}   
			
			
                
            if( j > 0)
			{
					if(j + 1 > rows)
				 	{
				 		energy = energy + abs((int)inImage.at<uchar>(j + 1,i) - (int)inImage.at<uchar>(j - 1,i));
					}
					else
					{
					 energy = energy + abs((int)inImage.at<uchar>(j,i) - (int)inImage.at<uchar>(j - 1,i));
           
					}
			}    
            else
			{
				energy = energy + abs((int)inImage.at<uchar>(j,i));	
			}    
        	
			energyMatrix.at<int>(j,i) = energy;
        }
    }
    
    return energyMatrix;
}



void remove_vertical(Mat &inImage, int col){
    
		int c = inImage.cols;
        int column = c, row = inImage.rows;
    	Mat grayImage,energyMat;
    	
	
	//cout<<"Inside vertical"<<endl;
    
	for(int i = 0; i < c - col; i++){
        cvtColor(inImage, grayImage, CV_BGR2GRAY);
        energyMat = contructEnergyMatrix(grayImage);
        
        int r = energyMat.rows;
        int c = energyMat.cols;
        
        for(int i = 0 ; i < r ; i ++)
        {
        	for(int j = 0 ; j < c ; j ++)
        	{
        
        		//cout<<" i and j "<<i<<":"<<j<<endl;
			}
		}
        
        for(int i = 0; i < column; i++)
	   {        
	    seam[0][i] = energyMat.at<int>(0, i);
        }

        for(int j = 1; j < row; j++)
		{
            for(int i = 0; i < column; i++)
			{
            	
                int val = energyMat.at<int>(j,i);
                seam[i][j] = -1;
                
                if(i > 0)
				{
                    seam[i][j] = val + seam[i - 1][j - 1];
                    nextpixel[i][j] = -1;
                }
                
                if(val + seam[i][j - 1] < seam[i][j] || seam[i][j] == -1){
                    seam[i][j] = val + seam[i][j - 1];
                    nextpixel[i][j] = 0;
                }
                
                if(i + 1 < column)
				{
		     		if(val + seam[i + 1][j - 1] < seam[i][j] || seam[i][j] == -1 )
					   {
			                    seam[i][j] = val + seam[i + 1][j - 1];
			                    nextpixel[i][j] = 1;
					   }
                }
            }
        }
        
        
        int best = seam[0][row - 1];
        int pos = 0;
        
        for(int i = 0; i < column; i++)
		{
            if(seam[i][row - 1] < best)
			{
                best = seam[i][row - 1];
                pos = i;
            }
        }
        
    
        
        Mat_<Vec3b> out(row,column - 1);
        
   		for(int j = row - 1; j >= 0 ; j--){
         
	
	  int counter = 0;
	 
	  for(int i = 0; i < column; i++)
	  {
				
			if(i == pos)
			{
				continue;			
			}
			else
			{
				out.at<Vec3b>(j,counter) = inImage.at<Vec3b>(j,i);

				counter++;
			}
	  	}

		if(j > 0)
		{
		pos = pos + nextpixel[pos][j];
		}
	}
       
        inImage = out;
        --column;
    }
}

   
   void remove_horizontal(Mat &inImage, int r){

    inImage = inImage.t();
    remove_vertical(inImage, r);
    inImage = inImage.t();
	Mat grayImage,energyMat;

	
    
	int row = inImage.rows,cols = inImage.cols;
    int rows = row,column = cols;
   
   
    
    
    for(int i = 0;i < row - r;i++)
	{
        cvtColor(inImage,grayImage,CV_BGR2GRAY);
        energyMat = contructEnergyMatrixHorizontal(grayImage);
        
        	for(int y = 0;y < rows;y++)
        	{
		    seam[0][y] = energyMat.at<int>(y,0);
        	}
             for(int x = 1;x < column;x++)
			 {
            
			 for(int y = 0;y < rows;y++)
			 {
            	
            	int val = energyMat.at<int>(y,x);
            	 direction[x][y] = -1;
            	 
            	
            	
            	
            	 
            	if(y > 0 )
				{
                    seam[x][y] = val + seam[x - 1][y - 1];
                    direction[x][y] = -1;
                }

                if(val + seam[x - 1][y] < seam[x][y] || seam[x][y] == -1 )
				{
                    seam[x][y] = val + seam[x - 1][y];
                    direction[x][y] = 0;
                }

                if(y + 1 < rows) 
				{
				
				if (seam[x][y] == -1 || val + seam[x - 1][y + 1] < seam[x][y])
				{
                    seam[x][y] = val + seam[x - 1][y + 1];
                    direction[x][y] = 1;
            	}
				}
            	
            }
        }
            
        int best = seam[column - 1][0];
        int pos = 0;

        for(int y = 0;y < rows;y++)
		{
            if(seam[column - 1][y] < best)
			{
                best = seam[column - 1][y];
                pos = y;
            }
        }
		
		Mat_<Vec3b> out(rows - 1,column);

        for(int x = column - 1;x >= 0;x--)
		{
        	int counter = 0;
            for(int i = 0;i < rows;i++)
			{
          	if(i == pos)
			{
				continue;			
			}
			else
			{
				out.at<Vec3b>(counter,x) = inImage.at<Vec3b>(x,i);

				counter++;
			}

            }

            	if(x > 0)
            	{
				pos = pos + seam[x][pos];
				}
        }

        inImage = out;
        --rows;
		
		
   	}

	
}
