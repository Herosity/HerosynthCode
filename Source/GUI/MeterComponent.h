/*
  ==============================================================================

    MeterComponent.h
    Created: 4 Aug 2021 2:42:19pm
    Author:  rodzi

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../PluginProcessor.h"
#include "CustomComponent.h"    

//==============================================================================
/*
*/
class MeterComponent  : public CustomComponent
{
public:
    MeterComponent(NewProjectAudioProcessor& p);
    ~MeterComponent() override;

    void paintOverChildren (juce::Graphics& g) override;
    void resized() override;

private:
    NewProjectAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MeterComponent)
};
