/*
  ==============================================================================

    AdsrData.cpp
    Created: 21 Jul 2021 1:24:41pm
    Author:  rodzi

  ==============================================================================
*/

#include "AdsrData.h"

void AdsrData::update (const float attack, const float decay, const float sustain, const float release)
{
    adsrParams.attack = attack;
    adsrParams.decay = decay;
    adsrParams.sustain = sustain;
    adsrParams.release = release;

    setParameters(adsrParams);
};