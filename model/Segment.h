/*
 * Segment.h
 *****************************************************************************
 * Copyright (C) 2013, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#ifndef SEGMENT_H_
#define SEGMENT_H_

#include "das-config.h"

#include "AbstractChunk.h"
#include "Path.h"
#include "ISegment.h"
#include "IBaseUrl.h"
#include "HTTPTransaction.h"

namespace ns3 {
namespace dash {
namespace mpd {
class Segment : public network::AbstractChunk, public virtual ISegment
{
public:
  Segment ();
  virtual ~Segment ();

  bool Init (const std::vector<IBaseUrl *> &baseurls, const std::string &uri,
             const std::string &range, dash::metrics::HTTPTransactionType type);
  std::string &AbsoluteURI ();
  std::string &Host ();
  size_t Port ();
  std::string &Path ();
  std::string &Range ();
  size_t StartByte ();
  size_t EndByte ();
  bool HasByteRange ();
  dash::metrics::HTTPTransactionType GetType ();

  void AbsoluteURI (std::string uri);
  void Host (std::string host);
  void Port (size_t port);
  void Path (std::string path);
  void Range (std::string range);
  void StartByte (size_t startByte);
  void EndByte (size_t endByte);
  void HasByteRange (bool hasByteRange);
  void SetType (dash::metrics::HTTPTransactionType type);

private:
  std::string absoluteuri;
  std::string host;
  size_t port;
  std::string path;
  std::string range;
  size_t startByte;
  size_t endByte;
  bool hasByteRange;
  dash::metrics::HTTPTransactionType type;
};
} // namespace mpd
} // namespace dash
} // namespace ns3
#endif /* SEGMENT_H_ */
