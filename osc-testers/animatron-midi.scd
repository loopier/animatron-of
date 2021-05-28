s.boot;
n = NetAddr("localhost", 12345);
MIDIClient.init;
m = MIDIOut.newByName("ofxMidiIn Client", "ofxMidi Input 0");
n.sendMsg("/midiports");
n.sendMsg("/midiport", 0);
n.sendMsg("/midimap", "midi-map-default.json");
n.sendMsg("/midimap", "midi-map-velocity-fps.json");
n.sendMsg("/midimap", "midi-map-note-goto.json");
n.sendMsg("/midimap", "midi-map-note-play-sequence.json");

(
n.sendMsg("/new", "hom");
n.sendMsg("/new", "ma");
// n.sendMsg("/animation", "hom", "hom-up-stairs-hd");
n.sendMsg("/animation", "ma", "mamo");
// n.sendMsg("/animation", "ele", "default");
// n.sendMsg("/play", "ala");
// n.sendMsg("/select", "hom");
n.sendMsg("/select", "ma");
// m.noteOn(0,37,70);
)
n.sendMsg("/pause");
n.sendMsg("/goto", 30);
n.sendMsg("/speed", 2);
n.sendMsg("/loop");
m.noteOn(0,0,64);
m.noteOff(0,60,60);
m.control(0,1,60);
(
t = Tdef(\m, {
	inf.do{
		var ch = 0;
		var note = 127.rand;
		var vel = 127.rand;
		m.noteOn(ch, note, vel);
		[ch, note, vel].debug;
		1.wait;
		// m.allNotesOff(ch);
		m.noteOff(ch, note, vel);
	}
});
)
t.play;
t.stop;

(
Pbindef(\a, \type, \midi, \midiout, m,
	\midinote, (0..7).pseq + 60,
	\dur, 1/4
).stop
)

n.sendMsg("/playfrom", 1, "ala, olo");