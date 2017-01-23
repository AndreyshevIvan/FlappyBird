#pragma once
#include "stdafx.h"

const float POINT_VOLUME = 30;
const float WING_VOLUME = 40;
const float FAIL_VOLUME = 30;

struct FBSound
{
	FBSound();

	sf::Music m_pointSound;
	sf::Music m_wingSound;
	sf::Music m_failSound;

	void Wing();
	void Fail();
	void Point();
};