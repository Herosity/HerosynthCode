/*
  ==============================================================================

    MeterData.h
    Created: 4 Aug 2021 2:40:13pm
    Author:  rodzi

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class MeterData
{
public:
    void processRMS(juce::AudioBuffer<float>& buffer);
    void processPeak(juce::AudioBuffer<float>& buffer);

    const std::atomic<float>& getRMS() { return rms; }
    const std::atomic<float>& getPeak() { return peak; }

private:
    std::atomic<float> rms{ 0.0f };
    std::atomic<float> peak{ 0.0f };
};
