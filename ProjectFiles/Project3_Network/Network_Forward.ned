//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 1992-2015 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

//
// Simple queueing network: generator + FIFO + sink.
//
network Network_Forward
{
    @display("bgb=564,254");
    submodules:
        gen: Source {
            parameters:
                @display("p=45,136");
        }
        fifo[6]: Fifo {
            @display("p=239,136,r,10");
        }
        sink[5]: Sink {
            @display("p=427,136,c");
        }
    // fifo[1]-fifo[5] correspond to fifoB --> fifoF
    connections:
        gen.out --> fifo[0].in++;
        fifo[0].out++ --> {  delay = 60 ms; } --> fifo[1].in++;
        fifo[0].out++ --> {  delay = 50 ms; } --> fifo[2].in++;
        fifo[1].out++ --> {  delay = 40 ms; } --> fifo[3].in++;
        fifo[1].out++ --> {  delay = 30 ms; } --> fifo[4].in++;
        fifo[2].out++ --> {  delay = 20 ms; } --> fifo[4].in++;
        fifo[2].out++ --> {  delay = 10 ms; } --> fifo[5].in++;

		// Output gates to sinks:
        fifo[1].sink --> sink[0].in;
        fifo[2].sink --> sink[1].in;
        fifo[3].sink --> sink[2].in;
        fifo[4].sink --> sink[3].in;
        fifo[5].sink --> sink[4].in;

}


