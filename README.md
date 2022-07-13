# Rubik-s-cube-solver

#### A programme simulates the assembly of a 3x3 Rubik's cube, implemented with a graphical application interface using the *OpenGL Utility Toolkit*.

The programme has the following functional requirements:
* save and read the rubik's cube state from a file
* check that the current state is correct
* display the current state on the console
* rotating the rubik's cube faces with the input commands
* generating a random Rubik's Cube state, correct from the point of view of the state invariant
* finding the solution for the current state as a sequence of rotation of the faces
* assemble a rubik's cube in a pattern (e.g. a flower)

```
                                        ______
         a b c                         |      |
         d e f                         |  up  |                        |  front - 0 - red
         g h k                   ______|______|_____________           |  back - 1 - orange
  a b c  a b c  a b c  a b c    |      |      |      |      |          |  left - 2 - blue
  d e f  d e f  d e f  d e f    | left |front |right | back |          |  right - 3 - green
  g h k  g h k  g h k  g h k    |______|______|______|______|          |  up - 4 - yellow
         a b c                         |      |                        |  down - 5 - white
         d e f                         | down |
         g h k                         |______|
```
