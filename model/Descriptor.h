/*
 * Descriptor.h
 *****************************************************************************
 * Copyright (C) 2012, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#ifndef DESCRIPTOR_H_
#define DESCRIPTOR_H_

#include "das-config.h"

#include "IDescriptor.h"
#include "AbstractMPDElement.h"

namespace ns3 {
namespace dash {
namespace mpd {
class Descriptor : public IDescriptor, public AbstractMPDElement
{
public:
  Descriptor ();
  virtual ~Descriptor ();

  const std::string &GetSchemeIdUri () const;
  const std::string &GetValue () const;

  void SetValue (const std::string &value);
  void SetSchemeIdUri (const std::string &schemeIdUri);

private:
  std::string schemeIdUri;
  std::string value;
};
} // namespace mpd
} // namespace dash
} // namespace ns3
#endif /* DESCRIPTOR_H_ */
