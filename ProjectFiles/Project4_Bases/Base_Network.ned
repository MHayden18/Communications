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
network Base_Network
{
    @display("bgb=564,527");
    submodules:
        srcBase[5]: Source {
            @display("p=138,259,c");
        }
        Hickam[5]: Fifo {
            @display("p=356,106,c");
        }
        Cheyenne[5]: Fifo {
            @display("p=356,179,c");
        }
        Qatar[5]: Fifo {
            @display("p=356,259,c");
        }
        Langley[5]: Fifo {
            @display("p=356,353,c");
        }
        Ramstein[5]: Fifo {
            @display("p=356,439,c");
        }
        // Five sinks, one per base:
        sink[5]: Sink {
            @display("p=511,259,c");
        }
        milSat_21[2]: Fifo {
            @display("p=228,499");
        }
        milSat_100[2]: Fifo {
            @display("p=228,42");
        }
        unusedSink: Sink {
            @display("p=67.968,418.428");
        }

    connections:

        // Send to appropriate source/dest pair FIFO:
        // We will account for propagation delays on the srcBase --> srcDest link, even though theoretically it is after the transmission

        // Source = Hickam
        srcBase[0].out++ --> {  delay = 00.00 ms; } --> Hickam[0].in++;
        srcBase[0].out++ --> {  delay = 18.00 ms; } --> Hickam[1].in++;
        srcBase[0].out++ --> {  delay = 46.67 ms; } --> Hickam[2].in++;
        // Hickam --> Langley, use a satellite link
        srcBase[0].out++ --> {  delay = 131.0 ms; } --> milSat_100[0].in++; // Hickam --> Langley, use a satellite link
        milSat_100[0].out++ --> {  delay = 126.0 ms; } --> Hickam[3].in++;
        srcBase[0].out++ --> {  delay = 40.00 ms; } --> Hickam[4].in++;

		// Source = Cheyenne
        srcBase[1].out++ --> {  delay = 18.00 ms; } --> Cheyenne[0].in++;
        srcBase[1].out++ --> {  delay = 00.00 ms; } --> Cheyenne[1].in++;
        srcBase[1].out++ --> {  delay = 41.67 ms; } --> Cheyenne[2].in++;
        srcBase[1].out++ --> {  delay = 08.33 ms; } --> Cheyenne[3].in++;
        srcBase[1].out++ --> {  delay = 27.33 ms; } --> Cheyenne[4].in++;

		// Source = Qatar
        srcBase[2].out++ --> {  delay = 46.67 ms; } --> Qatar[0].in++;
        srcBase[2].out++ --> {  delay = 41.67 ms; } --> Qatar[1].in++;
        srcBase[2].out++ --> {  delay = 00.00 ms; } --> Qatar[2].in++;
        srcBase[2].out++ --> {  delay = 37.33 ms; } --> Qatar[3].in++;
        srcBase[2].out++ --> {  delay = 15.33 ms; } --> Qatar[4].in++;

		// Source = Langley
        srcBase[3].out++ --> {  delay = 126.0 ms; } --> milSat_100[1].in++;
        // Langley --> Hickam, use satellite
        milSat_100[1].out++ --> {  delay = 131.0 ms; } --> Langley[0].in++;	// Langley --> Hickam, use satellite
        srcBase[3].out++ --> {  delay = 08.33 ms; } --> Langley[1].in++;
        srcBase[3].out++ --> {  delay = 37.33 ms; } --> Langley[2].in++;
        srcBase[3].out++ --> {  delay = 00.00 ms; } --> Langley[3].in++;
        // Langley --> Ramstein, use satellite
        srcBase[3].out++ --> {  delay = 132.5 ms; } --> milSat_21[0].in++;  // Langley --> Ramstein, use satellite
        milSat_21[0].out++ --> {  delay = 128.0 ms; } --> Langley[4].in++;

		// Source = Ramstein
        srcBase[4].out++ --> {  delay = 40.00 ms; } --> Ramstein[0].in++;
        srcBase[4].out++ --> {  delay = 27.33 ms; } --> Ramstein[1].in++;
        srcBase[4].out++ --> {  delay = 15.33 ms; } --> Ramstein[2].in++;
        // Ramstein --> Langley, use satellite
        srcBase[4].out++ --> {  delay = 128.0 ms; } --> milSat_21[1].in++; // Ramstein --> Langley, use satellite
        milSat_21[1].out++ --> {  delay = 132.5 ms; } --> Ramstein[3].in++;
        srcBase[4].out++ --> {  delay = 00.00 ms; } --> Ramstein[4].in++;

        // Output gates to sinks --> i = destination, send to destination sink
        for i=0..4 {
            Hickam[i].sink --> sink[i].in++;
            Cheyenne[i].sink --> sink[i].in++;
            Qatar[i].sink --> sink[i].in++;
            Langley[i].sink --> sink[i].in++;
            Ramstein[i].sink --> sink[i].in++;
        }
        for i=0..1 {
        	milSat_21[i].sink --> unusedSink.in++;
        	milSat_100[i].sink --> unusedSink.in++;
        }
}


