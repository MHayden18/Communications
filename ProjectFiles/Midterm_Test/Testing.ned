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
network Testing
{
    submodules:
        gen1: Source {
            parameters:
                @display("p=81,77");
        }
        fifo1: Fifo {
            parameters:
                @display("p=209,77");
        }
        fifo2: Fifo {
            parameters:
                @display("p=209,157");
        }
        sink: Sink {
            parameters:
                @display("p=329,227");
        }
    connections:
        gen1.out++ --> fifo1.in;
        fifo1.out --> sink.in++;

        gen1.out++ --> fifo2.in;
        fifo2.out --> sink.in++;
}


