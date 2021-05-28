n = NetAddr("localhost", 12345);
n.sendMsg("/config");
n.sendMsg("/silent");
n.sendMsg("/verbose");
n.sendMsg("/midiports");
n.sendMsg("/midiport", 0);