/*
  ==============================================================================

    AdsrData.h
    Created: 21 Jul 2021 1:24:41pm
    Author:  rodzi

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class AdsrData : public juce::ADSR
{
public:
    void update(const float attack, const float decay, const float sustain, const float release);

private:
    juce::ADSR::Parameters adsrParams;
};