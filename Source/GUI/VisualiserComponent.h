/*
  ==============================================================================

    VisualiserComponent.h
    Created: 10 Aug 2021 6:27:48pm
    Author:  rodzi

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "CustomComponent.h" 

//==============================================================================
/*
*/
class VisualiserComponent  : public juce::AudioVisualiserComponent
{
public:
    VisualiserComponent() : AudioVisualiserComponent(2)
    {
        setBufferSize(1024); //how fast
        setSamplesPerBlock(64); //how much info
        setColours(juce::Colour(50, 50, 50), juce::Colour(0, 255, 255));

    }

private:
};
