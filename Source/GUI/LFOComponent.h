/*
  ==============================================================================

    LFOComponent.h
    Created: 4 Aug 2021 2:42:08pm
    Author:  rodzi

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "CustomComponent.h"

//==============================================================================
/*
*/
class LFOComponent  : public CustomComponent
{
public:
    LFOComponent(juce::AudioProcessorValueTreeState& apvts, juce::String lfoFreqId, juce::String lfoDepthId);
    ~LFOComponent() override;

    void resized() override;

private:
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    //void  setSliderParams(juce::Slider& slider, juce::Label& label, std::unique_ptr<SliderAttachment>& attachment, juce::String paramId, juce::AudioProcessorValueTreeState& apvts);

    juce::Slider lfoFreqSlider;
    juce::Slider lfoDepthSlider;

    juce::Label lfoFreqLabel{ "Freq", "Freq" };
    juce::Label lfoDepthLabel{ "Depth", "Depth" };

    std::unique_ptr<SliderAttachment> lfoFreqAttachment;
    std::unique_ptr<SliderAttachment> lfoDepthAttachment;

    SliderWithLabel lfoFreq;
    SliderWithLabel lfoDepth;

    static constexpr int dialWidth = 70;
    static constexpr int dialHeight = 70;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LFOComponent)
};
