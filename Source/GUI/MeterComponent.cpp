/*
  ==============================================================================

    MeterComponent.cpp
    Created: 4 Aug 2021 2:42:19pm
    Author:  rodzi

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MeterComponent.h"

//==============================================================================
MeterComponent::MeterComponent(NewProjectAudioProcessor& p) : audioProcessor (p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

MeterComponent::~MeterComponent()
{
}

void MeterComponent::paintOverChildren(juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(20, 35).translated(0, 10);
    auto leftMeter = bounds.removeFromTop(bounds.getHeight() / 2).reduced(0, 5);
    auto rightMeter = bounds.reduced(0, 5);

    g.setColour(juce::Colour::fromRGB(0, 190, 255));
    const std::atomic<float>& rms = audioProcessor.getRMS();
    auto rmsLevel = juce::jmap<float>(rms.load(), 0.0f, 1.0f, 0.1f, leftMeter.getWidth());

    g.fillRoundedRectangle(leftMeter.getX(), leftMeter.getY(), rmsLevel, leftMeter.getHeight(), 5);
    g.fillRoundedRectangle(rightMeter.getX(), rightMeter.getY(), rmsLevel, rightMeter.getHeight(), 5);

    g.setColour(juce::Colour::fromRGB(0, 255, 255).withAlpha(0.5f));
    const std::atomic<float>& peak = audioProcessor.getPeak();
    auto peakLevel = juce::jmap<float>(peak.load(), 0.0f, 1.0f, 0.1f, rightMeter.getWidth());

    g.fillRoundedRectangle(leftMeter.getX(), leftMeter.getY(), peakLevel, leftMeter.getHeight(), 5);
    g.fillRoundedRectangle(rightMeter.getX(), rightMeter.getY(), peakLevel, rightMeter.getHeight(), 5);

    g.setColour(juce::Colour::fromRGB(0, 255, 255));
    g.drawRoundedRectangle(leftMeter.toFloat(), 5, 2.0f);
    g.drawRoundedRectangle(rightMeter.toFloat(), 5, 2.0f);
}

void MeterComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
