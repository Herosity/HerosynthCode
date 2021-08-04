/*
  ==============================================================================

    SynthSound.h
    Created: 17 Jul 2021 3:19:57pm
    Author:  rodzi

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote(int midiNoteNumber) override { return true; }
    bool appliesToChannel(int midiChannel) override { return true; }
};
