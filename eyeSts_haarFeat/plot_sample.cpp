// Matlab style plot functions for OpenCV by Changbo (zoccob@gmail).

#include "cv.h"
#include "highgui.h"
#include "cvplot.h"

#define rowPtr(imagePtr, dataType, lineIndex) \
	    (dataType *)(imagePtr->imageData + (lineIndex) * imagePtr->widthStep)
void plot_myData( int *a, int *b, int n, char *figName)
{


	// plot and label:
	//
	// template<typename T>
	// void plot(const string figure_name, const T* p, int count, int step = 1,
	//		     int R = -1, int G = -1, int B = -1);
	//
	// figure_name: required. multiple calls of this function with same figure_name
	//              plots multiple curves on a single graph.
	// p          : required. pointer to data.
	// count      : required. number of data.
	// step       : optional. step between data of two points, default 1.
	// R, G,B     : optional. assign a color to the curve.
	//              if not assigned, the curve will be assigned a unique color automatically.
	//
	// void label(string lbl):
	//
	// label the most recently added curve with lbl.
	//

	// specify a line to plot
	int the_line = 1;
    //cout<< "a Value At IDX : " << a[9] << endl;    cout<< "b Value At IDX : " << b[9] << endl;

	int key = -1;
	while (the_line < 50)
	{
		//unsigned char *pb = rowPtr(a, unsigned char, the_line);
		CvPlot::plot(figName, a, n , 1, 255);
		CvPlot::label("Modified_OP"); // similar to legend in Matlab

		CvPlot::plot(figName, b, n, 1, 0, 0, 255);
		CvPlot::label("Final Sts"); // similar to legend in Matlab

		cvWaitKey(0);


		key = cvWaitKey(0);

		if (key != 'q')
		{
			// plot the next line
			the_line++;
			// clear previous plots
			CvPlot::clear(figName);
		}
		else if(key == 27)
		{
			break;
		}
	}
}

