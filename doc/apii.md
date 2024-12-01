# Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class `[`Channel`](#class_channel) | 
`class `[`Device`](#class_device) | 
`class `[`Environment`](#class_environment) | 
`class `[`Message`](#class_message) | 
`class `[`ProtocolDevice`](#class_protocol_device) | 
`class `[`Robot`](#class_robot) | 
`class `[`Server`](#class_server) | 
`class `[`SimEvent`](#class_sim_event) | 
`class `[`Station`](#class_station) | 
`struct `[`Position`](#struct_position) | 
`struct `[`RobotData`](#struct_robot_data) | 
`struct `[`StationData`](#struct_station_data) | 

# class `Channel` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  explicit `[`Channel`](#class_channel_1af2b4b16288cbb2c592b1e0f6486c2430)`()` | 
`public void `[`occupy`](#class_channel_1a733b7b41797a067390f6872131c3448a)`(const `[`Message`](#class_message)` * msg)` | 
`public void `[`release`](#class_channel_1a5c59db70405be66123e0b22fb35cddb5)`()` | 
`public inline void `[`addListener`](#class_channel_1ab57ee24162df76536876d508c2c4e552)`(`[`Device`](#class_device)` * d)` | 
`public inline void `[`removeListener`](#class_channel_1ac80e93a8ed9f15eda394225d4510c61d)`(`[`Device`](#class_device)` * d)` | 
`public inline bool `[`isBusy`](#class_channel_1a5a1f020188da7b6abc82a588a16802fc)`() const` | 
`public inline bool `[`isMixed`](#class_channel_1a1a105f4b40be364d318beea3957f49b6)`() const` | 
`public inline const `[`Message`](#class_message)` * `[`getMsg`](#class_channel_1afe08fe719287ea3677c445199bd0c13a)`() const` | 
`public inline std::list< `[`Device`](#class_device)` * > `[`getListeners`](#class_channel_1a926a93a5aa40892cf763c7589ff840fc)`() const` | 
`public inline void `[`error`](#class_channel_1adeb1a392a6f4756c02eb3eb32e3567f3)`(std::string s)` | 

## Members

#### `public inline  explicit `[`Channel`](#class_channel_1af2b4b16288cbb2c592b1e0f6486c2430)`()` 

#### `public void `[`occupy`](#class_channel_1a733b7b41797a067390f6872131c3448a)`(const `[`Message`](#class_message)` * msg)` 

#### `public void `[`release`](#class_channel_1a5c59db70405be66123e0b22fb35cddb5)`()` 

#### `public inline void `[`addListener`](#class_channel_1ab57ee24162df76536876d508c2c4e552)`(`[`Device`](#class_device)` * d)` 

#### `public inline void `[`removeListener`](#class_channel_1ac80e93a8ed9f15eda394225d4510c61d)`(`[`Device`](#class_device)` * d)` 

#### `public inline bool `[`isBusy`](#class_channel_1a5a1f020188da7b6abc82a588a16802fc)`() const` 

#### `public inline bool `[`isMixed`](#class_channel_1a1a105f4b40be364d318beea3957f49b6)`() const` 

#### `public inline const `[`Message`](#class_message)` * `[`getMsg`](#class_channel_1afe08fe719287ea3677c445199bd0c13a)`() const` 

#### `public inline std::list< `[`Device`](#class_device)` * > `[`getListeners`](#class_channel_1a926a93a5aa40892cf763c7589ff840fc)`() const` 

#### `public inline void `[`error`](#class_channel_1adeb1a392a6f4756c02eb3eb32e3567f3)`(std::string s)` 

# class `Device` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  explicit `[`Device`](#class_device_1a534415da35664d5a9ff6fcf043029e84)`(`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5)` addr,`[`Environment`](#class_environment)` * en)` | 
`public virtual void `[`recieve`](#class_device_1adb6173df7a804fef6dc7a8254927defa)`(const `[`Message`](#class_message)` * msg,`[`CHANNEL_INDEX_TYPEDEF`](#__common_8h_1a9635220f023976d87c59d9234b98f11f)` channelIndex)` | 
`public inline `[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5)` `[`getAddr`](#class_device_1a9e924a4fac8366d76f2aa661bf8d3dac)`() const` | 
`public void `[`listenTo`](#class_device_1a996cfa9dad7ff28bcd6ca50ce41b1f53)`(`[`CHANNEL_INDEX_TYPEDEF`](#__common_8h_1a9635220f023976d87c59d9234b98f11f)` channelIndex)` | 
`public void `[`setBusy`](#class_device_1aa77235051cbb8db5bdeb55acbf92c439)`(bool v)` | 
`public void `[`setWaiting`](#class_device_1a68a3860b803cff4e2c46fbdda9577428)`(bool v)` | 
`public inline void `[`setOnBusyChanged`](#class_device_1a2c7928822cfb7b6f85980a51b8f94b12)`(std::function< void(bool)> callback)` | 
`public inline void `[`setOnWaitingChanged`](#class_device_1aed2179d42305c3053d3f99bfe1af92b4)`(std::function< void(bool)> callback)` | 
`public inline void `[`setLogEnable`](#class_device_1a10a65f15883b944469d65cb775d35a7e)`(bool v)` | 
`public inline void `[`error`](#class_device_1a25112960d14acd64e7f1b8388af1e132)`(std::string s)` | 
`protected inline void `[`send`](#class_device_1a00e1d363811ad74a7267211440045246)`(const std::string & payload,`[`CHANNEL_INDEX_TYPEDEF`](#__common_8h_1a9635220f023976d87c59d9234b98f11f)` channelIndex,`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5)` target)` | 
`protected void `[`log`](#class_device_1a02a4dcfb2be69394026033da9c0e0614)`(const std::string & log)` | 

## Members

#### `public  explicit `[`Device`](#class_device_1a534415da35664d5a9ff6fcf043029e84)`(`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5)` addr,`[`Environment`](#class_environment)` * en)` 

#### `public virtual void `[`recieve`](#class_device_1adb6173df7a804fef6dc7a8254927defa)`(const `[`Message`](#class_message)` * msg,`[`CHANNEL_INDEX_TYPEDEF`](#__common_8h_1a9635220f023976d87c59d9234b98f11f)` channelIndex)` 

#### `public inline `[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5)` `[`getAddr`](#class_device_1a9e924a4fac8366d76f2aa661bf8d3dac)`() const` 

#### `public void `[`listenTo`](#class_device_1a996cfa9dad7ff28bcd6ca50ce41b1f53)`(`[`CHANNEL_INDEX_TYPEDEF`](#__common_8h_1a9635220f023976d87c59d9234b98f11f)` channelIndex)` 

#### `public void `[`setBusy`](#class_device_1aa77235051cbb8db5bdeb55acbf92c439)`(bool v)` 

#### `public void `[`setWaiting`](#class_device_1a68a3860b803cff4e2c46fbdda9577428)`(bool v)` 

#### `public inline void `[`setOnBusyChanged`](#class_device_1a2c7928822cfb7b6f85980a51b8f94b12)`(std::function< void(bool)> callback)` 

#### `public inline void `[`setOnWaitingChanged`](#class_device_1aed2179d42305c3053d3f99bfe1af92b4)`(std::function< void(bool)> callback)` 

#### `public inline void `[`setLogEnable`](#class_device_1a10a65f15883b944469d65cb775d35a7e)`(bool v)` 

#### `public inline void `[`error`](#class_device_1a25112960d14acd64e7f1b8388af1e132)`(std::string s)` 

#### `protected inline void `[`send`](#class_device_1a00e1d363811ad74a7267211440045246)`(const std::string & payload,`[`CHANNEL_INDEX_TYPEDEF`](#__common_8h_1a9635220f023976d87c59d9234b98f11f)` channelIndex,`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5)` target)` 

#### `protected void `[`log`](#class_device_1a02a4dcfb2be69394026033da9c0e0614)`(const std::string & log)` 

# class `Environment` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  explicit `[`Environment`](#class_environment_1a8b427c4448d8b7536666837521b9e83d)`()` | 
`public inline void `[`addDevice`](#class_environment_1ac1a4674ff36b23837ff896ff444acaed)`(`[`Device`](#class_device)` * d)` | 
`public void `[`broadcast`](#class_environment_1ab2ffb01d897494de982ba47995664a66)`(const `[`Message`](#class_message)` * msg,`[`CHANNEL_INDEX_TYPEDEF`](#__common_8h_1a9635220f023976d87c59d9234b98f11f)` channelIndex,`[`TIME_TYPEDEF`](#__common_8h_1a3aace27b10c3e64c3fdccbe040b919f2)` sendingTime)` | 
`public void `[`update`](#class_environment_1a879586e4021854ef00fd17cb0fd9d15b)`()` | 
`public `[`SimEvent`](#class_sim_event)` * `[`registerEvent`](#class_environment_1abbe8d27b056f87ee58682f24debbbe7f)`(`[`TIME_TYPEDEF`](#__common_8h_1a3aace27b10c3e64c3fdccbe040b919f2)` tick,std::function< void()> callback)` | 
`public inline `[`SimEvent`](#class_sim_event)` * `[`delayEvent`](#class_environment_1a3cbe818a3649fe4f67fff09eda16acdc)`(`[`TIME_TYPEDEF`](#__common_8h_1a3aace27b10c3e64c3fdccbe040b919f2)` delayTick,std::function< void()> callback)` | 
`public void `[`log`](#class_environment_1a556221f2bc3959f05e43b366456ad8fa)`(const std::string & log)` | 
`public inline `[`TIME_TYPEDEF`](#__common_8h_1a3aace27b10c3e64c3fdccbe040b919f2)` `[`getTime`](#class_environment_1a27723957d844c1823b3582f106fcd47e)`() const` | 
`public void `[`endAt`](#class_environment_1a36e11b20457079823571426f49467083)`(`[`TIME_TYPEDEF`](#__common_8h_1a3aace27b10c3e64c3fdccbe040b919f2)` time)` | 
`public void `[`stopRun`](#class_environment_1ad78876e4438b3943eeb04229c03ff412)`()` | 
`public void `[`run`](#class_environment_1a41a43b88702fff5df95e98d10e49f541)`()` | 
`public inline `[`Channel`](#class_channel)` * `[`getChannels`](#class_environment_1a1f14697142a2a1997451806c42b6c91b)`()` | 
`public inline void `[`error`](#class_environment_1a8c2f99c71bcdee586346c2a61efbb884)`(std::string s)` | 

## Members

#### `public inline  explicit `[`Environment`](#class_environment_1a8b427c4448d8b7536666837521b9e83d)`()` 

#### `public inline void `[`addDevice`](#class_environment_1ac1a4674ff36b23837ff896ff444acaed)`(`[`Device`](#class_device)` * d)` 

#### `public void `[`broadcast`](#class_environment_1ab2ffb01d897494de982ba47995664a66)`(const `[`Message`](#class_message)` * msg,`[`CHANNEL_INDEX_TYPEDEF`](#__common_8h_1a9635220f023976d87c59d9234b98f11f)` channelIndex,`[`TIME_TYPEDEF`](#__common_8h_1a3aace27b10c3e64c3fdccbe040b919f2)` sendingTime)` 

#### `public void `[`update`](#class_environment_1a879586e4021854ef00fd17cb0fd9d15b)`()` 

#### `public `[`SimEvent`](#class_sim_event)` * `[`registerEvent`](#class_environment_1abbe8d27b056f87ee58682f24debbbe7f)`(`[`TIME_TYPEDEF`](#__common_8h_1a3aace27b10c3e64c3fdccbe040b919f2)` tick,std::function< void()> callback)` 

#### `public inline `[`SimEvent`](#class_sim_event)` * `[`delayEvent`](#class_environment_1a3cbe818a3649fe4f67fff09eda16acdc)`(`[`TIME_TYPEDEF`](#__common_8h_1a3aace27b10c3e64c3fdccbe040b919f2)` delayTick,std::function< void()> callback)` 

#### `public void `[`log`](#class_environment_1a556221f2bc3959f05e43b366456ad8fa)`(const std::string & log)` 

#### `public inline `[`TIME_TYPEDEF`](#__common_8h_1a3aace27b10c3e64c3fdccbe040b919f2)` `[`getTime`](#class_environment_1a27723957d844c1823b3582f106fcd47e)`() const` 

#### `public void `[`endAt`](#class_environment_1a36e11b20457079823571426f49467083)`(`[`TIME_TYPEDEF`](#__common_8h_1a3aace27b10c3e64c3fdccbe040b919f2)` time)` 

#### `public void `[`stopRun`](#class_environment_1ad78876e4438b3943eeb04229c03ff412)`()` 

#### `public void `[`run`](#class_environment_1a41a43b88702fff5df95e98d10e49f541)`()` 

#### `public inline `[`Channel`](#class_channel)` * `[`getChannels`](#class_environment_1a1f14697142a2a1997451806c42b6c91b)`()` 

#### `public inline void `[`error`](#class_environment_1a8c2f99c71bcdee586346c2a61efbb884)`(std::string s)` 

# class `Message` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public std::string `[`sender`](#class_message_1ab5549d9090edf543845ee21135c65bab) | 
`public std::string `[`target`](#class_message_1ad0489c1c0b8cecca393cd22f38757f0e) | 
`public std::string `[`payload`](#class_message_1a3c356102b83f3a77406a8d39bdeb0b18) | 
`public inline  explicit `[`Message`](#class_message_1a6fb6e5ae781217870dcd1d99fea59e07)`(`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5)` sender,`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5)` target,std::string payload)` | 

## Members

#### `public std::string `[`sender`](#class_message_1ab5549d9090edf543845ee21135c65bab) 

#### `public std::string `[`target`](#class_message_1ad0489c1c0b8cecca393cd22f38757f0e) 

#### `public std::string `[`payload`](#class_message_1a3c356102b83f3a77406a8d39bdeb0b18) 

#### `public inline  explicit `[`Message`](#class_message_1a6fb6e5ae781217870dcd1d99fea59e07)`(`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5)` sender,`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5)` target,std::string payload)` 

# class `ProtocolDevice` 

```
class ProtocolDevice
  : public Device
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  explicit `[`ProtocolDevice`](#class_protocol_device_1a86fe6dd895e9d31cb02f25aedeec4517)`(`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5)` addr,`[`Environment`](#class_environment)` * en)` | 
`public inline std::string `[`formatKeyStr`](#class_protocol_device_1ad4878a8e00eb38999144ea75b28b5015)`(const std::string & key)` | 
`public inline std::string `[`MsgTypeToHexString`](#class_protocol_device_1aa0da4767b6297edc518c84b9cc296e93)`(`[`MsgType`](#__common_8h_1a4d47dc9870566f2f294eaab1426094a2)` num)` | 
`public inline `[`MsgType`](#__common_8h_1a4d47dc9870566f2f294eaab1426094a2)` `[`hexStringToMsgType`](#class_protocol_device_1a7716806817011df76d855f30cf3f2b23)`(const std::string & hexStr)` | 
`public inline void `[`send`](#class_protocol_device_1ac8e76689b597199de9732533a9e18f0d)`(`[`MsgType`](#__common_8h_1a4d47dc9870566f2f294eaab1426094a2)` type,const std::string payload,`[`CHANNEL_INDEX_TYPEDEF`](#__common_8h_1a9635220f023976d87c59d9234b98f11f)` channelIndex,`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5)` target)` | 
`public inline void `[`send`](#class_protocol_device_1af611022232cd75f5a381a3249680c073)`(`[`MsgType`](#__common_8h_1a4d47dc9870566f2f294eaab1426094a2)` type,`[`CHANNEL_INDEX_TYPEDEF`](#__common_8h_1a9635220f023976d87c59d9234b98f11f)` channelIndex,`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5)` target)` | 
`public inline void `[`send`](#class_protocol_device_1ae7a3396842456d09c8d99adcbbb8b33f)`(`[`MsgType`](#__common_8h_1a4d47dc9870566f2f294eaab1426094a2)` type,const std::string payload,`[`CHANNEL_INDEX_TYPEDEF`](#__common_8h_1a9635220f023976d87c59d9234b98f11f)` channelIndex,`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5)` target,std::function< void(`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5), const std::string &)`> callback)` | 
`public inline void `[`send`](#class_protocol_device_1a6b00e2e8334f0184b9930a388de9ce0e)`(`[`MsgType`](#__common_8h_1a4d47dc9870566f2f294eaab1426094a2)` type,`[`CHANNEL_INDEX_TYPEDEF`](#__common_8h_1a9635220f023976d87c59d9234b98f11f)` channelIndex,`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5)` target,std::function< void(`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5), const std::string &)`> callback)` | 
`public inline void `[`on`](#class_protocol_device_1a1ac42bba860be61ca6867ff7f9978b1a)`(`[`MsgType`](#__common_8h_1a4d47dc9870566f2f294eaab1426094a2)` type,std::function< void(`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5), const std::string &)`> callback)` | 
`public inline void `[`once`](#class_protocol_device_1a201e9643176a39facc54e6e00bc8cd44)`(`[`MsgType`](#__common_8h_1a4d47dc9870566f2f294eaab1426094a2)` type,std::function< void(`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5), const std::string &)`> callback)` | 
`public inline void `[`msgHandler`](#class_protocol_device_1ab499901dbec84769ab86d6eb99d418ea)`(`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5)` senderAddr,`[`MsgType`](#__common_8h_1a4d47dc9870566f2f294eaab1426094a2)` type,const std::string & payload)` | 
`public inline virtual void `[`recieve`](#class_protocol_device_1a1f54fd7c5d99d865446e670080838fba)`(const `[`Message`](#class_message)` * msg,`[`CHANNEL_INDEX_TYPEDEF`](#__common_8h_1a9635220f023976d87c59d9234b98f11f)` channelIndex)` | 
`public inline void `[`log`](#class_protocol_device_1a54848a94b7290bc42b846be899758e41)`(const std::string & who,const std::string & log)` | 

## Members

#### `public inline  explicit `[`ProtocolDevice`](#class_protocol_device_1a86fe6dd895e9d31cb02f25aedeec4517)`(`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5)` addr,`[`Environment`](#class_environment)` * en)` 

#### `public inline std::string `[`formatKeyStr`](#class_protocol_device_1ad4878a8e00eb38999144ea75b28b5015)`(const std::string & key)` 

#### `public inline std::string `[`MsgTypeToHexString`](#class_protocol_device_1aa0da4767b6297edc518c84b9cc296e93)`(`[`MsgType`](#__common_8h_1a4d47dc9870566f2f294eaab1426094a2)` num)` 

#### `public inline `[`MsgType`](#__common_8h_1a4d47dc9870566f2f294eaab1426094a2)` `[`hexStringToMsgType`](#class_protocol_device_1a7716806817011df76d855f30cf3f2b23)`(const std::string & hexStr)` 

#### `public inline void `[`send`](#class_protocol_device_1ac8e76689b597199de9732533a9e18f0d)`(`[`MsgType`](#__common_8h_1a4d47dc9870566f2f294eaab1426094a2)` type,const std::string payload,`[`CHANNEL_INDEX_TYPEDEF`](#__common_8h_1a9635220f023976d87c59d9234b98f11f)` channelIndex,`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5)` target)` 

#### `public inline void `[`send`](#class_protocol_device_1af611022232cd75f5a381a3249680c073)`(`[`MsgType`](#__common_8h_1a4d47dc9870566f2f294eaab1426094a2)` type,`[`CHANNEL_INDEX_TYPEDEF`](#__common_8h_1a9635220f023976d87c59d9234b98f11f)` channelIndex,`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5)` target)` 

#### `public inline void `[`send`](#class_protocol_device_1ae7a3396842456d09c8d99adcbbb8b33f)`(`[`MsgType`](#__common_8h_1a4d47dc9870566f2f294eaab1426094a2)` type,const std::string payload,`[`CHANNEL_INDEX_TYPEDEF`](#__common_8h_1a9635220f023976d87c59d9234b98f11f)` channelIndex,`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5)` target,std::function< void(`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5), const std::string &)`> callback)` 

#### `public inline void `[`send`](#class_protocol_device_1a6b00e2e8334f0184b9930a388de9ce0e)`(`[`MsgType`](#__common_8h_1a4d47dc9870566f2f294eaab1426094a2)` type,`[`CHANNEL_INDEX_TYPEDEF`](#__common_8h_1a9635220f023976d87c59d9234b98f11f)` channelIndex,`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5)` target,std::function< void(`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5), const std::string &)`> callback)` 

#### `public inline void `[`on`](#class_protocol_device_1a1ac42bba860be61ca6867ff7f9978b1a)`(`[`MsgType`](#__common_8h_1a4d47dc9870566f2f294eaab1426094a2)` type,std::function< void(`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5), const std::string &)`> callback)` 

#### `public inline void `[`once`](#class_protocol_device_1a201e9643176a39facc54e6e00bc8cd44)`(`[`MsgType`](#__common_8h_1a4d47dc9870566f2f294eaab1426094a2)` type,std::function< void(`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5), const std::string &)`> callback)` 

#### `public inline void `[`msgHandler`](#class_protocol_device_1ab499901dbec84769ab86d6eb99d418ea)`(`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5)` senderAddr,`[`MsgType`](#__common_8h_1a4d47dc9870566f2f294eaab1426094a2)` type,const std::string & payload)` 

#### `public inline virtual void `[`recieve`](#class_protocol_device_1a1f54fd7c5d99d865446e670080838fba)`(const `[`Message`](#class_message)` * msg,`[`CHANNEL_INDEX_TYPEDEF`](#__common_8h_1a9635220f023976d87c59d9234b98f11f)` channelIndex)` 

#### `public inline void `[`log`](#class_protocol_device_1a54848a94b7290bc42b846be899758e41)`(const std::string & who,const std::string & log)` 

# class `Robot` 

```
class Robot
  : public ProtocolDevice
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  explicit `[`Robot`](#class_robot_1a5b96001154c6eeca6c7e546da8d1a009)`(`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5)` addr,`[`Environment`](#class_environment)` * en)` | 
`public inline void `[`listenTo`](#class_robot_1a9f9a68752b98bc25226f82414fc175b9)`(`[`CHANNEL_INDEX_TYPEDEF`](#__common_8h_1a9635220f023976d87c59d9234b98f11f)` channelIndex)` | 
`public inline void `[`log`](#class_robot_1a2760106a796c73b8e228858a459a35ae)`(const std::string & log)` | 
`public inline void `[`gotoPosition`](#class_robot_1a3c20a96cd27f849c2f9de4732529a07f)`(`[`Position`](#struct_position)` pos)` | 
`public inline void `[`chagingUp`](#class_robot_1a121dc12f848b37b9d446ec5a981b7428)`()` | 
`public inline `[`POWER_TYPEDEF`](#__common_8h_1ac90ccc37e41cdc297ad40132bdde4bdf)` `[`getPower`](#class_robot_1a5e30da99242282a7b48a3ee2717d440b)`() const` | 
`public void `[`login`](#class_robot_1acd8deb1e7ac139808adf1a451e8129ac)`(std::string loginKey)` | 
`public void `[`needCharge`](#class_robot_1ac1ec0b09fbaf4e34963210f85f94e70e)`()` | 
`public inline void `[`sendToServer`](#class_robot_1a226257e1f1a395ff3b679a94ff0c617a)`(`[`MsgType`](#__common_8h_1a4d47dc9870566f2f294eaab1426094a2)` type,const std::string payload)` | 
`public inline void `[`sendToServer`](#class_robot_1a68d609ae8ef5f328eb06e00f8e6aee5a)`(`[`MsgType`](#__common_8h_1a4d47dc9870566f2f294eaab1426094a2)` type)` | 
`public inline void `[`sendToServer`](#class_robot_1a516db19bce370845c445bed8a6af19e0)`(`[`MsgType`](#__common_8h_1a4d47dc9870566f2f294eaab1426094a2)` type,const std::string payload,std::function< void(`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5), const std::string &)`> callback)` | 
`public inline void `[`sendToServer`](#class_robot_1a2bd9a5a79fd59b6772e6dbb6582d26ef)`(`[`MsgType`](#__common_8h_1a4d47dc9870566f2f294eaab1426094a2)` type,std::function< void(`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5), const std::string &)`> callback)` | 
`public void `[`sendHandshakeToStation`](#class_robot_1a88731bc2d8090b7574ebe64e2452a9f6)`(std::string handShakey,`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5)` stationAddr,`[`CHANNEL_INDEX_TYPEDEF`](#__common_8h_1a9635220f023976d87c59d9234b98f11f)` channelIndex)` | 
`public inline void `[`keepAliveWhenCharging`](#class_robot_1a90a91424068bd658ed431162d929049c)`()` | 
`public inline void `[`sendPowerFinish`](#class_robot_1ac437a1d7ac2c8ec686ab0df30fcf95e5)`(`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5)` stationAddr)` | 

## Members

#### `public  explicit `[`Robot`](#class_robot_1a5b96001154c6eeca6c7e546da8d1a009)`(`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5)` addr,`[`Environment`](#class_environment)` * en)` 

#### `public inline void `[`listenTo`](#class_robot_1a9f9a68752b98bc25226f82414fc175b9)`(`[`CHANNEL_INDEX_TYPEDEF`](#__common_8h_1a9635220f023976d87c59d9234b98f11f)` channelIndex)` 

#### `public inline void `[`log`](#class_robot_1a2760106a796c73b8e228858a459a35ae)`(const std::string & log)` 

#### `public inline void `[`gotoPosition`](#class_robot_1a3c20a96cd27f849c2f9de4732529a07f)`(`[`Position`](#struct_position)` pos)` 

#### `public inline void `[`chagingUp`](#class_robot_1a121dc12f848b37b9d446ec5a981b7428)`()` 

#### `public inline `[`POWER_TYPEDEF`](#__common_8h_1ac90ccc37e41cdc297ad40132bdde4bdf)` `[`getPower`](#class_robot_1a5e30da99242282a7b48a3ee2717d440b)`() const` 

#### `public void `[`login`](#class_robot_1acd8deb1e7ac139808adf1a451e8129ac)`(std::string loginKey)` 

#### `public void `[`needCharge`](#class_robot_1ac1ec0b09fbaf4e34963210f85f94e70e)`()` 

#### `public inline void `[`sendToServer`](#class_robot_1a226257e1f1a395ff3b679a94ff0c617a)`(`[`MsgType`](#__common_8h_1a4d47dc9870566f2f294eaab1426094a2)` type,const std::string payload)` 

#### `public inline void `[`sendToServer`](#class_robot_1a68d609ae8ef5f328eb06e00f8e6aee5a)`(`[`MsgType`](#__common_8h_1a4d47dc9870566f2f294eaab1426094a2)` type)` 

#### `public inline void `[`sendToServer`](#class_robot_1a516db19bce370845c445bed8a6af19e0)`(`[`MsgType`](#__common_8h_1a4d47dc9870566f2f294eaab1426094a2)` type,const std::string payload,std::function< void(`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5), const std::string &)`> callback)` 

#### `public inline void `[`sendToServer`](#class_robot_1a2bd9a5a79fd59b6772e6dbb6582d26ef)`(`[`MsgType`](#__common_8h_1a4d47dc9870566f2f294eaab1426094a2)` type,std::function< void(`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5), const std::string &)`> callback)` 

#### `public void `[`sendHandshakeToStation`](#class_robot_1a88731bc2d8090b7574ebe64e2452a9f6)`(std::string handShakey,`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5)` stationAddr,`[`CHANNEL_INDEX_TYPEDEF`](#__common_8h_1a9635220f023976d87c59d9234b98f11f)` channelIndex)` 

#### `public inline void `[`keepAliveWhenCharging`](#class_robot_1a90a91424068bd658ed431162d929049c)`()` 

#### `public inline void `[`sendPowerFinish`](#class_robot_1ac437a1d7ac2c8ec686ab0df30fcf95e5)`(`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5)` stationAddr)` 

# class `Server` 

```
class Server
  : public ProtocolDevice
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  explicit `[`Server`](#class_server_1a7f8fbb3f78926eba5ca1552bf3481830)`(`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5)` addr,`[`Environment`](#class_environment)` * en)` | 
`public inline bool `[`isRobot`](#class_server_1a2acad211a3a98c6c08db2a4f3df9c184)`(`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5)` addr)` | 
`public inline bool `[`isStation`](#class_server_1a0b51c982917606fcdf3dfa620fcd3247)`(`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5)` addr)` | 
`public `[`StationData`](#struct_station_data)` * `[`getFreeStation`](#class_server_1a629a67198cf2a17f0d59131312eb7e26)`()` | 
`public inline void `[`setStationStatus`](#class_server_1aec2c8a08fe665a31d1ac62d502a73d7f)`(`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5)` addr,bool free)` | 
`public inline void `[`setRobotLoginKey`](#class_server_1a67c294d571d4c0fc45a797606940e2c3)`(const std::string & key)` | 
`public inline void `[`setStationLoginKey`](#class_server_1a04646e818326caa845257aeaa6a2b127)`(const std::string & key)` | 
`public inline void `[`addRobotAddr`](#class_server_1a6ea296e311b8156d4dcbded0807484db)`(`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5)` addr)` | 
`public inline void `[`addStationAddr`](#class_server_1a9bf195783d3c2a70c5b92fdb7ea4339d)`(`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5)` addr)` | 
`public inline void `[`listenTo`](#class_server_1a33bd24089bb8edb7edba8119a2377d35)`(`[`CHANNEL_INDEX_TYPEDEF`](#__common_8h_1a9635220f023976d87c59d9234b98f11f)` channelIndex)` | 
`public inline void `[`log`](#class_server_1a766d13d11edb006fdf256928a3d7aa3b)`(const std::string & log)` | 

## Members

#### `public  explicit `[`Server`](#class_server_1a7f8fbb3f78926eba5ca1552bf3481830)`(`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5)` addr,`[`Environment`](#class_environment)` * en)` 

#### `public inline bool `[`isRobot`](#class_server_1a2acad211a3a98c6c08db2a4f3df9c184)`(`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5)` addr)` 

#### `public inline bool `[`isStation`](#class_server_1a0b51c982917606fcdf3dfa620fcd3247)`(`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5)` addr)` 

#### `public `[`StationData`](#struct_station_data)` * `[`getFreeStation`](#class_server_1a629a67198cf2a17f0d59131312eb7e26)`()` 

#### `public inline void `[`setStationStatus`](#class_server_1aec2c8a08fe665a31d1ac62d502a73d7f)`(`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5)` addr,bool free)` 

#### `public inline void `[`setRobotLoginKey`](#class_server_1a67c294d571d4c0fc45a797606940e2c3)`(const std::string & key)` 

#### `public inline void `[`setStationLoginKey`](#class_server_1a04646e818326caa845257aeaa6a2b127)`(const std::string & key)` 

#### `public inline void `[`addRobotAddr`](#class_server_1a6ea296e311b8156d4dcbded0807484db)`(`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5)` addr)` 

#### `public inline void `[`addStationAddr`](#class_server_1a9bf195783d3c2a70c5b92fdb7ea4339d)`(`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5)` addr)` 

#### `public inline void `[`listenTo`](#class_server_1a33bd24089bb8edb7edba8119a2377d35)`(`[`CHANNEL_INDEX_TYPEDEF`](#__common_8h_1a9635220f023976d87c59d9234b98f11f)` channelIndex)` 

#### `public inline void `[`log`](#class_server_1a766d13d11edb006fdf256928a3d7aa3b)`(const std::string & log)` 

# class `SimEvent` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  explicit `[`SimEvent`](#class_sim_event_1a7e14a8f9726c5d4369cdc1fd4e11770c)`(`[`Environment`](#class_environment)` * en,`[`TIME_TYPEDEF`](#__common_8h_1a3aace27b10c3e64c3fdccbe040b919f2)` emitTick,std::function< void()> callback)` | 
`public `[`SimEvent`](#class_sim_event)` * `[`then`](#class_sim_event_1a931ac60ebd300eae7ad05f2b40197ee3)`(`[`TIME_TYPEDEF`](#__common_8h_1a3aace27b10c3e64c3fdccbe040b919f2)` delayTime,std::function< void()> callback)` | 
`public void `[`emit`](#class_sim_event_1a7e49f244ab65e1eedc879cc8ee130c3c)`()` | 
`public inline `[`TIME_TYPEDEF`](#__common_8h_1a3aace27b10c3e64c3fdccbe040b919f2)` `[`getEmitTick`](#class_sim_event_1a24c6ed79591db033b7e6ca11582df889)`() const` | 

## Members

#### `public  explicit `[`SimEvent`](#class_sim_event_1a7e14a8f9726c5d4369cdc1fd4e11770c)`(`[`Environment`](#class_environment)` * en,`[`TIME_TYPEDEF`](#__common_8h_1a3aace27b10c3e64c3fdccbe040b919f2)` emitTick,std::function< void()> callback)` 

#### `public `[`SimEvent`](#class_sim_event)` * `[`then`](#class_sim_event_1a931ac60ebd300eae7ad05f2b40197ee3)`(`[`TIME_TYPEDEF`](#__common_8h_1a3aace27b10c3e64c3fdccbe040b919f2)` delayTime,std::function< void()> callback)` 

#### `public void `[`emit`](#class_sim_event_1a7e49f244ab65e1eedc879cc8ee130c3c)`()` 

#### `public inline `[`TIME_TYPEDEF`](#__common_8h_1a3aace27b10c3e64c3fdccbe040b919f2)` `[`getEmitTick`](#class_sim_event_1a24c6ed79591db033b7e6ca11582df889)`() const` 

# class `Station` 

```
class Station
  : public ProtocolDevice
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  explicit `[`Station`](#class_station_1a9781dc4c4717fa7f3880c6e8051bd68f)`(`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5)` addr,`[`Environment`](#class_environment)` * en,`[`POSITION_UNIT_TYPEDEF`](#__common_8h_1affbae0dfdb59a8bb112e3b264b61e612)` x,`[`POSITION_UNIT_TYPEDEF`](#__common_8h_1affbae0dfdb59a8bb112e3b264b61e612)` y)` | 
`public inline void `[`log`](#class_station_1a5e9e7306431b60b151ce7a3ee8d5dd0c)`(const std::string & log)` | 
`public inline void `[`sendToServer`](#class_station_1ad61f3530485792bb90ede98fd3468df0)`(`[`MsgType`](#__common_8h_1a4d47dc9870566f2f294eaab1426094a2)` type,const std::string payload)` | 
`public inline void `[`sendToServer`](#class_station_1a843dd06e85f20ff0cc392afcd71bab12)`(`[`MsgType`](#__common_8h_1a4d47dc9870566f2f294eaab1426094a2)` type)` | 
`public inline void `[`sendToServer`](#class_station_1a5aa24240e29adab6f3ba0c7da8e8e6bb)`(`[`MsgType`](#__common_8h_1a4d47dc9870566f2f294eaab1426094a2)` type,const std::string payload,std::function< void(`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5), const std::string &)`> callback)` | 
`public inline void `[`sendToServer`](#class_station_1a2c2787a64c2e4780bcb49b1547bc2513)`(`[`MsgType`](#__common_8h_1a4d47dc9870566f2f294eaab1426094a2)` type,std::function< void(`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5), const std::string &)`> callback)` | 
`public void `[`login`](#class_station_1a2898b77556eb45cc99a69802a25ffb4c)`(std::string loginKey)` | 
`public void `[`updateFreeToServer`](#class_station_1aae013d77b9ddc54d2291327cc85cc6b2)`(bool free)` | 
`public void `[`updatePositionToServer`](#class_station_1aef4881fbd46e090ff84bc58984bf906b)`()` | 
`public inline `[`POSITION_UNIT_TYPEDEF`](#__common_8h_1affbae0dfdb59a8bb112e3b264b61e612)` `[`getX`](#class_station_1aa171db72c2471720b3d1fe30dfec5a36)`()` | 
`public inline `[`POSITION_UNIT_TYPEDEF`](#__common_8h_1affbae0dfdb59a8bb112e3b264b61e612)` `[`getY`](#class_station_1a4a6eefeff825559f5ef8310446170b90)`()` | 
`public inline void `[`setOccupied`](#class_station_1af3c6a6095fa84a46aa7549a82d1932ad)`(bool v)` | 

## Members

#### `public  explicit `[`Station`](#class_station_1a9781dc4c4717fa7f3880c6e8051bd68f)`(`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5)` addr,`[`Environment`](#class_environment)` * en,`[`POSITION_UNIT_TYPEDEF`](#__common_8h_1affbae0dfdb59a8bb112e3b264b61e612)` x,`[`POSITION_UNIT_TYPEDEF`](#__common_8h_1affbae0dfdb59a8bb112e3b264b61e612)` y)` 

#### `public inline void `[`log`](#class_station_1a5e9e7306431b60b151ce7a3ee8d5dd0c)`(const std::string & log)` 

#### `public inline void `[`sendToServer`](#class_station_1ad61f3530485792bb90ede98fd3468df0)`(`[`MsgType`](#__common_8h_1a4d47dc9870566f2f294eaab1426094a2)` type,const std::string payload)` 

#### `public inline void `[`sendToServer`](#class_station_1a843dd06e85f20ff0cc392afcd71bab12)`(`[`MsgType`](#__common_8h_1a4d47dc9870566f2f294eaab1426094a2)` type)` 

#### `public inline void `[`sendToServer`](#class_station_1a5aa24240e29adab6f3ba0c7da8e8e6bb)`(`[`MsgType`](#__common_8h_1a4d47dc9870566f2f294eaab1426094a2)` type,const std::string payload,std::function< void(`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5), const std::string &)`> callback)` 

#### `public inline void `[`sendToServer`](#class_station_1a2c2787a64c2e4780bcb49b1547bc2513)`(`[`MsgType`](#__common_8h_1a4d47dc9870566f2f294eaab1426094a2)` type,std::function< void(`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5), const std::string &)`> callback)` 

#### `public void `[`login`](#class_station_1a2898b77556eb45cc99a69802a25ffb4c)`(std::string loginKey)` 

#### `public void `[`updateFreeToServer`](#class_station_1aae013d77b9ddc54d2291327cc85cc6b2)`(bool free)` 

#### `public void `[`updatePositionToServer`](#class_station_1aef4881fbd46e090ff84bc58984bf906b)`()` 

#### `public inline `[`POSITION_UNIT_TYPEDEF`](#__common_8h_1affbae0dfdb59a8bb112e3b264b61e612)` `[`getX`](#class_station_1aa171db72c2471720b3d1fe30dfec5a36)`()` 

#### `public inline `[`POSITION_UNIT_TYPEDEF`](#__common_8h_1affbae0dfdb59a8bb112e3b264b61e612)` `[`getY`](#class_station_1a4a6eefeff825559f5ef8310446170b90)`()` 

#### `public inline void `[`setOccupied`](#class_station_1af3c6a6095fa84a46aa7549a82d1932ad)`(bool v)` 

# struct `Position` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public `[`POSITION_UNIT_TYPEDEF`](#__common_8h_1affbae0dfdb59a8bb112e3b264b61e612)` `[`x`](#struct_position_1ab9dc827ef4eb6bc0baa0bf7fbb952216) | 
`public `[`POSITION_UNIT_TYPEDEF`](#__common_8h_1affbae0dfdb59a8bb112e3b264b61e612)` `[`y`](#struct_position_1a75d8f39a70a68518d5c8d0d8086fa100) | 

## Members

#### `public `[`POSITION_UNIT_TYPEDEF`](#__common_8h_1affbae0dfdb59a8bb112e3b264b61e612)` `[`x`](#struct_position_1ab9dc827ef4eb6bc0baa0bf7fbb952216) 

#### `public `[`POSITION_UNIT_TYPEDEF`](#__common_8h_1affbae0dfdb59a8bb112e3b264b61e612)` `[`y`](#struct_position_1a75d8f39a70a68518d5c8d0d8086fa100) 

# struct `RobotData` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  explicit `[`RobotData`](#struct_robot_data_1a0007f4b014a950d356d2d63156b572af)`()` | 

## Members

#### `public inline  explicit `[`RobotData`](#struct_robot_data_1a0007f4b014a950d356d2d63156b572af)`()` 

# struct `StationData` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public `[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5)` `[`addr`](#struct_station_data_1a0a2865baaeb6b7e48d5cfd6f1ba78f58) | 
`public bool `[`free`](#struct_station_data_1ad7be5eb9da812dd11274f9a9a4f4cf5f) | 
`public `[`POSITION_UNIT_TYPEDEF`](#__common_8h_1affbae0dfdb59a8bb112e3b264b61e612)` `[`x`](#struct_station_data_1a578b66c3a3d771447a5553ba4ed7bfc6) | 
`public `[`POSITION_UNIT_TYPEDEF`](#__common_8h_1affbae0dfdb59a8bb112e3b264b61e612)` `[`y`](#struct_station_data_1a33a06bfb92e429730c71b4bc89299205) | 
`public inline  explicit `[`StationData`](#struct_station_data_1a07804cb95111bbbb828cc8964950f417)`(`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5)` addr)` | 

## Members

#### `public `[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5)` `[`addr`](#struct_station_data_1a0a2865baaeb6b7e48d5cfd6f1ba78f58) 

#### `public bool `[`free`](#struct_station_data_1ad7be5eb9da812dd11274f9a9a4f4cf5f) 

#### `public `[`POSITION_UNIT_TYPEDEF`](#__common_8h_1affbae0dfdb59a8bb112e3b264b61e612)` `[`x`](#struct_station_data_1a578b66c3a3d771447a5553ba4ed7bfc6) 

#### `public `[`POSITION_UNIT_TYPEDEF`](#__common_8h_1affbae0dfdb59a8bb112e3b264b61e612)` `[`y`](#struct_station_data_1a33a06bfb92e429730c71b4bc89299205) 

#### `public inline  explicit `[`StationData`](#struct_station_data_1a07804cb95111bbbb828cc8964950f417)`(`[`ADDR_TYPEDEF`](#__common_8h_1ace694e2135c52226445db7abe85136b5)` addr)` 

Generated by [Moxygen](https://sourcey.com/moxygen)