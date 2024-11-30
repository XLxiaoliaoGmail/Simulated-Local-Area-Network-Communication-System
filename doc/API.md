# API

This project simulates a local network communication system, divided into two main layers: the **Physical Simulation Layer** and the **Protocol Implementation Layer**.

## Environment Class

The `Environment` class simulates the physical environment for a local network communication system. It manages devices, channels, and simulation events while keeping track of the simulation time.

### Attributes

- **`running`** (`bool`): Indicates whether the simulation is currently running. Default is `false`.
- **`devices`** (`std::vector<Device*>`): A collection of pointers to `Device` objects participating in the simulation.
- **`time`** (`TIME_TYPEDEF`): Tracks the current simulation time in ticks.
- **`eventsAtCertainTick`** (`std::unordered_map<TIME_TYPEDEF, std::vector<SimEvent*>>`): Maps specific simulation ticks to lists of scheduled events (`SimEvent`).
- **`channels`** (`Channel[CHANNEL_COUNTS]`): An array of `Channel` objects, representing communication channels available in the environment.

### Methods

#### Constructor

- **`explicit Environment()`**
  - Initializes an `Environment` object with `running` set to `false` and `time` set to `0`.

#### Public Methods

- **`void addDevice(Device* d)`**
  - Adds a device to the simulation environment.
  - **Parameters:**
    - `d`: A pointer to the `Device` object to be added.

- **`void broadcast(const Message* msg, CHANNEL_INDEX_TYPEDEF channelIndex, TIME_TYPEDEF sendingTime)`**
  - Broadcasts a message to all devices listening to the specified channel.
  - **Parameters:**
    - `msg`: A pointer to the `Message` to be broadcasted.
    - `channelIndex`: The index of the channel through which the message is broadcasted.
    - `sendingTime`: The time at which the message is sent.

- **`void update()`**
  - Advances the simulation by processing events and updating the environment's state.

- **`SimEvent* registerEvent(TIME_TYPEDEF tick, std::function<void()> callback)`**
  - Registers a new event to be executed at a specific simulation tick.
  - **Parameters:**
    - `tick`: The simulation time (in ticks) when the event will occur.
    - `callback`: A function to be executed when the event triggers.
  - **Returns:** A pointer to the registered `SimEvent`.

- **`SimEvent* delayEvent(TIME_TYPEDEF delayTick, std::function<void()> callback)`**
  - Schedules an event to occur after a specified delay from the current simulation time.
  - **Parameters:**
    - `delayTick`: The delay (in ticks) from the current simulation time.
    - `callback`: A function to be executed when the event triggers.
  - **Returns:** A pointer to the scheduled `SimEvent`.

- **`void log(const std::string& log)`**
  - Logs a message for debugging or output purposes.
  - **Parameters:**
    - `log`: A string containing the message to log.

- **`TIME_TYPEDEF getTime() const`**
  - Retrieves the current simulation time.
  - **Returns:** The current time as a `TIME_TYPEDEF`.

- **`void endAt(TIME_TYPEDEF time)`**
  - Sets the simulation to stop at a specified tick.
  - **Parameters:**
    - `time`: The tick at which the simulation will end.

- **`void stopRun()`**
  - Immediately stops the simulation from running.

- **`void run()`**
  - Starts the simulation and processes events until manually stopped or the end time is reached.

- **`Channel* getChannels()`**
  - Retrieves a pointer to the array of channels in the environment.
  - **Returns:** A pointer to the `Channel` array.

- **`void error(std::string s)`**
  - Throws a runtime error with a specified message.
  - **Parameters:**
    - `s`: A string containing the error message.


## SimEvent Class

The `SimEvent` class represents an event scheduled to occur at a specific time during the simulation. It supports chaining events and executing callback functions.

### Attributes

- **`emitTick`** (`TIME_TYPEDEF`): The simulation tick at which the event will be triggered.
- **`callback`** (`std::function<void()>`): A function to execute when the event is triggered.
- **`en`** (`Environment*`): A pointer to the `Environment` instance where the event is scheduled.

### Methods

#### Constructor

- **`explicit SimEvent(Environment* en, TIME_TYPEDEF emitTick, std::function<void()> callback)`**
  - Creates a new `SimEvent` object.
  - **Parameters:**
    - `en`: A pointer to the `Environment` instance in which the event is scheduled.
    - `emitTick`: The simulation tick at which the event will be triggered.
    - `callback`: A function to execute when the event is triggered.

#### Public Methods

- **`SimEvent* then(TIME_TYPEDEF delayTime, std::function<void()> callback)`**
  - Schedules a new event to occur after a specified delay from the current event's trigger time.
  - **Parameters:**
    - `delayTime`: The delay (in ticks) after the current event's `emitTick` when the new event should occur.
    - `callback`: A function to execute for the new event.
  - **Returns:** A pointer to the newly created `SimEvent`.

- **`void emit()`**
  - Triggers the event by executing its callback function.

- **`TIME_TYPEDEF getEmitTick() const`**
  - Retrieves the simulation tick at which the event will be triggered.
  - **Returns:** The event's `emitTick` as a `TIME_TYPEDEF`.


### Channel
The `Channel` class simulates the behavior of various channels in the environment, including channel occupation and signal interference. An `Environment` instance may contain multiple `Channels`. When a `Device` sends a message to a `Channel` and the message is not interfered with, it will be broadcast to all `Devices` listening to that `Channel`.

**Description:**
<!-- Write a description of the class here -->

### Device
The `Device` class simulates the physical implementation of devices, each with its own address. Devices can send messages to a `Channel` (sending messages consumes ticks, during which the device is busy and the channel is occupied). Devices also implement basic channel occupation-waiting mechanisms and message queue mechanisms (if multiple message sending requests occur in a short time, messages are stored in a queue and sent sequentially). Devices can listen to messages on a `Channel` (each device can only listen to one channel at a time).

**Description:**
<!-- Write a description of the class here -->

## Protocol Implementation Layer

### ProtocolDevice
`ProtocolDevice` extends `Device` by adding basic protocol functionalities. Each message includes a type and payload, and received broadcast messages can be processed, such as filtering out messages not intended for the device, registering message handlers, sending messages, and listening for callbacks.

**Description:**
<!-- Write a description of the class here -->

### Server
The `Server` class is a specific implementation of `ProtocolDevice`, representing a central server device. It handles server-related behaviors, such as listening for login requests and handling robot charging requests. The server can manage all devices, which prioritize communication with the server unless authorized otherwise. The server does not manage any devices at startup; devices must log in to the server to be managed. Each device has a login key, and only devices with valid keys are added to the specific device pool.

**Description:**
<!-- Write a description of the class here -->

### Robot
The `Robot` class is a specific implementation of `ProtocolDevice`, representing a robot device. It implements behaviors related to robots, such as logging in and requesting charging.

**Description:**
<!-- Write a description of the class here -->

### Station
The `Station` class is a specific implementation of `ProtocolDevice`, representing a charging station device. It implements behaviors related to charging stations, such as logging in and handling charging requests.

**Description:**
<!-- Write a description of the class here -->

## Main Function

The main function demonstrates an instance of this system. In this experiment, a server, 10 robots, and 10 charging stations are started at the 10th tick. Robots and charging stations log in to the server using keys after startup. At the 5000th tick, a "robot requests charging" event occurs. Each device's behavior is logged in detail to the console, allowing the operator to see what happens and make further optimizations and adjustments.

The output\main.exe is the compiled file. You can open it if you trust it.

**Description:**
<!-- Write a description of the main function here -->
