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
network FifoNet
{
    submodules:
        gen1: Source {
            parameters:
                @display("p=81,77");
        }
        gen2: Source {
            parameters:
                @display("p=81,157");
        }
        gen3: Source {
            parameters:
                @display("p=81,227");
        }
        fifo1: Fifo {
            parameters:
                @display("p=209,77");
        }
        fifo2: Fifo {
            parameters:
                @display("p=209,157");
        }
        fifo3: Fifo {
            parameters:
                @display("p=209,227");
        }
        sink1: Sink {
            parameters:
                @display("p=329,77");
        }
        sink2: Sink {
            parameters:
                @display("p=329,157");
        }
        sink3: Sink {
            parameters:
                @display("p=329,227");
        }
    connections:
        gen1.out --> fifo1.in;
        fifo1.out --> sink1.in;

        gen2.out --> fifo2.in;
        fifo2.out --> sink2.in;

        gen3.out --> fifo3.in;
        fifo3.out --> sink3.in;
}


