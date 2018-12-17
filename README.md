# Fox_and_Rabbit
C programming | ACM | Petri-Net 

Game specification 

Detailed specification of the game.
The game is played on the alphanumerical terminal and 4 directional buttons are used to control the movements. Two objects are displayed: the moving target (rabbit) and the chaser (fox). Both are represented as a single character and moved at the speed of 1 position every 0.5 seconds. The rabbit makes random turns and never leaves the screen. The turns of the fox are controlled by the player. The game ends when the fox is placed at the same coordinates as the rabbit. 
Implement the keyboard reading function as a concurrent thread in order to make it independent from the animation. The output of the game is produced on the standard output stream. Use escape characters to position symbols on the screen. It uses a separate thread to read the keyboard.


ACM is designed by using the appropriate number of slots and the slot size. 
HOWTO?
The following are a few hints of advisory nature. You don’t need to follow them. 

• How to compile a programme? 
    – type “gcc -o myprogramme -lpthread mypro- gramme.c” 

• How to run a programme? 
    – type “./myprogramme” 

• How to display in a different terminal? 
    – Open two terminal windows 
    – Have a named fifo file created by “mkfifo myfifo” 
    – In one window type “cat myfifo” 
    – In the other window type “./myprogramme > myfifo” 

• How to delay the output? 
    – in the above example use “./myprogramme | ./delay > myfifo” 
• How to display both the delayed and the original screen? 
    – in the above example use “./myprogramme | tee /dev/stderr | ./delay > myfifo” 

• Where to include the ACM? 
    – “./myprogramme | tee /dev/stderr | ./acm | ./delay > myfifo” 
    – The ACM programme in this example includes a delay instruction matched to “./delay”, which prevents the pipeline “|” from accumulating more than one data item.
