//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 1992-2015 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

#include <omnetpp.h>
#include "netmsg_m.h"

using namespace omnetpp;

namespace fifo {

/**
 * Generates messages or jobs; see NED file for more info.
 */
class Source : public cSimpleModule
{
  private:
    Netmsg *sendMessageEvent;

  public:
    Source();
    virtual ~Source();

  protected:
    virtual void initialize() override;
    virtual void handleMessage(Netmsg *msg);
};

Define_Module(Source);

Source::Source()
{
    sendMessageEvent = nullptr;
}

Source::~Source()
{
    cancelAndDelete(sendMessageEvent);
}

void Source::initialize()
{
    sendMessageEvent = new Netmsg("sendMessageEvent");
    // Produce source and destination address using probabilities.
    int probDest = intuniform(1, 100);
    int dest;
    if (probDest <= 10) {
        // Destination = B
        dest = 1;
    }
    else if (probDest <= 25) {
        // Destination = C
        dest = 2;
    }
    else if (probDest <= 50) {
        // Destination = D
        dest = 3;
    }
    else if (probDest <= 80) {
        // Destination = E
        dest = 4;
    }
    else {
        // Destination = F
        dest = 5;
    }

    // Create message object and set source and destination field.
    sendMessageEvent->setDestination(dest);
    scheduleAt(simTime(), sendMessageEvent);
}

void Source::handleMessage(Netmsg *msg)
{
    ASSERT(msg == sendMessageEvent);

    Netmsg *job = new Netmsg("job");
    job->setDestination( msg->getDestination() );

    send(job, "out");
    scheduleAt(simTime()+par("sendIaTime").doubleValue(), sendMessageEvent);
}


}; //namespace

