/*
 * URLType.h
 *****************************************************************************
 * Copyright (C) 2012, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#ifndef URLTYPE_H_
#define URLTYPE_H_

#include "das-config.h"

#include "IURLType.h"
#include "Segment.h"
#include "Path.h"
#include "AbstractMPDElement.h"

namespace ns3 {
namespace dash {
namespace mpd {
class URLType : public IURLType, public AbstractMPDElement
{
public:
  URLType ();
  virtual ~URLType ();

  const std::string &GetSourceURL () const;
  const std::string &GetRange () const;
  ISegment *ToSegment (const std::vector<IBaseUrl *> &baseurls) const;

  void SetSourceURL (const std::string &sourceURL);
  void SetRange (const std::string &range);
  void SetType (dash::metrics::HTTPTransactionType type);

private:
  std::string sourceURL;
  std::string range;
  dash::metrics::HTTPTransactionType type;
};
} // namespace mpd
} // namespace dash
} // namespace ns3
#endif /* URLTYPE_H_ */
