/*
 * DASHManager.cpp
 *****************************************************************************
 * Copyright (C) 2012, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#include "DASHManager.h"

using namespace ns3::dash;
using namespace ns3::dash::xml;
using namespace ns3::dash::mpd;
using namespace ns3::dash::network;
using namespace ns3::dash::helpers;

DASHManager::DASHManager ()
{
}
DASHManager::~DASHManager ()
{
}
IMPD *
DASHManager::Open (char *path)
{
  DOMParser parser (path);

  uint32_t fetchTime = Time::GetCurrentUTCTimeInSec ();

  if (!parser.Parse ())
    return NULL;

  MPD *mpd = parser.GetRootNode ()->ToMPD ();

  if (mpd)
    mpd->SetFetchTime (fetchTime);

  return mpd;
}
void
DASHManager::Delete ()
{
  delete this;
}
