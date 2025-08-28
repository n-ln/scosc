# Simple Config OSC

SCOSC is an Unreal Engine plugin built on top of the official OSC plugin, allowing users to set up and manage OSC messaging in Unreal Engine 5 quickly and intuitively.

Currently, creating and managing OSC servers (receiving) is supported, and only OSC messages containing only float values are supported.

### Usage

#### Setting up OSC Server

* Click the icon on the editor toolbar to open the SCOSC Editor window.

* Create or edit OSC server endpoints.

* Click Toggle Receive OSC to turn on/off the OSC message receiving function.

#### Receiving OSC Message in Blueprint Actors

* In the Blueprint editor, add the SCOSCListener component.

* In the details panel of the Listener component, click the "+" button for the "On Incoming OSC Floats" event.

* An event will be created, where the user can access the OSC address and float array data every time an OSC message is received.
