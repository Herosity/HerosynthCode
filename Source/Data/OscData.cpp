/*
  ==============================================================================

    OscData.cpp
    Created: 25 Jul 2021 3:18:00pm
    Author:  rodzi

  ==============================================================================
*/

#include "OscData.h"

void OscData::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
    resetAll();

    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;
    
    prepare(spec);
    fmOsc.prepare(spec);
    gain.prepare(spec);
}

void OscData::setType(const int oscSelect)
{
    switch (oscSelect) 
    {
        case 0: //Sine
            initialise([](float x) { return std::sin(x); });
                break;

        case 1: //Saw
            initialise([](float x) { return x / juce::MathConstants<float>::pi; }); 
            break;

        case 2: //Square
            initialise([](float x) { return x < 0.0f ? -1.0f : 1.0f; });     
            break;

        default:
            jassertfalse; //Program isn't supposed to reach this point. If does means cases are faulty.
            break;
    }
}

void OscData::setGain(const float levelInDecibels)
{
    gain.setGainDecibels(levelInDecibels);
}

void OscData::setOscPitch(const int pitch)
{
    lastPitch = pitch;
    setFrequency(juce::MidiMessage::getMidiNoteInHertz((lastMidiNote + lastPitch) + fmMod));

}

void OscData::setFreq(const int midiNoteNumber)
{
    setFrequency(juce::MidiMessage::getMidiNoteInHertz ((midiNoteNumber + lastPitch) + fmMod));
    lastMidiNote = midiNoteNumber; //cause cant include midinotenumber out of this class
}

void OscData::setFmOsc(const float freq, const float depth)
{
    fmDepth = depth;
    fmOsc.setFrequency(freq);
    setFrequency(juce::MidiMessage::getMidiNoteInHertz((lastMidiNote + lastPitch) + fmMod));
}

void OscData::renderNextBlock(juce::dsp::AudioBlock<float>& audioBlock)
{
    jassert(audioBlock.getNumSamples() > 0);
    process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
}

float OscData::processNextSample(float input)
{
    fmMod = fmOsc.processSample(input) * fmDepth;
    return gain.processSample(processSample(input));
}

void OscData::setParameters(const int oscChoice, const float oscGain, const int oscPitch, const float fmFreq, const float fmDepth)
{
    setType(oscChoice);
    setGain(oscGain);
    setOscPitch(oscPitch);
    setFmOsc(fmFreq, fmDepth);
}

void OscData::resetAll()
{
    reset();
    fmOsc.reset();
    gain.reset();
}