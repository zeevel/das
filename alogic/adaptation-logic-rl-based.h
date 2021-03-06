/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/**
 * Copyright (c) 2015 Christian Kreuzberger and Daniel Posch,
 *Alpen-Adria-University Klagenfurt
 *
 * This file is part of amus-ndnSIM, based on ndnSIM. See AUTHORS for complete
 *list of authors and contributors.
 *
 * amus-ndnSIM and ndnSIM are free software: you can redistribute it and/or
 *modify it under the terms of the GNU General Public License as published by
 *the Free Software Foundation, either version 3 of the License, or (at your
 *option) any later version.
 *
 * amus-ndnSIM is distributed in the hope that it will be useful, but WITHOUT
 *ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 *FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 *details.
 *
 * You should have received a copy of the GNU General Public License along with
 * amus-ndnSIM, e.g., in COPYING.md file.  If not, see
 *<http://www.gnu.org/licenses/>.
 **/
#ifndef DASH_RL_BASED_ADAPTATION_LOGIC
#define DASH_RL_BASED_ADAPTATION_LOGIC

#include "../model/adaptation-logic.h"
#include "MediaGym.h"
// #include "ns3/MediaGym.h"
#include <stack>

#include "ns3/core-module.h"
#include "ns3/opengym-module.h"

extern unsigned int segmentTotalNumber;
extern double bufferNow;
extern double lastSegmentBitrate;

namespace ns3 {
namespace dash {
namespace player {
class RlBasedAdaptationLogic : public AdaptationLogic {
 public:
  RlBasedAdaptationLogic(MultimediaPlayer *mPlayer) : AdaptationLogic(mPlayer) {
    currentSegmentNumber = 0;
    std::cout << "Connecting to RL Proxy" << std::endl;
    std::cout << "mPlayer args RlBasedAdaptationLogic Constructor" << std::endl;
    openGymPort = 5555;
    openGymInterface = CreateObject<OpenGymInterface>(openGymPort);
    myGymEnv = CreateObject<ns3::MediaGym>();
    myGymEnv->SetOpenGymInterface(openGymInterface);
  }

  virtual std::string GetName() const {
    return "dash::player::RlBasedAdaptationLogic";
  }

  static AdaptationLogic *Create(MultimediaPlayer *mPlayer) {
    return new RlBasedAdaptationLogic(mPlayer);
  }

  virtual ISegmentURL *GetNextSegment(
      unsigned int *requested_segment_number,
      const dash::mpd::IRepresentation **usedRepresentation,
      bool *hasDownloadedAllSegments);

 protected:
  static RlBasedAdaptationLogic _staticLogic;

  unsigned int currentSegmentNumber;

  RlBasedAdaptationLogic() {
    ENSURE_ADAPTATION_LOGIC_REGISTERED(RlBasedAdaptationLogic);
    std::cout << "RL adaptation registered !!!!!" << std::endl;
  }

 public:
  uint32_t openGymPort;
  Ptr<OpenGymInterface> openGymInterface;
  Ptr<ns3::MediaGym> myGymEnv;

  std::map<int /*level/layer*/, IRepresentation *> m_orderdByDepIdReps;
  std::stack<dash::mpd::IRepresentation *> repsForCurSegment;
  unsigned int curSegmentNumber;
};
}  // namespace player
}  // namespace dash
}  // namespace ns3

#endif  // DASH_RATE_BASED_ADAPTATION_LOGIC
