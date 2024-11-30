# Local Network Communication Simulation

This project simulates a local network communication system, divided into two main layers: the **Physical Simulation Layer** and the **Protocol Implementation Layer**.

## Physical Simulation Layer

### Environment
The `Environment` class simulates the physical environment and basic simulation functions. Time in the simulation is measured in ticks, and certain events may be triggered at specific ticks to achieve the simulation effect.

### SimEvent
`SimEvent` is an auxiliary class for `Environment`, recording events that occur at specific times and triggering them when the simulation reaches that moment. This class facilitates setting up events in the simulation environment.

### Channel
The `Channel` class simulates the behavior of various channels in the environment, including channel occupation and signal interference. An `Environment` instance may contain multiple `Channels`. When a `Device` sends a message to a `Channel` and the message is not interfered with, it will be broadcast to all `Devices` listening to that `Channel`.

### Device
The `Device` class simulates the physical implementation of devices, each with its own address. Devices can send messages to a `Channel` (sending messages consumes ticks, during which the device is busy and the channel is occupied). Devices also implement basic channel occupation-waiting mechanisms and message queue mechanisms (if multiple message sending requests occur in a short time, messages are stored in a queue and sent sequentially). Devices can listen to messages on a `Channel` (each device can only listen to one channel at a time).

## Protocol Implementation Layer

### ProtocolDevice
`ProtocolDevice` extends `Device` by adding basic protocol functionalities. Each message includes a type and payload, and received broadcast messages can be processed, such as filtering out messages not intended for the device, registering message handlers, sending messages, and listening for callbacks.

### Server
The `Server` class is a specific implementation of `ProtocolDevice`, representing a central server device. It handles server-related behaviors, such as listening for login requests and handling robot charging requests. The server can manage all devices, which prioritize communication with the server unless authorized otherwise. The server does not manage any devices at startup; devices must log in to the server to be managed. Each device has a login key, and only devices with valid keys are added to the specific device pool.

### Robot
The `Robot` class is a specific implementation of `ProtocolDevice`, representing a robot device. It implements behaviors related to robots, such as logging in and requesting charging.

### Station
The `Station` class is a specific implementation of `ProtocolDevice`, representing a charging station device. It implements behaviors related to charging stations, such as logging in and handling charging requests.

## Main Function

The main function demonstrates an instance of this system. In this experiment, a server, 10 robots, and 10 charging stations are started at the 10th tick. Robots and charging stations log in to the server using keys after startup. At the 5000th tick, a "robot requests charging" event occurs. Each device's behavior is logged in detail to the console, allowing the operator to see what happens and make further optimizations and adjustments.