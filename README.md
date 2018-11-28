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

In order to print the boards, append `-v` to the previous command.

Example output (provided in example-out.txt):
```
> ./server-9x9.x ./random.x ./random_agent.py -v
Forking and executing ./random.x...
Forking and executing ./random_agent.py...
---------------- Turn  0 ----------------
   0   1   2     3   4   5     6   7   8
              |             |             
0    |   |    |    |   |    |    |   |    
  ---|---|--- | ---|---|--- | ---|---|--- 
1    |   |    |    |   |    |    |   |    
  ---|---|--- | ---|---|--- | ---|---|--- 
2    |   |    |    |   |    |    |   |    
              |             |             
 -------------|-------------|-------------
              |             |             
3    |   |    |    |   |    |    |   |    
  ---|---|--- | ---|---|--- | ---|---|--- 
4    |   |    |    |   |    |    |   |    
  ---|---|--- | ---|---|--- | ---|---|--- 
5    |   |    |    |   |    |    |   |    
              |             |             
 -------------|-------------|-------------
              |             |             
6    |   |    |    |   |    |    |   |    
  ---|---|--- | ---|---|--- | ---|---|--- 
7    |   |    |    |   |    |    |   |    
  ---|---|--- | ---|---|--- | ---|---|--- 
8    |   |    |    |   |    |    |   |    
              |             |             

Last filled: -1 -1
Active 3x3 block: -1 -1
Current player: 0

---------------- Turn  1 ----------------
   0   1   2     3   4   5     6   7   8
              |             |             
0    |   |    |    |   |    |    |   |    
  ---|---|--- | ---|---|--- | ---|---|--- 
1    |   |    |    |   |    |    |   |    
  ---|---|--- | ---|---|--- | ---|---|--- 
2    |   |    |    |   |    |    |   |    
              |             |             
 -------------|-------------|-------------
              |             |             
3    |   |    |    |   | x  |    |   |    
  ---|---|--- | ---|---|--- | ---|---|--- 
4    |   |    |    |   |    |    |   |    
  ---|---|--- | ---|---|--- | ---|---|--- 
5    |   |    |    |   |    |    |   |    
              |             |             
 -------------|-------------|-------------
              |             |             
6    |   |    |    |   |    |    |   |    
  ---|---|--- | ---|---|--- | ---|---|--- 
7    |   |    |    |   |    |    |   |    
  ---|---|--- | ---|---|--- | ---|---|--- 
8    |   |    |    |   |    |    |   |    
              |             |             

Last filled: 3 5
Active 3x3 block: 0 2
Current player: 1

---------------- Turn  2 ----------------

...

---------------- Turn 62 ----------------
   0   1   2     3   4   5     6   7   8
              |             |             
0  o | x | x  |  o | o | x  |    | x |    
  ---|---|--- | ---|---|--- | ---|---|--- 
1  x | o | o  |  x | x | x  |  o | x | x  
  ---|---|--- | ---|---|--- | ---|---|--- 
2  o | o | x  |  o |   | o  |  o | x | o  
      tie     |  won by: x  |  won by: x  
 -------------|-------------|-------------
              |             |             
3  x |   | o  |  x | x | x  |  o | o | o  
  ---|---|--- | ---|---|--- | ---|---|--- 
4  o | o | o  |    | o | x  |    |   |    
  ---|---|--- | ---|---|--- | ---|---|--- 
5  x | o | x  |    |   |    |    |   |    
   won by: o  |  won by: x  |  won by: o  
 -------------|-------------|-------------
              |             |             
6    | o |    |  x | o | o  |  x | x | x  
  ---|---|--- | ---|---|--- | ---|---|--- 
7  x | o | x  |  x | o | x  |  o | o | x  
  ---|---|--- | ---|---|--- | ---|---|--- 
8  x | o |    |  o | x | o  |    | x |    
   won by: o  |  won by: o  |  won by: x  

Last filled: 0 0
Active 3x3 block: -1 -1
Current player: 1

Game ends in a TIE!
```
