/*
  ==============================================================================

    OscComponent.cpp
    Created: 25 Jul 2021 4:02:57pm
    Author:  rodzi

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscComponent.h"

//==============================================================================
OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String oscId, juce::String gainId, juce::String pitchId, juce::String fmFreqId, juce::String fmDepthId)
    : gain("Gain", gainId, apvts, dialWidth, dialHeight)
    , pitch("Pitch", pitchId, apvts, dialWidth, dialHeight)
    , fmFreq("FM Freq", fmFreqId, apvts, dialWidth, dialHeight)
    , fmDepth("FM Depth", fmDepthId, apvts, dialWidth, dialHeight)
{
    juce::StringArray oscChoices{ "Sine", "Saw", "Square" };
    oscSelector.addItemList(oscChoices, 1);
    oscSelector.setSelectedItemIndex(0);
    oscSelector.setColour(juce::ComboBox::ColourIds::backgroundColourId, juce::Colour::fromRGB(60, 60, 60));
    oscSelector.setColour(juce::ComboBox::ColourIds::textColourId, juce::Colour::fromRGB(255, 100, 23));
    oscSelector.setColour(juce::ComboBox::ColourIds::outlineColourId, juce::Colour::fromRGB(60, 60, 60));
    oscSelector.setColour(juce::ComboBox::ColourIds::buttonColourId, juce::Colour::fromRGB(60, 60, 60));
    oscSelector.setColour(juce::ComboBox::ColourIds::arrowColourId, juce::Colour::fromRGB(255, 100, 23));
    oscSelector.setColour(juce::ComboBox::ColourIds::focusedOutlineColourId, juce::Colour::fromRGB(60, 60, 60));
    addAndMakeVisible(oscSelector);

    oscSelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, oscId, oscSelector);

    addAndMakeVisible(gain);
    addAndMakeVisible(pitch);
    addAndMakeVisible(fmFreq);
    addAndMakeVisible(fmDepth);
}

OscComponent::~OscComponent()
{
}

void OscComponent::resized()
{
    const auto yStart = 90;
    const auto width = 70;
    const auto height = 88;

    oscSelector.setBounds(15, 50, 100, 25);
    gain.setBounds(130, yStart, width, height);
    pitch.setBounds(200, yStart, width, height);
    fmFreq.setBounds(270, yStart, width, height);
    fmDepth.setBounds(340, yStart, width, height);
}
