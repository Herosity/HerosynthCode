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
AdsrComponent::AdsrComponent (juce::String name, juce::AudioProcessorValueTreeState& apvts, juce::String attackId, juce::String decayId, juce::String sustainId, juce::String releaseId)
{

    componentName = name;

    setSliderWithLabel(attackSlider, attackLabel, apvts, attackId, attackAttachment);
    setSliderWithLabel(decaySlider, decayLabel, apvts, decayId, decayAttachment);
    setSliderWithLabel(sustainSlider, sustainLabel, apvts, sustainId, sustainAttachment);
    setSliderWithLabel(releaseSlider, releaseLabel, apvts, releaseId, releaseAttachment);


}

AdsrComponent::~AdsrComponent()
{
}

void AdsrComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(5);
    auto labelSpace = bounds.removeFromTop(25.0f);
    
    g.fillAll(juce::Colours::grey);
    g.setColour(juce::Colours::white);
    g.setFont(20.0f);
    g.drawText(componentName, labelSpace.withX(5), juce::Justification::left);
    g.drawRoundedRectangle(bounds.toFloat(), 5.0f, 2.0f);
}

void AdsrComponent::resized()
{
    const auto bounds = getLocalBounds().reduced(10);
    const auto padding = 10;
    const auto sliderWidth = bounds.getWidth() / 4; //bounds.getWidth() / 20 - padding;
    const auto sliderHeight = bounds.getHeight() - 50; //bounds.getHeight() / 6 - padding;
    const auto sliderStartX = 0;
    const auto sliderStartY = 50;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;
    const auto labelStart = sliderStartY - labelYOffset;

    attackSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    attackLabel.setBounds(attackSlider.getX(), labelStart, sliderWidth, labelHeight);

    decaySlider.setBounds(attackSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    decayLabel.setBounds(decaySlider.getX(), labelStart, sliderWidth, labelHeight);

    sustainSlider.setBounds(decaySlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    sustainLabel.setBounds(sustainSlider.getX(), labelStart, sliderWidth, labelHeight);

    releaseSlider.setBounds(sustainSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    releaseLabel.setBounds(releaseSlider.getX(), labelStart, sliderWidth, labelHeight);
}

using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;

void AdsrComponent::setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment)
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
}