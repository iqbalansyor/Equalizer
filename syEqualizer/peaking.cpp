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

#include "peaking.h"

//-----------------------------------------------------------------------------
// Constructor and destructor
//-----------------------------------------------------------------------------
peaking::peaking()
{
    f = 0.0f;
    b = 0.0f;
    p = 0.0f;
    
    fSet = true;
    bSet = true;
    pSet = true;
    
    xl1 = xl2 = 0.0f;
    yl1 = yl2 = 0.0f;
    xr1 = xr2 = 0.0f;
    yr1 = yr2 = 0.0f;

    pi = 3.14159265f;

	calc();
}


//-----------------------------------------------------------------------------
peaking::~peaking()
{
    //delete all dynamic variables
}

//-----------------------------------------------------------------------------
void peaking::setFreq(float freq)
{
    f = freq;
    c = cos(2.0f * pi * f);
    fSet = true;
    if (bSet && pSet) calc();
}

//-----------------------------------------------------------------------------
void peaking::setBW(float BW)
{
    b = BW;
    bSet = true;
    if (fSet && pSet) calc();
}

//-----------------------------------------------------------------------------
void peaking::setPeak(float peak)
{
    p = peak;
    pSet = true;
    if (fSet && bSet) calc();
}

void peaking::setGain(float gain)
{
	mainGain = gain;
}
//-----------------------------------------------------------------------------
// H(z)
//-----------------------------------------------------------------------------
float peaking::H(float z)
{
    return (z * z + a1 * z + a2) / (z * z - b1 * z - b2);
}

//-----------------------------------------------------------------------------
// calc() and settings-changing functions
//-----------------------------------------------------------------------------
void peaking::calc()
{
    absz = 1.0f - b*f*p;
    absp = 1.0f - b*f;
    
    a1 = -2 * absz * c;
    a2 = absz * absz;
    b1 = 2 * absp * c;
    b2 = - absp * absp;
    
    if (p > 1.0f)
    {
        gain = 1.0f / min(H(1.0f), H(-1.0f)); //take the minimum...
    }
    else
    {
        gain = 1.0f / max(H(1.0f), H(-1.0f)); //or the maximum...
    }
}

//-----------------------------------------------------------------------------
// peakingfilter() functions
//-----------------------------------------------------------------------------
void peaking::processL(float in)
{
        float out = in + a1 * xl1 + a2 * xl2 + b1 * yl1 + b2 * yl2;
        xl2 = xl1;
        xl1 = in;
        yl2 = yl1;
        yl1 = out;
        in = out * gain *mainGain;
}

//-----------------------------------------------------------------------------
void peaking::processR(float in)
{
        float out = in + a1 * xr1 + a2 * xr2 + b1 * yr1 + b2 * yr2;
        xr2 = xr1;
        xr1 = in;
        yr2 = yr1;
        yr1 = out;
        in = out * gain * mainGain;
}
