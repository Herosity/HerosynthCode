/*
  ==============================================================================

    OscData.h
    Created: 25 Jul 2021 3:18:00pm
    Author:  rodzi

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class OscData : public juce::dsp::Oscillator<float>
{
public:
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
    void setType(const int oscSelection);
    void setGain(const float levelInDecibels);
    void setOscPitch(const int pitch);
    void setFreq(const int midiNoteNumber);
    void setFmOsc(const float freq, const float depth);
    void renderNextBlock(juce::dsp::AudioBlock<float>& audioBlock);
    float processNextSample(float input);
    void setParameters(const int oscChoice, const float oscGain, const int oscPitch, const float fmFreq, const float fmDepth);
    void resetAll();

private:
    juce::dsp::Oscillator<float> fmOsc{ [](float x) { return std::sin (x); } };
    juce::dsp::Gain<float> gain;
    float fmMod{ 0.0f };
    float fmDepth{ 0.0f };
    int lastPitch{ 0 };
    int lastMidiNote{ 0 };
};