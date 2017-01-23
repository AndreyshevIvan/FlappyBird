#include "stdafx.h"
#include "sound.h"


FBSound::FBSound()
{
	m_pointSound.openFromFile("resources/Sounds/point.ogg");
	m_wingSound.openFromFile("resources/Sounds/sfx_wing.ogg");
	m_failSound.openFromFile("resources/Sounds/hit.ogg");

	m_pointSound.setVolume(POINT_VOLUME);
	m_wingSound.setVolume(WING_VOLUME);
	m_failSound.setVolume(FAIL_VOLUME);
}

void FBSound::Wing()
{
	m_wingSound.play();
}

void FBSound::Fail()
{
	m_failSound.play();
}

void FBSound::Point()
{
	m_pointSound.play();
}