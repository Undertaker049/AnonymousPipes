# Description
Demo project of three synchronized console processes that exchange data through anonymous channels, created in Visual Studio

# How it works
The Server process transmits the user-defined array size to the Client process via an anonymous channel. 
After receiving the dimension, the Client process generates an array of random numbers from one to one hundred of the specified size, outputs it to the console and passes it back to the Server process character by character. 

It decrypts the received characters into an array, outputs it to the console and passes it to the Part process in the same way, which, after receiving and decrypting the array, also outputs it to the console and prompts the user to set a range from N to M, after which the program outputs to the console the numbers in the array that fall within the specified range.

To work correctly, the project directories must be located in C:\
