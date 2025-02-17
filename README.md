# DigitalGuitarPedal
Code and Schematics for a digital guitar pedal using a teensy 3.0

Can I use a teensy 3.0 microcontroller I have on hand to digitally process and output an audio signal?

Preamble:

  As of writing—early 2025—I've been learning to play the bass guitar. It's going alright, but the sound can be kind of basic. The way people fix this is by connecting some sort of electronic signal processing between the guitar and the output. Many effects can be achived with simple(ish) analog circuits, and are pretty rad. I'm totally going to make some of those, but the main drawbacks are that a single circuit can only really perform one effect, and to have more complicated effects—like a delay or reverb—you need some heavily specialized and complicated ICs for true analog. However, a setup that converts the analog signal to digital, runs some kind of calculation on the numbers, then converts back to analog, is only *really* limited by how much calculation you can do in real time. (You also lose the "analog warmth" many people strive for, but you can get that back real easily by having some awful solders)

A Digital Pedal:

  The choice of microcontroller was mainly due to the fact it's what I had on hand. The teensy is great for this kind of application because of it's really fast processing speed, low power requirements, and built in analog converter. To get a signal in is simple, just connect it to one of the ADC pins on the teesny and call an analog read; however, to get the maximum possible fidelity and versatility out of the teensy's 1024-bit ADC, the signal needs to modified. Power for the teensy is from the 9v battery in the case, which is run through a fixed voltage regulator at 5v. The teenst runs at 3.3v, but the max voltage in it can take is 5v.

Signal In:

  Signal is taken in by a quarter-inch jack, which is wired to an op-amp amplier circuit with a volume knob. This allows for the device to take in a lot of different signal strengths, and bring them to a level the teensy can understand. One note is that the pedal is designed to be powered with a single 9V battery, so to give the op amps a reference ground between 0 and 9v I use a voltage divider connected to an op amp follower to provide a pretty decent(for my purposes) exact middle voltage. 
  
  The amplified signal is decoupled with a capacitor to remove any bias, and then isloated using a voltage follower with another opamp on the chip I'm using. Then, using a divider across my battery with a pair of fixed resistors to give a 1.65(ish) voltage, I center the signal at the exact middle of the teensy's analog range. Then connect it to the A0 pin for reading.

Signal Out:

  Originally, I set up a twelve-bit resistor ladder to just use pins 0-11, because that's how many digital out pins the teensy has to a side. It's a bit more precise than is maybe required, but it's cool to be silly and overengineered sometimes. Code at first was just a loop and digital write for every pin, but that was really slow, and bottlenecked the whole system by quite a bit.

  Conveniently, the teensy does allow you to write to a whole output bus in a single operation, like an arduino. Even more conveniently, the largest single bus the teensy has is twelve bits, allowing me to still use the original design. Inconvienently, the twelve pins that make up the bus are neither next to each other, in any coherent order, or even on the header pins. I ended up having to monkey around a bunch of tangled wires to have the bits of the bus in order for a pair of ribbon cables, research showed that newer boards might not have this issue, but c'est la vie. 

Incredibly thankful for the people on the teensy forum who mapped all of these pins out, [the discussion was here](https://forum.pjrc.com/index.php?threads/tutorial-on-digital-i-o-atmega-pin-port-ddr-d-b-registers-vs-arm-gpio_pdir-_pdor.17532/#post-21228).

The resistor ladder was tough to fit within the size constraints, but I came up with the idea of soldering the two parallel resistors on opposite sides and using their legs to bridge other connections, which is what made that at all possible. 
If you've kept count of how many op amps I've used, I have one left; the ouput from the DAC is then sent through an op amp voltage follower, then connected to the ouput jack. It's really convenient that I was able to use the entire chip. 

Digital Signal Processing:

At the moment I do not have any code beyond the test code for the circuit, I intend to write some when it is finished.
