/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "GUI/AdsrComponent.h"
#include "GUI/OscComponent.h"
#include "GUI/FMComponent.h"
#include "GUI/LFOComponent.h"
#include "GUI/MeterComponent.h"
#include "GUI/ReverbComponent.h"


//=======================================================================================
/**
*/
class NewProjectAudioProcessorEditor  : public juce::AudioProcessorEditor, juce::Timer
{
public:
    NewProjectAudioProcessorEditor (NewProjectAudioProcessor&);
    ~NewProjectAudioProcessorEditor() override;

 
    void paint (juce::Graphics&) override;
    void resized() override;
    void timerCallback() override;

private:
    NewProjectAudioProcessor& audioProcessor;
    OscComponent osc1;
    OscComponent osc2;
    AdsrComponent adsr;
    AdsrComponent filterAdsr;
    FMComponent filter;
    LFOComponent lfo1;
    ReverbComponent reverb;
    MeterComponent meter;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NewProjectAudioProcessorEditor)
};
