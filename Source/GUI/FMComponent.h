/*
  ==============================================================================

    FMComponent.h
    Created: 28 Jul 2021 8:51:06pm
    Author:  rodzi

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "CustomComponent.h"

//==============================================================================
/*
*/
class FMComponent  : public CustomComponent
{
public:
    FMComponent(juce::AudioProcessorValueTreeState& apvts, juce::String filterTypeSelectorId, juce::String filterFreqId, juce::String filterResId);
    ~FMComponent() override;

    void resized() override;

private:

    juce::ComboBox filterTypeSelector;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeAttachment;

    SliderWithLabel cutoff;
    SliderWithLabel resonance;

    static constexpr int dialWidth = 70;
    static constexpr int dialHeight = 70;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FMComponent)
};
