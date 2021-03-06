/*
  ==============================================================================

    SynthVoice.cpp
    Created: 17 Jul 2021 3:19:40pm
    Author:  rodzi

  ==============================================================================
*/

#include "SynthVoice.h"



bool SynthVoice::canPlaySound (juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}
void SynthVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    for (int i = 0; i < 2; i++)
    {
        osc1[i].setFreq(midiNoteNumber);
        osc2[i].setFreq(midiNoteNumber);
    }
    adsr.noteOn();
    filterAdsr.noteOn();
}
void SynthVoice::stopNote (float velocity, bool allowTailOff)
{
    adsr.noteOff();
    filterAdsr.noteOff();

    if (!allowTailOff || !adsr.isActive())
        clearCurrentNote();
}
void SynthVoice::controllerMoved (int controllerNumber, int newControllerValue)
{

}
void SynthVoice::pitchWheelMoved (int newPitchWheelValue)
{

}
void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
    reset();
    
    
    adsr.setSampleRate(sampleRate);
    filterAdsr.setSampleRate(sampleRate);

    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;

    for (int ch = 0; ch < numChannelsToProcess; ch++)
    {
        osc1[ch].prepareToPlay(sampleRate, samplesPerBlock, outputChannels);
        osc2[ch].prepareToPlay(sampleRate, samplesPerBlock, outputChannels);
        filter[ch].prepareToPlay(sampleRate, samplesPerBlock, outputChannels);
        lfo[ch].prepare(spec);
        lfo[ch].initialise([](float x) { return std::sin(x); });
    }
    
    gain.prepare(spec);
    gain.setGainLinear(0.7f);

    isPrepared = true;
}   

void SynthVoice::renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
    jassert(isPrepared);

    if (!isVoiceActive())
        return;
        
    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);


    synthBuffer.clear();

    for (int ch = 0; ch < synthBuffer.getNumChannels(); ++ch)
    {
        auto * buffer = synthBuffer.getWritePointer(ch, 0);

        for (int s = 0; s < synthBuffer.getNumSamples(); ++s)
        {
            buffer[s] = osc1[ch].processNextSample(buffer[s]) + osc2[ch].processNextSample(buffer[s]);
        }
    }

    juce::dsp::AudioBlock<float> audioBlock{ synthBuffer };
    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());

    for (int ch = 0; ch < synthBuffer.getNumChannels(); ++ch)
    {
        auto * buffer = synthBuffer.getWritePointer(ch, 0);
        float cutoffCache = filter[ch].getCutoffFrequency();

        for (int s = 0; s < synthBuffer.getNumSamples(); ++s)
        {
            filterAdsrOutput = filterAdsr.getNextSample();
            auto lfoOut = lfo[ch].processSample(0.0f);
            auto clampted = std::clamp<float>(juce::jmap(filterAdsrOutput * lfoOut, -1.0f, 1.0f, cutoffCache - lfoSweep, cutoffCache + lfoSweep), 20.0f, 20000.0f);
            filter[ch].setCutoffFrequency(clampted);
            buffer[s] = filter[ch].processNextSample(ch, synthBuffer.getSample(ch, s));
        }
        
        filter[ch].setCutoffFrequency(cutoffCache);
    }

    // https://docs.juce.com/master/classADSR.html //ignore!!!
    // filterAdsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples()); //ignore!!!

    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
    {
        outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);

        if (!adsr.isActive())
            clearCurrentNote();
    }

}

void SynthVoice::reset()
{
    gain.reset();
    adsr.reset();
    filterAdsr.reset();
}

void SynthVoice::updateModParams(const int filterType, const float filterCutoff, const float filterResonance, const float adsrDepth, const float lfoFreq, const float lfoDepth)
{
    for (int ch = 0; ch < numChannelsToProcess; ++ch)
    {
        filter[ch].setParameters(filterType, filterCutoff, filterResonance);
        lfo[ch].setFrequency(lfoFreq);
        lfoSweep = lfoDepth;
    }
}
