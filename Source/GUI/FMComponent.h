/*
  ==============================================================================

    FMComponent.h
    Created: 28 Jul 2021 8:51:06pm
    Author:  rodzi

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class FMComponent  : public juce::Component
{
public:
    FMComponent(juce::AudioProcessorValueTreeState& apvts, juce::String filterTypeSelectorId, juce::String filterFreqId, juce::String filterResId);
    ~FMComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    juce::ComboBox filterTypeSelector{ "Filter Type" };
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeSelectorAttachment;

    juce::Slider filterFreqSlider;
    juce::Slider filterResSlider;

    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    std::unique_ptr<Attachment> filterFreqAttachment;
    std::unique_ptr<Attachment> filterResAttachment;

    juce::Label filterSelectorLabel{ "Filter Type", "Filter Type" };
    juce::Label filterFreqLabel{ "Filter Freq", "Filter Freq" };
    juce::Label filterResLabel{ "Filter Res", "FilterRes" };

    void setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FMComponent)
};
