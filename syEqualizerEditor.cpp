/*
  ==============================================================================

    syEqualizer
	
	syEqualizerEditor.h
	
	created by syor - March 2014

	 * Contents:
     1. Constructor and destructor
     2. Open and close functions
     3. Functions to make some bands blue or gray
     4. Parameter-related functions

  ==============================================================================
*/


#include "syEqualizerProcessor.h"
#include "syEqualizerEditor.h"


//==============================================================================
SyEqualizerAudioProcessorEditor::SyEqualizerAudioProcessorEditor (SyEqualizerAudioProcessor* ownerFilter)
    : AudioProcessorEditor (ownerFilter)
{
    // This is where our plugin's editor size is set.
    setSize (400, 300);
}

SyEqualizerAudioProcessorEditor::~SyEqualizerAudioProcessorEditor()
{
}

//==============================================================================
void SyEqualizerAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::white);
    g.setColour (Colours::black);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!",
                      0, 0, getWidth(), getHeight(),
                      Justification::centred, 1);
}
