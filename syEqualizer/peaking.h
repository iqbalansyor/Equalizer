/*
  ==============================================================================

    syEqualizer
	
	peaking.h
	
	created by syor - March 2014

	* Creates a biquad peaking filter (2 poles, 2 zeros).
	* You can use peakinghandler.cpp to handle multiple peaking filters in series.
	* That way it creates an equalizer.
  ==============================================================================
*/

#include <math.h>
#define min(a, b)  (((a) < (b)) ? (a) : (b))
#define max(a, b)  (((a) > (b)) ? (a) : (b))

class peaking
{
    public:
    peaking();
    peaking( float freq, float BW, float peak);
    ~peaking();
    
    void setFreq(float freq);
    void setBW(float BW);
    void setPeak(float peak);
    void setGain(float gain);

	float H(float z);   //calculate frequency response for z = {1, -1}
						// (well, actually for all z on the unit circle, but C++ doesn't support complex numbers)
	void calc();

    void processL(float in);
    void processR(float in);
    
    private:
   
    float f;        //center frequency
    float b;        //bandwidth
    float p;        //peak
    float pi;
    
    float c;        //cos(f)
    float absz;     //abs(z)
    float absp;     //abs(p)
    
    float xl1, xl2; //x[n-1] and x[n-2] for the left channel
    float yl1, yl2; //y[n-1] and y[n-2]
    
    float xr1, xr2; //x[n-1] and x[n-2] for the right channel
    float yr1, yr2; //y[n-1] and y[n-2]
    
    float a1, a2;
    float b1, b2;
    float gain;
    float mainGain;

    bool fSet;
    bool bSet;
    bool pSet;
    bool canfilter;
};