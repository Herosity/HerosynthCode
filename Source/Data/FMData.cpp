/*
  ==============================================================================

    FMData.cpp
    Created: 28 Jul 2021 9:21:29pm
    Author:  rodzi

  ==============================================================================
*/

#include "FMData.h"

void FMData::prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels)
{
    filter.reset();

    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = numChannels;

    filter.prepare(spec);

    isPrepared = true;
}

void FMData::process(juce::AudioBuffer<float>& buffer)
{
    jassert(isPrepared);

    juce::dsp::AudioBlock<float> block{ buffer };
    filter.process(juce::dsp::ProcessContextReplacing<float> { block });
}

void FMData::updateParameters(const float modulator, const int filterType, const float frequency, const float resonance)
{
    switch (filterType)
    {
    case 0:
        filter.setType(juce::dsp::StateVariableTPTFilterType::lowpass);
        break;

    case 1:
        filter.setType(juce::dsp::StateVariableTPTFilterType::bandpass);
        break;

    case 2:
        filter.setType(juce::dsp::StateVariableTPTFilterType::highpass);
        break;
    }

    float modulatedFreq = frequency * modulator;
    modulatedFreq = std::fmax(std::fmin(modulatedFreq, 20000.0f), 20.0f);

    filter.setCutoffFrequency(modulatedFreq);
    filter.setResonance(resonance);
}

void FMData::reset()
{
    filter.reset();
}
