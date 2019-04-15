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
        A: Fifo {
            parameters:
                @display("p=120,136");
        }
        fifoB: Fifo {
            parameters:
                @display("p=218,78");
        }
        fifoC: Fifo {
            parameters:
                @display("p=218,192");
        }
        fifoD: Fifo {
            parameters:
                @display("p=321,49");
        }
        fifoE: Fifo {
            parameters:
                @display("p=321,136");
        }
        fifoF: Fifo {
            parameters:
                @display("p=321,218");
        }
        sink[5]: Sink {
            parameters:
                @display("p=508,136");
        }
    connections:
        gen.out --> A.in++;
        A.out++ --> fifoB.in++;
        A.out++ --> fifoC.in++;
        fifoB.out++ --> fifoD.in++;
        fifoB.out++ --> fifoE.in++;
        fifoC.out++ --> fifoE.in++;
        fifoC.out++ --> fifoF.in++;

        fifoB.out++ --> sink[0].in;
        fifoC.out++ --> sink[1].in;
        fifoD.out++ --> sink[2].in;
        fifoE.out++ --> sink[3].in;
        fifoF.out++ --> sink[4].in;

}


