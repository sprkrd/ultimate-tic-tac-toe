# Ultimate Tic Tac Toe server

![GPLv3 License](gplv3-logo.png "Licensed under GPLv3")

This repo contains a C server for hosting regular Tic Tac Toe and
Ultimate Tic Tac Toe games between bots. It follows the protocol and
specifications of
the competitive game "Ultimate Tic Tac Toe" from
[CodinGame](https://www.codingame.com/multiplayer/bot-programming/tic-tac-toe).

This server has been developed to test locally the performance of AI agents,
without the need of the CodinGame platform. Examples of a random agent programmed
both in Python and in C++ are provided.

For those looking for different alternatives,
[tic-tac-tic-tac-toe-toe](https://github.com/kjav/tic-tac-tic-tac-toe-toe) is
another project of interest.


## Instructions

In order to build the servers and the example C++ random agents, just run `make`.

To execute the server, you must specify the competing players as command line
arguments. Example:
```
./server-9x9.x ./random.x ./random_agent.py
```
This will run a game between `random` (C++) and `random_agent.py`. Any other
agent can be given as long as it follows the CodinGame convention.

Example output (provided in example-out.txt):
```
> ./server-9x9.x ./random.x ./random_agent.py
Forking and executing ./random.x...
Forking and executing ./random_agent.py...
---------------- Turn  0 ----------------
Board:
             |             |             
    |   |    |    |   |    |    |   |    
 ---|---|--- | ---|---|--- | ---|---|--- 
    |   |    |    |   |    |    |   |    
 ---|---|--- | ---|---|--- | ---|---|--- 
    |   |    |    |   |    |    |   |    
             |             |             
-------------|-------------|-------------
             |             |             
    |   |    |    |   |    |    |   |    
 ---|---|--- | ---|---|--- | ---|---|--- 
    |   |    |    |   |    |    |   |    
 ---|---|--- | ---|---|--- | ---|---|--- 
    |   |    |    |   |    |    |   |    
             |             |             
-------------|-------------|-------------
             |             |             
    |   |    |    |   |    |    |   |    
 ---|---|--- | ---|---|--- | ---|---|--- 
    |   |    |    |   |    |    |   |    
 ---|---|--- | ---|---|--- | ---|---|--- 
    |   |    |    |   |    |    |   |    
             |             |             
3x3 blocks' status:
   |   |  
---|---|---
   |   |  
---|---|---
   |   |  
Last filled: -1 -1
Active 3x3 block: -1 -1
Current player: 0
---------------- Turn  1 ----------------
Board:
             |             |             
    |   |    |    |   |    |    |   |    
 ---|---|--- | ---|---|--- | ---|---|--- 
    |   |    |    |   |    |    |   |    
 ---|---|--- | ---|---|--- | ---|---|--- 
    |   |    |    |   |    |    |   |    
             |             |             
-------------|-------------|-------------
             |             |             
    |   |    |    |   |    |    |   |    
 ---|---|--- | ---|---|--- | ---|---|--- 
    |   |    |    |   |    |    |   |    
 ---|---|--- | ---|---|--- | ---|---|--- 
    |   |    |    |   |    |    |   |    
             |             |             
-------------|-------------|-------------
             |             |             
    |   |    |    |   |    |    |   |    
 ---|---|--- | ---|---|--- | ---|---|--- 
  x |   |    |    |   |    |    |   |    
 ---|---|--- | ---|---|--- | ---|---|--- 
    |   |    |    |   |    |    |   |    
             |             |             
3x3 blocks' status:
   |   |  
---|---|---
   |   |  
---|---|---
   |   |  
Last filled: 7 0
Active 3x3 block: 1 0
Current player: 1
...
---------------- Turn 69 ----------------
Board:
             |             |             
  o | x | o  |  x | x | x  |  o | o | o  
 ---|---|--- | ---|---|--- | ---|---|--- 
  o | x | o  |    |   | o  |  x | o | o  
 ---|---|--- | ---|---|--- | ---|---|--- 
  x | o | x  |  x | x |    |  o |   | x  
             |             |             
-------------|-------------|-------------
             |             |             
  x | x | o  |  x | o | x  |  x |   | x  
 ---|---|--- | ---|---|--- | ---|---|--- 
  x | o |    |  o | x | o  |  x | x |    
 ---|---|--- | ---|---|--- | ---|---|--- 
  o | o |    |  o | o | x  |    | x | x  
             |             |             
-------------|-------------|-------------
             |             |             
  x | o | x  |    | o |    |  o | o | x  
 ---|---|--- | ---|---|--- | ---|---|--- 
  x | o | o  |  o | x | o  |  o |   | o  
 ---|---|--- | ---|---|--- | ---|---|--- 
  o | o | x  |  x | x | x  |  x | x | o  
             |             |             
3x3 blocks' status:
 F | x | o
---|---|---
 o | x | x
---|---|---
 o | x |  
Last filled: 5 5
Active 3x3 block: -1 -1
Current player: 0
Player 0 (x) WINS!
```