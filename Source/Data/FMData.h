/*
  ==============================================================================

    FMData.h
    Created: 28 Jul 2021 9:21:29pm
    Author:  rodzi

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class FMData
{
public:
    void prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels);
    void process(juce::AudioBuffer<float>& buffer);
    void updateParameters(const float modulator, const int filterType, const float frequency, const float resonance);
    void reset();

private:
    juce::dsp::StateVariableTPTFilter<float> filter;
    bool isPrepared{ false };
};
