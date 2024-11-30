# Local Network Communication Simulation System

This project is divided into `physical simulation layer` and `protocol layer`. 

For detailed information, please refer to the [API documentation](https://github.com/XLxiaoliaoGmail/Simulated-Local-Area-Network-Communication-System/blob/master/doc/API.md).

## physical simulation layer
The physical simulation layer simulates the key behaviors of lower-layer firmware of the 802.15.4, which is a widely used protocol for low-rate wireless personal area networks (LR-WPANs) , including message sending and listening, channel occupancy and waiting, and communication interference. It also creates a virtual experimental environment that allows these devices to operate in the time dimension. 

The following diagram demonstrates how a device sends data to the channel, which is then broadcast to each device listening to the channel.
![image](https://github.com/user-attachments/assets/ebea5d4c-99fe-448e-8f04-83ef44eb6cd3)

## protocol layer
The protocol layer simulates the behavior of real devices. Users can easily use the protocol layer's API directly without needing to worry about the underlying implementation.

The following diagram demonstrates the class relationship between the "communication protocol specialized device" and the "underlying physical device".
![image](https://github.com/user-attachments/assets/dc4a513e-795a-40a1-a022-533d12ee1d00)



## demo (main function)

The main function demonstrates an instance of this system. In this experiment, a server, 10 robots, and 10 charging stations are started at the 10th tick. Robots and charging stations log in to the server using keys after startup. At the 5000th tick, a "robot requests charging" event occurs. Each device's behavior is logged in detail to the console, allowing the operator to see what happens and make further optimizations and adjustments. The output\main.exe is the compiled file. You can open it if you trust it.

It simulated the following events:

1. Due to some reasons, the robot needs to charge and sends a request to the server.
2. The server finds an available charging station and sends the communication address, location, and handshake key to the robot, then sends the handshake key to the charging station.
3. The robot uses the key to handshake with the charging station.
4. The robot starts charging.
5. During charging, the robot and the charging station maintain a keep-alive connection.
6. Charging is completed, and the keep-alive connection is canceled.
7. The charging station returns to idle status.

The following diagram delays the process of this experiment.
![image](https://github.com/user-attachments/assets/b7969871-1b95-48f9-a388-333767f2f0a6)

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

For detailed information, please refer to the [API documentation](https://github.com/XLxiaoliaoGmail/Simulated-Local-Area-Network-Communication-System/blob/master/doc/API.md).
