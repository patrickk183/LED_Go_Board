struct Color 
{
	double R, G, B;
};

//Percentage is percentage from c1 to c2
Color interpolate(Color c1, Color c2, int percentage) {
	double fraction = (double) percentage/100.0;

	Color c3;
	c3.R = 0;
	c3.G = 0;
	c3.B = 0;


	c3.R = c1.R + (c2.R - c1.R)*fraction;
	c3.G = c1.G + (c2.G - c1.G)*fraction;
	c3.B = c1.B + (c2.B - c1.B)*fraction;

	return c3;
}

// class ChooseColorMenu : public ThreadedCanvasManipulator { 
// public: 
//   ChooseColorMenu(Canvas *m, string arg)  : ThreadedCanvasManipulator(m) {
//   	filename = "../../assets/" + arg;
//   }

//   void Run() {
//   	bool isLeaving = false;
//   	int count = 0;
//   	int percentage = 0;
//   	std::fstream fs(filename.c_str(), std::ios_base::in);
//   	Color c1 = {200, 0, 0};
//   	Color c2 = {0, 200, 0};
//   	Color c3 = {0, 0, 200};
//   	Color display = {0, 0, 0};
//   	Color former = ;
//   	Color latter = ;

//   	while (true) {
//   		if (former == c1) {former = c2; latter = c3;}
//   		if (former == c2) {former = c3; latter = c1;}
//   		if (former == c3) {former = c1; latter = c2;}
// 	    while(percentage != 1000) {
// 	    	for (int i = 0; i < MATRIX_SIZE; ++i) {
// 		        for (int j = 0; j < MATRIX_SIZE; j++) {
// 		        	if (i < 12 && i > 20 && j < 12 && j > 20) {
// 			        	fs >> value;
// 				        if (!fs.good()) break;
// 				        switch (value) {
// 				          case 1:
// 				            canvas()->SetPixel(j, i, 200, 0, 0);
// 				            break;
// 				          case 2:
// 				            canvas()->SetPixel(j, i, 200, 200, 200);
// 				            break;
// 				          default:
// 				            canvas()->SetPixel(j, i, 0, 0, 0);
// 				            break;
// 				        }
// 				    }
// 				    else {
// 				    	display = interpolate(former, latter, percentage);
// 				    	canvas()->SetPixel(j, i, display.R, display.G, display.B);
// 				    }
// 		        }
// 		    }
// 			percentage++;
// 			sleep(.001);
// 			if (isSelected(1)) {
// 				isLeaving = true;
// 				break;
// 			}
// 	    }
// 	    percentage = 0;

// 	    if (isLeaving == true) {
// 	    	break;
// 	    }
// 	}

//     fs.close();
//   }

// private:
// 	string filename;
// };