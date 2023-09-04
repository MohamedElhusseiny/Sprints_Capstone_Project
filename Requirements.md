**IPC_LIBRARY**
- Objective
  - The library is built for other applications' usage
  - The library provides API to ease the communication between different processes
  - The library shall handle the creation of the message queues internally and handle errors
- Content
  - The library shall provide two classes
    - The first class is used by the receiver to handle the following :
      - message_que creation
      - message_que receiving values, shall take into consideration:
        - API used for reception could be synchronous (blocking)
        - API used for the reception could be asynchronous (non-blocking)
    - The second class shall be responsible for the sender to handle the following :
      - message_que connecting on an already existing message_que created by the receiver
        - In case the receiver does not exist then it returns an error
      - API used to send message
  - You should take into consideration that the library shall have its own descriptive error handling
  - library shall be logging using the daemon logger will be described later on
- Note
  - This library will be used by all the applications that will be communicating with each other in the system.

---

**Logger Daemon Application**
- Objective
  - This application will be used by all other applications to log in the log file
  - This application will send the logs also through ethernet to the external logger collector will be described later on
- Content
  - Log file
    - Boost logger will log all the monitored applications in one file till a maximum size of 1k lines
    - If the file size exceeds 1k lines then the logger shall create a new file with the time-stamp of the creation time as a name and start logging in to this file
  - Logger shall run as a daemon and other applications use the library that was created previously using a message queue to log
  - When the daemon receives the log it will :
    - Write this log to the file, Each log received shall contain also the application name that sent this log at the beginning
    - Send this log through ethernet to the log receiver through TCP/IP outside the system
  - For the logger to know the application which will use the daemon for logging
    - The logger will use a configuration file in the /etc defined by the developer in a text format
    - The daemon will use this configuration file to create the message queues using the library that the daemon will receive the dlt using it

---

**Mathematical Operation Applications**
- Objective
  - This application does mathematical operations by command line arguments
  - The application will be running by the user from the terminal giving the needed arguments
- Content
  - The application shall contain a help manual to be printed if the user misuses the application or requests the manual using --help
  - The application shall log in using the message_que library and the log daemon
  - For the application to use the log daemon then shall be added to the configuration file of the log daemon

---

**Logger Receiver Application**
- Objective
  - This application shall be running on your own machine receiving from the hardware using the ethernet logs and printing them on the console
- Content
  - The application shall be native
  - The application shall communicate with the log daemon on the board using TCP/IP
  - The application shall receive the logs and print them on the console
