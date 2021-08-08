/*
  ==============================================================================

    FMData.cpp
    Created: 28 Jul 2021 9:21:29pm
    Author:  rodzi

  ==============================================================================
*/

#include "FMData.h"

FMData::FMData()
{
    setType(juce::dsp::StateVariableTPTFilterType::lowpass);
}

void FMData::setParameters(const int filterType, const float filterCutoff, const float filterResonance)
{
    selectFilterType(filterType);
    setCutoffFrequency(filterCutoff);
    setResonance(filterResonance);
}

void FMData::setLfoParams(const float freq, const float depth)
{
    //lfoGain = juce::Decibels::gainToDecibels (depth);
    lfo.setFrequency (freq);
}

void FMData::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
    resetAll();
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;
    prepare(spec);
}


void FMData::selectFilterType(const int filterType)
{
    switch (filterType)
    {
    case 0:
        setType(juce::dsp::StateVariableTPTFilterType::lowpass);
        break;

    case 1:
        setType(juce::dsp::StateVariableTPTFilterType::bandpass);
        break;

    case 2:
        setType(juce::dsp::StateVariableTPTFilterType::highpass);
        break;

    default:
        jassertfalse;//setType(juce::dsp::StateVariableTPTFilterType::lowpass);
        break;
    }
}

void FMData::processNextBlock(juce::AudioBuffer<float>& buffer)
{
    juce::dsp::AudioBlock<float> block{ buffer };
    process(juce::dsp::ProcessContextReplacing<float>(block));
}

float FMData::processNextSample(int channel, float inputValue)
{
    return processSample(channel, inputValue);
}

void FMData::resetAll()
{
    reset();
    lfo.reset();
}