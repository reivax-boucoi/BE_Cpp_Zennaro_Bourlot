 #!/usr/bin/bash
echo "g++ -Wall -Wextra -Werror -std=c++11 -lpthread board.cpp core_simulation.cpp mydevices.cpp LCDObject.cpp SmartMenuLCD.cpp Encoder.cpp sketch_ino.cpp -o arduino"
g++ -Wall -Wextra -Werror -std=c++11 -pthread board.cpp core_simulation.cpp mydevices.cpp LCDObject.cpp SmartMenuLCD.cpp Encoder.cpp sketch_ino.cpp -o arduino
