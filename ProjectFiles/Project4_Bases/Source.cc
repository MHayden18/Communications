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
    }
    else if (probSrc <= 5155) { // Src = Cheyenne
        src = CHE;
        if (probDest <= 2381 ) { // Hickam
            dest = HIC;
        }
        else if (probDest <= 7141) { // Qatar
            dest = QAT;
        }
        else if (probDest <= 9524) { // Langley
             dest = LAN;
        }
        else { // Ramstein
             dest = RAM;
        }
    }
    else if (probSrc <= 6701) { // Src = Qatar
        src = QAT;
		if (probDest <= 1667 ) { // Hickam
            dest = HIC;
        }
        else if (probDest <= 5000) { // Cheyenne
            dest = CHE;
        }
        else if (probDest <= 8333) { // Langley
             dest = LAN;
        }
        else { // Ramstein
             dest = RAM;
        }
    }
    else if (probSrc <= 8247) { // Src = Langley
        src = LAN;
		if (probDest <= 1667 ) { // Hickam
            dest = HIC;
        }
        else if (probDest <= 5000) { // Qatar
            dest = CHE;
        }
        else if (probDest <= 8333) { // Langley
             dest = QAT;
        }
        else { // Ramstein
             dest = RAM;
        }
    }
    else {          // Src = Ramstein
        src = RAM;
		if (probDest <= 1471 ) { // Hickam
            dest = HIC;
        }
        else if (probDest <= 2647) { // Cheyenne
            dest = CHE;
        }
        else if (probDest <= 4118) { // Qatar
             dest = QAT;
        }
        else { // Langley
             dest = LAN;
        }
    }
	// I now have source, destination pairs:
	//send to the "src" queue, with the set destination
	job -> setDestination( dest );
    send(job, "out", src);

    scheduleAt(simTime()+par("sendIaTime").doubleValue(), sendMessageEvent);
}


}; //namespace

