//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 1992-2015 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

#include "Fifo.h"

namespace fifo {

Define_Module(Fifo);

simtime_t Fifo::startService(cMessage *msg)
{
    EV << "Starting service of " << msg->getName() << endl;
    return par("serviceTime");
}

void Fifo::endService(cMessage *msg)
{
    EV << "Completed service of " << msg->getName() << endl;
    Netmsg *mymsg = check_and_cast<Netmsg *>(msg);
    int dest = mymsg->getDestination();
    // At destination:
    if (getIndex() == dest) {
        send(msg, "sink");
    }
    // At A:
    else if (getIndex() == 0) {
        if (dest == 1 || dest == 3 || dest == 4)
            send(msg, "out", 0);
        else {
            send(msg, "out", 1);
        }
    }
    // At B:
    else if (getIndex() == 1) {
        if (dest == 3) {
            send(msg, "out", 0);
        }
        else {
            send(msg, "out", 1);
        }
    }
    // At C:
    else if (getIndex() == 2) {
        if (dest == 4) {
            send(msg, "out", 0);
        }
        else {
            send(msg, "out", 1);
        }
    }
}

}; //namespace

