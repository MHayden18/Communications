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
network TandemSatellite
{
    @display("bgb=528,254");
    submodules:
        gen: Source {
            parameters:
                @display("p=45,136");
        }
        fifo1: Fifo {
            parameters:
                @display("p=160,136");
        }
        fifo2: Fifo {
            parameters:
                @display("p=360,136");
        }
        satellite: Satellite {
            parameters:
                @display("p=260,51");
        }
        sink: Sink {
            parameters:
                @display("p=475,136");
        }
    connections:
        gen.out --> fifo1.in;
        fifo1.out --> {  delay = satellite.propDelay; } --> satellite.in;
        satellite.out --> {  delay = satellite.propDelay; } --> fifo2.in;
        fifo2.out --> sink.in;
}


