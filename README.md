Concurrent Order Processor
Concurrent Order Processor is a comprehensive C++ application designed to demonstrate advanced programming concepts such as design patterns and multithreading. The project showcases how to build an efficient order management system using a combination of Singleton, Observer, Factory Method, and Command patterns. It also integrates multithreading for concurrent processing and simulates file-based data storage.

Features
Singleton Pattern: Implements a FileManager class that ensures a single instance is used for file operations, simplifying file handling and avoiding conflicts.
Observer Pattern: Utilizes OrderObserver and ConcreteOrderObserver to provide notifications about order updates. Observers are notified whenever a new order is placed.
Factory Method Pattern: Employs ProductFactory and its concrete implementation, ConcreteProductFactory, to create instances of Product. This pattern allows for flexible and scalable product creation.
Command Pattern: Used in the OrderProcessor class to handle the processing of orders. Orders are processed in separate threads to enhance efficiency and responsiveness.
Multithreading: Utilizes C++ threads to process orders concurrently, allowing the system to handle multiple orders simultaneously without blocking the main execution flow.
File I/O: Orders are serialized and stored in a text file (orders.txt). The FileManager class handles file operations, ensuring data is written and read efficiently.

