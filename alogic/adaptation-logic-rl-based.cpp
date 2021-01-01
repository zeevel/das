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

#include "adaptation-logic-rl-based.h"

#include "../model/multimedia-player.h"

namespace ns3 {
namespace dash {
namespace player {

ENSURE_ADAPTATION_LOGIC_INITIALIZED(RlBasedAdaptationLogic)

// segmentTotalNumber = getTotalSegments();

ISegmentURL *RlBasedAdaptationLogic::GetNextSegment(
    unsigned int *requested_segment_number,
    const dash::mpd::IRepresentation **usedRepresentation,
    bool *hasDownloadedAllSegments) {
  double last_download_speed =
      this->m_multimediaPlayer->GetLastDownloadBitRate();

  if (currentSegmentNumber < getTotalSegments())
    *hasDownloadedAllSegments = false;
  else {
    *hasDownloadedAllSegments = true;
    return NULL;  // everything downloaded
  }

  unsigned int segmentTotalNumber = getTotalSegments();
  std::cout << "--------------segmentTotalNumber------------"
            << segmentTotalNumber << std::endl;

  double bufferNow = m_multimediaPlayer->GetBufferLevel();
  std::cout << "-------------bufferNow-------------" << bufferNow << std::endl;

  double lastSegmentBitrate = m_multimediaPlayer->GetLastDownloadBitRate();
  std::cout << "-------------lastSegmentBitrate-------------"
            << lastSegmentBitrate << std::endl;

  // 测试用 仅向rl agent传递固定状态
  myGymEnv->UpdateState(segmentTotalNumber, bufferNow, lastSegmentBitrate);

  int m_repindex = myGymEnv->GetRepIndex();

  std::cout << "env get action from the rl-test agent: action is " << m_repindex
            << std::endl;

  //------------------------------------------------------------------------

  // IRepresentation *rep =
  // (this->m_availableRepresentations->begin()->second);
  const IRepresentation *useRep = GetLowestRepresentation();
  // int idx = 0;
  // for (RepresentationsMap::iterator it = m_availableRepresentations->begin();
  //      it != m_availableRepresentations->end() && idx <= m_repindex;
  //      it++, idx++) {
  //   if (idx == m_repindex) {
  //     useRep = it->second;
  //   }
  // }
  *usedRepresentation = useRep;

  *requested_segment_number = currentSegmentNumber;
  *hasDownloadedAllSegments = false;
  return useRep->GetSegmentList()->GetSegmentURLs().at(currentSegmentNumber++);
}
}  // namespace player
}  // namespace dash
}  // namespace ns3
