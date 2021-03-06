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

#define HIC 0
#define CHE 1
#define QAT 2
#define LAN 3
#define RAM 4

using namespace omnetpp;

namespace fifo {

/**
 * Generates messages or jobs; see NED file for more info.
 */
class Source : public cSimpleModule
{
  private:
    cMessage *sendMessageEvent;

  public:
    Source();
    virtual ~Source();

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
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
    sendMessageEvent = new cMessage("sendMessageEvent");
    scheduleAt(simTime(), sendMessageEvent);

}

void Source::handleMessage(cMessage *msg)
{
    ASSERT(msg == sendMessageEvent);

    Netmsg *job = new Netmsg("job");
    // Produce source and destination address using probabilities.
    int probSrc = intuniform(1, 10000);
    int src;
    int dest;
    int probDest;
    if (probSrc <= 4072) { // Src = Hickam
        // Destination = B
        src = HIC;
        probDest = intuniform(1, 10000);
        if (probDest <= 506 ) { // Cheyenne
            dest = CHE;
        }
        else if (probDest <= 6835) { // Qatar
            dest = QAT;
        }
        else if (probDest <= 9367) { // Langley
             dest = LAN;
        }
        else { // Ramstein
             dest = RAM;
        }
        job -> setDestination( dest );
        send(job, "out", src);
    }
    else if (probSrc <= 5155) { // Src = Cheyenne
        src = CHE;

    }
    else if (probSrc <= 6701) { // Src = Qatar
        src = QAT;

    }
    else if (probSrc <= 8247) { // Src = Langley
        src = LAN;

    }
    else {          // Src = Ramstein
        src = RAM;
    }

    job->setDestination( dest );
    send(job, "out");

    scheduleAt(simTime()+par("sendIaTime").doubleValue(), sendMessageEvent);
}


}; //namespace

