/*
  ==============================================================================

    LFOComponent.cpp
    Created: 4 Aug 2021 2:42:08pm
    Author:  rodzi

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LFOComponent.h"

//==============================================================================
LFOComponent::LFOComponent(juce::AudioProcessorValueTreeState& apvts, juce::String lfoFreqId, juce::String lfoDepthId)
    : lfoFreq("LFO Freq", lfoFreqId, apvts, dialWidth, dialHeight)
    , lfoDepth("LFO Depth", lfoDepthId, apvts, dialWidth, dialHeight)
{
    addAndMakeVisible(lfoFreq);
    addAndMakeVisible(lfoDepth);
}

LFOComponent::~LFOComponent()
{
}

void LFOComponent::resized()
{
    const auto width = 70;
    const auto height = 88;
    const auto startY = 40;

    lfoFreq.setBounds(18, startY, width, height);
    lfoDepth.setBounds(90, startY, width, height);
}
