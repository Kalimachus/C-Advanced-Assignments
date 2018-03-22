This assignment will give you practice processing a binary file, using standard output manipulators, and performing bitwise operations.

Program Steps
This file contains an unknown number of int values stored in binary.  Download the file.  Open it, determine the file size and number of int values that it contains.
Allocate memory dynamically to hold the int data from the binary file.
Read the binary file into the dynamically allocated memory.
Display each int value in decimal, with a width of 12, six to a line.
Display each int value in hexadecimal, with a width of 12, six to a line.
Extract the 3rd byte of each int and display it in hexadecimal, with a width of 6, twelve to a line.
Reverse the nibbles of  the resulting byte and display it in hexadecimal, with a width of 6, twelve to a line.
Interpret each result from step 7 as a BCD (binary coded decimal) value and add 32 to each.  Cast each result to a char and display the secret message.
Clean up your mess.

Your output should look like this:

The file size is ??? bytes
The file contains ?? ints

   768561990   688166836  2027456360 -1476454593   737224956  -646293866
   153897125  1467242596  -995137771   681858793  1473988702   553334584
 -1471244378   345212709  1445214276  -547811187  1132134590 -1877576311
 ...
  -480313154 -1290508678   660100647  1796241112 -1324329062 -1375387384

  0x2dcf5346  0x290497b4  0x78d88768  0xa7ff173f  0x2bf128fc  0xd97a5696
   0x92c48a5  0x57745864  0xc4af6715  0x28a456e9  0x57db485e  0x20fb3738
  0xa84e97a6  0x14938725  0x56243844  0xdf59108d  0x437b00be  0x90167589
 ...
  0xe35f00be  0xb314667a  0x27585627  0x6b1076d8  0xb110579a  0xae054108

  0x53  0x97  0x87  0x17  0x28  0x56  0x48  0x58  0x67  0x56  0x48  0x37
  0x97  0x87  0x38  0x10     0  0x75  0x97  0x58     0  0x27  0x56  0x68
  0x96     0  0x76  0x97  0x77   0x8  0x67  0x96  0x48  0x96  0x86     0
  ...
  0x97  0x87     0  0x48  0x27  0x96     0  0x66  0x56  0x76  0x57  0x41

  0x35  0x79  0x78  0x71  0x82  0x65  0x84  0x85  0x76  0x65  0x84  0x73
  0x79  0x78  0x83   0x1     0  0x57  0x79  0x85     0  0x72  0x65  0x86
  0x69     0  0x67  0x79  0x77  0x80  0x76  0x69  0x84  0x69  0x68     0
  ...
  0x79  0x78     0  0x84  0x72  0x69     0  0x66  0x65  0x67  0x75  0x14

Con... ??? ... .