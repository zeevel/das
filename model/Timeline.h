/*
 * Timeline.h
 *****************************************************************************
 * Copyright (C) 2012, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#ifndef TIMELINE_H_
#define TIMELINE_H_

#include "das-config.h"

#include "ITimeline.h"
#include "AbstractMPDElement.h"

namespace ns3 {
namespace dash {
namespace mpd {
class Timeline : public ITimeline, public AbstractMPDElement
{
public:
  Timeline ();
  virtual ~Timeline ();

  uint32_t GetStartTime () const;
  uint32_t GetDuration () const;
  uint32_t GetRepeatCount () const;

  void SetStartTime (uint32_t startTime);
  void SetDuration (uint32_t duration);
  void SetRepeatCount (uint32_t repeatCount);

private:
  uint32_t startTime;
  uint32_t duration;
  uint32_t repeatCount;
};
} // namespace mpd
} // namespace dash
} // namespace ns3
#endif /* TIMELINE_H_ */
