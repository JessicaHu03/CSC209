# CSC209
All of my work from the course CSC209 Software Tools and Systems Programming

# A1 DNA Sequence
In this assignment you will use some of your newfound C skills including functions, loops and arrays on problems involving DNA sequences. DNA sequences can be represented as simple character arrays that contain only the characters A, C, G or T, so programs that work with DNA are often written in C. You won't need to know any biology to complete this assignment.

In this assignment you will be presented with some problems in your (pretend) job as a software developer at the fictional AGTCorp, the world's leading company for synthesizing DNA molecules. AGTCorp is developing their latest DNA synthesis machine, called SEQbot, and you've joined the project to help the team prepare for the launch.

Note that for this assignment you are working with arrays of characters, not strings. That means that these arrays will not necessarily have a null-termination character at the end, and you cannot use string operations on them. This is also why all of the operations require the length of the array to be specified. The only string operations appear in main which you will not be modifying.

It is important that your programs produce only the output specified in the handout, and exactly in the format specified.  You must not have any additional output.

# A2 Wordle!

We just couldn't resist creating an assignment around wordle (Links to an external site.), the word game that has caught the attention of the world.  Please read the rules for wordle in the app, and try playing a couple of times if you haven't already.

This assignment is not about writing a program to solve the game.  Instead we are going to produce a tree that contains all of the possible paths to a solution given 1) the solution word, and 2) the grid of coloured tiles that will impose constraints on the potential paths, and then print all of the possible paths to a solution.

The goal of this assignment is to give you experience working with dynamic data structures and strings.

Wordle rules for our version of the game
Your program will actually apply these rules in reverse order, but it is helpful to understand the rules of the game when someone is trying to guess the solution.

Each guess must be a valid WORDLEN-letter word.  After each guess, the colour of the tiles will change to show which, if any, letters are in the solution word.   (WORDLEN is defined as 5 in common.h, but you should not use hard-coded numbers in your code.)

A green tile means that the letter is in the solution in the same position. 
A yellow tile means that the letter is in the solution in a different position. 
A grey tile means that the letter is not in the solution.
For our purposes, we are going to create an extra-hard mode: 

If a letter was marked as grey, it cannot be used again.
If a letter was marked as yellow, that letter must be used in the next guess in a different position that the previous guess.
If a letter was marked as green, that letter must be used in the same position in the next guess.
