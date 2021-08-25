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
    auto bounds = getLocalBounds().reduced(5, 30).translated(0, 10);
    auto leftMeter = bounds.removeFromTop(bounds.getHeight() / 2).reduced(5, 5);
    auto rightMeter = bounds.reduced(5, 5);

    g.setColour(juce::Colour::fromRGB(40, 40, 40));
    const std::atomic<float>& rms = audioProcessor.getRMS();
    auto rmsLevel = juce::jmap<float>(rms.load(), 0.0f, 1.0f, 0.1f, leftMeter.getWidth());

    g.fillRoundedRectangle(leftMeter.getX(), leftMeter.getY(), std::clamp<float>(rmsLevel, 0.0f, 622.0f), leftMeter.getHeight(), 5);
    g.fillRoundedRectangle(rightMeter.getX(), rightMeter.getY(), std::clamp<float>(rmsLevel, 0.0f, 622.0f), rightMeter.getHeight(), 5);

    g.setColour(juce::Colour::fromRGB(0, 0, 0).withAlpha(0.2f));
    const std::atomic<float>& peak = audioProcessor.getPeak();
    auto peakLevel = juce::jmap<float>(peak.load(), 0.0f, 1.0f, 0.1f, rightMeter.getWidth());

    g.fillRoundedRectangle(leftMeter.getX(), leftMeter.getY(), std::clamp<float>(peakLevel, 0.0f, 622.0f), leftMeter.getHeight(), 5);
    g.fillRoundedRectangle(rightMeter.getX(), rightMeter.getY(), std::clamp<float>(peakLevel, 0.0f, 622.0f), rightMeter.getHeight(), 5);

    g.setColour(juce::Colour::fromRGB(0, 255, 255));
    g.drawRoundedRectangle(leftMeter.toFloat(), 5.0f, 2.0f);
    g.drawRoundedRectangle(rightMeter.toFloat(), 5.0f, 2.0f);
}

void MeterComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
