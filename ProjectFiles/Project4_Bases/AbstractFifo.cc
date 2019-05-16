//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 1992-2015 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

#include "AbstractFifo.h"
#include "netmsg_m.h"

namespace fifo {

AbstractFifo::AbstractFifo()
{
    msgServiced = endServiceMsg = nullptr;
}

AbstractFifo::~AbstractFifo()
{
    delete msgServiced;
    cancelAndDelete(endServiceMsg);
}

void AbstractFifo::initialize()
{
    endServiceMsg = new cMessage("end-service");
    queue.setName("queue");

    qlenSignal = registerSignal("qlen");
    busySignal = registerSignal("busy");
    queueingTimeSignal = registerSignal("queueingTime");
    serviceTimeSignal = registerSignal("serviceTime");
    nodeTimeSignal = registerSignal("nodeTime");
    emit(qlenSignal, queue.getLength());
    emit(busySignal, false);
}

void AbstractFifo::handleMessage(cMessage *msg)
{
    if (msg == endServiceMsg) {
        endService(msgServiced);
        if (queue.isEmpty()) {
            msgServiced = nullptr;
            emit(busySignal, false);
        }
        else {
            msgServiced = (cMessage *)queue.pop();
            emit(qlenSignal, queue.getLength());
            simtime_t queueTime = simTime() - msgServiced->getTimestamp();
            emit(queueingTimeSignal, simTime() - msgServiced->getTimestamp());
            simtime_t serviceTime = startService(msgServiced);
            emit(serviceTimeSignal, serviceTime);
            emit(nodeTimeSignal, serviceTime + queueTime);
            scheduleAt(simTime()+serviceTime, endServiceMsg);
        }
    }
    else if (!msgServiced) {
        arrival(msg);
        msgServiced = msg;
        emit(queueingTimeSignal, SIMTIME_ZERO);
        simtime_t serviceTime = startService(msgServiced);
        emit(serviceTimeSignal, serviceTime);
        emit(nodeTimeSignal, serviceTime);
        scheduleAt(simTime()+serviceTime, endServiceMsg);
        emit(busySignal, true);
    }
    else {
        arrival(msg);
        queue.insert(msg);
        msg->setTimestamp();
        emit(qlenSignal, queue.getLength());
    }
}

}; //namespace

