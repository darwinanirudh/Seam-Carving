#include <opencv2/opencv.hpp>
#include "sc.h"

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
	
	time_t tt;
    struct tm * ti; 
    time (&tt); 
	ti = localtime(&tt); 
     
	 cout << "Start time is :  "  << asctime(ti)<<endl;
	 
    if(argc!=5){
        cout<<"Usage: ../sc input_image new_width new_height output_image"<<endl;
        return -1;
    }
    
    Mat in_image;
    in_image = imread(argv[1]/*, CV_LOAD_IMAGE_COLOR*/);
   
    if(!in_image.data)
    {
        cout<<"Could not load input image!!!"<<endl;
        return -1;
    }

    if(in_image.channels()!=3){
        cout<<"Image does not have 3 channels!!! "<<in_image.depth()<<endl;
        return -1;
    }
    
    int new_width = atoi(argv[2]);
    int new_height = atoi(argv[3]);

    int inImageHeight = in_image.rows;
    int inImageWidth = in_image.cols;
    
    
    Mat out_image =  in_image.clone();

	if(new_width <= inImageWidth)
        remove_vertical(out_image, new_width);
    else
        cout<<" The desired width is greater than the image width "<<endl;
 
	if(new_height <= inImageHeight)
        remove_horizontal(out_image, new_height);
    else
        cout<<" The desired height is greater than the image height"<<endl;
        
        
    time_t t2;
    struct tm * t2i; 
    time (&t2); 
	t2i = localtime(&t2); 
     
    cout <<"End time is :  "  << asctime(t2i)<<endl;
	cout<<"End of the program"<<endl;
	   
		    
	imwrite( argv[4], out_image);
	
    
    namedWindow( "Original image", WINDOW_AUTOSIZE );
    namedWindow( "Seam Carved Image", WINDOW_AUTOSIZE );
    imshow( "Original image", in_image );
    imshow( "Seam Carved Image", out_image );
    waitKey(0);
    return 0;
}
