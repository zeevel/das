/*
 * Time.h
 *****************************************************************************
 * Copyright (C) 2013, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#ifndef DASH_HELPERS_TIME_H_
#define DASH_HELPERS_TIME_H_

#include <time.h>
#include "das-config.h"

namespace ns3 {
namespace dash {
namespace helpers {
class Time
{
public:
  static uint32_t GetCurrentUTCTimeInSec ();
  static std::string GetCurrentUTCTimeStr ();

private:
  static struct tm *GetCurrentUTCTime ();
};
} // namespace helpers
} // namespace dash
} // namespace ns3
#endif /* DASH_HELPERS_TIME_H_ */
