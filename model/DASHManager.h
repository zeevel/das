/*
 * DASHManager.h
 *****************************************************************************
 * Copyright (C) 2012, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#ifndef DASHMANAGER_H_
#define DASHMANAGER_H_

#include "das-config.h"

#include "Node.h"
#include "DOMParser.h"
#include "IDASHManager.h"
#include "Time.h"

namespace ns3 {
namespace dash {
class DASHManager : public IDASHManager
{
public:
  DASHManager ();
  virtual ~DASHManager ();

  mpd::IMPD *Open (char *path);
  void Delete ();
};
} // namespace dash
} // namespace ns3

#endif /* DASHMANAGER_H_ */
