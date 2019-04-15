//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 1992-2015 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

#ifndef __ABSTRACTFIFO_H
#define __ABSTRACTFIFO_H

#include <omnetpp.h>
#include "netmsg_m.h"

using namespace omnetpp;

namespace fifo {

/**
 * Abstract base class for single-server queues. Subclasses should
 * define startService() and endService(), and may override other
 * virtual functions.
 */
class AbstractFifo : public cSimpleModule
{
  protected:
    Netmsg *msgServiced;
    Netmsg *endServiceMsg;
    cQueue queue;
    simsignal_t qlenSignal;
    simsignal_t busySignal;
    simsignal_t queueingTimeSignal;

  public:
    AbstractFifo();
    virtual ~AbstractFifo();

  protected:
    virtual void initialize() override;
    virtual void handleMessage(Netmsg *msg);

    // hook functions to (re)define behaviour
    virtual void arrival(Netmsg *msg) {}
    virtual simtime_t startService(Netmsg *msg) = 0;
    virtual void endService(Netmsg *msg) = 0;
};

}; //namespace

#endif
