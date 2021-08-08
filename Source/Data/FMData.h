/*
  ==============================================================================

    FMData.h
    Created: 28 Jul 2021 9:21:29pm
    Author:  rodzi

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class FMData : public juce::dsp::StateVariableTPTFilter<float>
{
public:
    FMData();
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
    void setParameters(const int filterType, const float filterCutoff, const float filterResonance);
    void setLfoParams(const float freq, const float depth);
    void processNextBlock(juce::AudioBuffer<float>& buffer);
    float processNextSample(int channel, float inputValue);
    void resetAll();

private:
    void selectFilterType(const int type);
    juce::dsp::Oscillator<float> lfo{ [](float x) { return std::sin(x); } };
};
