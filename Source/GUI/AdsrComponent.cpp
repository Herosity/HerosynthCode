/*
  ==============================================================================

    AdsrComponent.cpp
    Created: 21 Jul 2021 1:23:22pm
    Author:  rodzi

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AdsrComponent.h"

//==============================================================================
AdsrComponent::AdsrComponent(juce::AudioProcessorValueTreeState& apvts, juce::String attackId, juce::String decayId, juce::String sustainId, juce::String releaseId)
    : attack("A", attackId, apvts, sliderWidth, sliderHeight, juce::Slider::SliderStyle::LinearVertical)
    , decay("D", decayId, apvts, sliderWidth, sliderHeight, juce::Slider::SliderStyle::LinearVertical)
    , sustain("S", sustainId, apvts, sliderWidth, sliderHeight, juce::Slider::SliderStyle::LinearVertical)
    , release("R", releaseId, apvts, sliderWidth, sliderHeight, juce::Slider::SliderStyle::LinearVertical)
{
    addAndMakeVisible(attack);
    addAndMakeVisible(decay);
    addAndMakeVisible(sustain);
    addAndMakeVisible(release);
}

AdsrComponent::~AdsrComponent()
{
}

/*void AdsrComponent::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(5);
   auto labelSpace = bounds.removeFromTop(25.0f);
    
    g.fillAll(juce::Colours::grey);
    g.setColour(juce::Colours::white);
    g.setFont(20.0f);
    g.drawText(componentName, labelSpace.withX(5), juce::Justification::left);
    g.drawRoundedRectangle(bounds.toFloat(), 5.0f, 2.0f);
}*/

void AdsrComponent::resized()
{
    const auto startX = 15;
    const auto startY = 55;
    const auto width = sliderWidth;
    const auto height = sliderHeight + 20;

    attack.setBounds(startX, startY, width, height);
    decay.setBounds(attack.getRight(), startY, width, height);
    sustain.setBounds(decay.getRight(), startY, width, height);
    release.setBounds(sustain.getRight(), startY, width, height);
}

/*void AdsrComponent::setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment)
{

    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setPopupDisplayEnabled(true, false, this);
    slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(slider);

    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, paramId, slider);

    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setFont(15.0f);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);
}*/ //====================================================================== moved to custom component to keep clean