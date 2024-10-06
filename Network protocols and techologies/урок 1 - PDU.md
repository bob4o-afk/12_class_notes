# Network Fundamentals and Protocol Data Units

## Protocol Data Unit (PDU)

- **Definition**: A Protocol Data Unit is a specific block of information transferred over a network. Each layer of the OSI model uses its own type of PDU:
  - **Physical Layer (Layer 1)**: Bits
  - **Data Link Layer (Layer 2)**: Frames
  - **Network Layer (Layer 3)**: Packets
  - **Transport Layer (Layer 4)**: Segments

## Broadcast and Collision Domains

- **Broadcast Domain**: A network segment where if one device sends a broadcast message, all devices receive it. Routers typically separate broadcast domains.
- **Collision Domain**: A network area where data packets can collide with one another when being sent over a shared medium. Switches and bridges can separate collision domains.

## Networking Devices

### Switch

- **Function**: Connects multiple end devices within a local area network (LAN).
- **Operation**: Works at the Data Link Layer (Layer 2) of the OSI model.
- **Capabilities**:
  - Forwards data based on MAC addresses.
  - Does not process or understand IP addresses.

### Router

- **Function**: Directs data packets between different networks.
- **Operation**: Works at the Network Layer (Layer 3) of the OSI model.
- **Capabilities**:
  - Determines optimal paths for data transmission.
  - Processes and understands IP addresses.

## Ethernet Frames

### Frame

- **Definition**: A data packet at the Data Link Layer, containing necessary control information to move data from point A to point B within a local network.

### Jumbo Frame

- **Definition**: Ethernet frames that carry more than the standard maximum of 1,500 bytes of payload.
- **Specification**: Can carry up to 9,000 bytes of payload.
- **Standard**: Exceed the limit set by the IEEE 802.3 standard.
- **Usage**: Reduce overhead and improve efficiency for large data transfers.

## VLAN (Virtual Local Area Network)

- **Standard**: Defined by **IEEE 802.1Q**.
- **Function**: Allows network administrators to segment networks logically without physical separation.
- **Benefit**: Improves network performance and security by isolating broadcast traffic within VLANs.

## Wake-on-LAN (WoL)

- **Definition**: A networking standard that allows a computer to be turned on or awakened remotely by a network message.
- **Mechanism**: Utilizes a "magic packet" broadcasted over the local network to the target machine's MAC address.
- **Use Cases**: Remote management, energy savings by powering off unused machines.