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

