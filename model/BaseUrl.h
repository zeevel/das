/*
 * BaseUrl.h
 *****************************************************************************
 * Copyright (C) 2012, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#ifndef BASEURL_H_
#define BASEURL_H_

#include "das-config.h"

#include "Segment.h"
#include "IBaseUrl.h"
#include "AbstractMPDElement.h"

namespace ns3 {
namespace dash {
namespace mpd {
class BaseUrl : public IBaseUrl, public AbstractMPDElement
{
public:
  BaseUrl ();
  virtual ~BaseUrl ();

  const std::string &GetUrl () const;
  const std::string &GetServiceLocation () const;
  const std::string &GetByteRange () const;

  void SetUrl (const std::string &url);
  void SetServiceLocation (const std::string &serviceLocation);
  void SetByteRange (const std::string &byteRange);

  virtual ISegment *ToMediaSegment (const std::vector<IBaseUrl *> &baseurls) const;

private:
  std::string url;
  std::string serviceLocation;
  std::string byteRange;
};
} // namespace mpd
} // namespace dash
} // namespace ns3
#endif /* BASEURL_H_ */
