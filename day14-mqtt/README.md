# Day 14: MQTT Protocol – IoT Communication

## What I Learned

### MQTT Core Concepts
- **Broker** – Central server routing messages
- **Publisher** – Device sending data
- **Subscriber** – Device receiving data
- **Topic** – Message channel name
- **QoS** – Quality of Service (0,1,2)

### Why MQTT for IoT
- Low bandwidth usage
- Real-time communication
- One-to-many messaging
- Battery efficient

### PubSubClient Functions
```cpp
client.setServer(broker, port);    // Set broker
client.setCallback(callback);       // Set message handler
client.connect(clientId);           // Connect
client.subscribe(topic);            // Subscribe
client.publish(topic, message);     // Publish
client.loop();                      // Process messages
