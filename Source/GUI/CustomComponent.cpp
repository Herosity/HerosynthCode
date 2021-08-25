/*
  ==============================================================================

    CustomComponent.cpp
    Created: 4 Aug 2021 2:41:57pm
    Author:  rodzi

  ==============================================================================
*/

#include <JuceHeader.h>
#include "CustomComponent.h"

//==============================================================================
using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
using SliderStyle = juce::Slider::SliderStyle;

SliderWithLabel::SliderWithLabel(juce::String labelName, juce::String paramId, juce::AudioProcessorValueTreeState& apvts, const int width, const int height, SliderStyle style)
{
    sliderWidth = width;
    sliderHeight = height;

    slider.setSliderStyle(style);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, textBoxWidth, textBoxHeight);
    slider.setColour(juce::Slider::ColourIds::trackColourId, juce::Colour::fromRGB(85, 83, 87));             //linear filled     
    slider.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colour::fromRGB(60, 60, 60));           //linear unfilled   
    slider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colour::fromRGB(85, 83, 87));     //rotary filled     
    slider.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colour::fromRGB(60, 60, 60));  //rotary unfilled   
    slider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colour::fromRGB(0, 255, 255));              //both thumb        
    slider.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colour::fromRGB(0, 255, 255));         //both textbox text 
    slider.setColour(juce::Slider::ColourIds::textBoxBackgroundColourId, juce::Colour::fromRGB(60, 60, 60));    //both textbox bg   
    slider.setColour(juce::Slider::ColourIds::textBoxHighlightColourId, juce::Colour::fromRGB(60, 60, 60));     //both null         
    slider.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colour::fromRGB(60, 60, 60));       //both null         
    addAndMakeVisible(slider);

    label.setFont(fontHeight);
    label.setText(labelName, juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
    label.setColour(juce::Label::ColourIds::backgroundColourId, juce::Colour::fromRGB(60, 60, 60));             //label bg          
    label.setColour(juce::Label::ColourIds::textColourId, juce::Colour::fromRGB(0, 255, 255));                  //label text        
    label.setColour(juce::Label::ColourIds::outlineColourId, juce::Colour::fromRGB(60, 60, 60));                //outline           

    addAndMakeVisible(label);

    attachment = std::make_unique<SliderAttachment>(apvts, paramId, slider);
}

void SliderWithLabel::resized()
{
    const auto dialToLabelRatio = 15;
    const auto labelHeight = 18;

    jassert(sliderWidth > 0);
    jassert(sliderHeight > 0);

    label.setBounds(0, 0, sliderWidth, labelHeight);
    slider.setBounds(0, 0 + dialToLabelRatio, sliderWidth, sliderHeight);
}

CustomComponent::CustomComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

CustomComponent::~CustomComponent()
{
}

void CustomComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour::fromRGB(60, 60, 60));
    auto bounds = getLocalBounds();
    g.setColour(boundsColour);
    g.drawRoundedRectangle(bounds.toFloat().reduced(2.0f), 14.0f, 2.0f);

    g.setColour(juce::Colour::fromRGB(0, 255, 255));
    g.setFont(fontHeight);
    g.setFont(g.getCurrentFont().boldened());

    jassert(name.isNotEmpty());
    g.drawText(name, 20, 15, 100, 25, juce::Justification::left);
}

void CustomComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
