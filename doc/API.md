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


## Channel Class

The `Channel` class simulates a communication channel in the local network, supporting message transmission and device listening mechanisms.

### Attributes

- **`userNum`** (`uint8_t`): Tracks the number of users currently occupying the channel.
- **`mixed`** (`bool`): Indicates whether signal interference has occurred on the channel.
- **`msg`** (`const Message*`): A pointer to the message currently being transmitted on the channel.
- **`listeners`** (`std::list<Device*>`): A list of devices currently listening to the channel.

### Methods

#### Constructor

- **`explicit Channel()`**
  - Initializes a `Channel` object with no users (`userNum = 0`), no signal interference (`mixed = false`), and no active message.

#### Public Methods

- **`void occupy(const Message* msg)`**
  - Occupies the channel with a message for transmission.
  - **Parameters:**
    - `msg`: A pointer to the `Message` to be transmitted.

- **`void release()`**
  - Releases the channel, making it available for new transmissions.

- **`void addListener(Device* d)`**
  - Adds a device to the channel's list of listeners.
  - **Parameters:**
    - `d`: A pointer to the `Device` to be added as a listener.

- **`void removeListener(Device* d)`**
  - Removes a device from the channel's list of listeners.
  - **Parameters:**
    - `d`: A pointer to the `Device` to be removed.

- **`bool isBusy() const`**
  - Checks if the channel is currently occupied.
  - **Returns:** `true` if the channel is occupied, `false` otherwise.

- **`bool isMixed() const`**
  - Checks if signal interference has occurred on the channel.
  - **Returns:** `true` if interference is present, `false` otherwise.

- **`const Message* getMsg() const`**
  - Retrieves the message currently being transmitted on the channel.
  - **Returns:** A pointer to the `Message`.

- **`std::list<Device*> getListeners() const`**
  - Retrieves the list of devices currently listening to the channel.
  - **Returns:** A list of pointers to `Device` objects.

- **`void error(std::string s)`**
  - Throws a runtime error with a specified message.
  - **Parameters:**
    - `s`: A string containing the error message.


## Device Class

The `Device` class represents a physical device in the simulated network. It can send and receive messages, listen to channels, and manage its busy or waiting states.

### Attributes

- **`addr`** (`ADDR_TYPEDEF`): The address of the device.
- **`en`** (`Environment*`): A pointer to the environment where the device operates.
- **`txDelay`** (`TIME_TYPEDEF`): The time delay required for the device to transmit a message.
- **`busy`** (`bool`): Indicates whether the device is currently busy sending messages.
- **`waiting`** (`bool`): Indicates whether the device is in a waiting state to access a channel.
- **`onBusyChanged`** (`std::function<void(bool)>`): A callback function triggered when the device's busy state changes.
- **`onWaitingChanged`** (`std::function<void(bool)>`): A callback function triggered when the device's waiting state changes.
- **`listeningIndex`** (`CHANNEL_INDEX_TYPEDEF`): The index of the channel the device is currently listening to.
- **`logEnable`** (`bool`): Controls whether the device's actions are logged.
- **`msgQueue`** (`std::queue<std::tuple<std::string, CHANNEL_INDEX_TYPEDEF, ADDR_TYPEDEF>>`): A queue storing messages to be sent, with each message containing a payload, target channel, and target address.

### Methods

#### Constructor

- **`explicit Device(ADDR_TYPEDEF addr, Environment* en)`**
  - Initializes a `Device` object with a specific address and environment.
  - **Parameters:**
    - `addr`: The address of the device.
    - `en`: A pointer to the `Environment` where the device operates.

#### Protected Methods

- **`void send(const std::string& payload, CHANNEL_INDEX_TYPEDEF channelIndex, ADDR_TYPEDEF target)`**
  - Enqueues a message to be sent.
  - **Parameters:**
    - `payload`: The message content.
    - `channelIndex`: The target channel index.
    - `target`: The target address.

- **`void log(const std::string& log)`**
  - Logs the specified message if logging is enabled.
  - **Parameters:**
    - `log`: The message to log.

#### Public Methods

- **`void recieve(const Message* msg, CHANNEL_INDEX_TYPEDEF channelIndex)`**
  - Handles receiving a message on a specific channel.
  - **Parameters:**
    - `msg`: A pointer to the received `Message`.
    - `channelIndex`: The index of the channel where the message was received.

- **`ADDR_TYPEDEF getAddr() const`**
  - Retrieves the device's address.
  - **Returns:** The device's `ADDR_TYPEDEF`.

- **`void listenTo(CHANNEL_INDEX_TYPEDEF channelIndex)`**
  - Sets the device to listen to a specific channel.
  - **Parameters:**
    - `channelIndex`: The index of the channel to listen to.

- **`void setBusy(bool v)`**
  - Updates the device's busy state and triggers the `onBusyChanged` callback if defined.
  - **Parameters:**
    - `v`: The new busy state (`true` or `false`).

- **`void setWaiting(bool v)`**
  - Updates the device's waiting state and triggers the `onWaitingChanged` callback if defined.
  - **Parameters:**
    - `v`: The new waiting state (`true` or `false`).

- **`void setOnBusyChanged(std::function<void(bool)> callback)`**
  - Sets the callback function for busy state changes.
  - **Parameters:**
    - `callback`: A function to execute when the busy state changes.

- **`void setOnWaitingChanged(std::function<void(bool)> callback)`**
  - Sets the callback function for waiting state changes.
  - **Parameters:**
    - `callback`: A function to execute when the waiting state changes.

- **`void setLogEnable(bool v)`**
  - Enables or disables logging for the device.
  - **Parameters:**
    - `v`: `true` to enable logging, `false` to disable.

- **`void error(std::string s)`**
  - Throws a runtime error with the specified message.
  - **Parameters:**
    - `s`: A string containing the error message.

## ProtocolDevice Class

The `ProtocolDevice` class extends the `Device` class and provides functionality for handling protocol-specific communication with other devices. It supports message sending, receiving, and callback management.



### Attributes

- **`callbacks`** (`std::unordered_map<MsgType, std::function<void(ADDR_TYPEDEF, const std::string&)>>`): A map of registered callbacks for specific message types.
- **`onceCallbacks`** (`std::unordered_map<MsgType, std::function<void(ADDR_TYPEDEF, const std::string&)>>`): A map of one-time callbacks for specific message types.



### Methods

#### Constructor

- **`explicit ProtocolDevice(ADDR_TYPEDEF addr, Environment* en)`**
  - Initializes the `ProtocolDevice` object with the provided address and environment.
  - **Parameters:**
    - `addr`: The address of the device.
    - `en`: A pointer to the environment.



#### Utility Methods

- **`std::string formatKeyStr(const std::string& key)`**
  - Formats the given key string to a specific length, adding 'x' at the beginning or truncating if necessary.
  - **Parameters:**
    - `key`: The key string to format.
  - **Returns:** A formatted key string.

- **`std::string MsgTypeToHexString(MsgType num)`**
  - Converts a `MsgType` value to its hexadecimal string representation.
  - **Parameters:**
    - `num`: The message type to convert.
  - **Returns:** A hexadecimal string representing the message type.

- **`MsgType hexStringToMsgType(const std::string& hexStr)`**
  - Converts a hexadecimal string to a `MsgType` value.
  - **Parameters:**
    - `hexStr`: The hexadecimal string to convert.
  - **Returns:** The corresponding `MsgType` value.



#### Sending Messages

- **`void send(MsgType type, const std::string payload, CHANNEL_INDEX_TYPEDEF channelIndex, ADDR_TYPEDEF target)`**
  - Sends a message with a `MsgType` and payload to a specific target.
  - **Parameters:**
    - `type`: The message type.
    - `payload`: The message content.
    - `channelIndex`: The target channel.
    - `target`: The target address.

- **`void send(MsgType type, CHANNEL_INDEX_TYPEDEF channelIndex, ADDR_TYPEDEF target)`**
  - Sends a message with a `MsgType` to a specific target without a payload.
  - **Parameters:**
    - `type`: The message type.
    - `channelIndex`: The target channel.
    - `target`: The target address.

- **`void send(MsgType type, const std::string payload, CHANNEL_INDEX_TYPEDEF channelIndex, ADDR_TYPEDEF target, std::function<void(ADDR_TYPEDEF, const std::string&)> callback)`**
  - Sends a message with a `MsgType` and payload to a specific target and registers a one-time callback for the response.
  - **Parameters:**
    - `type`: The message type.
    - `payload`: The message content.
    - `channelIndex`: The target channel.
    - `target`: The target address.
    - `callback`: A callback function to execute when a response is received.

- **`void send(MsgType type, CHANNEL_INDEX_TYPEDEF channelIndex, ADDR_TYPEDEF target, std::function<void(ADDR_TYPEDEF, const std::string&)> callback)`**
  - Sends a message with a `MsgType` to a specific target and registers a one-time callback for the response.
  - **Parameters:**
    - `type`: The message type.
    - `channelIndex`: The target channel.
    - `target`: The target address.
    - `callback`: A callback function to execute when a response is received.



#### Callback Management

- **`void on(MsgType type, std::function<void(ADDR_TYPEDEF, const std::string&)> callback)`**
  - Registers a callback function to be executed when a message of the specified type is received.
  - **Parameters:**
    - `type`: The message type.
    - `callback`: The callback function to execute.

- **`void once(MsgType type, std::function<void(ADDR_TYPEDEF, const std::string&)> callback)`**
  - Registers a one-time callback function to be executed once when a message of the specified type is received.
  - **Parameters:**
    - `type`: The message type.
    - `callback`: The callback function to execute.

- **`void msgHandler(ADDR_TYPEDEF senderAddr, MsgType type, const std::string& payload)`**
  - Handles the received message by executing the appropriate callback.
  - If the message has a one-time callback, it is executed and removed from the `onceCallbacks`.
  - **Parameters:**
    - `senderAddr`: The address of the sender.
    - `type`: The message type.
    - `payload`: The message content.


#### Receiving Messages

- **`void recieve(const Message* msg, CHANNEL_INDEX_TYPEDEF channelIndex) override`**
  - Receives a message and processes it if the message's target is the current device.
  - **Parameters:**
    - `msg`: The message to receive.
    - `channelIndex`: The channel index the message was received on.


#### Logging

- **`void log(const std::string& who, const std::string& log)`**
  - Logs a message with a specific prefix indicating the origin of the message.
  - **Parameters:**
    - `who`: The source of the log (e.g., "ProtocolDevice").
    - `log`: The message content to log.


## Server Class

The `Server` class extends the `ProtocolDevice` class to manage and coordinate `RobotData` and `StationData`. It provides functionalities to handle robot and station information, login key management, and channel listening.


### Attributes

- **`robotsInfo`** (`std::unordered_map<ADDR_TYPEDEF, RobotData*>`): A mapping of robot addresses to their corresponding `RobotData` objects.
- **`stationsInfo`** (`std::unordered_map<ADDR_TYPEDEF, StationData*>`): A mapping of station addresses to their corresponding `StationData` objects.
- **`robotLoginKey`** (`std::string`): The formatted key for robot login.
- **`stationLoginKey`** (`std::string`): The formatted key for station login.


### Methods

#### Constructor

- **`explicit Server(ADDR_TYPEDEF addr, Environment* en)`**
  - Initializes the `Server` object with a specific address and environment.
  - **Parameters:**
    - `addr`: The server's address.
    - `en`: A pointer to the `Environment`.


#### Public Methods

- **`bool isRobot(ADDR_TYPEDEF addr)`**
  - Checks if a given address belongs to a robot.
  - **Parameters:**
    - `addr`: The address to check.
  - **Returns:** `true` if the address belongs to a robot, `false` otherwise.

- **`bool isStation(ADDR_TYPEDEF addr)`**
  - Checks if a given address belongs to a station.
  - **Parameters:**
    - `addr`: The address to check.
  - **Returns:** `true` if the address belongs to a station, `false` otherwise.

- **`StationData* getFreeStation()`**
  - Retrieves a pointer to a free station.
  - **Returns:** A pointer to a `StationData` object, or `nullptr` if no free station is available.

- **`void setStationStatus(ADDR_TYPEDEF addr, bool free)`**
  - Updates the status of a station (free or busy).
  - **Parameters:**
    - `addr`: The station address.
    - `free`: The new status (`true` for free, `false` for busy).

- **`void setRobotLoginKey(const std::string& key)`**
  - Sets the robot login key.
  - **Parameters:**
    - `key`: The login key string.

- **`void setStationLoginKey(const std::string& key)`**
  - Sets the station login key.
  - **Parameters:**
    - `key`: The login key string.

- **`void addRobotAddr(ADDR_TYPEDEF addr)`**
  - Adds a robot address to the `robotsInfo` map.
  - **Parameters:**
    - `addr`: The robot address.

- **`void addStationAddr(ADDR_TYPEDEF addr)`**
  - Adds a station address to the `stationsInfo` map.
  - **Parameters:**
    - `addr`: The station address.

- **`void listenTo(CHANNEL_INDEX_TYPEDEF channelIndex)`**
  - Listens to a specific channel and logs the action.
  - **Parameters:**
    - `channelIndex`: The index of the channel to listen to.

- **`void log(const std::string& log)`**
  - Logs a message with the prefix "Server."
  - **Parameters:**
    - `log`: The message to log.





## Robot Class

The `Robot` class extends the `ProtocolDevice` class and represents a robotic device that can interact with a server and charging stations. It handles communication, navigation, charging, and login operations.


### Attributes

- **`needCharging`** (`bool`): Indicates if the robot requires charging.
- **`loginSuccess`** (`bool`): Indicates if the robot has successfully logged in.
- **`power`** (`POWER_TYPEDEF`): The robot's current power level.
- **`chargingStationAddr`** (`ADDR_TYPEDEF`): The address of the charging station the robot is associated with.


### Methods

#### Constructor

- **`explicit Robot(ADDR_TYPEDEF addr, Environment* en)`**
  - Initializes the `Robot` object with a specific address and environment.
  - **Parameters:**
    - `addr`: The robot's address.
    - `en`: A pointer to the `Environment`.


#### Public Methods

- **`void listenTo(CHANNEL_INDEX_TYPEDEF channelIndex)`**
  - Listens to a specific channel and logs the action.
  - **Parameters:**
    - `channelIndex`: The index of the channel to listen to.

- **`void log(const std::string& log)`**
  - Logs a message with the prefix "Robot."
  - **Parameters:**
    - `log`: The message to log.

- **`void gotoPosition(Position pos)`**
  - Logs the action of moving to a specific position.
  - **Parameters:**
    - `pos`: The target position, with `x` and `y` coordinates.

- **`void chagingUp()`**
  - Increases the robot's power level by 20 units.

- **`POWER_TYPEDEF getPower() const`**
  - Retrieves the robot's current power level.
  - **Returns:** The power level as a `POWER_TYPEDEF`.


#### Communication with Server

- **`void login(std::string loginKey)`**
  - Logs in to the server using a specific key.
  - **Parameters:**
    - `loginKey`: The login key as a string.

- **`void needCharge()`**
  - Sends a request to the server indicating the need for charging.

- **`void sendToServer(MsgType type, const std::string payload)`**
  - Sends a message with a payload to the server.
  - **Parameters:**
    - `type`: The message type.
    - `payload`: The message payload.

- **`void sendToServer(MsgType type)`**
  - Sends a message to the server without a payload.
  - **Parameters:**
    - `type`: The message type.

- **`void sendToServer(MsgType type, const std::string payload, std::function<void(ADDR_TYPEDEF, const std::string&)> callback)`**
  - Sends a message with a payload to the server and registers a callback for the response.
  - **Parameters:**
    - `type`: The message type.
    - `payload`: The message payload.
    - `callback`: A function to handle the server's response.

- **`void sendToServer(MsgType type, std::function<void(ADDR_TYPEDEF, const std::string&)> callback)`**
  - Sends a message to the server without a payload and registers a callback for the response.
  - **Parameters:**
    - `type`: The message type.
    - `callback`: A function to handle the server's response.



#### Communication with Station

- **`void sendHandshakeToStation(std::string handShakey, ADDR_TYPEDEF stationAddr, CHANNEL_INDEX_TYPEDEF channelIndex)`**
  - Sends a handshake message to a charging station.
  - **Parameters:**
    - `handShakey`: The handshake key.
    - `stationAddr`: The address of the station.
    - `channelIndex`: The channel index for communication.

- **`void keepAliveWhenCharging()`**
  - Sends periodic signals to indicate the robot is active while charging.

- **`void sendPowerFinish(ADDR_TYPEDEF stationAddr)`**
  - Sends a message to the station indicating the charging process is complete.
  - **Parameters:**
    - `stationAddr`: The address of the charging station.


## Station Class

The `Station` class extends the `ProtocolDevice` class and represents a station that can be used by robots for various operations, such as charging. It handles communication with the server, state management, and position updates.



### Attributes

- **`occupied`** (`bool`): Indicates whether the station is occupied by a robot.
- **`loginSuccess`** (`bool`): A flag indicating whether the login process was successful.
- **`x`** (`POSITION_UNIT_TYPEDEF`): The x-coordinate of the station's position.
- **`y`** (`POSITION_UNIT_TYPEDEF`): The y-coordinate of the station's position.
- **`chargingBotAddr`** (`ADDR_TYPEDEF`): The address of the robot that is currently charging at the station.



### Methods

#### Constructor

- **`explicit Station(ADDR_TYPEDEF addr, Environment* en, POSITION_UNIT_TYPEDEF x, POSITION_UNIT_TYPEDEF y)`**
  - Initializes the `Station` object with the provided address, environment, and position.
  - **Parameters:**
    - `addr`: The station's address.
    - `en`: A pointer to the `Environment`.
    - `x`: The x-coordinate of the station's position.
    - `y`: The y-coordinate of the station's position.



#### Public Methods

- **`void log(const std::string& log)`**
  - Logs a message with the prefix "Station."
  - **Parameters:**
    - `log`: The message to log.

- **`void sendToServer(MsgType type, const std::string payload)`**
  - Sends a message with a payload to the server.
  - **Parameters:**
    - `type`: The type of the message.
    - `payload`: The message content.

- **`void sendToServer(MsgType type)`**
  - Sends a message to the server without a payload.
  - **Parameters:**
    - `type`: The type of the message.

- **`void sendToServer(MsgType type, const std::string payload, std::function<void(ADDR_TYPEDEF, const std::string&)> callback)`**
  - Sends a message with a payload to the server and provides a callback for a response.
  - **Parameters:**
    - `type`: The type of the message.
    - `payload`: The message content.
    - `callback`: The callback function to handle the response.

- **`void sendToServer(MsgType type, std::function<void(ADDR_TYPEDEF, const std::string&)> callback)`**
  - Sends a message to the server and provides a callback for a response.
  - **Parameters:**
    - `type`: The type of the message.
    - `callback`: The callback function to handle the response.

- **`void login(std::string loginKey)`**
  - Logs the station into the server using the provided login key.
  - **Parameters:**
    - `loginKey`: The login key for authentication.

- **`void updateFreeToServer(bool free)`**
  - Updates the station's status (free or occupied) to the server.
  - **Parameters:**
    - `free`: `true` if the station is free, `false` if occupied.

- **`void updatePositionToServer()`**
  - Updates the station's position to the server.

- **`POSITION_UNIT_TYPEDEF getX()`**
  - Returns the x-coordinate of the station's position.
  - **Returns:** The x-coordinate of the station.

- **`POSITION_UNIT_TYPEDEF getY()`**
  - Returns the y-coordinate of the station's position.
  - **Returns:** The y-coordinate of the station.

- **`void setOccupied(bool v)`**
  - Sets the station's occupancy status and updates its status to the server.
  - **Parameters:**
    - `v`: `true` to mark the station as occupied, `false` to mark it as free.

