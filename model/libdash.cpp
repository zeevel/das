/*
 * libdash.cpp
 *****************************************************************************
 * Copyright (C) 2012, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#include "libdash.h"
#include "DASHManager.h"

using namespace ns3::dash;

__declspec(dllexport) IDASHManager *__cdecl CreateDashManager ()
{
  return new DASHManager ();
}